#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

using v_matrix = std::vector<std::vector<int>>;

class Matrix {
private:
    int width, height;
    v_matrix matrix;

public:
    void print_matrix() const;
    void set_identity(int size);

    long long determinant();
    void luDecomposition(std::vector<std::vector<float>>& L, std::vector<std::vector<float>>& U) const;

    Matrix& operator=(const Matrix& other);
    friend bool operator+(Matrix& A, const Matrix& B);
    friend bool operator*(Matrix& A, const Matrix& B);
    friend bool operator^(Matrix& A, long long p);
    friend std::ostream& operator<<(std::ostream& stream, const Matrix& A);
    friend std::istream& operator>>(std::istream& stream, Matrix& A);
};

#endif // MATRIX_H
