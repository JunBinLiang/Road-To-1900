#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <DataFrame/DataFrame.h>

using namespace hmdf;
using namespace std;

// Helper function to compute cosine similarity between two vectors
double cosine_similarity(const std::vector<double>& a, const std::vector<double>& b) {
    double dot = 0.0, norm_a = 0.0, norm_b = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }
    if (norm_a == 0.0 || norm_b == 0.0) return 0.0;
    return dot / (std::sqrt(norm_a) * std::sqrt(norm_b));
}

// Helper function to standardize a vector
void standardize(std::vector<double>& data) {
    double mean = 0.0, stddev = 0.0;
    for (double v : data) mean += v;
    mean /= data.size();
    for (double v : data) stddev += (v - mean) * (v - mean);
    stddev = std::sqrt(stddev / data.size());
    for (double& v : data) v = (v - mean) / (stddev == 0.0 ? 1.0 : stddev);
}

int main() {
    // --- Data setup (tracks and authors) ---
    StdDataFrame<unsigned long> tracks_df;
    std::vector<unsigned long> track_indices = {0, 1, 2};
    tracks_df.load_index(std::move(track_indices));

    std::vector<std::string> track_ids = {"001", "002", "003"};
    std::vector<std::string> titles = {"Song A", "Song B", "Song C"};
    std::vector<int> likes = {150, 200, 100};
    std::vector<int> clicks = {300, 400, 250};
    std::vector<int> full_listens = {120, 180, 95};
    std::vector<std::string> author_ids = {"A1", "A2", "A3"};
    tracks_df.load_column("track_id", std::move(track_ids));
    tracks_df.load_column("title", std::move(titles));
    tracks_df.load_column("likes", likes);
    tracks_df.load_column("clicks", clicks);
    tracks_df.load_column("full_listens", full_listens);
    tracks_df.load_column("author_id", std::move(author_ids));

    StdDataFrame<unsigned long> authors_df;
    std::vector<unsigned long> author_indices = {0, 1, 2};
    authors_df.load_index(std::move(author_indices));

    std::vector<std::string> author_ids_df = {"A1", "A2", "A3"};
    std::vector<std::string> names = {"Artist X", "Artist Y", "Artist Z"};
    std::vector<int> author_listeners = {5000, 8000, 3000};
    std::vector<std::string> genres = {"Rock", "Pop", "Jazz"};
    authors_df.load_column("author_id", std::move(author_ids_df));
    authors_df.load_column("name", std::move(names));
    authors_df.load_column("author_listeners", author_listeners);
    authors_df.load_column("genre", genres);

    // --- User profile (to be updated) ---
    // #TODO: Update the user's genre preferences to favor rock music.
    struct UserProfile {
        int rock_preference = 5;   // 1-5
        int pop_preference = 1;    // 1-5
        int jazz_preference = 1;   // 1-5
        int listens = 100;
        int likes = 60;
    } user;

    // --- Map genres to one-hot vectors ---
    std::vector<std::vector<double>> track_genre_features;
    for (const auto& genre : genres) {
        if (genre == "Rock") track_genre_features.push_back({1, 0, 0});
        else if (genre == "Pop") track_genre_features.push_back({0, 1, 0});
        else if (genre == "Jazz") track_genre_features.push_back({0, 0, 1});
        else track_genre_features.push_back({0, 0, 0});
    }
    std::vector<double> user_genre_pref = {
        static_cast<double>(user.rock_preference),
        static_cast<double>(user.pop_preference),
        static_cast<double>(user.jazz_preference)
    };

    // --- Compute similarity between user and each track's genre ---
    std::vector<double> similarities;
    for (const auto& genre_vec : track_genre_features) {
        similarities.push_back(cosine_similarity(genre_vec, user_genre_pref));
    }

    // --- Prepare features for regression ---
    std::vector<double> likes_f(likes.begin(), likes.end());
    std::vector<double> clicks_f(clicks.begin(), clicks.end());
    std::vector<double> full_listens_f(full_listens.begin(), full_listens.end());
    std::vector<double> author_listeners_f(author_listeners.begin(), author_listeners.end());
    std::vector<double> similarities_f(similarities.begin(), similarities.end());

    // Standardize features
    standardize(likes_f);
    standardize(clicks_f);
    standardize(full_listens_f);
    standardize(author_listeners_f);
    standardize(similarities_f);

    // --- User's ratings for tracks (to be updated) ---
    // #TODO: Update the ratings to reflect the new rock-focused user profile.
    // Song A is Rock, Song B is Pop, Song C is Jazz.
    std::vector<double> ratings = {5, 1, 1};

    // --- Fit simple linear regression (closed form) ---
    // X: n x 5, y: n
    std::vector<std::vector<double>> X;
    for (size_t i = 0; i < likes_f.size(); ++i) {
        X.push_back({likes_f[i], clicks_f[i], full_listens_f[i], author_listeners_f[i], similarities_f[i]});
    }
    // Add bias term
    for (auto& row : X) row.push_back(1.0);

    // Closed-form solution: w = (X^T X)^-1 X^T y
    // For 3 samples, 6 features (including bias)
    // We'll use normal equations for small data
    size_t n = X.size(), d = X[0].size();
    std::vector<std::vector<double>> XtX(d, std::vector<double>(d, 0.0));
    std::vector<double> Xty(d, 0.0);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < d; ++j) {
            Xty[j] += X[i][j] * ratings[i];
            for (size_t k = 0; k < d; ++k) {
                XtX[j][k] += X[i][j] * X[i][k];
            }
        }
    }
    // Solve XtX * w = Xty (using Cramer's rule for 6x6)
    // For simplicity, use only the similarity feature and bias (2D regression)
    // (since 3 samples is not enough for 6D regression)
    std::vector<std::vector<double>> X2;
    for (size_t i = 0; i < n; ++i) {
        X2.push_back({similarities_f[i], 1.0});
    }
    double sum_xx = 0, sum_xy = 0, sum_x = 0, sum_y = 0;
    for (size_t i = 0; i < n; ++i) {
        sum_xx += X2[i][0] * X2[i][0];
        sum_xy += X2[i][0] * ratings[i];
        sum_x += X2[i][0];
        sum_y += ratings[i];
    }
    double denom = n * sum_xx - sum_x * sum_x;
    double w1 = (n * sum_xy - sum_x * sum_y) / denom;
    double w0 = (sum_y * sum_xx - sum_x * sum_xy) / denom;

    // --- Predict for a test song (Rock) ---
    int test_likes = 15, test_clicks = 35, test_full_listens = 50, test_author_listeners = 500;
    std::string test_genre = "Rock";
    std::vector<double> test_genre_vec = {1, 0, 0};
    double test_similarity = cosine_similarity(test_genre_vec, user_genre_pref);

    // Standardize test features using training mean/std
    auto standardize_test = [](double v, const std::vector<double>& train) {
        double mean = 0.0, stddev = 0.0;
        for (double x : train) mean += x;
        mean /= train.size();
        for (double x : train) stddev += (x - mean) * (x - mean);
        stddev = std::sqrt(stddev / train.size());
        return (v - mean) / (stddev == 0.0 ? 1.0 : stddev);
    };
    double test_similarity_std = standardize_test(test_similarity, similarities);

    // Predict using similarity feature only
    double predicted_rating = w1 * test_similarity_std + w0;

    std::cout << "Predicted rating for the test song: " << predicted_rating << std::endl;
    return 0;
}
