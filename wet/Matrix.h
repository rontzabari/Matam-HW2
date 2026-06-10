

#pragma once

class Matrix{
    int n; //Rows of matrix
    int m; //Cullomns of matrix
    int len = n * m;
    int *mat_ptr = nullptr;

    public:
        //without third argument
        Matrix(int n, int m, int initial);
        //with third argument
        Matrix(int n, int m);
        //default constructor
        Matrix();

        //copy constructor - const because we don't want to change the passed matrix
        Matrix(const Matrix& mat);

        //destructor
        ~Matrix();
        

        //get/set functions for Matrix variables
        int getN();
        int getM();
        int* getMatPtr();

        //get/set functions for elements
        int getMatElement(int i, int j);
        void setMatElement(int i, int j, int new_value);
};