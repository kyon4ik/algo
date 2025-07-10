#pragma once

#include <bitset>
#include <iostream>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

namespace algo 
{

template <class Ar> requires std::is_arithmetic_v<Ar>
void read_impl(Ar& value) {
    std::cin >> value;
}

template <class T>
void read_impl(std::basic_string<T>& value) {
    std::cin >> value;
}

template <size_t N>
void read_impl(std::bitset<N>& value) {
    std::cin >> value;
}

template <class T, class U>
void read_impl(std::pair<T, U>& value) {
    read_impl(value.first);
    read_impl(value.second);
}

template <class T, size_t N>
void read_impl(std::array<T, N>& rng) {
    for (size_t i = 0; i < N; ++i) {
        read_impl(rng[i]);
    }
}

template <class T>
void read_impl(std::vector<T>& rng) {
    for (size_t i = 0; i < rng.size(); ++i) {
        read_impl(rng[i]);
    }
}

template <class ...Args>
void read(Args&&... args) {
    (read_impl(std::forward<Args>(args)), ...); 
}

template <class T>
void write_impl(T& value, std::string_view end) {
    std::cout << end << value;
}

template <class T>
void write_impl(T& value, char end) {
    std::cout << end << value;
}

template <class T>
void write_impl(T& value) {
    std::cout << value;
}

template <class Head, class ...Rest>
void write_head_then_rest(Head&& head, Rest&&... rest) {
    write_impl(std::forward<Head>(head)); 
    (write_impl(std::forward<Rest>(rest), ' '), ...); 
}

template <class ...Args>
inline void write(Args&&... args) {
    write_head_then_rest(std::forward<Args>(args)...);
}

template <class ...Args>
inline void writeln(Args&&... args) {
    write(std::forward<Args>(args)...);
    std::cout << '\n';
}

}
