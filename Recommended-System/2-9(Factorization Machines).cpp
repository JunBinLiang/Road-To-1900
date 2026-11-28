
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <limits>
#include "data_extractor.hpp" // Helper to prepare data
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class SimpleFactorizationMachine {
public:
    SimpleFactorizationMachine(int n_factors, int n_features, double learning_rate = 0.01, int epochs = 100, double reg = 0.01)
        : n_factors_(n_factors), lr_(learning_rate), epochs_(epochs), reg_(reg), w0_(0.0) {
        
        W_ = VectorXd::Zero(n_features);
        
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(0.0, 0.1);
        V_ = MatrixXd::NullaryExpr(n_features, n_factors, [&](){ return distribution(generator); });
    }

    void fit(const MatrixXd& X, const VectorXd& y) {
        for (int epoch = 0; epoch < epochs_; ++epoch) {
            for (int i = 0; i < X.rows(); ++i) {
                VectorXd x_i = X.row(i);
                double linear_terms = w0_ + x_i.dot(W_);
                
                double interaction_term = 0.0;
                for (int f = 0; f < n_factors_; ++f) {
                    double dot_xv = x_i.dot(V_.col(f));
                    double dot_x2_v2 = x_i.array().square().matrix().dot(V_.col(f).array().square().matrix());
                    interaction_term += 0.5 * (dot_xv * dot_xv - dot_x2_v2);
                }
                
                double prediction = linear_terms + interaction_term;
                double err = prediction - y(i);
                
                w0_ -= lr_ * err;
                W_ -= lr_ * (err * x_i + reg_ * W_);
                
                for (int f = 0; f < n_factors_; ++f) {
                    VectorXd v_f = V_.col(f);
                    V_.col(f) -= lr_ * (err * (x_i * x_i.dot(v_f) - x_i.array().square().matrix().cwiseProduct(v_f)) + reg_ * v_f);
                }
            }
        }
    }

    VectorXd predict(const MatrixXd& X) {
        VectorXd y_pred(X.rows());
        for (int i = 0; i < X.rows(); ++i) {
            VectorXd x_i = X.row(i);
            double linear_terms = w0_ + x_i.dot(W_);

            double interaction_term = 0.0;
            for (int f = 0; f < n_factors_; ++f) {
                double dot_xv = x_i.dot(V_.col(f));
                double dot_x2_v2 = x_i.array().square().matrix().dot(V_.col(f).array().square().matrix());
                interaction_term += 0.5 * (dot_xv * dot_xv - dot_x2_v2);
            }
            y_pred(i) = linear_terms + interaction_term;
        }
        return y_pred;
    }

private:
    int n_factors_;
    double lr_, reg_;
    int epochs_;
    double w0_;
    VectorXd W_;
    MatrixXd V_;
};

// Helper function to compute Mean Absolute Error
double mean_absolute_error(const VectorXd& y_true, const VectorXd& y_pred) {
    return (y_true - y_pred).array().abs().mean();
}

int main() {
    // Extract dataset
    auto [X, y] = extract_dataset();

    // Split dataset into train, validation, and test sets (60% train, 20% val, 20% test)
    long n_samples = X.rows();
    long train_size = n_samples * 0.6;
    long val_size = n_samples * 0.2;
    long test_size = n_samples - train_size - val_size;

    // NOTE: For simplicity, we do not shuffle the data here.
    MatrixXd X_train = X.topRows(train_size);
    VectorXd y_train = y.head(train_size);

    MatrixXd X_val = X.middleRows(train_size, val_size);
    VectorXd y_val = y.segment(train_size, val_size);

    MatrixXd X_test = X.bottomRows(test_size);
    VectorXd y_test = y.tail(test_size);

    // Hyperparameter tuning
    std::vector<double> learning_rates = {0.001, 0.01};
    std::vector<int> n_factors_list = {2, 3};
    std::vector<double> reg_list = {0.01, 0.1};

    double best_mae = std::numeric_limits<double>::max();
    double best_lr = 0.0;
    int best_n_factors = 0;
    double best_reg = 0.0;

    for (double lr : learning_rates) {
        for (int n_factors : n_factors_list) {
            for (double reg : reg_list) {
                // TODO: Initialize model with n_factors, lr, reg, and train for 1000 epochs
                SimpleFactorizationMachine fm_model(n_factors, X_train.cols(), lr, 1000, reg);
                fm_model.fit(X_train, y_train);

                // VectorXd y_val_pred = fm_model.predict(X_val);
                VectorXd y_val_pred = fm_model.predict(X_val);

                // double mae = mean_absolute_error(y_val, y_val_pred);
                double mae = mean_absolute_error(y_val, y_val_pred);

                // std::cout << "Parameters: lr=" << lr << ", n_factors=" << n_factors << ", reg=" << reg
                //           << " ==> MAE=" << std::fixed << std::setprecision(4) << mae << std::endl;
                std::cout << "Parameters: lr=" << lr << ", n_factors=" << n_factors << ", reg=" << reg
                          << " ==> MAE=" << std::fixed << std::setprecision(4) << mae << std::endl;

                if (mae < best_mae) {
                    // TODO: Update best_mae, best_lr, best_n_factors, best_reg
                    best_mae = mae;
                    best_lr = lr;
                    best_n_factors = n_factors;
                    best_reg = reg;
                }
            }
        }
    }

    std::cout << "Best Parameters: lr=" << best_lr << ", n_factors=" << best_n_factors
              << ", reg=" << best_reg << " with MAE=" << std::fixed << std::setprecision(4) << best_mae << std::endl;

    // Train final model with best parameters
    // SimpleFactorizationMachine final_model(best_n_factors, X_train.cols(), best_lr, 1000, best_reg);
    // final_model.fit(X_train, y_train);
    // VectorXd y_pred = final_model.predict(X_test);

    SimpleFactorizationMachine final_model(best_n_factors, X_train.cols(), best_lr, 1000, best_reg);
    final_model.fit(X_train, y_train);
    VectorXd y_pred = final_model.predict(X_test);

    // Evaluate model using Mean Absolute Error
    // double test_mae = mean_absolute_error(y_test, y_pred);
    // std::cout << "Test Mean Absolute Error: " << std::fixed << std::setprecision(4) << test_mae << std::endl;

    double test_mae = mean_absolute_error(y_test, y_pred);
    std::cout << "Test Mean Absolute Error: " << std::fixed << std::setprecision(4) << test_mae << std::endl;

    return 0;
}
