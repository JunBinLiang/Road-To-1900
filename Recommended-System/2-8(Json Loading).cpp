#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <nlohmann/json.hpp>

// For convenience
using json = nlohmann::json;

// Helper function to read JSON file with multiple path attempts
json read_json_file(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        std::ifstream file(path);
        if (file.is_open()) {
            json j;
            file >> j;
            return j;
        }
    }
    throw std::runtime_error("Could not open any of the specified file paths");
}

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

int main() {
    // Read JSON files with multiple path attempts
    json tracks_json = read_json_file({"../tracks.json", "tracks.json", "../../tracks.json"});
    json users_json = read_json_file({"../users.json", "users.json", "../../users.json"});
    json interactions_json = read_json_file({"../interactions.json", "interactions.json", "../../interactions.json"});

    // Genre encoding: Jazz = [1,0,0], Pop = [0,1,0], Rock = [0,0,1]
    std::map<std::string, std::vector<double>> genre_encodings = {
        {"Jazz", {1, 0, 0}},
        {"Pop", {0, 1, 0}},
        {"Rock", {0, 0, 1}}
    };

    // For each interaction, calculate genre similarity
    for (const auto& interaction : interactions_json) {
        int user_id = interaction["user_id"];
        int track_id = interaction["track_id"];
        int rating = interaction["rating"];

        // Find user and track
        json user, track;
        for (const auto& u : users_json) {
            if (u["id"] == user_id) {
                user = u;
                break;
            }
        }
        for (const auto& t : tracks_json) {
            if (t["id"] == track_id) {
                track = t;
                break;
            }
        }

        // User genre preferences as vector (Jazz, Pop, Rock)
        std::vector<double> user_genre_vec = {
            user["genre_preferences"]["Jazz"],
            user["genre_preferences"]["Pop"],
            user["genre_preferences"]["Rock"]
        };

        // Track genre encoding
        std::string track_genre = track["genre"];
        std::vector<double> track_genre_vec = genre_encodings[track_genre];

        // TODO: Calculate cosine similarity between user_genre_vec and track_genre_vec
        double sim = cosine_similarity(user_genre_vec, track_genre_vec);
        // Print the genre similarity score
        std :: cout << "Similarity : " << sim << std :: endl;
    }

    return 0;
}
















//Part 2






#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <DataFrame/DataFrame.h>

using json = nlohmann::json;
using namespace hmdf;

// Helper function to read JSON file
json read_json(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    json j;
    in >> j;
    return j;
}

// Helper function for cosine similarity
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

int main() {
    // Read JSON files
    json tracks = read_json("../../tracks.json");
    json users = read_json("../../users.json");
    json interactions = read_json("../../interactions.json");

    // TODO: Define genre encodings
      std::map<std::string, std::vector<double>> genre_encodings = {
        {"Jazz", {1, 0, 0}},
        {"Pop", {0, 1, 0}},
        {"Rock", {0, 0, 1}}
    };

    // Prepare columns
    std::vector<int> user1_col, user2_col, user3_col;
    std::vector<int> track1_col, track2_col, track3_col;
    std::vector<int> track_likes_col;
    std::vector<int> user_listening_avg_col;
    std::vector<double> genre_similarity_col;
    std::vector<int> rating_col;
    
    for (const auto& interaction : interactions) {
        int user_id = interaction["user_id"];
        int track_id = interaction["track_id"];
        int rating = interaction["rating"];
       
        auto user = users[user_id - 1];
        auto track = tracks[track_id - 1];

        // User dummy variables
        user1_col.push_back(user_id == 1 ? 1 : 0);
        user2_col.push_back(user_id == 2 ? 1 : 0);
        user3_col.push_back(user_id == 3 ? 1 : 0);

        // Track dummy variables
        track1_col.push_back(track_id == 1 ? 1 : 0);
        track2_col.push_back(track_id == 2 ? 1 : 0);
        track3_col.push_back(track_id == 3 ? 1 : 0);

        // TODO: Extract user and track features
        // Find user and track in the JSON arrays
        int track_likes = track["likes"];
        int user_listening_avg = user["time_listening_avg"];

        // TODO: Compute genre similarity
        std::vector<double> user_genre_array = {
            user["genre_preferences"]["Jazz"],
            user["genre_preferences"]["Pop"],
            user["genre_preferences"]["Rock"]
        };
        std::vector<double> track_genre_array = genre_encodings[track["genre"]];
        double genre_similarity = cosine_similarity(user_genre_array, track_genre_array);

        // TODO: Append features to columns
        track_likes_col.push_back(track_likes);
        user_listening_avg_col.push_back(user_listening_avg);
        genre_similarity_col.push_back(genre_similarity);
        rating_col.push_back(rating);
    }

    // Create DataFrame
    StdDataFrame<unsigned long> df;
    std::vector<unsigned long> idx(interactions.size());
    for (size_t i = 0; i < idx.size(); ++i) idx[i] = i;
    df.load_index(std::move(idx));
    df.load_column("user1", user1_col);
    df.load_column("user2", user2_col);
    df.load_column("user3", user3_col);
    df.load_column("track1", track1_col);
    df.load_column("track2", track2_col);
    df.load_column("track3", track3_col);
    df.load_column("track_likes", track_likes_col);
    df.load_column("user_listening_avg", user_listening_avg_col);
    df.load_column("genre_similarity", genre_similarity_col);
    df.load_column("rating", rating_col);

    // Print DataFrame
    std::cout << "user1 user2 user3 track1 track2 track3 track_likes user_listening_avg genre_similarity rating\n";
    for (size_t i = 0; i < df.shape().first; ++i) {
        std::cout
            << df.get_column<int>("user1")[i] << "     "
            << df.get_column<int>("user2")[i] << "     "
            << df.get_column<int>("user3")[i] << "     "
            << df.get_column<int>("track1")[i] << "      "
            << df.get_column<int>("track2")[i] << "      "
            << df.get_column<int>("track3")[i] << "      "
            << df.get_column<int>("track_likes")[i] << "         "
            << df.get_column<int>("user_listening_avg")[i] << "                "
            << df.get_column<double>("genre_similarity")[i] << "         "
            << df.get_column<int>("rating")[i] << "\n";
    }

    return 0;
}
