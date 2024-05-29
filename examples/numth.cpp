#include <algo/numth.hpp>
#include <iostream>

int main() {
    std::cout << "Primes under 100:\n";
    for (auto&& prime : algo::seive(100)) {
        std::cout << prime << " ";
    }
    std::cout << "\n";
    std::cout << "Lowest divisors under 100:\n";
    for (auto&& div : algo::lowest_divisor(100)) {
        std::cout << div << " ";
    }
    std::cout << "\n";
}
