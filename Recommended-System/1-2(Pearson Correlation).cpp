#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

/*
Pearson Correlation measures the strength and direction of the linear relationship between two users' rating patterns.
*/

// Function to calculate Pearson correlation between two users
double pearsonCorrelation(const std::vector<double>& x, const std::vector<double>& y) {
    int n = x.size();
    double meanX = std::accumulate(x.begin(), x.end(), 0.0) / n;
    double meanY = std::accumulate(y.begin(), y.end(), 0.0) / n;

    double numerator = 0.0, denomX = 0.0, denomY = 0.0;
    for (int i = 0; i < n; ++i) {
        double diffX = x[i] - meanX;
        double diffY = y[i] - meanY;
        numerator += diffX * diffY;
        denomX += diffX * diffX;
        denomY += diffY * diffY;
    }

    double denominator = std::sqrt(denomX * denomY);
    return (denominator == 0.0) ? 0.0 : numerator / denominator;
}

int main() {
    // Example user ratings
    std::vector<double> user1_ratings = {5, 3, 4, 2, 1, 5, 3, 4, 2, 1, 5, 3, 4, 2, 1};
    std::vector<double> user2_ratings = {5, 3, 3, 2, 1, 3, 3, 4, 2, 1, 5, 2, 2, 2, 1};

    double pearson_similarity = pearsonCorrelation(user1_ratings, user2_ratings);
    std::cout << "Pearson Correlation: " << pearson_similarity << "\n";
    return 0;
}
