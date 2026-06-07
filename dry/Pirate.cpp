
#include "Pirate.h"
#include <string>


Pirate::Pirate(const string& name, int bounty): name(name), bounty(bounty) {}

//default constructor
Pirate::Pirate(){}


void Pirate::setName(const string& name){
    this->name = name;
}


std::string Pirate::getName(){
    return name;
}

//Implement bounty functions
void Pirate::setBounty(int bounty){
    this->bounty = bounty;
}
int Pirate::getBounty(){
    return bounty;
}

std::ostream &operator<<(std::ostream &os, const Pirate &pirate){
    os << pirate.name;
    return os;
}

//Print operator for bounty
std::ostream &operator<<(std::ostream &os, const Pirate &pirate){
    os << pirate.bounty;
    return os;
}