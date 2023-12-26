#include <iostream>
#include "AirTravelManSys.h"

int main() {

    AirTravelManSys travelsys;
    travelsys.readAirlinesDataFile();
    travelsys.readAirportsDataFile();
    travelsys.readFlightsDataFile();
    Airport source = travelsys.getCodeToAirport().at("JFK");
    Airport destination = travelsys.getCodeToAirport().at("OPO");
    NetworkAirport* sourcen = travelsys.getFlightNetwork().findAirport(source);
    NetworkAirport* destinationn = travelsys.getFlightNetwork().findAirport(destination);
    vector<NetworkAirport*> sources {sourcen};
    vector<NetworkAirport*> destinations {destinationn};
    travelsys.bestFlightOption(sources,destinations);
    return 0;
}
