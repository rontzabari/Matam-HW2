
#pragma once

#include <iostream>

using std::string;

class Pirate {
private:
    string name;
    int bounty;

public:
    Pirate(const string& name, int bounty);
    //default constructor
    Pirate();
    ~Pirate() = default;

    void setName(const string& name);

    string getName();

    //bounty functions
    void setBounty(int bounty);
    int getBounty();

    friend std::ostream &operator<<(std::ostream &os, const Pirate &pirate);
};
