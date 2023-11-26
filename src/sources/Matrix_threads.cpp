#include "../headers/Matrix.h"
#include <climits>
#include <cmath>
#include <thread>

#ifndef N_THREADS
#define N_THREADS 8
#endif


void Matrix::luDecomposition(std::vector<std::vector<float>>& L, std::vector<std::vector<float>>& U) const {
    int n = matrix.size();
    int n_threads = std::min(N_THREADS, n);
    L.resize(n, std::vector<float>(n, 0));
    U.resize(n, std::vector<float>(n, 0));

    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
        std::vector<std::thread> threads(n_threads);

        // First loop
        for (int t = 0; t < n_threads; ++t) {
            threads[t] = std::thread([&, t, i, n]() {
                for (int j = i + t; j < n; j += n_threads) {
                    U[i][j] = matrix[i][j];
                    float sum = 0;
                    for (int k = 0; k < i; ++k) {
                        sum -= L[i][k] * U[k][j];
                    }
                    U[i][j] -= sum;
                }
            });
        }

        for (auto& th : threads) {
            if (th.joinable()) th.join();
        }

        // Second loop
        for (int t = 0; t < n_threads; ++t) {
            threads[t] = std::thread([&, t, i, n]() {
                for (int j = i + 1 + t; j < n; j += n_threads) {
                    L[j][i] = matrix[j][i];
                    float sum = 0;
                    for (int k = 0; k < i; ++k) {
                        sum -= L[j][k] * U[k][i];
                    }
                    L[j][i] -= sum;

                    L[j][i] /= U[i][i];
                }
            });
        }

        for (auto& th : threads) {
            if (th.joinable()) th.join();
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
        matrix.clear();
        width = other.width;
        height = other.height;
        matrix.resize(height);

        std::vector<std::thread> threads(N_THREADS);

        for (int t = 0; t < N_THREADS; ++t) {
            threads[t] = std::thread([&](int startRow) {
                for (int i = startRow; i < height; i += N_THREADS) {
                    matrix[i].resize(width);
                    matrix[i] = other.matrix[i];
                }
            }, t);
        }

        for (auto& th : threads) {
            if (th.joinable()) th.join();
        }
    }

    return *this;
}


bool operator+(Matrix& A, const Matrix& B) {
    if (A.width != B.width || A.height != B.height) return false;

    std::vector<std::thread> threads(N_THREADS);

    for (int t = 0; t < N_THREADS; ++t) {
        threads[t] = std::thread([&](int startRow) {
            for (int i = startRow; i < A.height; i += N_THREADS) {
                for (int j = 0; j < A.width; ++j) {
                    A.matrix[i][j] += B.matrix[i][j];
                }
            }
        }, t);
    }

    for (auto& th : threads) {
        if (th.joinable()) th.join();
    }

    return true;
}

bool operator*(Matrix& A, const Matrix& B) {
    if (A.width != B.height) return false;

    Matrix result;
    result.width = B.width;
    result.height = A.height;
    result.matrix.resize(result.height, std::vector<int>(result.width, 0));

    std::vector<std::thread> threads(N_THREADS);

    for (int t = 0; t < N_THREADS; ++t) {
        threads[t] = std::thread([&](int startRow) {
            for (int i = startRow; i < A.height; i += N_THREADS) {
                for (int j = 0; j < B.width; ++j) {
                    int sum = 0;
                    for (int k = 0; k < A.width; ++k) {
                        sum += A.matrix[i][k] * B.matrix[k][j];
                    }
                    result.matrix[i][j] = sum;
                }
            }
        }, t);
    }

    for (auto& th : threads) {
        if (th.joinable()) th.join();
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

        A * A;
        p /= 2;
    }

    A = result;
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
