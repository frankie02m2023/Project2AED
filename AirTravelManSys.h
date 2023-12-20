//
// Created by lucas on 20/12/2023.
//

#ifndef TRABALHOAED2_AIRTRAVELMANSYS_H
#define TRABALHOAED2_AIRTRAVELMANSYS_H

#include <unordered_map>
#include <string>
#include "NetworkAirports.h"
#include "FlightNetwork.h"

class AirTravelManSys{
public:

    void readFlightsDataFile();
    void readAirportsDataFile();
    void readAirlinesDataFile();

private:
    std::unordered_map<std::string,vector<NetworkAirport>> cityToNetworkAirport;
    std::unordered_map<std::string,vector<NetworkAirport>> countryToNetworkAirport;
    std::unordered_map<std::string,NetworkAirport> codeToNetworkAirport;
    std::unordered_map<std::string,NetworkAirport> nameToNetworkAirport;
    std::unordered_set<Airline> availableAirlines;
    FlightNetwork flightNetwork;
};
#endif //TRABALHOAED2_AIRTRAVELMANSYS_H
