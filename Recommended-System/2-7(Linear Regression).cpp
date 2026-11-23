
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <cassert>
#include <stdexcept>
#include <DataFrame/DataFrame.h>

using namespace hmdf;

// 1. Cosine similarity
double cosine_similarity(
    const std::vector<double>& a,
    const std::vector<double>& b
) {
    assert(a.size() == b.size());

    double dot = 0.0;
    double norm_a = 0.0;
    double norm_b = 0.0;

    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }

    if (norm_a == 0.0 || norm_b == 0.0)
        return 0.0;

    return dot / (std::sqrt(norm_a) * std::sqrt(norm_b));
}

// 2. Standardize columns
void standardize_columns(
    std::vector<std::vector<double>>& data,
    std::vector<double>& means,
    std::vector<double>& stds
) {
    if (data.empty())
        throw std::invalid_argument("Empty dataset");

    size_t n_samples = data.size();
    size_t n_features = data[0].size();

    means.assign(n_features, 0.0);
    stds.assign(n_features, 0.0);

    // Calculate means
    for (size_t j = 0; j < n_features; ++j) {
        for (size_t i = 0; i < n_samples; ++i) {
            means[j] += data[i][j];
        }
        means[j] /= n_samples;
    }

    // Calculate standard deviations
    for (size_t j = 0; j < n_features; ++j) {
        for (size_t i = 0; i < n_samples; ++i) {
            double diff = data[i][j] - means[j];
            stds[j] += diff * diff;
        }

        stds[j] = std::sqrt(stds[j] / n_samples);

        if (stds[j] == 0.0)
            stds[j] = 1.0;
    }

    // Standardize
    for (size_t i = 0; i < n_samples; ++i) {
        for (size_t j = 0; j < n_features; ++j) {
            data[i][j] = (data[i][j] - means[j]) / stds[j];
        }
    }
}

// 3. Standardize one row
std::vector<double> standardize_row(
    const std::vector<double>& row,
    const std::vector<double>& means,
    const std::vector<double>& stds
) {
    if (row.size() != means.size() ||
        row.size() != stds.size()) {
        throw std::invalid_argument("Feature size mismatch");
    }

    std::vector<double> result(row.size());

    for (size_t j = 0; j < row.size(); ++j) {
        result[j] = (row[j] - means[j]) / stds[j];
    }

    return result;
}

// 4. Linear Regression with Ridge Regularization
class LinearRegression {
public:
    std::vector<double> weights;
    double bias = 0.0;

    double lambda = 1.0;

    // Gaussian elimination with partial pivoting
    std::vector<double> solve(
        std::vector<std::vector<double>> A,
        std::vector<double> b
    ) {
        int n = static_cast<int>(b.size());

        for (int i = 0; i < n; ++i) {

            // Find pivot
            int pivot = i;

            for (int j = i + 1; j < n; ++j) {
                if (std::abs(A[j][i]) >
                    std::abs(A[pivot][i])) {
                    pivot = j;
                }
            }

            std::swap(A[i], A[pivot]);
            std::swap(b[i], b[pivot]);

            if (std::abs(A[i][i]) < 1e-12) {
                throw std::runtime_error("Singular matrix");
            }

            // Eliminate
            for (int j = i + 1; j < n; ++j) {
                double factor = A[j][i] / A[i][i];

                for (int k = i; k < n; ++k) {
                    A[j][k] -= factor * A[i][k];
                }

                b[j] -= factor * b[i];
            }
        }

        // Back substitution
        std::vector<double> x(n, 0.0);

        for (int i = n - 1; i >= 0; --i) {
            x[i] = b[i];

            for (int j = i + 1; j < n; ++j) {
                x[i] -= A[i][j] * x[j];
            }

            x[i] /= A[i][i];
        }

        return x;
    }

    // Train model
    void fit(
        const std::vector<std::vector<double>>& X,
        const std::vector<double>& y
    ) {
        if (X.empty() || X.size() != y.size())
            throw std::invalid_argument("Invalid training data");

        int n = static_cast<int>(X.size());
        int m = static_cast<int>(X[0].size());
        int p = m + 1;

        for (const auto& row : X) {
            if (static_cast<int>(row.size()) != m)
                throw std::invalid_argument("Inconsistent features");
        }

        std::vector<std::vector<double>> A(
            p, std::vector<double>(p, 0.0)
        );

        std::vector<double> b(p, 0.0);

        // Construct X transpose * X and X transpose * y
        for (int i = 0; i < n; ++i) {

            std::vector<double> row(p, 1.0);

            for (int j = 0; j < m; ++j) {
                row[j + 1] = X[i][j];
            }

            for (int j = 0; j < p; ++j) {
                b[j] += row[j] * y[i];

                for (int k = 0; k < p; ++k) {
                    A[j][k] += row[j] * row[k];
                }
            }
        }

        // Ridge regularization.
        // Do not regularize the intercept.
        for (int j = 1; j < p; ++j) {
            A[j][j] += lambda;
        }

        // Solve for parameters
        std::vector<double> theta = solve(A, b);

        bias = theta[0];

        weights.assign(
            theta.begin() + 1,
            theta.end()
        );
    }

    // Predict rating
    double predict(const std::vector<double>& x) const {
        if (x.size() != weights.size())
            throw std::invalid_argument("Feature size mismatch");

        double result = bias;

        for (size_t i = 0; i < x.size(); ++i) {
            result += weights[i] * x[i];
        }

        return result;
    }
};

int main() {

    // 1. Create tracks dataframe
    StdDataFrame<unsigned long> tracks_df;

    std::vector<unsigned long> track_indices = {0, 1, 2};
    tracks_df.load_index(std::move(track_indices));

    std::vector<std::string> track_ids = {
        "001", "002", "003"
    };

    std::vector<std::string> titles = {
        "Song A", "Song B", "Song C"
    };

    std::vector<int> likes = {150, 200, 100};
    std::vector<int> clicks = {300, 400, 250};
    std::vector<int> full_listens = {120, 180, 95};

    std::vector<std::string> author_ids = {
        "A1", "A2", "A3"
    };

    tracks_df.load_column("track_id", track_ids);
    tracks_df.load_column("title", titles);
    tracks_df.load_column("likes", likes);
    tracks_df.load_column("clicks", clicks);
    tracks_df.load_column("full_listens", full_listens);
    tracks_df.load_column("author_id", author_ids);

    // 2. Create authors dataframe
    StdDataFrame<unsigned long> authors_df;

    std::vector<unsigned long> author_indices = {0, 1, 2};
    authors_df.load_index(std::move(author_indices));

    std::vector<std::string> author_ids_df = {
        "A1", "A2", "A3"
    };

    std::vector<std::string> names = {
        "Artist X", "Artist Y", "Artist Z"
    };

    std::vector<int> author_listeners = {
        5000, 8000, 3000
    };

    std::vector<std::string> genres = {
        "Rock", "Pop", "Jazz"
    };

    authors_df.load_column("author_id", author_ids_df);
    authors_df.load_column("name", names);
    authors_df.load_column("author_listeners", author_listeners);
    authors_df.load_column("genre", genres);

    // 3. Merge tracks and authors
    std::vector<std::map<std::string, std::string>> merged;

    for (size_t i = 0; i < track_ids.size(); ++i) {

        std::map<std::string, std::string> row;

        row["track_id"] = track_ids[i];
        row["title"] = titles[i];
        row["likes"] = std::to_string(likes[i]);
        row["clicks"] = std::to_string(clicks[i]);
        row["full_listens"] = std::to_string(full_listens[i]);
        row["author_id"] = author_ids[i];

        for (size_t j = 0; j < author_ids_df.size(); ++j) {

            if (author_ids[i] == author_ids_df[j]) {

                row["author_listeners"] =
                    std::to_string(author_listeners[j]);

                row["genre"] = genres[j];

                break;
            }
        }

        if (row.find("genre") == row.end()) {
            throw std::runtime_error("Author not found");
        }

        merged.push_back(row);
    }

    // 4. User preferences
    std::map<std::string, double> user_profile = {
        {"rock_preference", 5.0},
        {"pop_preference", 4.0},
        {"jazz_preference", 2.0}
    };

    // 5. Genre one-hot encoding
    std::map<std::string, std::vector<double>> genre_map = {
        {"Rock", {1.0, 0.0, 0.0}},
        {"Pop",  {0.0, 1.0, 0.0}},
        {"Jazz", {0.0, 0.0, 1.0}}
    };

    std::vector<double> user_genre_pref = {
        user_profile["rock_preference"],
        user_profile["pop_preference"],
        user_profile["jazz_preference"]
    };

    // 6. Calculate genre similarity
    std::vector<double> similarities;

    for (const auto& row : merged) {

        std::string genre = row.at("genre");

        double sim = cosine_similarity(
            genre_map.at(genre),
            user_genre_pref
        );

        similarities.push_back(sim);
    }

    // 7. Prepare training features and targets
    std::vector<std::vector<double>> features;

    // Synthetic user ratings
    std::vector<double> target = {
        4.0, 5.0, 3.0
    };

    for (size_t i = 0; i < merged.size(); ++i) {

        std::vector<double> feat = {
            std::stod(merged[i].at("likes")),
            std::stod(merged[i].at("clicks")),
            std::stod(merged[i].at("full_listens")),
            std::stod(merged[i].at("author_listeners")),
            similarities[i]
        };

        features.push_back(feat);
    }

    // 8. Standardize training features
    std::vector<double> means, stds;

    standardize_columns(
        features,
        means,
        stds
    );

    // 9. Train model
    LinearRegression reg;

    reg.lambda = 1.0;

    reg.fit(features, target);

    std::cout << "Model trained successfully!\n\n";

    std::cout << "Bias: " << reg.bias << "\n";

    std::cout << "Weights:\n";

    for (size_t i = 0; i < reg.weights.size(); ++i) {
        std::cout << "Feature " << i + 1
                  << ": " << reg.weights[i] << "\n";
    }

    // 10. Define test songs
    struct TestSong {
        int likes;
        int clicks;
        int full_listens;
        int author_listeners;
        std::string genre;
    };

    std::vector<TestSong> test_songs = {
        {120, 350, 110, 6000, "Rock"},
        {130, 300, 100, 6500, "Pop"},
        {110, 320, 105, 5500, "Jazz"}
    };

    // 11. Predict test songs
    std::cout << "\nPredicted Ratings:\n";

    for (size_t i = 0; i < test_songs.size(); ++i) {

        double sim = cosine_similarity(
            genre_map.at(test_songs[i].genre),
            user_genre_pref
        );

        std::vector<double> test_feat = {
            static_cast<double>(test_songs[i].likes),
            static_cast<double>(test_songs[i].clicks),
            static_cast<double>(test_songs[i].full_listens),
            static_cast<double>(test_songs[i].author_listeners),
            sim
        };

        // Apply training means and standard deviations
        std::vector<double> test_feat_std =
            standardize_row(test_feat, means, stds);

        double prediction = reg.predict(test_feat_std);

        // Clamp rating to 1-5. Linear regression can predict values outside your rating scale. For example, it might predict 6.3 stars even though your rating system only supports 1–5. std::clamp() prevents that.
        prediction = std::clamp(prediction, 1.0, 5.0);

        std::cout << "Song " << i + 1
                  << " (" << test_songs[i].genre << ")"
                  << " Rating: " << prediction
                  << std::endl;
    }

    return 0;
}
