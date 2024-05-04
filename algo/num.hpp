#pragma once

namespace algo {

template <typename T>
struct GcdExt {
    T gcd;
    T x, y;
};

// a*x + b*y = gcd(a,b)
template <typename T>
constexpr GcdExt<T> gcd_ext(const T& a, const T& b) {
    if (a == 0) {
        return {.gcd = b, .x = 0, .y = 1};
    }
    auto res = gcd_ext(b % a, a);
    return {
        .gcd = res.gcd, 
        .x = res.y - (b / a) * res.x, 
        .y = res.x
    };
}

template <typename T, typename Num>
constexpr T binpow(T a, Num n, T id = 1) {
    T res = id;
    while (n > 0) {
        if (n & 1) {
            res = res * a;
        }
        a = a * a;
        n >>= 1;
    }
    return res;
}

template <typename T>
constexpr T euler(const T& n) {
    T res = n;
    for (T d = 2; d * d <= n; ++d) {
        if (n % d == 0) {
            while (n % d == 0) {
                n /= d;
            }
            res -= res / d;
        }
    }
    if (n > 1) {
        res -= res / n;
    }
    return res;
}

}
