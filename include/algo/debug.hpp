#pragma once

#include <bitset>
#include <complex>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define debug(...) algo::debug_impl(__func__, __LINE__, __VA_ARGS__)

namespace algo {

template <class Int> requires std::integral<Int>
void print(Int value) {
    std::cout << value;
}

template <class Float> requires std::floating_point<Float>
void print(Float value) {
    std::cout << value;
}

template <typename T>
void print(std::complex<T> value) {
    std::cout << value.real() << '+' << value.imag() << 'i';
}

void print(std::monostate) {}

template <class T>
void print(T const* value) {
    std::cout << value;
}

template <class T>
void print(std::basic_string<T> const& value) {
    std::cout << "\"" << value << '"';
}

template <class T>
void print(std::basic_string_view<T> value) {
    std::cout << "str[" << value << ']';
}

template <size_t N>
void print(std::bitset<N> const& value) {
    std::cout << "bits[" << value << ']';
}

template <class T, class U>
void print(std::pair<T, U> const& value) {
    std::cout << '(';
    print(value.first);
    std::cout << ", ";
    print(value.second);
    std::cout << ')';
}

template <class Rng> requires std::ranges::range<Rng>
struct RangeFormat {
    static const char obracket = '[';
    static const char cbracket = ']';
    static inline const std::string separator = ", ";
};

template <class T>
struct RangeFormat<std::set<T>> {
    static const char obracket = '{';
    static const char cbracket = '}';
    static inline const std::string separator = ", ";
};

template <class Key, class T>
struct RangeFormat<std::map<Key, T>> {
    static const char obracket = '{';
    static const char cbracket = '}';
    static inline const std::string separator = ", ";
};

template <class Rng> requires std::ranges::range<Rng>
void print(Rng&& rng);

template <class Rng> requires std::ranges::range<Rng>
void print_range(Rng&& rng) {
    using Fmt = RangeFormat<std::decay_t<Rng>>;
    if (std::cbegin(rng) == std::cend(rng)) {
        return;
    }
    print(*std::cbegin(rng));
    for (auto it = std::next(std::cbegin(rng)); it != std::cend(rng); ++it) {
        std::cout << Fmt::separator; 
        print(*it); 
    }
}

template <class Rng> requires std::ranges::range<Rng>
void print(Rng&& rng) {
    using Fmt = RangeFormat<std::decay_t<Rng>>;
    std::cout << Fmt::obracket;
    print_range(std::forward<Rng>(rng));
    std::cout << Fmt::cbracket;
}

template <class T>
void println(T const& value) {
    print(value);
    std::cout << '\n';
}

template <class ...Args>
void debug_print_many(Args&&... args) {
    std::ios_base::fmtflags old_flags(std::cout.flags());
    std::cout << std::fixed << std::setprecision(9);
    (println(std::forward<Args>(args)), ...); 
    std::cout.flags(old_flags);
}

template <class ...Args>
void debug_impl(std::string const& funcname, size_t line, Args&&... args) {
    std::cout << ANSI_COLOR_YELLOW;
    std::cout << "[DEBUG at " << funcname << ':' << line << "]\n";
    std::cout << ANSI_COLOR_GREEN;
    debug_print_many(std::forward<Args>(args)...);
    std::cout << ANSI_COLOR_RESET;
    std::cout.flush();
}

}
