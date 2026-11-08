#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <cmath>
#include <map>
#include <fstream>
#include <sstream>

// Type aliases
using ItemRatings = std::map<std::string, double>;
using RatingsMap = std::unordered_map<std::string, ItemRatings>;

// Reads the user-item matrix from a file
RatingsMap readUsersItemsMatrix(const std::string& filePath) {
    RatingsMap usersItemsMatrix;
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string user, item, ratingStr;
        if (std::getline(iss, user, ',') &&
            std::getline(iss, item, ',') &&
            std::getline(iss, ratingStr)) {
            int rating = std::stoi(ratingStr);
            usersItemsMatrix[user][item] = rating;
        }
    }
    return usersItemsMatrix;
}

// Function to calculate Pearson correlation
double pearsonCorrelation(const std::vector<double>& ratings1, const std::vector<double>& ratings2) {
    size_t n = ratings1.size();
    if (n == 0 || n != ratings2.size()) return 0.0;

    double mean1 = std::accumulate(ratings1.begin(), ratings1.end(), 0.0) / n;
    double mean2 = std::accumulate(ratings2.begin(), ratings2.end(), 0.0) / n;

    double numerator = 0.0, denom1 = 0.0, denom2 = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double diff1 = ratings1[i] - mean1;
        double diff2 = ratings2[i] - mean2;
        numerator += diff1 * diff2;
        denom1 += diff1 * diff1;
        denom2 += diff2 * diff2;
    }

    double denominator = std::sqrt(denom1) * std::sqrt(denom2);
    if (denominator == 0.0) return 0.0;
    return numerator / denominator;
}

// Prediction function
double adjustedWeightedRatingPrediction(const std::string& targetUser,
                                        const std::string& targetItem,
                                        const RatingsMap& userRatings) {
    auto calculateAverage = [](const ItemRatings& ratings) {
        double sum = 0.0;
        for (const auto& [_, r] : ratings) sum += r;
        return sum / ratings.size();
    };

    const auto& targetMap = userRatings.at(targetUser);
    double targetAvg = calculateAverage(targetMap);
    double weightedSum = 0.0, sumOfWeights = 0.0;

    for (const auto& [user, ratings] : userRatings) {
        if (user == targetUser || ratings.count(targetItem) == 0) continue;

        // Find common items
        std::vector<double> targetVec, otherVec;
        for (const auto& [item, rating] : targetMap) {
            if (ratings.count(item)) {
                targetVec.push_back(rating);
                otherVec.push_back(ratings.at(item));
            }
        }
        
        // TODO: Calculate similarity using pearsonCorrelation
        double similarity = pearsonCorrelation(targetVec, otherVec);
        
        // TODO: Calculate average rating for this user
        double userAvg = calculateAverage(ratings);
        
        // TODO: Calculate ratingDiff as the difference between this user's rating for targetItem and their average
        weightedSum += similarity * (ratings.at(targetItem) - userAvg);
        sumOfWeights += std::abs(similarity);
        // TODO: Update weightedSum using similarity and ratingDiff
        // TODO: Update sumOfWeights using similarity
    }

    // Return the predicted rating
    return (sumOfWeights == 0.0) ? targetAvg : targetAvg + (weightedSum / sumOfWeights);
}

int main() {
    RatingsMap users = readUsersItemsMatrix("../data/user_items_matrix.txt");
    
    double improved_prediction = adjustedWeightedRatingPrediction("User3", "ItemC", users);
    std::cout << "Predicted Rating for User3 on ItemC (Weighted Average): " 
              << improved_prediction << "\n";
    return 0;
}
