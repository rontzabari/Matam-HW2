#include "Matrix.h"
#include <iostream>
#include "Utilities.h"
#include "cmath"

Matrix::Matrix(int n, int m, int initial) : n(n), m(m), len(n * m), matPtr(new int[len]) {
    for(int i = 0; i < len; i++){
        matPtr[i] = initial;
    }
}

Matrix::Matrix() : n(0), m(0), len(0), matPtr(nullptr) {

}

Matrix::Matrix(const Matrix& mat){
    n = mat.n;
    m = mat.m;
    len = mat.len;
    matPtr = new int[len];

    for (int i = 0; i < mat.len; i++) {
        matPtr[i] = mat.matPtr[i];
    }
}


//destructor
Matrix::~Matrix(){
    delete[] matPtr;
}

/*
 * Assignment Operator
 * Must do the following:
 * Delete the old aray, save the array's new size, allocate new memory for
 * the array. Finally, copy all of the passed matrix's elements into the
 * allocated memory. Then return a reference to the new matrix.
 */

Matrix& Matrix::operator=(const Matrix& mat) {
    if (this ==  &mat) {
        return *this;
    }

    delete[] matPtr;

    m = mat.m;
    n = mat.n;
    len = mat.len;

    matPtr = new int[len];

    for (int i = 0; i < len; i++) {
        matPtr[i] = mat.matPtr[i];
    }
    return *this;

}

int Matrix::getN() const{
    return n;
}

int Matrix::getM() const{
    return m;
}

int Matrix::getLen() const {
    return len;
}

int* Matrix::getMatPtr(){
    return matPtr;
}

int Matrix::getMatElement(int i, int j) {
    if ( i < 0 || i >= n || j < 0 || j >= m) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    int width = getM();
    return matPtr[(i * width) + j];
}

void Matrix::setMatElement(int i, int j, int new_value){
    if ( i < 0 || i >= n || j < 0 || j >= m) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    int width = getM();
    int element = (i * width) + j;
    matPtr[element] = new_value;
}

Matrix Matrix::operator-() const {
    Matrix minusMatrix(*this);

    for (int i = 0; i < minusMatrix.len; i++) {
        minusMatrix.matPtr[i] *= -1;
    }

    return minusMatrix;
}

Matrix& Matrix::operator+=(const Matrix &mat) {
    if (this -> n != mat.n || this -> m != mat.m) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }


    for (int i = 0; i < len; i++) {
        this -> matPtr[i] += mat.matPtr[i];
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix& mat) const {

    // Create a copy matrix of *this with dimensions n x m
    Matrix new_mat(*this);


    // += also checks that the dimensions match as required
    return (new_mat += mat);

}

Matrix& Matrix::operator*=(int scalar) {

    for (int i = 0; i < len; i++) {
        this -> matPtr[i] *= scalar;
    }

    return *this;
}

Matrix& Matrix::operator*=(const Matrix &mat) {
    if (this -> m != mat.n) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }

    Matrix product_mat(n, mat.getM());

    for (int i = 0; i < n; i++) { // for all the (*rows)


        for (int j = 0; j < mat.getM(); j++) { // for all the columns of mat
            // The sum is for a single element in the product matrix. Reset every (i,j)
            double elementSum = 0;
            for (int k = 0; k < m; k++) { // for all the columns of (*this)
                /*
                 * Based on the product matrix formula which is the sum
                 * from k = 1 to n of a(i,k) * b(k,j)
                 */
                elementSum += (*this)(i, k) * mat(k,j);
            }

            product_mat(i,j) = elementSum;
        }

    }

    (*this) = product_mat;
    return (*this);
}

Matrix operator*(int scalar, const Matrix& mat) {
    return mat * scalar;
}




Matrix& Matrix::operator-=(const Matrix &mat) {
    if (this -> n != mat.n || this -> m != mat.m) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }

    for (int i = 0; i < len; i++) {
        this -> matPtr[i] -= mat.matPtr[i];
    }

    return *this;
}



Matrix Matrix::operator-(const Matrix& mat) const{

    return (*this) + (-mat);

}

bool Matrix::operator==(const Matrix& mat) const {
    if (this->n != mat.getN() || this->m != mat.getM()) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (matPtr[i] != mat.matPtr[i]) {
            return false;
        }
    }

    return true;

}

bool Matrix::operator!=(const Matrix& mat) const {
    return !((*this) == mat);
}

Matrix Matrix::rotateClockwise() const {
    Matrix rotatedMatrix(this->m, this->n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rotatedMatrix(j,n - 1 -i) = (*this)(i,j);
        }
    }
    return rotatedMatrix;
}

Matrix Matrix::rotateCounterClockwise() const {
    Matrix rotatedMatrix(this->m, this->n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rotatedMatrix(m - 1 - j,i) = (*this)(i,j);
        }
    }
    return rotatedMatrix;
}

Matrix Matrix::transpose() const {
    Matrix transposedMatrix(this->m, this->n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            transposedMatrix(j, i) = (*this)(i,j);
        }
    }
    return transposedMatrix;
}

double Matrix::CalcFrobeniusNorm(const Matrix& mat) {
    double sum = 0;

    for (int i = 0; i < mat.getN(); i++) {
        for (int j = 0; j < mat.getM(); j++) {
            sum += mat(i,j) * mat(i,j);
        }
    }

    sum = sqrt(sum);

    return sum;
}

Matrix Matrix::operator*(const Matrix& mat) const { // matrix * matrix
    Matrix newMatrix(*this);
    return (newMatrix *= mat);
}

Matrix Matrix::operator*(int scalar) const {
    Matrix newMatrix(*this);
    return (newMatrix *= scalar);
}

int Matrix::CalcDeterminant(const Matrix& mat) {

    if (mat.getN() != mat.getM()) {
        exitWithError(MatamErrorType::NotSquareMatrix);
    }

    int determinant;
    int sum = 0;

    // base case

    if (mat.getM() == 0) {
        return 0;
    }

    if (mat.getM() == 1) {
        return mat(0, 0);
    }
    if (mat.getM() == 2) {
        return (mat(0,0) * mat(1,1)) - (mat(0,1) * mat(1,0));
    }

    for(int i = 0; i < mat.getN(); i++){
        Matrix minor(mat.getN() - 1, mat.getM() - 1);
        int row = 0;
        for(int j = 1; j < mat.getN(); j++) {
            int col = 0;
            for(int k = 0; k < mat.getN(); k++){
                if(i == k) {
                    continue;
                }
                minor(row, col) = mat(j, k);
                col++;
        }
        row++;
    }
    int sign = (i % 2 == 0) ? 1 : -1;
    determinant = sign * mat(0, i) * CalcDeterminant(minor);
    sum += determinant;
    }
return sum;
}


int Matrix::operator() (int e1, int e2) const{
    int n1 = getN();
    int m1 = getM();
    if(e1 > n1 - 1 || e1 < 0 || e2 > m1 - 1 || e2 < 0){
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return matPtr[(e1 * m1) + e2];
}

int& Matrix::operator()(int e1, int e2){
    int n1 = getN();
    int m1 = getM();
    if(e1 > n1 - 1 || e1 < 0 || e2 > m1 - 1 || e2 < 0){
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return matPtr[(e1 * m1) + e2];
}

std::ostream& operator<<(std::ostream& sd, const Matrix& mat){
    for(int i = 0; i < mat.getN(); i++){
        sd << "|";
        for(int j = 0; j < mat.getM(); j++){
            sd << mat(i, j) << "|";
        }
        sd << std::endl;
    }
    return sd;
}










