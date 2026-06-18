#include <iostream>
#include "Pirate.h"
#include <cstring>

using std::cout;
using std::endl; 


int main() {


    Pirate luffy("Luffy", 1000000, GUM_GUM_FRUIT);
    Pirate zoro("Zoro", 500000);


    const int CREW_SIZE = 2;
    
    Pirate strawHatCrew[CREW_SIZE];
    strawHatCrew[0] = luffy;
    strawHatCrew[1] = zoro;

    cout << "Straw Hat crew contains:" << endl;
    for (int i = 0; i < CREW_SIZE; i++) {
        cout << strawHatCrew[i] << endl;
    }

    return 0;
}
