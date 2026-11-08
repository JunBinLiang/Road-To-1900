#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <iomanip>

#include <DataFrame/DataFrame.h>

using namespace hmdf;

// Simple dot product similarity between user and item features
double compute_similarity(const std::vector<double>& user, const std::vector<double>& item) {
    double sim = 0.0;
    for (size_t i = 0; i < user.size(); ++i) {
        sim += user[i] * item[i];
    }
    return sim;
}

int main() {
    // Create tracks dataframe manually
    StdDataFrame<unsigned long> tracks_df;
    std::vector<unsigned long> track_indices = {0, 1, 2, 3};
    tracks_df.load_index(std::move(track_indices));

    std::vector<std::string> track_ids = {"001", "002", "003", "004"};
    std::vector<std::string> titles = {"Song A", "Song B", "Song C", "Song C"};
    std::vector<int> likes = {150, 200, 100, 200};
    std::vector<int> clicks = {300, 400, 250, 200};
    std::vector<int> full_listens = {120, 180, 95, 150};
    std::vector<std::string> author_ids = {"A1", "A2", "A3", "A1"};

    tracks_df.load_column("track_id", std::move(track_ids));
    tracks_df.load_column("title", std::move(titles));
    tracks_df.load_column("likes", std::move(likes));
    tracks_df.load_column("clicks", std::move(clicks));
    tracks_df.load_column("full_listens", std::move(full_listens));
    tracks_df.load_column("author_id", std::move(author_ids));

    // Create authors dataframe manually
    StdDataFrame<unsigned long> authors_df;
    std::vector<unsigned long> author_indices = {0, 1, 2};
    authors_df.load_index(std::move(author_indices));

    std::vector<std::string> author_ids_df = {"A1", "A2", "A3"};
    std::vector<std::string> names = {"Artist X", "Artist Y", "Artist Z"};
    std::vector<int> author_listeners = {5000, 8000, 3000};
    std::vector<std::string> genres = {"Rock", "Pop", "Jazz"};

    authors_df.load_column("author_id", std::move(author_ids_df));
    authors_df.load_column("name", std::move(names));
    authors_df.load_column("author_listeners", std::move(author_listeners));
    authors_df.load_column("genre", std::move(genres));

    // User profile: prefers tracks with high likes, clicks, and full_listens
    // (weights for each feature, normalized)
    std::vector<double> user_profile = {0.5, 0.2, 0.3}; // likes, clicks, full_listens

    // Prepare item profiles (normalize features for fair comparison)
    const auto& likes_col = tracks_df.get_column<int>("likes");
    const auto& clicks_col = tracks_df.get_column<int>("clicks");
    const auto& full_listens_col = tracks_df.get_column<int>("full_listens");
    const auto& titles_col = tracks_df.get_column<std::string>("title");

    // Find max for normalization
    int max_likes = *std::max_element(likes_col.begin(), likes_col.end());
    int max_clicks = *std::max_element(clicks_col.begin(), clicks_col.end());
    int max_full_listens = *std::max_element(full_listens_col.begin(), full_listens_col.end());

    // Compute similarity and store results
    std::vector<std::tuple<std::string, double>> recommendations;
    for (size_t i = 0; i < titles_col.size(); ++i) {
        std::vector<double> item_profile = {
            static_cast<double>(likes_col[i]) / max_likes,
            static_cast<double>(clicks_col[i]) / max_clicks,
            static_cast<double>(full_listens_col[i]) / max_full_listens
        };
        double sim = compute_similarity(user_profile, item_profile);
        recommendations.emplace_back(titles_col[i], sim);
    }

    // Sort by similarity descending
    std::sort(recommendations.begin(), recommendations.end(),
              [](const auto& a, const auto& b) { return std::get<1>(a) > std::get<1>(b); });

    // Output recommendations
    std::cout << "Recommendations (track, score):" << std::endl;
    for (const auto& rec : recommendations) {
        std::cout << std::setw(8) << std::left << std::get<0>(rec)
                  << " | " << std::fixed << std::setprecision(3) << std::get<1>(rec) << std::endl;
    }

    // TODO: Add a new track to the tracks_df DataFrame with your chosen values for likes, clicks, full_listens, and author_id.
    // Then, rerun the recommendation logic to see how the new track ranks.

    return 0;
}
