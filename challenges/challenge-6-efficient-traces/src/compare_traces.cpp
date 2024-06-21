#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <unordered_set>

std::string join(const std::vector<std::string>& alist, const char* sep) {
    return std::accumulate(alist.begin(), alist.end(), std::string(), 
    [sep](const std::string& a, const std::string& b) -> std::string { 
        return a + (a.length() > 0 ? sep : "") + b; 
    } );
}

// Function to split a string into words (assuming words are separated by underscores)
std::unordered_set<std::string> split_to_words(const std::string& identifier) {
    std::unordered_set<std::string> words;
    std::istringstream stream(identifier);
    std::string word;
    while (std::getline(stream, word, '_')) {
        words.insert(word);
    }
    return words;
}

float switch_cost_similarity(const std::string& lhs_identifier, const std::string& rhs_identifier) {
    // Split the identifiers into words
    std::unordered_set<std::string> lhs_words = split_to_words(lhs_identifier);
    std::unordered_set<std::string> rhs_words = split_to_words(rhs_identifier);

    // Compute the number of common words
    std::unordered_set<std::string> common_words;
    std::set_intersection(lhs_words.begin(), lhs_words.end(),
                            rhs_words.begin(), rhs_words.end(),
                            std::inserter(common_words, common_words.begin()));

    // Compute the cost
    return 1.0f - (2.0f * common_words.size() / (lhs_words.size() + rhs_words.size()));
}

int levenshteinDistance(const std::string& s1, const std::string& s2) {
    int m = s1.size();
    int n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    return dp[m][n];
}

// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


// Function to compute the cost of switching two instructions
double switch_cost_levenshtein(const std::string& s1, const std::string& s2) {
    // Placeholder function, to be implemented
    int dist = levenshteinDistance(s1, s2);
    int maxLen = std::max(s1.size(), s2.size());
    return 1.0 - static_cast<double>(dist) / maxLen;
}

// Function to compute the transformation cost without caching
double computeTransformationCost(const std::vector<std::string>& trace1, const std::vector<std::string>& trace2, int i, int j) {
    if (i == trace1.size()) return trace2.size() - j;
    if (j == trace2.size()) return trace1.size() - i;
    
    if (trace1[i] == trace2[j]) {
        return computeTransformationCost(trace1, trace2, i + 1, j + 1);
    } else {
        double deleteFromTrace1 = 1 + computeTransformationCost(trace1, trace2, i + 1, j);
        double deleteFromTrace2 = 1 + computeTransformationCost(trace1, trace2, i, j + 1);
        double switchInstructions = switch_cost_levenshtein(trace1[i], trace2[j]) + computeTransformationCost(trace1, trace2, i + 1, j + 1);
        return std::min({deleteFromTrace1, deleteFromTrace2, switchInstructions});
    }
}

// Function to read traces from a file
std::vector<std::vector<std::string>> readTraces(const std::string& filename) {
    std::vector<std::vector<std::string>> traces;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        traces.push_back(split(line, ','));
    }
    return traces;
}

// Function to find the best corresponding trace from baseline for each trace in target
void findBestCorrespondingTraces(const std::vector<std::vector<std::string>>& baseline, const std::vector<std::vector<std::string>>& target) {
    for (const auto& targetTrace : target) {
        double bestCorrespondence = std::numeric_limits<double>::max();
        std::vector<std::string> bestTrace;
        for (const auto& baselineTrace : baseline) {
            double correspondence = computeTransformationCost(targetTrace, baselineTrace, 0, 0);
            if (correspondence < bestCorrespondence) {
                bestCorrespondence = correspondence;
                bestTrace = baselineTrace;
            }
        }
        std::cout << join(targetTrace, ",") << "\n" << join(bestTrace, ",") << "\n\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <baseline_file> <target_file>\n";
        return 1;
    }

    std::vector<std::vector<std::string>> baselineTraces = readTraces(argv[1]);
    std::vector<std::vector<std::string>> targetTraces = readTraces(argv[2]);

    findBestCorrespondingTraces(baselineTraces, targetTraces);

    return 0;
}
