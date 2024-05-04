#pragma once

#include "num.hpp"
#include <functional>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>

// Vec<T>, Svec<T, N>
// Mat<T>, Smat<T, N, M>
// Set<T>, Hashset<T>
// Map<T>, Hashmap<T>
// Treap<T>, Treapset<T>
// Fenwick<T>
// String
// i64, i32, u64, u32, u8, f32, f64, Mod<M>
// 

namespace algo {

template <typename T, T mod>
class Modulo {
    static_assert(mod > 0, 
            "mod must be greater than zero");
    static_assert(mod <= std::numeric_limits<T>::max() / 2 + 1, 
            "requires 2*(mod-1) <= MAX");
    static_assert(-mod >= std::numeric_limits<T>::min() / 2 + 1,
            "requires -2*(mod-1) >= MIN");
    
    struct NonNegNum {};

    constexpr inline Modulo(T num, NonNegNum) : rem(num % mod) {}

public:
    constexpr inline Modulo() : rem(0) {}
    
    constexpr inline Modulo(T num) 
        : rem((num % mod + mod) % mod) {}

    constexpr inline Modulo& operator=(T num) {
        rem = (num % mod + mod) % mod;
        return *this;
    }

    constexpr inline T remainder() const noexcept {
        return rem;
    }

    constexpr inline Modulo inverse() const {
        auto res = gcd_ext(rem, mod);
        if (res.gcd != 1) {
            throw std::runtime_error("Inverse: rem and mod must be coprime");
        }
        return Modulo(res.x);
    }

    constexpr inline Modulo& operator+=(const Modulo& other) {
        rem = (rem + other.rem) % mod;
        return *this;
    }
    
    constexpr inline Modulo& operator-=(const Modulo& other) {
        rem = (rem + mod - other.rem) % mod;
        return *this;
    }
    
    constexpr inline Modulo& operator*=(const Modulo& other) {
        static_assert((mod - 1) * (mod - 1) <= std::numeric_limits<T>::max(), 
                "Multiplication requires (mod-1)^2 <= MAX");
        rem = (rem * other.rem) % mod;
        return *this;
    }
    
    constexpr inline Modulo& operator/=(const Modulo& other) {
        rem = (rem * other.inverse().rem) % mod;
        return *this;
    }
    
    friend constexpr inline bool operator==(const Modulo& lhs, const Modulo& rhs) {
        return lhs.rem == rhs.rem;
    }

    friend constexpr inline auto operator<=>(const Modulo& lhs, const Modulo& rhs) {
        return lhs.rem <=> rhs.rem;
    }
    
    friend constexpr inline Modulo operator-(const Modulo& val) {
        return Modulo(mod - val.rem, NonNegNum{});
    }

    friend constexpr inline Modulo operator+(const Modulo& lhs, const Modulo& rhs) {
        return Modulo(lhs.rem + rhs.rem, NonNegNum{});
    }
    
    friend constexpr inline Modulo operator-(const Modulo& lhs, const Modulo& rhs) {
        return Modulo(lhs.rem + mod - rhs.rem, NonNegNum{});
    }

    friend constexpr inline Modulo operator*(const Modulo& lhs, const Modulo& rhs) {
        static_assert((mod - 1) * (mod - 1) <= std::numeric_limits<T>::max(), 
                "Multiplication requires (mod-1)^2 <= MAX");
        return Modulo(lhs.rem * rhs.rem, NonNegNum{});
    }
    
    friend constexpr inline Modulo operator/(const Modulo& lhs, const Modulo& rhs) {
        return lhs * rhs.inverse();
    }

    friend std::istream& operator>>(std::istream& is, Modulo& val) {
        is >> val.rem;
        val.rem %= mod;
        return is;
    }
private:
    T rem;
};

template <typename T, T mod>
std::ostream& operator<<(std::ostream& os, const Modulo<T, mod>& val) {
    return os << val.remainder();
}

}

template <typename T, T mod>
struct std::hash<algo::Modulo<T, mod>> {
    size_t operator()(const algo::Modulo<T, mod>& val) const noexcept {
        return hash<T>(val.remainder());
    }
};
