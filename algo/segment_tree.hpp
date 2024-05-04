#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

namespace algo {

constexpr inline size_t next_power_of_two(std::uint32_t num) noexcept {
    auto lz = __builtin_clz(num - 1);
    assert(lz != 0);
    return 1ul << (32 - lz);
}

template <typename T>
class SegmentTree {
    using V = T::ValueType;

public:
    SegmentTree(size_t n, const V& val) : data(2 * n) {
        std::fill(data.begin() + n, data.end(), T(val)); 
        for (size_t i = n - 1; i > 0; --i) {
            data[i] = data[i << 1] + data[(i << 1) | 1];
        }
    }
    
    SegmentTree(const std::vector<V>& arr) : data(2 * arr.size()) {
        std::copy(arr.begin(), arr.end(), data.begin() + arr.size());
        for (size_t i = arr.size() - 1; i > 0; --i) {
            data[i] = data[i << 1] + data[(i << 1) | 1];
        }
    }

    void update_point(size_t pos, const V& val) {
        pos += data.size() >> 1;
        data[pos] = T(val);
        for (pos >>= 1; pos > 0; pos >>= 1) {
            data[pos] = data[pos << 1] + data[(pos << 1) | 1];
        }
    }
    
    // calculate on [l, r)
    T get(size_t l, size_t r) {
        T resl{};
        T resr{};
        l += data.size() >> 1;
        r += data.size() >> 1;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + data[l++];
            if (r & 1) resr = data[--r] + resr;
        }
        return resl + resr;
    }

private:
    std::vector<T> data;
};

template <typename T, typename D>
class LazySegmentTree {
    using V = T::ValueType;

public:
    LazySegmentTree(size_t n, const V& val) 
    : data(2 * next_power_of_two(n)), 
    delayed(2 * next_power_of_two(n)) {
        size_t half = data.size() >> 1;
        std::fill(data.begin() + half, data.end(), T(val)); 
        for (size_t i = half - 1; i > 0; --i) {
            data[i] = data[i << 1] + data[(i << 1) | 1];
        }
    }
    
    LazySegmentTree(const std::vector<V>& arr) 
    : data(2 * next_power_of_two(arr.size())), 
    delayed(2 * next_power_of_two(arr.size())) {
        size_t half = data.size() >> 1;
        std::copy(arr.begin(), arr.end(), data.begin() + half);
        for (size_t i = half - 1; i > 0; --i) {
            data[i] = data[i << 1] + data[(i << 1) | 1];
        }
    }
    
    // update on [l, r)
    void update(size_t l, size_t r, const D& val) {
        raw_update(1, 0, data.size() >> 1, l, r, val); 
    }
    
    // calculate on [l, r)
    T query(size_t l, size_t r) {
        return raw_query(1, 0, data.size() >> 1, l, r);    
    }

private:
    void push(int node) {
        delayed[node << 1] = delayed[node << 1] + delayed[node];
        delayed[(node << 1) | 1] = delayed[(node << 1) | 1] + delayed[node];
        delayed[node] = D();
    }

    void pull(size_t node) {
        data[node] = (data[node << 1] * delayed[node << 1]) 
            + (data[(node << 1) | 1] * delayed[(node << 1) | 1]);
    }

    void raw_update(size_t node, size_t tl, size_t tr, size_t ql, size_t qr, const D& val) {
        if (tl >= qr || tr <= ql) return;
        if (tl >= ql && tr <= qr) {
            delayed[node] = delayed[node] + val;
            return;
        }

        push(node);
        size_t mid = tl + ((tr - tl) >> 1);
        raw_update(node << 1, tl, mid, ql, qr, val);
        raw_update((node << 1) | 1, mid, tr, ql, qr, val);
        pull(node);
    }

    T raw_query(size_t node, size_t tl, size_t tr, size_t ql, size_t qr) {
        if (tl >= qr || tr <= ql) return T{};
        if (tl >= ql && tr <= qr) {
            return data[node] * delayed[node];
        }

        push(node);
        size_t mid = tl + ((tr - tl) >> 1);
        T res = raw_query(node << 1, tl, mid, ql, qr) 
            + raw_query((node << 1) | 1, mid, tr, ql, qr);
        pull(node);
        return res;
    }
    
    std::vector<T> data;
    std::vector<D> delayed;
};

}
