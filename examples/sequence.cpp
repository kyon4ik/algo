#include <algo/sequence.hpp>
#include <iostream>
#include <vector>

void lcs() {
    std::cout << "Enter two strings:\n";
    std::string s, t;
    std::cin >> s >> t;
    auto res = algo::longest_common_subseq(s.begin(), s.end(), t.begin(), t.end()); 
    std::cout << "Longest common subsequence length: " << res.size() << "\n";
    std::cout << "Longest common subsequence: ";
    for (auto&& [ind1, ind2] : res) {
        std::cout << t[ind2]; 
    }
    std::cout << "\n";
}

void lis() {
    std::cout << "Enter integer numbers: ";
    std::vector<int> nums;
    do {
        int x;
        std::cin >> x;
        nums.push_back(x);
    } while (std::cin.get() != '\n');
    auto res = algo::longest_increasing_subseq(nums.begin(), nums.end());
    std::cout << "Longest increasing subsequence length: " << res.size() << "\n";
    std::cout << "Longest increasing subsequence: "; 
    for (auto&& el : res) {
        std::cout << nums[el] << " ";
    }
    std::cout << "\n";
}

int main() {
    // lcs();
    lis();
}
