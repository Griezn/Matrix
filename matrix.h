#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cassert>

template <typename T>
class matrix{
    matrix(int rows, int columns);

    int rows, columns;

    T& operator[](int i, int j);

    matrix<T>& operator+(const matrix<T>& matrix1);
    matrix<T>& operator+=(const matrix<T>& matrix1);

    matrix<T>& operator*(T scale);
    matrix<T>& operator*=(T scale);

    matrix<T>& operator*(const matrix<T>& matrix1);

    matrix<T>& transpose();

    T determinant();

    void vectorToMatrix(std::vector<T> vector);

private:
    std::vector<T> items;
};

template <typename T>
matrix<T>::matrix(int rows, int columns) : rows(rows), columns(columns) {
    assert(rows != 0 and columns != 0);
    items.resize(rows * columns);
}

// TODO: 99% shore this doesn't return the right value
template<typename T>
T &matrix<T>::operator[](int i, int j) {
    assert(i <= rows and j <= columns);
    return items[i*columns + j];
}

template<typename T>
matrix<T> &matrix<T>::operator+(const matrix<T> &matrix1) {
    assert(this->rows == matrix1.rows and this->columns == matrix1.columns);
    matrix<T> matrix2(this->rows, this->columns);

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            matrix2[i, j] = this[i, j] + matrix1[i, j];
        }
    }

    return *matrix2;
}

template<typename T>
matrix<T> &matrix<T>::operator+=(const matrix<T> &matrix1) {
    assert(this->rows == matrix1.rows and this->columns == matrix1.columns);

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            this[i, j] = this[i, j] + matrix1[i, j];
        }
    }

    return *this;
}

template<typename T>
matrix<T> &matrix<T>::operator*(const T scale) {
    matrix<T> matrix1(this->rows, this->columns);

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            matrix1[i, j] = this[i, j] * scale;
        }
    }

    return *matrix1;
}

template<typename T>
matrix<T> &matrix<T>::operator*=(const T scale) {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            this[i, j] = this[i, j] * scale;
        }
    }

    return *this;
}

// TODO: update the indexing (not complete)
template<typename T>
matrix<T> &matrix<T>::operator*(const matrix<T> &matrix1) {
    assert(this->columns == matrix1.rows);
    matrix<T> matrix2(this->rows, matrix1.columns);

    for (int i = 0; i < this; ++i) {
        for (int j = 0; j < this; ++j) {
            matrix2[i, j] = this[] * matrix1[];
        }
    }

    return *matrix2;
}

template<typename T>
matrix<T> &matrix<T>::transpose() {
    matrix<T> matrix1(this->columns, this->rows);

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            matrix1[j, i] = this[i, j];
        }
    }

    return *matrix1;
}

template<typename T>
T matrix<T>::determinant() {
    assert(this->rows == this->columns);
    T sum;

}

template<typename T>
void matrix<T>::vectorToMatrix(const std::vector<T> vector) {
    assert(items.size() == vector.size());
    for (auto &item : vector) {
        items.template emplace_back(item);
    }
}

#endif //MATRIX_H