#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <Eigen/Dense>

using Eigen::MatrixXd;

// Function to load a matrix from a text file
MatrixXd load_matrix(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::vector<double>> data;
    int cols = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        double value;
        std::vector<double> row;
        while (ss >> value) {
            row.push_back(value);
        }
        if (!row.empty()) {
            if (cols == 0) {
                cols = row.size();
            }
            data.push_back(row);
        }
    }

    MatrixXd matrix(data.size(), cols);
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            matrix(i, j) = data[i][j];
        }
    }
    return matrix;
}

int main() {
    // Initialize user-item interaction matrix with explicit feedback
    MatrixXd R = load_matrix("../data/explicit-ratings.txt");

    // Randomly selectively mark some entries as missing (-1) to use for testing
    MatrixXd original_R = R; // Create a copy to track original values for RMSE calculation

    std::vector<std::pair<int, int>> existing_indices;
    for (int r = 0; r < R.rows(); ++r) {
        for (int c = 0; c < R.cols(); ++c) {
            if (R(r, c) != -1) {
                existing_indices.push_back({r, c});
            }
        }
    }

    double missing_ratio = 0.2; // Fraction of entries to exclude
    size_t num_missing = static_cast<size_t>(missing_ratio * existing_indices.size());

    // Shuffle and select indices to mark as missing
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(existing_indices.begin(), existing_indices.end(), g);

    std::vector<std::pair<int, int>> missing_indices;
    for (size_t i = 0; i < num_missing; ++i) {
        missing_indices.push_back(existing_indices[i]);
    }

    for (const auto& p : missing_indices) {
        R(p.first, p.second) = -1; // Mark selected original values as missing
    }

    // In the context of recommendation systems, marking certain entries as missing is fundamental when it comes to testing and validating models. We can compare an algorithm's predictions to the entries that we manually marked as missing.
    
    std::cout << "Missing Indices: [";
    for (size_t i = 0; i < missing_indices.size(); ++i) {
        std::cout << "(" << missing_indices[i].first << ", " << missing_indices[i].second << ")";
        if (i != missing_indices.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    return 0;
}
