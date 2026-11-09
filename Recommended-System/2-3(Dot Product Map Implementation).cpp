#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

// Item profiles: described by movie genres and their scores
std::map<std::string, std::map<std::string, double>> item_profiles = {
    {"Movie1", {{"Action", 0.9}, {"Romance", 0.1}, {"Sci-Fi", 0.5}}},
    {"Movie2", {{"Action", 0.2}, {"Romance", 0.8}, {"Sci-Fi", 0.1}}},
    {"Movie3", {{"Action", 0.4}, {"Romance", 0.9}, {"Sci-Fi", 0.2}}}
};

// Sample user profile: representing preferences for genres
// User has watched and liked past movies mostly in 'Action' and 'Sci-Fi'
std::map<std::string, double> user_profile = {
    {"Action", 0.1},
    {"Romance", 0.0},
    {"Sci-Fi", 0.8}
};

// TODO: Change the user_profile by adjusting the preferences for different genres (Action, Romance, Sci-Fi)
// Recompute the recommendations to see the effect of changes.

// Compute similarity using a dot product
double compute_similarity(const std::map<std::string, double>& user, const std::map<std::string, double>& item) {
    double score = 0.0;
    for (const auto& [feature, user_value] : user) {
        auto it = item.find(feature);
        if (it != item.end()) {
            score += user_value * it->second;
        }
    }
    return score;
}

// Recommend items based on similarity to user profile
std::vector<std::pair<std::string, double>> recommend_items(
    const std::map<std::string, double>& user_profile,
    const std::map<std::string, std::map<std::string, double>>& item_profiles
) {
    std::vector<std::pair<std::string, double>> recommendations;
    for (const auto& [item, profile] : item_profiles) {
        double sim = compute_similarity(user_profile, profile);
        recommendations.push_back({item, sim});
    }
    std::sort(recommendations.begin(), recommendations.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    return recommendations;
}

int main() {
    auto recommendations = recommend_items(user_profile, item_profiles);
    std::cout << "Recommendations:" << std::endl;
    for (const auto& [movie, score] : recommendations) {
        std::cout << movie << ": " << score << std::endl;
    }
    return 0;
}
