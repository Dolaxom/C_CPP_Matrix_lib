#include <iostream>
#include "src/s21_matrix.h"

int main() {
    S21Matrix matrix_a(3, 3);
    S21Matrix matrix_b(3, 3);

    bool value = matrix_b(5, 1);

    std::cout << value;

    return 0;
}
