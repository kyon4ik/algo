#include <algo/sort.hpp>
#include <algorithm>
#include <cassert>
#include <random>

const int ITER_COUNT = 20;
const int N = 3000;

int main() {
    std::random_device dev;
    std::default_random_engine eng(dev());
    std::uniform_int_distribution dist(-100, 100);
    std::vector<int> v(N), test(N);
    for (int iter = 0; iter < ITER_COUNT; ++iter) {
        std::generate(v.begin(), v.end(), [&]() { return dist(eng); });
        std::copy(v.begin(), v.end(), test.begin());
        std::sort(v.begin(), v.end());
        algo::bubble_sort(test.begin(), test.end());
        assert(v == test);
    }
}
