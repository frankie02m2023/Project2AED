//
// Created by lucas on 20/12/2023.
//

#include "AirTravelManSys.h"
#include <fstream>
#include <sstream>
#include <iostream>

/** Reads data from the airlines file
 *
 */
void AirTravelManSys::readAirlinesDataFile() {

    string line;
    string fileName = "../dataset/airlines.csv";
    ifstream file(fileName);

    if(!file.is_open()){
        std::cerr << "Error: Unable to open the file." << '\n';
    }


    getline(file,line); //header line

    //get the airline information from the file
    string code, name, callSign, country;
    while(getline(file,line)){

        //get code
        size_t it = line.find_first_of(',');
        code = line.substr(0,it);
        line = line.substr(it + 1);

        //get name
        it = line.find_first_of(',');
        name = line.substr(0,it);
        line = line.substr(it + 1);

        //get callSign
        it = line.find_first_of(',');
        callSign = line.substr(0,it);
        line = line.substr(it + 1);

        //get country
        country = line;

        //Create airline and puts it in the hash table
        Airline airline {code, name, callSign, country};
        availableAirlines.insert(airline);
    }
}

