#pragma once

#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

namespace algo 
{

using IndPair = std::pair<size_t, size_t>;

template <class It1, class It2>
std::vector<IndPair> longest_common_subseq(It1 first1, It1 last1, It2 first2, It2 last2) {
    size_t n = std::distance(first1, last1);
    size_t m = std::distance(first2, last2);
    std::vector<std::vector<size_t>> lcs(n + 1, std::vector<size_t>(m + 1));
    std::vector<std::vector<IndPair>> anc(n + 1, std::vector<IndPair>(m + 1));

    size_t i = 0;
    for (It1 seq1 = first1; seq1 != last1; ++seq1, ++i) {
        size_t j = 0;
        for (It2 seq2 = first2; seq2 != last2; ++seq2, ++j) {
            if (*seq1 == *seq2) {
                lcs[i + 1][j + 1] = lcs[i][j] + 1;
                anc[i + 1][j + 1] = {i, j}; 
            } else { 
                if (lcs[i + 1][j] > lcs[i][j + 1]) {
                    lcs[i + 1][j + 1] = lcs[i + 1][j];
                    anc[i + 1][j + 1] = anc[i + 1][j];
                } else {
                    lcs[i + 1][j + 1] = lcs[i][j + 1];
                    anc[i + 1][j + 1] = anc[i][j + 1];
                }
            }
        }
    }

    // Backtracking
    IndPair indices = anc[n][m];
    std::vector<IndPair> res;
    while (indices.first > 0 && indices.second > 0) {
        res.emplace_back(indices.first, indices.second);
        indices = anc[indices.first][indices.second];
    }
    std::reverse(res.begin(), res.end());
    return res;
}

template <class It, class T = typename std::iterator_traits<It>::value_type>
std::vector<size_t> longest_increasing_subseq(It first, It last) {
    size_t n = std::distance(first, last); 
    std::vector<T> min_tail_of_len(n + 1, std::numeric_limits<T>::max());
    std::vector<size_t> tail_ind_of_len(n + 1);
    std::vector<size_t> anc(n);
    min_tail_of_len[0] = std::numeric_limits<T>::min();

    size_t i = 0;
    for (It it = first; it != last; ++it, ++i) {
        auto gt = std::upper_bound(min_tail_of_len.begin(), min_tail_of_len.end(), *it);
        if (gt == min_tail_of_len.end()) break;
        size_t j = gt - min_tail_of_len.begin();
        if (*it > min_tail_of_len[j - 1]) {
            min_tail_of_len[j] = *it;
            tail_ind_of_len[j] = i + 1;
            anc[i] = tail_ind_of_len[j - 1];
        }
    }
    
    // Backtracking
    size_t pos = 0;
    std::vector<size_t> res;
    for (size_t j = n; j > 0; --j) {
        if (min_tail_of_len[j] < std::numeric_limits<T>::max()) {
            pos = tail_ind_of_len[j];
            break;
        }
    }
    while (pos > 0) {
        res.push_back(pos - 1);
        pos = anc[pos - 1];
    }
    std::reverse(res.begin(), res.end());
    return res;
}

}
