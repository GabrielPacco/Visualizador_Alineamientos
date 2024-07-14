//needlman_wunsh.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

#ifndef MATCH_SCORE
#define MATCH_SCORE 1
#endif

#ifndef MISMATCH_SCORE
#define MISMATCH_SCORE -1
#endif

#ifndef GAP_PENALTY
#define GAP_PENALTY -2
#endif

void initialize_matrix(vector<vector<int>>& matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        matrix[i][0] = i * GAP_PENALTY;
    }
    for (int j = 0; j < cols; j++) {
        matrix[0][j] = j * GAP_PENALTY;
    }
}

void fill_matrix(vector<vector<int>>& matrix, const string& seq1, const string& seq2) {
    for (int i = 1; i < seq1.length() + 1; i++) {
        for (int j = 1; j < seq2.length() + 1; j++) {
            int score_diag = matrix[i-1][j-1] + (seq1[i-1] == seq2[j-1] ? MATCH_SCORE : MISMATCH_SCORE);
            int score_up = matrix[i-1][j] + GAP_PENALTY;
            int score_left = matrix[i][j-1] + GAP_PENALTY;
            matrix[i][j] = max({score_diag, score_up, score_left});
        }
    }
}

vector<pair<string, string>> traceback_all(const vector<vector<int>>& matrix, const string& seq1, const string& seq2, int i, int j) {
    if (i == 0 && j == 0) {
        return {{"", ""}};
    }
    vector<pair<string, string>> alignments;
    if (i > 0 && j > 0 && matrix[i][j] == matrix[i-1][j-1] + (seq1[i-1] == seq2[j-1] ? MATCH_SCORE : MISMATCH_SCORE)) {
        auto previous = traceback_all(matrix, seq1, seq2, i-1, j-1);
        for (auto &p : previous) {
            alignments.push_back({p.first + seq1[i-1], p.second + seq2[j-1]});
        }
    }
    if (i > 0 && matrix[i][j] == matrix[i-1][j] + GAP_PENALTY) {
        auto previous = traceback_all(matrix, seq1, seq2, i-1, j);
        for (auto &p : previous) {
            alignments.push_back({p.first + seq1[i-1], p.second + '-'});
        }
    }
    if (j > 0 && matrix[i][j] == matrix[i][j-1] + GAP_PENALTY) {
        auto previous = traceback_all(matrix, seq1, seq2, i, j-1);
        for (auto &p : previous) {
            alignments.push_back({p.first + '-', p.second + seq2[j-1]});
        }
    }
    return alignments;
}

int main() {
    string seq1, seq2;
    cin >> seq1 >> seq2;

    vector<vector<int>> matrix(seq1.length() + 1, vector<int>(seq2.length() + 1, 0));
    initialize_matrix(matrix, seq1.length() + 1, seq2.length() + 1);
    fill_matrix(matrix, seq1, seq2);
    int score_final = matrix[seq1.length()][seq2.length()];

    auto alignments = traceback_all(matrix, seq1, seq2, seq1.length(), seq2.length());

    ofstream result_file("alignment_results.txt");
    result_file << "Final Score: " << score_final << "\n";
    result_file << "Matrix of Scores:\n";
    for (auto& row : matrix) {
        for (int value : row) {
            result_file << setw(4) << value;
        }
        result_file << "\n";
    }
    result_file << "Number of Alignments Produced: " << alignments.size() << "\n";
    result_file << "Alignments:\n";
    for (const auto& alignment : alignments) {
        result_file << alignment.first << "\n" << alignment.second << "\n\n";
    }
    result_file.close();

    return 0;
}