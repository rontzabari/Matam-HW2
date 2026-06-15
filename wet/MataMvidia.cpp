#include "MataMividia.h"
#include "Utilities.h"

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