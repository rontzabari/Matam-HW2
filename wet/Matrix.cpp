#include "Matrix.h"
#include "Utilities.h"

Matrix::Matrix(int n, int m, int initial) {
    mat_ptr = new int[len];
    for(int i = 0; i < len - 1; i++){
        mat_ptr[i] = initial;
    }
}

Matrix::Matrix() : n(0), m(0){}

Matrix::Matrix(const Matrix& mat){
    n = mat.n;
    m = mat.m;
    len = mat.len;
    mat_ptr = new int[len];

    for (int i = 0; i < mat.len; i++) {
        mat_ptr[i] = mat.mat_ptr[i];
    }
}


//destructor
Matrix::~Matrix(){
    delete[] mat_ptr;
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

    delete[] mat_ptr;

    m = mat.m;
    n = mat.n;
    len = mat.len;

    mat_ptr = new int[len];

    for (int i = 0; i < len; i++) {
        mat_ptr[i] = mat.mat_ptr[i];
    }
    return *this;

}

int Matrix::getN(){
    return n;
}

int Matrix::getM(){
    return m;
}

int* Matrix::getMatPtr(){
    return mat_ptr;
}

int Matrix::getMatElement(int i, int j){
    exitWithError(MatamErrorType::OutOfBounds);
    int width = getM();
    return ((i - 1) * width) + j;
}

void Matrix::setMatElement(int i, int j, int new_value){
    exitWithError(MatamErrorType::OutOfBounds);
    int width = getM();
    int element = ((i - 1) * width) + j;
    mat_ptr[element] = new_value;
}

Matrix Matrix::operator-() const {
    for (int i = 0; i < len; i++) {
        this->mat_ptr[i] *= -1;
    }

    return *(this);
}

Matrix& Matrix::operator+=(const Matrix &mat) {
    if (this -> n != mat.n || this -> m != mat.m) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }

    for (int i = 0; i < len; i++) {
        this -> mat_ptr[i] += mat.mat_ptr[i];
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
        this -> mat_ptr[i] *= scalar;
    }

    return *this;
}

Matrix& Matrix::operator*=(const Matrix &mat) {
    if (this -> m != mat.n) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }

    Matrix product_mat(m, mat.getN());

    for (int i = 0; i < n; i++) { // for all the (*rows)


        for (int j = 0; j < mat.getM(); j++) { // for all the columns of mat
            // The sum is for a single element in the product matrix. Reset every (i,j)
            double element_sum = 0;
            for (int k = 0; k < m; k++) { // for all the columns of (*this)
                /*
                 * Based on the product matrix formula which is the sum
                 * from k = 1 to n of a(i,k) * b(k,j)
                 */
                element_sum += (*this)(i, k) * mat(k,j);
            }

            product_mat(i,j) = element_sum;
        }

    }

    (*this) = product_mat;
    return (*this);
}



Matrix& Matrix::operator-=(const Matrix &mat) {
    if (this -> n != mat.n || this -> m != mat.m) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }

    for (int i = 0; i < len; i++) {
        this -> mat_ptr[i] -= mat.mat_ptr[i];
    }

    return *this;
}



Matrix Matrix::operator-(const Matrix& mat) const{

    return (*this) + (-mat);

}

bool Matrix::operator==(const Matrix& mat) const {
    if (this->n != mat.getN() || this->m != mat.getM()) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for (int i = 0; i < len; i++) {
        if (mat_ptr[i] != mat.mat_ptr[i]) {
            return false;
        }
    }

    return true;

}

bool Matrix::operator!=(const Matrix& mat) const {
    return !((*this) == mat);
}

Matrix Matrix::rotateClockwise() {
    Matrix rotatedMatrix(this->m, this->n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rotatedMatrix(j,n - 1 -i) = (*this)(i,j);
        }
    }
    return rotatedMatrix;
}

Matrix Matrix::rotateCounterClockwise() {
    Matrix rotatedMatrix(this->m, this->n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rotatedMatrix(n - 1 - j,i) = (*this)(i,j);
        }
    }
    return rotatedMatrix;
}









