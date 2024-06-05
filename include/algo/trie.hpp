#pragma once

#include <array>
#include <vector>
namespace algo 
{

template <class T, int BITS = sizeof(T) * 8>
class BinaryTrie {
public:    
    BinaryTrie(size_t n) : cnt(n * BITS), data(n * BITS, {-1, -1}) {}

    void add(T x) {
        int current = 0;
        for (int i = BITS-1; i >= 0; --i) {
            cnt[current]++;
            auto bit = (x >> i) & 1;
            auto next = data[current][bit]; 
            if (next == -1) {
                data[current][bit] = ++last;
                next = last;
            }
            current = next;
        }
        cnt[current]++;
    }

    bool remove(T x) {
        if (!contains(x)) return false;
        int current = 0;
        for (int i = BITS-1; i >= 0; --i) {
            cnt[current]--;
            auto bit = (x >> i) & 1;
            current = data[current][bit]; 
        }
        cnt[current]--;
        return true;
    }

    bool empty() const {
        return cnt[0] == 0;
    }
    
    bool contains(T x) const {
        int current = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            auto bit = (x >> i) & 1;
            auto next = data[current][bit]; 
            if (next == -1 || cnt[next] == 0) 
                return false;
            current = next;
        }
        return true;
    }
    
    T closest(T x) const {
        int res = 0;
        int current = 0;
        for (int i = BITS-1; i >= 0; --i) {
            auto bit = (x >> i) & 1;
            auto next = data[current][bit]; 
            if (next == -1 || cnt[next] == 0) bit ^= 1;
            res |= (bit << i);
            current = data[current][bit];
        }
        return res;
    }
private:
    int last = 0;
    std::vector<int> cnt;
    std::vector<std::array<int, 2>> data; 
};

}
