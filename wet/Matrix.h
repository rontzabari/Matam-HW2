

#pragma once

class Matrix{
    int n; //Rows of matrix
    int m; //Columns of matrix
    int len = n * m;
    int *mat_ptr = nullptr;

    public:
        Matrix(int n, int m, int initial = 0);
        //default constructor
        Matrix();

    //*********** The Big Three ************

        //copy constructor - const because we don't want to change the passed matrix
        Matrix(const Matrix& mat);

        //destructor
        ~Matrix();

        // Assignment operator - make a new matrix a reference to the passed matrix
        Matrix& operator=(const Matrix& mat);


        //getter and setter functions for Matrix variables
        int getN() const;
        int getM() const;
        int getLen() const;
        int* getMatPtr();

        int operator()(int e1, int e2) const; // access to natrix element
        int& operator()(int e1, int e2); 

        //getter and setter functions for elements
        int getMatElement(int i, int j);
        void setMatElement(int i, int j, int new_value);

        // rotation
        Matrix rotateClockwise(); // no parameters because it rotates the current matrix
        Matrix rotateCounterClockwise(); // no parameters because it rotates the current matrix


        // Transpose
        Matrix transpose() const;

        /*
         * Forbinius Norm - sum of the square of all elements in the matrix.
         * Static because it is not called on an object.
         */
        static double CalcFrobeniusNorm(const Matrix& mat);

        // determinant
        static double CalcDeterminant(const Matrix& mat);

        // operator overloading
        Matrix operator+(const Matrix& mat) const; // add two matrices
        Matrix operator-(const Matrix& mat) const; // minus two matrices
        Matrix operator*(const Matrix& mat) const; // times
        Matrix operator*(int scalar) const; // matrix times scalar
        Matrix& operator+=(const Matrix& mat); // plus equals
        Matrix& operator-=(const Matrix& mat); // minus equals
        Matrix& operator*=(const Matrix& mat); // times equals
        Matrix operator-() const;  //unary minus

        bool operator==(const Matrix& mat) const; // checks if matrices are equal
        bool operator!=(const Matrix& mat) const; // checks if matrices are not equal

        // double sided multiplcation of a scalar and a matrix
        friend Matrix operator*(int scalar, const Matrix& mat); // scalar times matrix

        Matrix& operator*=(int scalar); // matrix times scalar


};