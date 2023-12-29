//
// Created by lucas on 20/12/2023.
//

#ifndef TRABALHOAED2_AIRTRAVELMANSYS_H
#define TRABALHOAED2_AIRTRAVELMANSYS_H

#include <unordered_map>
#include <string>
#include <set>
#include "FlightNetwork.h"

/**
 * @file AirTravelManSys.h
 * @brief Definition of class AirTravelManSys.
 *
 * \class AirTravelManSys
 * Where are preformed the most important functions in our system.
 * Stores some hash tables (unordered_maps) and a FlightNetwork (Graph)
 */
typedef  pair<pair<int,int>,pair<NetworkAirport*,int>> ParentChild;
class AirTravelManSys{
public:


    void readFlightsDataFile();
    void readAirportsDataFile();
    void readAirlinesDataFile();

    void addInfoCityToAirport(const string& city, const Airport& airport);
    void addInfoCountryToAirport(const string& country, const Airport& airport);
    void addInfoCodeToAirport(const string& code, const Airport& airport);
    void addInfoCodeToAirlines(const string& code, const Airline& airline);

    int totalNumberOfAirports() const;
    int totalNumberOfFlights() const;
    int numberFlightsFromAirport(const Airport& airport) const;
    int numberOfAirlinesInAirport(const Airport& airport) const;
    int numberOfFlightsToCity(const string& city) const;
    int numberOfFlightsFromCity(const string& city) const;
    int numberOfFlightsPerAirline(const Airline& airline) const;
    int numberOfCountriesFromAirport(const Airport& airport) const;
    int numberOfCountriesFromCity(const string& city) const;
    int numberOfCitiesFromAirport(const Airport& airport) const;
    int numberOfAirportsFromAirport(const Airport& airport) const;
    int numberOfReachableAirportsFromAirport(const Airport& airport);
    int numberOfReachableCitiesFromAirport(const Airport& airport);
    int numberOfReachableCountriesFromAirport(const Airport& airport);
    int numberOfReachableAirports(const Airport& airport, int stops);
    int numberOfReachableCities(const Airport& airport, int stops);
    int numberOfReachableCountries(const Airport& airport, int stops);

    NetworkAirport* convertNameToAirport(const string& name, const FlightNetwork& flightNetwork);
    NetworkAirport* convertCodeToAirport(const string& code, const FlightNetwork& flightNetwork);
    vector<NetworkAirport*> convertCityToAirports(const string& city, const FlightNetwork& flightNetwork);
    vector<NetworkAirport*> convertLocationToAirports(const double& latitude, const double& longitude, const FlightNetwork& flightNetwork);


    int maxTrip(vector<pair<Airport,Airport>>& maxTripAirportPairs);

    vector<NetworkAirport*> topKAirportCapacity(int k);


    unordered_set<Airport> essentialAirports();
    set<vector<NetworkAirport *>> bestFlightOption(const vector<NetworkAirport*>& sources,const vector<NetworkAirport*>& destinations);
    void findMinDistDFS(NetworkAirport* source, NetworkAirport* destination, int& minDist, int& countDist);
    void findMinDistBFS(NetworkAirport* source, NetworkAirport* destination, int& minDist);
    void findFlightOptionsDFS(NetworkAirport* source, NetworkAirport* destination, vector<NetworkAirport*> flightOption, set<vector<NetworkAirport*>> &flightOptions, int dist);
    void findFlightOptionsBFS(NetworkAirport* source, NetworkAirport* destination,set<vector<NetworkAirport*>> &flightOptions, int dist);
    void buildFlightOption(ParentChild root, vector<ParentChild> parents, set<vector<NetworkAirport*>> &flightOptions);
    void reAddAirportsToFlightNetwork();
    FlightNetwork flightNetworkFilteredByDesiredAirlines(unordered_set<Airline> airlines);
    FlightNetwork flightNetworkFilteredByUndesiredAirlines(unordered_set<Airline> airlines);

    const unordered_map<std::string, Airline> &getCodeToAirlines() const;
    const FlightNetwork &getFlightNetwork() const;
    const unordered_map<std::string, vector<Airport>> &getCityToAirport() const;
    const unordered_map<std::string, vector<Airport>> &getCountryToAirport() const;
    const unordered_map<std::string, Airport> &getCodeToAirport() const;
    void setCityToAirport(unordered_map<std::string, vector<Airport>> newCityToAirport);
    void setFlightNetwork(FlightNetwork NewFlightNetwork);
    void setCodeToAirport(const unordered_map<std::string, Airport> &codeToAirport);


    void cleanProcessState();
    void cleanVisitedState();

private:
    std::vector<Airport> Airports;
    std::unordered_map<std::string,vector<Airport>> cityToAirport;
    std::unordered_map<std::string,vector<Airport>> countryToAirport;
    std::unordered_map<std::string,Airport> codeToAirport;
    std::unordered_map<std::string,Airline> codeToAirlines;
    FlightNetwork flightNetwork;
};
#endif //TRABALHOAED2_AIRTRAVELMANSYS_H
