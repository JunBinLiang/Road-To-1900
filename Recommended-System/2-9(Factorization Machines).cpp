#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
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

                // TODO: Calculate linear terms using global bias and feature coefficients
                double linear_terms = w0_ + x_i.dot(W_);

                // Calculate interaction term
                double interaction_term = 0.0;
                for (int f = 0; f < n_factors_; ++f) {
                    double dot_xv = x_i.dot(V_.col(f));
                    double dot_x2_v2 = x_i.array().square().matrix().dot(V_.col(f).array().square().matrix());
                    interaction_term += 0.5 * (dot_xv * dot_xv - dot_x2_v2);
                }

                // TODO: Combine linear terms and interaction term for prediction
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

int main() {
    // Extract dataset
    auto [X, y] = extract_dataset();

    // Split dataset into train and test
    // NOTE: A real implementation would shuffle the data first for a random split.
    long train_size = X.rows() * 0.8;
    MatrixXd X_train = X.topRows(train_size);
    VectorXd y_train = y.head(train_size);
    MatrixXd X_test = X.bottomRows(X.rows() - train_size);
    VectorXd y_test = y.tail(y.size() - train_size);
    
    // Define and train factorization machine model
    SimpleFactorizationMachine fm_model(3, X_train.cols(), 0.01, 50);
    fm_model.fit(X_train, y_train);

    // Test the model
    VectorXd y_pred = fm_model.predict(X_test);
    
    // Evaluate model using Mean Squared Error
    double mse = (y_test - y_pred).array().square().mean();
    std::cout << "Mean Squared Error: " << std::fixed << std::setprecision(4) << mse << std::endl;

    return 0;
}
