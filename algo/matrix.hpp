#pragma once

#include <array>
#include <cstddef>
#include <limits>
#include <ostream>
#include <fmt/core.h>
#include <iostream>

namespace algo {

template <typename T, std::size_t N, std::size_t M = N> 
class Matrix {
public:
    constexpr Matrix() = default;
    
    constexpr Matrix(std::array<T, N * M> ar) {
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                rows[i][j] = ar[i * N + j];
            }
        }
    }

    constexpr Matrix<T, M, N> transposed() {
        Matrix<T, M, N> res;
        for (std::size_t r = 0; r < N; ++r) {
            for (std::size_t c = 0; c < M; ++c) {
                res[{c, r}] = rows[r][c];
            }
        }
        return res;
    }

    constexpr const T& operator[](std::pair<std::size_t, std::size_t> pos) const {
        return rows[pos.first][pos.second];
    }
    
    constexpr T& operator[](std::pair<std::size_t, std::size_t> pos) {
        return rows[pos.first][pos.second];
    }

    static constexpr Matrix Zero() {
        Matrix res; 
        for (std::size_t r = 0; r < N; ++r) {
            std::array<T, M> row;
            row.fill(T(0));
            res.rows[r].swap(row);
        }
        return res;
    }
    
    static constexpr Matrix Id() {
        Matrix res = Zero(); 
        for (std::size_t r = 0; r < N; ++r) {
            res.rows[r][r] = T(1);
        }
        return res;
    }
    
    friend constexpr bool operator==(const Matrix& lhs, const Matrix& rhs) {
        return lhs.rows == rhs.rows;
    }
    
    template <typename S>
    friend constexpr Matrix operator*(const Matrix& mat, const S& scalar) {
        Matrix res;
        for (std::size_t r = 0; r < N; ++r) {
            for (std::size_t c = 0; c < M; ++c) {
                res.rows[r][c] = mat.rows[r][c] * scalar;
            }
        }
        return res;
    }
    
    template <typename S>
    friend constexpr Matrix operator/(const Matrix& mat, const S& scalar) {
        Matrix res;
        for (std::size_t r = 0; r < N; ++r) {
            for (std::size_t c = 0; c < M; ++c) {
                res.rows[r][c] = mat.rows[r][c] / scalar;
            }
        }
        return res;
    }
    
    friend constexpr Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
        Matrix res;
        for (std::size_t r = 0; r < N; ++r) {
            for (std::size_t c = 0; c < M; ++c) {
                res.rows[r][c] = lhs.rows[r][c] + rhs.rows[r][c];
            }
        }
        return res;
    }
    
    friend constexpr Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
        Matrix res;
        for (std::size_t r = 0; r < N; ++r) {
            for (std::size_t c = 0; c < M; ++c) {
                res.rows[r][c] = lhs.rows[r][c] - rhs.rows[r][c];
            }
        }
        return res;
    }
    
    template <std::size_t K>
    friend constexpr Matrix<T, N, K> operator*(const Matrix& lhs, const Matrix<T, M, K>& rhs) {
        auto res = Matrix<T, N, K>::Zero();
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t k = 0; k < K; ++k) {
                for (std::size_t j = 0; j < M; ++j) {
                    res[{i, k}] += lhs.rows[i][j] * rhs[{j, k}];
                }
            }
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& val) {
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                os << val.rows[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }

    friend Matrix<T, N, M> ref(const Matrix<T, N, M>& mat_orig) {
        Matrix<T, N, M> mat(mat_orig);

        for (size_t j = 0; j < N; ++j) {
            auto min_val = std::numeric_limits<T>::max();
            auto min_row = 0;
            for (size_t i = j; i < N; ++i) {
                if (mat.rows[i][j] != 0 && abs(mat.rows[i][j]) < min_val) {
                    min_val = abs(mat.rows[i][j]);
                    min_row = i;
                }
            }

            if (min_val == std::numeric_limits<T>::max())
                continue;

            fmt::println("col: {}, min_row: {}, min_val: {}", j, min_row, mat.rows[min_row][j]);
            std::cout << mat << "\n";
            
            for (size_t i = 0; i < N; ++i) {
                if (i == min_row || mat.rows[i][j] == 0) continue;
            
                auto factor = mat.rows[i][j] / mat.rows[min_row][j];                      
                for (size_t k = j; k < N; ++k) {
                    mat.rows[i][k] -= factor * mat.rows[min_row][k];
                }
            }
            
            for (size_t k = j; k < N; ++k) {
                std::swap(mat.rows[min_row][k], mat.rows[j][k]);
            }
        }

        return mat;
    }

private:
    std::array<std::array<T, M>, N> rows;
};

template <typename T, std::size_t N>
using Vector = Matrix<T, 1, N>;

}
