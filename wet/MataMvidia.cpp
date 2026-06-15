#include "MataMividia.h"

 MataMvidia::MataMvidia(const std::string movie_name, const std::string movie_creator, const Matrix *frames, const int movie_length){
    this->movie_name = movie_name;
    this->movie_creator = movie_creator;
    this->movie_length = movie_length;

    //handking the frames
    this->frames = new Matrix[movie_length];
    for(int i = 0; i < movie_length; i++){
        this->frames[i] = frames[i];
    }
 }