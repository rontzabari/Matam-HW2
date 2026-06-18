#pragma once
#include <string>
#include "Matrix.h"

class MataMvidia{
    int movieLength;
    Matrix *frames;
    std::string movieName;
    std::string movieCreator;

    public:
        MataMvidia(const std::string movieName, const std::string movieCreator,
            const Matrix *frames, const int movieLength);
        MataMvidia(const MataMvidia& movie);
        ~MataMvidia();
        MataMvidia& operator=(const MataMvidia& movie);

        //overloaded functions
        Matrix& operator[](int index);

        const Matrix& operator[](int index) const;

        MataMvidia& operator+=(const MataMvidia& movie);

        MataMvidia& operator+=(const Matrix& frame);

        MataMvidia operator+(const MataMvidia& movie) const;

        // printing
        friend std::ostream& operator<<(std::ostream& output, const MataMvidia& movie);


};