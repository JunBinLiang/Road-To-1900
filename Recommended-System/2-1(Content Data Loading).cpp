#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <DataFrame/DataFrame.h>

using namespace hmdf;

// Struct to hold merged row data
struct MergedRow {
    std::string track_id;
    std::string title;
    int likes;
    int clicks;
    int full_listens;
    std::string author_id;
    std::string author_name;
    int author_listeners;
    std::string genre;
};

// TODO: Implement this function to merge tracks_df and authors_df on author_id
std::vector<MergedRow> merge_tracks_authors(
    const StdDataFrame<unsigned long>& tracks_df,
    const StdDataFrame<unsigned long>& authors_df
) {
    // TODO: Merge the dataframes on the common 'author_id' field
    // TODO: Return a vector of MergedRow containing the combined data
    
    // 1. Fetch the required columns
    const auto& track_ids = tracks_df.get_column<std::string>("track_id");
    const auto& titles = tracks_df.get_column<std::string>("title");
    const auto& likes = tracks_df.get_column<int>("likes");
    const auto& clicks = tracks_df.get_column<int>("clicks");
    const auto& full_listens = tracks_df.get_column<int>("full_listens");
    const auto& track_author_ids = tracks_df.get_column<std::string>("author_id");

    const auto& author_ids = authors_df.get_column<std::string>("author_id");
    const auto& names = authors_df.get_column<std::string>("name");
    const auto& author_listeners = authors_df.get_column<int>("author_listeners");
    const auto& genres = authors_df.get_column<std::string>("genre");
    
    std::unordered_map<std::string, size_t> author_map;
    for (size_t i = 0; i < author_ids.size(); ++i) {
        author_map[author_ids[i]] = i;
    }
    
    std::vector<MergedRow> result;
    for (size_t i = 0; i < track_ids.size(); ++i) {
        size_t author_idx = author_map[track_author_ids[i]];
        result.push_back({
            track_ids[i],
            titles[i],
            likes[i],
            clicks[i],
            full_listens[i],
            track_author_ids[i],
            names[author_idx],
            author_listeners[author_idx],
            genres[author_idx]
        });
    }

    return result;
}

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
    // Note: Different order from authors to test proper matching
    std::vector<std::string> author_ids = {"A2", "A3", "A1"};

    tracks_df.load_column("track_id", std::move(track_ids));
    tracks_df.load_column("title", std::move(titles));
    tracks_df.load_column("likes", std::move(likes));
    tracks_df.load_column("clicks", std::move(clicks));
    tracks_df.load_column("full_listens", std::move(full_listens));
    tracks_df.load_column("author_id", std::move(author_ids));

    // Create authors dataframe manually with different ordering
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

    // Merge the dataframes
    std::vector<MergedRow> merged = merge_tracks_authors(tracks_df, authors_df);

    // Display the merged dataset
    std::cout << "Merged Tracks and Authors Data:" << std::endl;
    std::cout << "Track ID | Title   | Likes | Clicks | Full Listens | Author ID | Author Name | Author Listeners | Genre" << std::endl;
    std::cout << "---------|---------|-------|--------|--------------|-----------|-------------|------------------|------" << std::endl;
    for (const auto& row : merged) {
        std::cout << row.track_id << "      | "
                  << row.title << " | "
                  << row.likes << "   | "
                  << row.clicks << "    | "
                  << row.full_listens << "          | "
                  << row.author_id << "      | "
                  << row.author_name << "    | "
                  << row.author_listeners << "             | "
                  << row.genre << std::endl;
    }

    return 0;
}
