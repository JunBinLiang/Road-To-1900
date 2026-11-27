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
