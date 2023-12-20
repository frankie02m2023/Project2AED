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
    void addInfoCityToAirport(const string& city, const Airport& airport);
    void addInfoCountryToAirport(const string& country, const Airport& airport);
    void addInfoCodeToAirport(const string& code, const Airport& airport);
    void addInfoNameToAirport(const string& name,const Airport& airport);
    void addInfoCodeToAirlines(const string& code, const Airline& airline);

private:
    std::unordered_map<std::string,vector<Airport>> cityToAirport;
    std::unordered_map<std::string,vector<Airport>> countryToAirport;
    std::unordered_map<std::string,Airport> codeToAirport;
    std::unordered_map<std::string,Airport> nameToAirport;
    std::unordered_map<std::string,Airline> codeToAirlines;
    FlightNetwork flightNetwork;
};
#endif //TRABALHOAED2_AIRTRAVELMANSYS_H
