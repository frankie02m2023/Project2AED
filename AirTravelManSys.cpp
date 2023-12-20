//
// Created by lucas on 20/12/2023.
//

#include "AirTravelManSys.h"
#include <fstream>
#include <sstream>

/** Reads data from the airlines file
 *
 */
void AirTravelManSys::readAirlinesDataFile() {
    string fileName = "../dataset/airlines.csv";
    fstream file(fileName);
    file.getline();
    
}