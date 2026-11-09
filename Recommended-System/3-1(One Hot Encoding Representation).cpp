#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <DataFrame/DataFrame.h>

using namespace hmdf;

int main() {
    // Create tracks dataframe manually
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
    tracks_df.load_column("likes", std::move(likes));
    tracks_df.load_column("clicks", std::move(clicks));
    tracks_df.load_column("full_listens", std::move(full_listens));
    tracks_df.load_column("author_id", std::move(author_ids));

    // Create authors dataframe manually
    StdDataFrame<unsigned long> authors_df;
    std::vector<unsigned long> author_indices = {0, 1, 2, 3, 4};
    authors_df.load_index(std::move(author_indices));

    std::vector<std::string> author_ids_df = {"A1", "A2", "A3", "A4", "A5"};
    std::vector<std::string> names = {"Artist X", "Artist Y", "Artist Z", "Artist A", "Artist B"};
    std::vector<int> author_listeners = {5000, 8000, 3000, 10000, 7000};
    std::vector<std::string> genres = {"Rock", "Pop", "Jazz", "Classical", "Electronic"};

    authors_df.load_column("author_id", std::move(author_ids_df));
    authors_df.load_column("name", std::move(names));
    authors_df.load_column("author_listeners", std::move(author_listeners));
    authors_df.load_column("genre", std::move(genres));

    // Merge tracks and authors on author_id
    // For simplicity, we'll create merged vectors manually for the three tracks
    std::vector<std::string> merged_genres;
    const auto& track_author_ids = tracks_df.get_column<std::string>("author_id");
    const auto& author_ids_col = authors_df.get_column<std::string>("author_id");
    const auto& genres_col = authors_df.get_column<std::string>("genre");
    
    for (const auto& aid : track_author_ids) {
        for (size_t i = 0; i < author_ids_col.size(); ++i) {
            if (aid == author_ids_col[i]) {
                merged_genres.push_back(genres_col[i]);
                break;
            }
        }
    }

    // TODO: Define genre_map with one-hot encoding for all genres in the data
    std::unordered_map<std::string, std::vector<int>> genre_map = {
        // Fill in the genre map here, e.g. {"Rock", {1, 0, 0, 0, 0}}, ...
        {"Rock", {1, 0, 0, 0, 0}},
        {"Pop", {0, 1, 0, 0, 0}},
        {"Jazz", {0, 0, 1, 0, 0}},
        {"Classical", {0, 0, 0, 1, 0}},
        {"Electronic", {0, 0, 0, 0, 1}}
    };

    // Validate the one-hot encoding in the map
    for (const auto& pair : genre_map) {
        const auto& vec = pair.second;
        int sum = 0;
        bool invalid_value_found = false;
        for (int val : vec) {
            if (val != 0 && val != 1) {
                invalid_value_found = true;
                break;
            }
            sum += val;
        }

        if (invalid_value_found || sum != 1) {
            std::cerr << "Error: The vector for genre '" << pair.first << "' is not a valid one-hot encoding. It must contain only 0s and one 1." << std::endl;
            return 1;
        }
    }

    // Map genres to one-hot vectors and print them
    for (size_t i = 0; i < merged_genres.size(); ++i) {
        const std::string& genre = merged_genres[i];
        const auto& vec = genre_map[genre]; // This will fail if genre_map is incomplete!
        std::cout << "Genre array representation for song " << (i + 1) << ": [";
        for (size_t j = 0; j < vec.size(); ++j) {
            std::cout << vec[j];
            if (j + 1 < vec.size()) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}
