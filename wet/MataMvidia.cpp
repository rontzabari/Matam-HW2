#include "MataMvidia.h"
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

MataMvidia::MataMvidia(const MataMvidia& movie)
    : MataMvidia(movie.movie_name,
                 movie.movie_creator,
                 movie.frames,
                 movie.movie_length)
 {
 }


 MataMvidia::~MataMvidia(){
    delete[] this->frames;
 }

 MataMvidia& MataMvidia::operator=(const MataMvidia& movie){
     if(this == &movie){
         return *this;
     }

     Matrix* newFrames = new Matrix[movie.movie_length];
    this->movie_name = movie.movie_name;
    this->movie_creator = movie.movie_creator;
    this->movie_length = movie.movie_length;
    for(int i = 0; i < this->movie_length; i++){
        newFrames[i] = movie.frames[i];
    }

     delete[] frames;
     frames = newFrames;

     return *this;
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

     for (int i = 0; i < movie.movie_length; i++) {
         biggerMovie[this->movie_length + i] = movie.frames[i];
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

     for (int i = 0; i < this->movie_length; i++) {
         biggerMovie[i] = this->frames[i];
     }

     biggerMovie[movie_length] = frame;

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
     output << "Author: " << movie.movie_creator << std::endl << std::endl;

     for (int i = 0; i < movie.movie_length; i++) {
         output << "Frame " << i << ":" << std::endl;
         output << movie.frames[i] << std::endl;
     }

     output << "-----End of Movie-----" << std::endl;

     return output;
 }



