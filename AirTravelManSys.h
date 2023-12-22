//
// Created by lucas on 20/12/2023.
//

#ifndef TRABALHOAED2_AIRTRAVELMANSYS_H
#define TRABALHOAED2_AIRTRAVELMANSYS_H

#include <unordered_map>
#include <string>
#include "FlightNetwork.h"

class AirTravelManSys{
public:

    void readFlightsDataFile();
    void readAirportsDataFile();
    void readAirlinesDataFile();

    void addInfoCityToAirport(const string& city, const Airport& airport);
    void addInfoCountryToAirport(const string& country, const Airport& airport);
    void addInfoCodeToAirport(const string& code, const Airport& airport);
    void addInfoCodeToAirlines(const string& code, const Airline& airline);

    int numberFlightsFromAirport(const Airport& airport) const;
    int numberOfAirlinesInAirport(const Airport& airport) const;
    int numberOfCountriesFromAirport(const Airport& airport) const;
    int numberOfCountriesFromCity(const string& city) const;
    int numberOfReachableAirports(const Airport& airport, int stops);
    int numberOfReachableCities(const Airport& airport, int stops);
    int numberOfReachableCountries(const Airport& airport, int stops);

    const unordered_map<std::string, Airline> &getCodeToAirlines() const;
    const FlightNetwork &getFlightNetwork() const;
    const unordered_map<std::string, vector<Airport>> &getCityToAirport() const;
    const unordered_map<std::string, vector<Airport>> &getCountryToAirport() const;
    const unordered_map<std::string, Airport> &getCodeToAirport() const;
    void setCityToAirport(unordered_map<std::string, vector<Airport>> newCityToAirport);
    void setFlightNetwork(FlightNetwork NewFlightNetwork);


    void cleanProcessState();
    void cleanVisitedState();

private:
    std::unordered_map<std::string,vector<Airport>> cityToAirport;
    std::unordered_map<std::string,vector<Airport>> countryToAirport;
    std::unordered_map<std::string,Airport> codeToAirport;
    std::unordered_map<std::string,Airline> codeToAirlines;
    FlightNetwork flightNetwork;
};
#endif //TRABALHOAED2_AIRTRAVELMANSYS_H
