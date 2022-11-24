#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <array>
#include <vector>
#include <iterator>
#include <cstddef>


template<typename T, size_t X, size_t Y>
/// A struct to represent a matrix.
/// \tparam T Type of the values stored in the matrix.
/// \tparam X Number of rows.
/// \tparam Y Number of columns.
struct Matrix{
public:
    /// Default constructor for the matrix struct.
    Matrix() = default;

    /// Constructor for the Matrix struct.
    /// \param a The array tot convert to an matrix.
    explicit Matrix(const std::array<T, X*Y> &a) {
        for (int i = 0; i < X * Y; ++i) {
            this->_a[i] = a[i];
        }
    }

    /// Constructor for the Matrix struct.
    /// \param v The vector tot convert to an matrix.
    explicit Matrix(const std::vector<T> &v) {
        assert(v.size() == X*Y);
        for (int i = 0; i < X * Y; ++i) {
            this->_a[i] = v[i];
        }
    }

    /// Turns the rows into columns and vice versa.
    /// \return The transposed matrix.
    Matrix<T, Y, X> transpose(){
        Matrix<T, Y, X> newMatrix{this->_a};
        return newMatrix;
    }

    /// Operator to access a certain element in the matrix.
    /// \param x The row of the element
    /// \param y The column of the element
    /// \return The element at the specified position
    constexpr T& operator[](size_t x, size_t y) {
        assert(x > 0 and x <= X);
        assert(y > 0 and y <= Y);
        return _a[(x - 1) * Y + (y - 1)];
    }

    ///============ ITERATOR ============///
    struct Iterator{
        using iterator_category = std::forward_iterator_tag;
        using differe_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(pointer ptr) : _ptr(ptr){}

        reference operator*()const {return *_ptr;}
        pointer operator->() {return _ptr;}

        Iterator& operator++() { _ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a._ptr == b._ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a._ptr != b._ptr; };

    private:
        pointer _ptr;
    };

    Iterator begin() {return Iterator(&_a[0]);}
    Iterator end() {return Iterator(&_a[X*Y]);}

private:
    std::array<T, X*Y> _a;
};

template<typename T, size_t X, size_t Y>
/// Adds two matrices with each other.
/// \tparam T Type of the values stored in the matrices.
/// \tparam X Number of rows.
/// \tparam Y Number of columns.
/// \param m1 First matrix to add.
/// \param m2 Second matrix to add.
/// \return The resulting matrix.
constexpr Matrix<T, X, Y> operator+(Matrix<T, X, Y>& m1, Matrix<T, X, Y>& m2) {
    Matrix<T, X, Y> newMatrix{};

    for (int i = 1; i <= X; ++i) {
        for (int j = 1; j <= Y; ++j) {
            newMatrix[i, j] = m1[i, j] + m2[i, j];
        }
    }

    return newMatrix;
}

template<typename T, size_t X, size_t Y>
/// Adds a matrix to an other matrix.
/// \tparam T Type of the values stored in the matrices.
/// \tparam X Number of rows.
/// \tparam Y Number of columns.
/// \param m1 First matrix to add.
/// \param m2 Second matrix to add.
/// \return Reference to the matrix with the new values.
constexpr Matrix<T, X, Y> &operator+=(Matrix<T, X, Y>& m1, Matrix<T, X, Y>& m2){

    for (int i = 1; i <= X; ++i) {
        for (int j = 1; j <= Y; ++j) {
            m1[i, j] += m2[i, j];
        }
    }

    return m1;
}

template<typename T, size_t X, size_t Y>
/// Multiplies a matrix with a scale.
/// \tparam T Type of the values stored in the matrix and type of the scale.
/// \tparam X Number of rows.
/// \tparam Y Number of columns.
/// \param scale Value to scale the matrix with.
/// \param m The matrix that is going to be scaled.
/// \return The scaled matrix.
constexpr Matrix<T, X, Y> operator*(T scale, Matrix<T, X, Y>& m){
    Matrix<T, X, Y> newMatrix{};

    for (int i = 1; i <= X; ++i) {
        for (int j = 1; j <= Y; ++j) {
            newMatrix[i, j] = scale * m[i, j];
        }
    }

    return newMatrix;
}

template<typename T, size_t X, size_t Y>
/// Multiplies a matrix with a scale.
/// \tparam T Type of the values stored in the matrix and type of the scale.
/// \tparam X Number of rows.
/// \tparam Y Number of columns.
/// \param scale Value to scale the matrix with.
/// \param m The matrix that is going to be scaled.
/// \return The scaled matrix.
constexpr Matrix<T, X, Y> operator*(Matrix<T, X, Y>& m, T scale){
    Matrix<T, X, Y> newMatrix{};

    for (int i = 1; i <= X; ++i) {
        for (int j = 1; j <= Y; ++j) {
            newMatrix[i, j] = scale * m[i, j];
        }
    }

    return newMatrix;
}

template<typename T, size_t X, size_t Y, size_t Z>
/// Multiplies two matrices with each other.
/// \tparam T Type of the values stored in the matrices.
/// \tparam X Number of rows in the first matrix.
/// \tparam Y Number of columns in the second matrix.
/// \tparam Z Number of columns in the first matrix and number of rows in the second matrix.
/// \param m1 The first matrix to be multiplied.
/// \param m2 The second matrix to be multiplied.
/// \return A X by Y matrix filled with the dot products of the corresponding row of m1 with the corresponding column of m2.
constexpr Matrix<T, X, Y> operator*(Matrix<T, X, Z>& m1, Matrix<T, Z, Y>& m2) {
    Matrix<T, X, Y> newMatrix{};

    for (int i = 1; i <= X; ++i) {
        for (int j = 1; j <= Y; ++j) {
            T sum = 0;
            for (int k = 1; k <= Z; ++k) {
                sum += m1[i, k] * m2[k, j];
            }
            newMatrix[i, j] = sum;
        }
    }

    return newMatrix;
}

#endif //MATRIX_H