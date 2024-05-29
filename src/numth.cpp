#include <algo/numth.hpp>
#include <cstdint>

namespace algo
{

std::vector<int> seive(size_t limit) {
    std::vector<uint8_t> is_prime(limit + 1, true);
    std::vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (size_t i = 2; i * i <= limit; ++i) {
        if (!is_prime[i]) 
            continue;
        for (size_t j = i * i; j <= limit; j += i) {
            is_prime[j] = false;
        }
    }
    for (size_t i = 2; i <= limit; ++i) {
        if (is_prime[i])
            primes.push_back(i);
    }
    return primes;
}

std::vector<int> lowest_divisor(size_t limit) {
    std::vector<int> lowest_div(limit + 1);
    std::vector<int> primes;
    lowest_div[0] = lowest_div[1] = 1;
    for (size_t i = 2; i <= limit; ++i) {
        if (lowest_div[i] == 0) {
            lowest_div[i] = i;
            primes.push_back(i);
        }
        for (auto&& prime : primes) {
            if (prime > lowest_div[i])
                break;
            if (i * prime > limit)
                break;
            lowest_div[i * prime] = prime;
        }
    }
    return lowest_div;
}

}
