#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <Eigen/Dense>

using Eigen::MatrixXd;

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
    MatrixXd R = load_matrix("explicit-ratings.txt");
    // TODO: Read each line of the file as a separate row for the resulting 2D matrix
    // TODO: Print the loaded rating matrix
    for (int r = 0; r < R.rows(); ++r) {
        for (int c = 0; c < R.cols(); ++c) {
            // access element via matrix(r, c)
            std :: cout << R(r, c) << " ";
        }
        std :: cout << std :: endl;
    }
    return 0;
}
