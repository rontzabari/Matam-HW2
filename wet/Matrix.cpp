#include "Matrix.h"
#include "Utilities.h"

Matrix::Matrix(int n, int m, int initial){
    mat_ptr = new int[len];
    for(int i = 0; i < len - 1; i++){
        mat_ptr[i] = initial;
    }
}

Matrix::Matrix(int n, int m){
    mat_ptr = new int[len];
    for(int i = 0; i < len - 1; i++){
        mat_ptr[i] = 0;
    }
}

Matrix::Matrix() : n(0), m(0){}

Matrix::Matrix(const Matrix& mat){
    n = mat.n;
    m = mat.m;
    mat_ptr = new int[len];
}

//destructor
Matrix::~Matrix(){
    delete[] mat_ptr;
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

Matrix Matrix::operator+(const Matrix& mat){

    for(int i = 0; i < len - 1; i++){
        this->mat_ptr[i] += mat.mat_ptr[i];
    }

    return mat;

}

Matrix& Matrix::operator=(const Matrix& mat){

    if(this->mat_ptr != mat.mat_ptr){
        return *this;
    }

    for(int i = 0; i < len; i++){
        this->mat_ptr[i] = mat.mat_ptr[i];
    }

    return *this;
}

int Matrix::operator()(int e1, int e2){
    return mat_ptr[(e1 * m) + e2];
}

std::ostream& operator<<(std::ostream& sd, Matrix& mat){
    for(int i = 0; i < mat.getN(); i++){
        sd << "|";
        for(int j = 0; j < mat.getM(); j++){
            sd << mat(i, j) << "|";
        }
        sd << std::endl;
    }
}





