#include <iostream>

// Функция для обмена значениями (аналог std::swap)
void swap(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

// Функция для перестановки столбцов внутри "плоского" массива
// Перемещает столбец colIndex на позицию 0 (в рамках текущего размера n)
void shiftColumnToFront(double* matrix, int n, int totalN, int colIndex) {
    for (int i = 0; i < n; ++i) {
        for (int j = colIndex; j > 0; --j) {
            // matrix[i * totalN + j] — доступ к элементу i-й строки j-го столбца
            swap(matrix[i * totalN + j], matrix[i * totalN + j - 1]);
        }
    }
}

// Возвращает столбцы обратно после вычислений
void shiftColumnBack(double* matrix, int n, int totalN, int colIndex) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < colIndex; ++j) {
            swap(matrix[i * totalN + j], matrix[i * totalN + j + 1]);
        }
    }
}

double calculateDeterminant(double* matrix, int n, int totalN) {
    // Базовый случай: матрица 1x1
    if (n == 1) {
        return matrix[0];
    }

    // Базовый случай: матрица 2x2 (для ускорения)
    if (n == 2) {
        // a11*a22 - a12*a21
        return matrix[0] * matrix[totalN + 1] - matrix[1] * matrix[totalN];
    }

    double det = 0;
    int sign = 1;

    for (int j = 0; j < n; ++j) {
        // 1. Выбираем j-й элемент первой строки.
        // Чтобы свести задачу к подматрице, "гоним" столбец j в начало
        shiftColumnToFront(matrix, n, totalN, j);

        // 2. Рекурсивно вызываем функцию для подматрицы (n-1)x(n-1)
        // Мы передаем указатель на элемент [1][1], который становится [0][0] для подматрицы
        double subDet = calculateDeterminant(&matrix[totalN + 1], n - 1, totalN);

        // 3. Накапливаем результат: знак * элемент [0][0] * детерминант подматрицы
        det += sign * matrix[0] * subDet;

        // 4. Возвращаем столбцы на место, чтобы сохранить структуру для следующей итерации
        shiftColumnBack(matrix, n, totalN, j);

        // Перемена знака при переходе к следующему элементу строки
        sign *= -1;
    }

    return det;
}

int main() {
    int n;
    std::cout << "Enter matrix size (n x n): ";
    if (!(std::cin >> n) || n <= 0) return 1;

    double* matrix = new double[n * n];
    std::cout << "Enter matrix elements:" << std::endl;
    for (int i = 0; i < n * n; ++i) {
        std::cin >> matrix[i];
    }

    // totalN передается, чтобы правильно вычислять смещение в "плоском" массиве
    double result = calculateDeterminant(matrix, n, n);

    std::cout << "Determinant: " << result << std::endl;

    delete[] matrix;
    return 0;
}
