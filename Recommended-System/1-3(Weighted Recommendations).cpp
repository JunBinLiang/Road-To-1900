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
            double rating = std::stod(ratingStr);
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

// Calculate non-weighted average of a specific item
double calculateNonWeightedAverage(const std::string& targetItem, const RatingsMap& userRatings) {
    std::vector<double> ratings;
    for (const auto& [user, ratingsMap] : userRatings) {
        auto it = ratingsMap.find(targetItem);
        if (it != ratingsMap.end()) {
            ratings.push_back(it->second);
        }
    }
    if (ratings.empty()) return 0.0;
    double sum = std::accumulate(ratings.begin(), ratings.end(), 0.0);
    return sum / ratings.size();
}

// Weighted rating prediction using Pearson similarity
double weightedRatingPrediction(const std::string& targetUser,
                                const std::string& targetItem,
                                const RatingsMap& userRatings) {
    double weightedSum = 0.0, sumOfWeights = 0.0;
    const auto& targetRatings = userRatings.at(targetUser);

    // Create target ratings vector (all items except target item)
    std::vector<double> targetVec;
    for (const auto& [item, rating] : targetRatings) {
        if (item != targetItem) {
            targetVec.push_back(rating);
        }
    }

    for (const auto& [user, ratings] : userRatings) {
        if (user == targetUser || ratings.count(targetItem) == 0) continue;

        // Create other user's ratings vector (all items except target item)
        std::vector<double> otherVec;
        for (const auto& [item, rating] : ratings) {
            if (item != targetItem) {
                otherVec.push_back(rating);
            }
        }
        
        double similarity = pearsonCorrelation(targetVec, otherVec);
        weightedSum += similarity * ratings.at(targetItem);
        sumOfWeights += std::abs(similarity);
    }

    return (sumOfWeights == 0.0) ? 0.0 : weightedSum / sumOfWeights;
}

int main() {
    // Read the user-item matrix from file
    std::string filePath = "../data/user_items_matrix.txt";
    RatingsMap usersItemsMatrix = readUsersItemsMatrix(filePath);

    // Calculate and print non-weighted average for ItemC
    double nonWeightedAverage = calculateNonWeightedAverage("ItemC", usersItemsMatrix);
    std::cout << "Non-Weighted Average Rating for ItemC: " << nonWeightedAverage << "\n";

    // Print the list of ratings for ItemC
    std::cout << "Ratings for ItemC by users: [";
    bool first = true;
    for (const auto& [user, ratings] : usersItemsMatrix) {
        auto it = ratings.find("ItemC");
        if (it != ratings.end()) {
            if (!first) std::cout << ", ";
            std::cout << it->second;
            first = false;
        }
    }
    std::cout << "]\n";

    // Calculate and print weighted average prediction for User3 on ItemC
    double weightedPrediction = weightedRatingPrediction("User3", "ItemC", usersItemsMatrix);
    std::cout << "Predicted Rating for User3 on ItemC (Weighted Average): " 
              << weightedPrediction << "\n";

    return 0;
}
