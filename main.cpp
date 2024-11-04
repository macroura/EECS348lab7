#include <iostream>
#include <fstream>
#include <vector>

const int SIZE = 4;

class Matrix {
private:
    int matrix[SIZE][SIZE];

public:
    Matrix() {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                matrix[i][j] = 0;
    }

    Matrix(int m[SIZE][SIZE]) {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                matrix[i][j] = m[i][j];
    }

    Matrix operator+(const Matrix& other) {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }


    Matrix operator*(const Matrix& other) {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < SIZE; ++k) {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    void readFromFile(const std::string& fileName) {
        std::ifstream file(fileName + ".txt");
        if (file.is_open()) {
            for (int i = 0; i < SIZE; ++i)
                for (int j = 0; j < SIZE; ++j)
                    file >> matrix[i][j];
            file.close();
        } else {
            std::cerr << "Unable to open file!" << std::endl;
        }
    }

    void readFromStdin() {
        for (int i = 0; i < SIZE; ++i) {
            std::cout << "Enter Line " << i << ": ";
            for (int j = 0; j < SIZE; ++j) {
                std::cin >> matrix[i][j];
            }
        }
    }

    void display() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    int sumOfDiagonals() const {
        int total = 0;
        for (int i = 0; i < SIZE; ++i) {
            total += matrix[i][i]; 
            total += matrix[i][SIZE - 1 - i]; 
        }
        
        if (SIZE % 2 != 0) {
            total -= matrix[SIZE / 2][SIZE / 2];
        }
        return total;
    }

    Matrix swapRows(int r1, int r2) const {
        Matrix copy = *this;
        for (int j = 0; j < SIZE; ++j) {
            std::swap(copy.matrix[r1][j], copy.matrix[r2][j]);
        }
        return copy;
    }
};

int main() {
    Matrix m1;
    std::string fileName;
    std::cout << "Matrix 1 being read from file" << std::endl;
    std::cout << "Name: ";
    std::cin >> fileName;
    m1.readFromFile(fileName);
    m1.display();

    std::cout << "Enter Values for Matrix 2:" << std::endl;
    Matrix m2;
    m2.readFromStdin();
    m2.display();

    std::cout << "Sum of matrices:" << std::endl;
    Matrix sumMatrix = m1 + m2;
    sumMatrix.display();

    std::cout << "Product of matrices:" << std::endl;
    Matrix productMatrix = m1 * m2;
    productMatrix.display();

    std::cout << "Sum of diagonals of matrix 1:" << std::endl;
    std::cout << m1.sumOfDiagonals() << std::endl;

    std::cout << "Matrix 1 after swapping rows:" << std::endl;
    Matrix swappedMatrix = m1.swapRows(0, 2);
    swappedMatrix.display();

    return 0;
}
