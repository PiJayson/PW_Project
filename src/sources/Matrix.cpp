#include "../headers/Matrix.h"

void Matrix::print_matrix() const {
    for (const auto& v : matrix) {
        for (int i : v) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

void Matrix::set_identity(int size) {
    width = size;
    height = size;

    matrix.resize(size);

    for (int i = 0; i < width; i++) {
        matrix[i].resize(size);
        matrix[i][i] = 1;
    }
}

// Implement other member functions and friend functions here.
