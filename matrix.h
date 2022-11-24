#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <array>
#include <vector>
#include <iterator>
#include <cstddef>


template<typename T, size_t X, size_t Y>
struct Matrix{
public:
    /// Constructor for the Matrix class.
    /// \param a The array tot convert to an matrix.
    explicit Matrix(const std::array<T, X*Y> &a);

    /// Constructor for the Matrix class.
    /// \param v The vector tot convert to an matrix.
    explicit Matrix(const std::vector<T> &v);

    //========== OPERATORS ===========//
    /// Operator to access a certain element in the matrix.
    /// \param x The row of the element
    /// \param y The column of the element
    /// \return The element at the specified position
    constexpr T& operator[](size_t x, size_t y);

    //========= ITERATOR ===========//
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
Matrix<T, X, Y>::Matrix(const std::array<T, X * Y> &a) {
    for (int i = 0; i < X * Y; ++i) {
        this->_a[i] = a[i];
    }
}

template<typename T, size_t X, size_t Y>
Matrix<T, X, Y>::Matrix(const std::vector<T> &v) {
    assert(v.size() == X*Y);
    for (int i = 0; i < X * Y; ++i) {
        this->_a[i] = v[i];
    }
}

template<typename T, size_t X, size_t Y>
constexpr T &Matrix<T, X, Y>::operator[](size_t x, size_t y){
    assert(x > 0 and x <= X);
    assert(y > 0 and y <= Y);
    return _a[(x - 1) * Y + (y - 1)];
}


#endif //MATRIX_H