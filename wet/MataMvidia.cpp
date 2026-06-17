#include "MataMividia.h"
#include "Utilities.h"
#include <iostream>


 MataMvidia::MataMvidia(const std::string movie_name, const std::string movie_creator, const Matrix *frames, const int movie_length){
    this->movie_name = movie_name;
    this->movie_creator = movie_creator;
    this->movie_length = movie_length;

    //handling the frames
    this->frames = new Matrix[movie_length];
    for(int i = 0; i < movie_length; i++){
        this->frames[i] = frames[i];
    }
 }

 MataMvidia::~MataMvidia(){
    delete[] this->frames;
 }

 MataMvidia& MataMvidia::operator=(const MataMvidia& movie){
    if(this->movie_length != movie.movie_length){
        /*exitWithError(UnmatchedSizes);*/
    }
    this->movie_name = movie.movie_name;
    this->movie_creator = movie.movie_creator;
    this->movie_length = movie.movie_length;
    if(this->frames == movie.frames){
        return *this;
    }
    for(int i = 0; i < this->movie_length; i++){
        this->frames[i] = movie.frames[i];
    }
 }

Matrix& MataMvidia::operator[](int index) {
    if (index < 0 || index >= this->movie_length) {
        exitWithError(MatamErrorType::OutOfBounds);
    }

    return frames[index];
}

const Matrix& MataMvidia::operator[](int index) const {
    if (index < 0 || index >= this->movie_length) {
        exitWithError(MatamErrorType::OutOfBounds);
    }

    return frames[index];
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& movie) {
     // create a new bigger array
     Matrix* biggerMovie = new Matrix[this->movie_length + movie.movie_length];

     for (int i = 0; i < this->movie_length; i++) {
         biggerMovie[i] = this->frames[i];
     }

     for (int i = movie_length + 1; i < movie_length + movie.movie_length; i++) {
         biggerMovie[i] = movie.frames[i];
     }

     // copy it onto the called object
     delete[] frames;

     this->frames = biggerMovie;
     this->movie_length += movie.movie_length;


     return (*this);
 }

MataMvidia& MataMvidia::operator+=(const Matrix& frame) {

     // create a new bigger array
     Matrix* biggerMovie = new Matrix[this->movie_length + 1];

     int i = 0;
     for (i = 0; i < this->movie_length; i++) {
         biggerMovie[i] = this->frames[i];
     }

     biggerMovie[i + 1] = frame;

     // copy it onto the called object
     delete[] frames;

     this->frames = biggerMovie;
     this->movie_length += 1;


     return (*this);
 }

MataMvidia MataMvidia::operator+(const MataMvidia& movie) const {
     MataMvidia newMovie(*this);
     return (newMovie += movie);
 }

std::ostream& operator<<(std::ostream& output, const MataMvidia& movie) {
     output << "Movie Name: " << movie.movie_name << std::endl;
     output << "Author: " << movie.movie_creator << std::endl;

     for (int i = 0; i < movie.movie_length; i++) {
         output << "Frame " << i << ":" << std::endl;
         output << movie.frames[i];
     }

     output << "-----End Of Movie-----" << std::endl;

     return output;
 }



