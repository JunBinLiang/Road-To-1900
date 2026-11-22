#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <DataFrame/DataFrame.h>

using namespace hmdf;

// Helper function to compute mean
double mean(const std::vector<double>& v) {
    double sum = 0.0;
    for (double x : v) sum += x;
    return sum / v.size();
}

// Helper function to compute stddev
double stddev(const std::vector<double>& v, double m) {
    double sum = 0.0;
    for (double x : v) sum += (x - m) * (x - m);
    return std::sqrt(sum / v.size());
}

// Standardize a vector in-place
void standardize(std::vector<double>& v) {
    double m = mean(v);
    double s = stddev(v, m);
    for (double& x : v) x = (x - m) / s;
}

// Cosine similarity between two vectors
double cosine_similarity(const std::vector<double>& a, const std::vector<double>& b) {
    double dot = 0.0, norm_a = 0.0, norm_b = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }
    return dot / (std::sqrt(norm_a) * std::sqrt(norm_b));
}

int main() {
    // Create tracks dataframe manually (TODO: add duration)
    StdDataFrame<unsigned long> tracks_df;
    std::vector<unsigned long> track_indices = {0, 1, 2};
    tracks_df.load_index(std::move(track_indices));
    std::vector<std::string> track_ids = {"001", "002", "003"};
    std::vector<std::string> titles = {"Song A", "Song B", "Song C"};
    std::vector<int> likes = {150, 200, 100};
    std::vector<int> clicks = {300, 400, 250};
    std::vector<int> full_listens = {120, 180, 95};
    std::vector<int> durations = { 30, 60, 50}; // TODO: add duration values
    std::vector<std::string> author_ids = {"A1", "A2", "A3"};
    tracks_df.load_column("track_id", std::move(track_ids));
    tracks_df.load_column("title", std::move(titles));
    tracks_df.load_column("likes", std::move(likes));
    tracks_df.load_column("clicks", std::move(clicks));
    tracks_df.load_column("full_listens", std::move(full_listens));
    tracks_df.load_column("duration", std::move(durations)); // TODO: add duration column
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

    // User profile
    std::vector<double> user_genre_pref = {5.0, 4.0, 2.0}; // [rock, pop, jazz]

    // Map genre to one-hot
    auto genre_to_onehot = [](const std::string& genre) -> std::vector<double> {
        if (genre == "Rock") return {1.0, 0.0, 0.0};
        if (genre == "Pop")  return {0.0, 1.0, 0.0};
        if (genre == "Jazz") return {0.0, 0.0, 1.0};
        return {0.0, 0.0, 0.0};
    };

    // Merge tracks and authors
    std::vector<double> likes_v, clicks_v, full_listens_v, duration_v, author_listeners_v, similarity_v;
    std::vector<std::string> genre_v;
    for (size_t i = 0; i < tracks_df.get_index().size(); ++i) {
        std::string author_id = tracks_df.get_column<std::string>("author_id")[i];
        // Find author row
        size_t author_idx = 0;
        for (; author_idx < authors_df.get_index().size(); ++author_idx)
            if (authors_df.get_column<std::string>("author_id")[author_idx] == author_id)
                break;
        // Get genre and author_listeners
        std::string genre = authors_df.get_column<std::string>("genre")[author_idx];
        int author_listen = authors_df.get_column<int>("author_listeners")[author_idx];
        // Cosine similarity
        std::vector<double> genre_onehot = genre_to_onehot(genre);
        double sim = cosine_similarity(genre_onehot, user_genre_pref);
        // Collect features
        likes_v.push_back(tracks_df.get_column<int>("likes")[i]);
        clicks_v.push_back(tracks_df.get_column<int>("clicks")[i]);
        full_listens_v.push_back(tracks_df.get_column<int>("full_listens")[i]);
        duration_v.push_back(tracks_df.get_column<int>("duration")[i]); // TODO: add duration
        author_listeners_v.push_back(author_listen);
        similarity_v.push_back(sim);
        genre_v.push_back(genre);
    }
    

    // Standardize features
    std::vector<double> likes_std = likes_v, clicks_std = clicks_v, full_listens_std = full_listens_v, duration_std = duration_v, author_listeners_std = author_listeners_v, similarity_std = similarity_v;
    standardize(likes_std);
    standardize(clicks_std);
    standardize(full_listens_std);
    standardize(duration_std); // TODO: standardize duration
    standardize(author_listeners_std);
    standardize(similarity_std);

    // Ratings (mock)
    std::vector<double> ratings = {4.0, 5.0, 3.0};

    // Linear regression (closed form, TODO: update for 6 features)
    // X: n x 6, y: n
    std::vector<std::vector<double>> X;
    for (size_t i = 0; i < likes_std.size(); ++i) {
        X.push_back({likes_std[i], clicks_std[i], full_listens_std[i], author_listeners_std[i], similarity_std[i], duration_std[i]});
        // TODO: add duration_std[i] to the feature vector
    }

    // Prepare test song
    std::string test_genre = "Rock";
    std::vector<double> test_genre_onehot = genre_to_onehot(test_genre);
    double test_similarity = cosine_similarity(test_genre_onehot, user_genre_pref);

    double test_likes = 120;
    double test_clicks = 350;
    double test_full_listens = 110;
    double test_duration = 70; // TODO: set test song duration
    double test_author_listeners = 6000;

    // Standardize test song features using train means/stddevs
    auto standardize_one = [](double x, const std::vector<double>& v) {
        double m = mean(v);
        double s = stddev(v, m);
        return (x - m) / s;
    };
    double test_likes_std = standardize_one(test_likes, likes_v);
    double test_clicks_std = standardize_one(test_clicks, clicks_v);
    double test_full_listens_std = standardize_one(test_full_listens, full_listens_v);
    double test_duration_std = standardize_one(test_duration, duration_v); // TODO: standardize test duration
    double test_author_listeners_std = standardize_one(test_author_listeners, author_listeners_v);
    double test_similarity_std = standardize_one(test_similarity, similarity_v);
    
    
    double y_mean = (ratings[0] + ratings[1] + ratings[2]) / 3.0;
    std::vector<double> weights(6, 0.0);
    for (int j = 0; j < 6; ++j) {
        double num = 0.0, denom = 0.0;
        for (int i = 0; i < 3; ++i) {
            num += X[i][j] * (ratings[i] - y_mean);
            denom += X[i][j] * X[i][j];
        }
        weights[j] = (denom == 0.0) ? 0.0 : num / denom;
    }
    double pred = y_mean
        + weights[0] * test_likes_std
        + weights[1] * test_clicks_std
        + weights[2] * test_full_listens_std
        + weights[3] * test_author_listeners_std
        + weights[4] * test_similarity_std
        + weights[5] * test_duration_std;

    std::cout << "Predicted rating for the test song: " << pred << std::endl;
    return 0;
}
