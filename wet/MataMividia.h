#pragma once
#include <string>
#include "Matrix.h"

class MataMvidia{
    int movie_length;
    Matrix *frames;
    std::string movie_name;
    std::string movie_creator;

    public:
        MataMvidia(const std::string movie_name, const std::string movie_creator, const Matrix *frames, const int movie_length);
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