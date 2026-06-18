#include "MataMvidia.h"
#include "Utilities.h"
#include <iostream>


 MataMvidia::MataMvidia(const std::string movieName, const std::string movieCreator, const Matrix *frames, const int movieLength){
    this->movieName = movieName;
    this->movieCreator = movieCreator;
    this->movieLength = movieLength;

    //handling the frames
    this->frames = new Matrix[movieLength];
    for(int i = 0; i < movieLength; i++){
        this->frames[i] = frames[i];
    }
 }

MataMvidia::MataMvidia(const MataMvidia& movie)
    : MataMvidia(movie.movieName,
                 movie.movieCreator,
                 movie.frames,
                 movie.movieLength)
 {
 }


 MataMvidia::~MataMvidia(){
    delete[] this->frames;
 }

 MataMvidia& MataMvidia::operator=(const MataMvidia& movie){
     if(this == &movie){
         return *this;
     }

     Matrix* newFrames = new Matrix[movie.movieLength];
    this->movieName = movie.movieName;
    this->movieCreator = movie.movieCreator;
    this->movieLength = movie.movieLength;
    for(int i = 0; i < this->movieLength; i++){
        newFrames[i] = movie.frames[i];
    }

     delete[] frames;
     frames = newFrames;

     return *this;
 }

Matrix& MataMvidia::operator[](int index) {
    if (index < 0 || index >= this->movieLength) {
        exitWithError(MatamErrorType::OutOfBounds);
    }

    return frames[index];
}

const Matrix& MataMvidia::operator[](int index) const {
    if (index < 0 || index >= this->movieLength) {
        exitWithError(MatamErrorType::OutOfBounds);
    }

    return frames[index];
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& movie) {
     // create a new bigger array
     Matrix* biggerMovie = new Matrix[this->movieLength + movie.movieLength];

     for (int i = 0; i < this->movieLength; i++) {
         biggerMovie[i] = this->frames[i];
     }

     for (int i = 0; i < movie.movieLength; i++) {
         biggerMovie[this->movieLength + i] = movie.frames[i];
     }

     // copy it onto the called object
     delete[] frames;

     this->frames = biggerMovie;
     this->movieLength += movie.movieLength;


     return (*this);
 }

MataMvidia& MataMvidia::operator+=(const Matrix& frame) {

     // create a new bigger array
     Matrix* biggerMovie = new Matrix[this->movieLength + 1];

     for (int i = 0; i < this->movieLength; i++) {
         biggerMovie[i] = this->frames[i];
     }

     biggerMovie[movieLength] = frame;

     // copy it onto the called object
     delete[] frames;

     this->frames = biggerMovie;
     this->movieLength += 1;


     return (*this);
 }

MataMvidia MataMvidia::operator+(const MataMvidia& movie) const {
     MataMvidia newMovie(*this);
     return (newMovie += movie);
 }

std::ostream& operator<<(std::ostream& output, const MataMvidia& movie) {
     output << "Movie Name: " << movie.movieName << std::endl;
     output << "Author: " << movie.movieCreator << std::endl << std::endl;

     for (int i = 0; i < movie.movieLength; i++) {
         output << "Frame " << i << ":" << std::endl;
         output << movie.frames[i] << std::endl;
     }

     output << "-----End of Movie-----" << std::endl;

     return output;
 }



