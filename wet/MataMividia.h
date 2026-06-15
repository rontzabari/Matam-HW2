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

};