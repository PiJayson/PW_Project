#include "../headers/Matrix.h"
#include <climits>
#include <cmath>

void Matrix::luDecomposition(std::vector<std::vector<float>>& L,
                     std::vector<std::vector<float>>& U) const {
    int n = matrix.size();

    L.resize(n, std::vector<float>(n, 0));
    U.resize(n, std::vector<float>(n, 0));

    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;  // Diagonal of L is 1
        for (int j = i; j < n; ++j) {
            U[i][j] = matrix[i][j];
            for (int k = 0; k < i; ++k) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
        for (int j = i + 1; j < n; ++j) {
            L[j][i] = matrix[j][i];
            for (int k = 0; k < i; ++k) {
                L[j][i] -= L[j][k] * U[k][i];
            }
            L[j][i] /= U[i][i];
        }
    }
}

long long Matrix::determinant() {
    if (width != height) {
        return LONG_LONG_MIN;
    }

    std::vector<std::vector<float>> L, U;
    luDecomposition(L, U);

    double det = 1.0;
    for (int i = 0; i < width; ++i) {
        det *= U[i][i];
    }

    return std::round(det);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // Check for self-assignment to avoid unnecessary work

        // Clear current matrix data, if any
        matrix.clear();

        // Copy dimensions
        width = other.width;
        height = other.height;

        // Set vectors
        matrix.resize(height);
        for (int i = 0; i < height; i++) {
            matrix[i].resize(width);
            matrix[i] = other.matrix[i];
        }
    }

    return *this;
}

bool operator+(Matrix& A, const Matrix& B) {
    if (A.width != B.width || A.height != B.height) return false;

    // Perform element-wise addition
    for (int i = 0; i < A.height; ++i) {
        for (int j = 0; j < A.width; ++j) {
            A.matrix[i][j] += B.matrix[i][j];
        }
    }

    return true;
}

bool operator*(Matrix& A, const Matrix& B) {
    if (A.width != B.height) return false;

    Matrix result;
    result.width = B.width;
    result.height = A.height;
    result.matrix.resize(result.height, std::vector<int>(result.width, 0));

    for (int i = 0; i < A.height; ++i) {
        for (int j = 0; j < B.width; ++j) {
            int sum = 0;
            for (int k = 0; k < A.width; ++k) {
                sum += A.matrix[i][k] * B.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }

    A = result;

    return true;
}

bool operator^(Matrix& A, long long p) {
    if (A.width != A.height) {
        return false;
    }

    Matrix result;
    result.set_identity(A.width);

    while (p > 0) {
        if (p % 2 == 1) {
            result * A;
        }

        A * A;  // Square A for the next iteration
        p /= 2;
    }

    A = result;  // Update the current instance with the result
    return true;
}

std::ostream& operator<<(std::ostream& stream, const Matrix& A) {
    A.print_matrix();

    return stream;
}

std::istream& operator>>(std::istream& stream, Matrix& A) {
    stream >> A.width >> A.height;

    A.matrix.resize(A.height);

    for (auto& v : A.matrix) {
        v.resize(A.width);

        for (int& i : v) {
            stream >> i;
        }
    }

    return stream;
}
