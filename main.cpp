#include <iostream>
#include "AirTravelManSys.h"

int main() {
    AirTravelManSys travelsys;
    travelsys.readAirlinesDataFile();
    travelsys.readAirportsDataFile();
    travelsys.readFlightsDataFile();
    travelsys.topKAirportCapacity(10);
    return 0;
}
