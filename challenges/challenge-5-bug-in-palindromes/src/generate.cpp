#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

std::unordered_set<std::string> palindromeCache;

// Function to check if a vector is a palindrome
bool isPalindrome(const std::vector<char> v) {
    int n = v.size();
    for (int i = 0; i < n / 2; ++i) {
        if (v[i] != v[n - 1 - i]) {
            return false;
        }
    }
    return true;
}

// Function to generate all permutations of the vector and check for palindromes
void generatePermutations(std::vector<char> v, int start, int end) {
    if (start == end) {
        if (isPalindrome(v)) {
            // Print the palindrome permutation
            std::string palindrome(v.begin(), v.end());
            palindromeCache.insert(palindrome);
        }
    } else {
        for (int i = start; i <= end; ++i) {
            std::swap(v[start], v[i]); // Swap the elements
            generatePermutations(v, start + 1, end); // Recur for the next position
            std::swap(v[start], v[i]); // Backtrack
        }
    }
}

std::vector<char> breakStringIntoChars(const std::string& str) {
    return std::vector<char>(str.begin(), str.end());
}


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <string>" << std::endl;
        return 1;
    }    
    std::string word = argv[1];

    std::vector<char> chars = breakStringIntoChars(word);
    generatePermutations(chars, 0, chars.size() - 1);

    for (const std::string& palindrome : palindromeCache) {
        std::cout << palindrome << std::endl;
    }
    return 0;
}
