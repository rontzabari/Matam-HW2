

#pragma once

class Matrix{
    int n; //Rows of matrix
    int m; //Cullomns of matrix
    int len = n * m;
    int *mat_ptr = new Matrix[len];

    public:
        //without third argument
        Matrix(int n, int m, int initial){
            for(int i = 0; i < len - 1; i++){
                mat_ptr[i] = initial;
            }
        }
        //with third argument
        Matrix(int n, int m){
            for(int i = 0; i < len - 1; i++){
                mat_ptr[i] = 0;
            }
        }
        //default c'tor
        Matrix() : n(0), m(0){}

        //copy c'tor
        Matrix(Matrix& mat){
            n = mat.n;
            m = mat.m;
            *mat_ptr = new Matrix[len];
        }

        //destructor
        ~Matrix(){
            delete[];
        }
};