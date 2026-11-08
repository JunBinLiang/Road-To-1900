#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

// Type alias for a user's ratings.
using ItemRatings = std::map<std::string, double>;
// Type alias for the main data structure.
using RatingsMap = std::unordered_map<std::string, ItemRatings>;

// Function to compute global averages
std::map<std::string, double> computeGlobalAverages(const RatingsMap& userRatings) {
    std::map<std::string, double> totalRatings;
    std::map<std::string, int> ratingCounts;

    for (const auto& [user, ratings] : userRatings) {
        for (const auto& [item, rating] : ratings) {
            totalRatings[item] += rating;
            ratingCounts[item]++;
        }
    }

    std::map<std::string, double> averages;
    for (const auto& [item, total] : totalRatings) {
        averages[item] = total / ratingCounts.at(item);
    }
    return averages;
}

int main() {
    RatingsMap users{
        {"User1", {{"ItemA", 5.0}, {"ItemB", 3.0}, {"ItemC", 4.0}}},
        {"User2", {{"ItemA", 3.0}, {"ItemB", 1.0}, {"ItemC", 2.0}}},
        {"User3", {{"ItemA", 4.0}, {"ItemB", 3.0}}},
        {"User4", {{"ItemA", 4.0}, {"ItemC", 3.0}}}
        // TODO: Add User4 with ratings for ItemA and ItemC, but not for ItemB
    };
    
    auto global_averages = computeGlobalAverages(users);
    // TODO: Predict User4's rating for ItemB using the global average for ItemB and print it
    cout << global_averages["ItemB"] << endl;
    return 0;
}
