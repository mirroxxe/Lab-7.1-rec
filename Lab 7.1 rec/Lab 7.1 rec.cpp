#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;
// функція для обчислення характеристики стовпця
int col(int* column, int k, int i = 0, int sum = 0) {
    if (i == k) return sum;
    if (column[i] < 0 && column[i] % 2 != 0) sum += abs(column[i]);
    return col(column, k, i + 1, sum);
}

// функція для перестановки стовпців матриці за зростанням характеристик
void rearrangeCol(int** matrix, int k, int n, int i = 0, int j = 0) {
    if (i == n - 1) return;
    if (j == n - i - 1) return rearrangeCol(matrix, k, n, i + 1);
    if (col(matrix[j], k) > col(matrix[j + 1], k)) {
        std::swap(matrix[j], matrix[j + 1]);
    }
    rearrangeCol(matrix, k, n, i, j + 1);
}

// функція для обчислення суми елементів у стовпці з від'ємними елементами
int sumOfColumnsWithNegativeElements(int** matrix, int k, int n, int j = 0, int sum = 0) {
    if (j == n) return sum;
    int hasNegative = std::any_of(matrix[j], matrix[j] + k, [](int val) { return val < 0; });

    if (hasNegative) {
        sum += col(matrix[j], k);
    }

    return sumOfColumnsWithNegativeElements(matrix, k, n, j + 1, sum);
}

// функція для виводу матриці
void printMatrix(int** matrix, int k, int n, int i = 0, int j = 0) {
    if (i == k) return;
    if (j == n) {
        std::cout << "\n";
        return printMatrix(matrix, k, n, i + 1);
    }
    std::cout << std::setw(5) << matrix[j][i] << " ";
    printMatrix(matrix, k, n, i, j + 1);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int k, n;
    std::cout << "Print rows size (k): ";
    std::cin >> k;
    std::cout << "Print cols size (n): ";
    std::cin >> n;

    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[k];
    }

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[j][i] = rand() % 100 - 50;
        }
    }

    std::cout << "Original matrix:\n";
    printMatrix(matrix, k, n);

    rearrangeCol(matrix, k, n);

    std::cout << "Sorted matrix:\n";
    printMatrix(matrix, k, n);

    int sum = sumOfColumnsWithNegativeElements(matrix, k, n);

    std::cout << "Sum of elements in cols with at least one negative element: " << sum << "\n";

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
