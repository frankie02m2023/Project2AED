//
// Created by lucas on 20/12/2023.
//

#include "AirTravelManSys.h"
#include <fstream>
#include <iostream>
#include <set>
#include <queue>
#include <utility>
#include <cmath>
#include <cfloat>
#include <stack>

using namespace std;

/** @file AirTravelManSys.cpp
 *  @brief Implementation of AirTravelManSys class
 */

//Basic getters

/** Gets the airline code map.
 * Complexity: O(1)
 * @return airline code map
 */
const unordered_map<std::string, Airline> &AirTravelManSys::getCodeToAirlines() const {
    return codeToAirlines;
}

/** Gets the flightNetwork (Graph)
 *  Complexity: O(1)
 * @return flightNetwork (Graph)
 */
const FlightNetwork &AirTravelManSys::getFlightNetwork() const {
    return flightNetwork;
}

/** Gets the cityToAirport map
 *  Complexity: O(1)
 * @return cityToAirport map
 */
const unordered_map<std::string, vector<Airport>> &AirTravelManSys::getCityToAirport() const {
    return cityToAirport;
}

/** Gets the countryToAirport map
 *  Complexity: O(1)
 * @return countryToAirport map
 */
const unordered_map<std::string, vector<Airport>> &AirTravelManSys::getCountryToAirport() const {
    return countryToAirport;
}

/** Gets the codeToAirport map
 *  Complexity: O(1)
 * @return codeToAirport map
 */
const unordered_map<std::string, Airport> &AirTravelManSys::getCodeToAirport() const {
    return codeToAirport;
}

/** cleans the process state (set to false) of the networkAirport vertexes
 *  Complexity: O(n)
 */
void AirTravelManSys::cleanProcessState() {
    for(NetworkAirport* networkAirport: flightNetwork.getFlightNetwork()){
        networkAirport->setProcessing(false);
    }
}

/** cleans the visited state (set to false) of the networkAirport vertexes
 *  Complexity: O(n)
 */
void AirTravelManSys::cleanVisitedState() {
    for(NetworkAirport* networkAirport: flightNetwork.getFlightNetwork()){
        networkAirport->setVisited(false);
    }
}

/** Sets the flightNetwork to a given value
 *  Complexity: O(1)
 * @param NewFlightNetwork new value to the flightNetwork
 */
void AirTravelManSys::setFlightNetwork(FlightNetwork NewFlightNetwork) {
    this->flightNetwork = std::move(NewFlightNetwork);
}

/** Sets the cityToAirport map to a given value
 *  Complexity: O(1)
 * @param newCityToAirport new value of the flightNetwork
 */
void AirTravelManSys::setCityToAirport(unordered_map<std::string, vector<Airport>> newCityToAirport) {
    this->cityToAirport = std::move(newCityToAirport);
}

/** Sets the CodeToAirport map to a given value
 *  Complexity: O(1)
 * @param codeToAirport new value of the codeToAirport
 */
void AirTravelManSys::setCodeToAirport(const unordered_map<std::string, Airport> &codeToAirport) {
    AirTravelManSys::codeToAirport = codeToAirport;
}


//--------------------------------------------------------------------------------------------------------
//Hash table manipulators

/** Adds info to the airlines hash table .
 * Complexity : O(1) in average
 *
 * @param airline airline that is going to be inserted
 * @param code code that is going to be inserted
 */
void AirTravelManSys::addInfoCodeToAirlines(const string& code,const Airline& airline) {
    auto canInsert = codeToAirlines.insert({code,airline});

    if(!canInsert.second){
        cout << "Airline and code already inserted" << '\n';
    }
}

/** Adds info to the cities hash table.
 * Complexity: O(1) in average
 *
 * @param city city that is going to be inserted
 * @param airport airport that is going to be inserted
 */
void AirTravelManSys::addInfoCityToAirport(const string& city, const Airport& airport) {
    auto it = cityToAirport.find(city);

    if(it == cityToAirport.end()){
        vector<Airport> airports =  {airport};
        cityToAirport.insert({city,airports});
    }
    else{
        cityToAirport.at(city).push_back(airport);
    }
}

/** Adds info to the code hash table.
 *  Complexity: O(1) in average
 * @param code code that is going to be inserted
 * @param airport airport that is going to be inserted
 */
void AirTravelManSys::addInfoCodeToAirport(const string& code, const Airport& airport) {
    auto canInsert = codeToAirport.insert({code,airport});

    if(! canInsert.second){
        cout << "Code and Airport already inserted" << '\n';
    }
}

/** Adds info to the country hash table
 * Complexity: O(1) in average
 * @param country country that is going to be inserted
 * @param airport airport that is going to be inserted
 */
void AirTravelManSys::addInfoCountryToAirport(const string& country, const Airport& airport) {
    auto it = countryToAirport.find(country);
    if(it == countryToAirport.end()){
        vector<Airport> airports =  {airport};
        countryToAirport.insert({country,airports});
    }
    else{
        countryToAirport.at(country).push_back(airport);
    }
}


//------------------------------------------------------------------------------------------------------------------------
//Data Readers

/** Reads data from the airlines file
 *  Complexity: O(n)
 */
void AirTravelManSys::readAirlinesDataFile() {

    string line;
    string fileName = "../dataset/airlines.csv";
    ifstream file(fileName);

    if(!file.is_open()){
        cerr << "Error: Unable to open the file." << '\n';
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
        addInfoCodeToAirlines(code,airline);
    }
}

/** Reads data from the airports file
 * Complexity. O(n)
 */
void AirTravelManSys::readAirportsDataFile() {

    string line;
    string fileName = "../dataset/airports.csv";
    ifstream file(fileName);

    if(!file.is_open()){
        cerr << "Error: Unable to open the file." << '\n';
    }


    getline(file,line); //header line

    //get the airports information from the file
    string code,  name, city, country;
    double latitude, longitude;
    while (getline(file,line)){

        //get code
        size_t it = line.find_first_of(',');
        code = line.substr(0,it);
        line = line.substr(it + 1);

        //get name
        it = line.find_first_of(',');
        name = line.substr(0,it);
        line = line.substr(it + 1);

        //get city
        it = line.find_first_of(',');
        city = line.substr(0,it);
        line = line.substr(it + 1);

        //get country
        it = line.find_first_of(',');
        country = line.substr(0,it);
        line = line.substr(it + 1);

        //get latitude
        it = line.find_first_of(',');
        latitude = std::stod(line.substr(0,it));
        line = line.substr(it + 1);

        //get longitude
        longitude = stod(line);

        //create airport and puts it in the flight Network
        Location location {latitude,longitude};
        Airport airport {code,name,country,city,location};
        flightNetwork.addNetworkAirport(airport);

        //put airport in airports vector
        Airports.push_back(airport);

        //adds info to the cities hash table
        addInfoCityToAirport(city,airport);

        //Adds info to the country hash table
        addInfoCountryToAirport(country,airport);

        //adds info to the code hash table
        addInfoCodeToAirport(code,airport);

    }
}

/** Reads data from the flights file
 * Complexity: O(n)
 */
void AirTravelManSys::readFlightsDataFile() {
    string line;
    string fileName = "../dataset/flights.csv";
    ifstream file(fileName);

    if(!file.is_open()){
        cerr << "Error: Unable to open the file." << '\n';
    }


    getline(file,line); //header line

    string source, target, airlineCode;
    while(getline(file,line)){

        //get source
        size_t it = line.find_first_of(',');
        source = line.substr(0,it);
        line = line.substr(it + 1);

        //get target
        it = line.find_first_of(',');
        target = line.substr(0,it);
        line = line.substr(it + 1);

        //get airline
        airlineCode = line;

        //find the airports and airline
        Airport airportSource = codeToAirport.at(source);
        Airport airportTarget = codeToAirport.at(target);
        Airline airline = codeToAirlines.at(airlineCode);

        //add flight to the source airport
        flightNetwork.addFlight(airportSource,airportTarget,airline);
    }
}

// Network Statistics ------------------------------------------------------------------

/** Gets the total number of airports in the flight Network.
 *  Complexity: O(1)
 * @return number of airports
 */
int AirTravelManSys::totalNumberOfAirports() const {
    return flightNetwork.getFlightNetwork().size();
}


/** Gets the total number of flights in the flight Network.
 *  Complexity: O(n)
 * @return number of flights
 */
int AirTravelManSys::totalNumberOfFlights() const {
    int numberOfFlights = 0;
    for(auto networkAirport : flightNetwork.getFlightNetwork()){
        numberOfFlights+= networkAirport->getNumberOfFlightsFromAirport();
    }
    return numberOfFlights;
}


/** Gets the number of flights from an Airport.
 *  Complexity: O(1)
 * @param airport airport we want to know the number of flights
 * @return number of flights
 */
int AirTravelManSys::numberFlightsFromAirport(const Airport &airport) const {

    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);

    if(networkAirport == nullptr){
        cout << "Airport not found" << endl;
        return 0;
    }

    return networkAirport->getNumberOfFlightsFromAirport();
}


/** Gets the number of airlines that operate in an airport
 *  Complexity: O(n^2)
 * @param airport airport we want to know the number of airlines
 * @return number of airlines
 */
int AirTravelManSys::numberOfAirlinesInAirport(const Airport &airport) const {

    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);

    if(networkAirport == nullptr){
        cout << "Airport not found" << endl;
        return 0;
    }

    vector<Airline> airlines;
    int counter = 0;

    for(const Flight &flight: networkAirport->getFlightsFromAirport()){
        auto it = std::find(airlines.begin(), airlines.end(),flight.getAirLine());
        if(it == airlines.end()) {
            counter++;
            airlines.push_back(flight.getAirLine());
        }
    }

    return counter;
}

/** Gets the number of flights that travel to a certain city
 * Complexity: O(n)
 * @param city the name of the target city
 * @return number of flights that travel to the city
 */

int AirTravelManSys::numberOfFlightsToCity(const std::string &city) const {
    auto it  = cityToAirport.find(city);
    int numberOfFlightsToCity = 0;
    vector<Airport> targetAirports = it->second;
    for(const Airport& airport: targetAirports){
       NetworkAirport* networkAirport = flightNetwork.findAirport(airport);
       numberOfFlightsToCity+=networkAirport->getNumberOfFlightsToAirport();
    }
    return numberOfFlightsToCity;
}

/** Gets the number of flights that depart from a certain city
 * Complexity: O(n)
 * @param city the name of the target city
 * @return number of flights that travel from the city
 */

int AirTravelManSys::numberOfFlightsFromCity(const std::string &city) const {
    auto it  = cityToAirport.find(city);
    int numberOfFlightsFromCity = 0;
    vector<Airport> targetAirports = it->second;
    for(const Airport& airport: targetAirports){
        NetworkAirport* networkAirport = flightNetwork.findAirport(airport);
        numberOfFlightsFromCity+=networkAirport->getNumberOfFlightsFromAirport();
    }
    return numberOfFlightsFromCity;
}

/** Gets the number of flights associated with a certain airline
 * Complexity: O(n^2)
 * @param city the name of the target airline
 * @return number of flights associated to the target airline
 */
int AirTravelManSys::numberOfFlightsPerAirline(const Airline &airline) const {
    int numberOfFlightsPerAirline = 0;
    for(auto airport : flightNetwork.getFlightNetwork()){
        for(const auto& flight : airport->getFlightsFromAirport()){
            if(flight.getAirLine() == airline){
                numberOfFlightsPerAirline++;
            }
        }
    }
    return numberOfFlightsPerAirline;
}

/** Gets the number of different countries an airport flies to
 *  Complexity: O(nlog(n))
 * @param airport airport we want to know the number of countries
 * @return number of countries
 */
int AirTravelManSys::numberOfCountriesFromAirport(const Airport &airport) const {

    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);

    if(networkAirport == nullptr){
        cout << "Airport not found" << endl;
        return 0;
    }

    set<string> countries;
    int counter = 0;

    for(const Flight &flight: networkAirport->getFlightsFromAirport()){
        string country = flight.getDestination()->getAirport().getCountry();
        auto it = countries.find(country);
        if(it == countries.end()) {
            counter++;
            countries.insert(country);
        }
    }

    return counter;

}

/** Gets the number of Countries a city flies to
 * Complexity: O(n^2log(n)) in the worst case
 * @param city city we want to know the number of countries
 * @return number of countries
 */
int AirTravelManSys::numberOfCountriesFromCity(const string &city) const {

    vector<Airport> airports = cityToAirport.at(city);
    int counter = 0;
    set<string> countries;

    for(const Airport& airport: airports){
        NetworkAirport* networkAirport = flightNetwork.findAirport(airport);

        if(networkAirport == nullptr){
            cout << "Airport not found" << endl;
            return 0;
        }

        for(const Flight &flight: networkAirport->getFlightsFromAirport()){
            string country = flight.getDestination()->getAirport().getCountry();
            auto it = countries.find(country);
            if(it == countries.end()) {
                counter++;
                countries.insert(country);
            }
        }
    }

    return counter;
}

/** Gets the number of different cities an airport flies to
 *  Complexity: O(nlog(n))
 * @param airport airport we want to know the number of cities
 * @return number of cities
 */
int AirTravelManSys::numberOfCitiesFromAirport(const Airport &airport) const {
    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);
    vector<string> cities;
    int numberOfCitiesFromAirport = 0;
    for(const auto& flight: networkAirport->getFlightsFromAirport()){
        string city = flight.getDestination()->getAirport().getCity();
        auto it = find(cities.begin(),cities.end(),city);
        if(it == cities.end()){
            cities.push_back(city);
            numberOfCitiesFromAirport++;
        }
    }
    return numberOfCitiesFromAirport;
}

/** Gets the number of different airports an airport flights to
 *  Complexity: O(nlog(n))
 * @param airport airport we want to know the number of airports
 * @return number of airports
 */
 int AirTravelManSys::numberOfAirportsFromAirport(const Airport &airport) const {
     NetworkAirport* networkAirport = flightNetwork.findAirport(airport);
     vector<Airport> airports;
     int numberOfAirportsFromAirport = 0;
     for(const auto& flight : networkAirport->getFlightsFromAirport()){
         Airport destAirport = flight.getDestination()->getAirport();
         auto it = find(airports.begin(),airports.end(),destAirport);
         if(it == airports.end()){
             airports.push_back(destAirport);
             numberOfAirportsFromAirport++;
         }
     }
    return numberOfAirportsFromAirport;
 }

/** Gets the number of reachable airports from a given airport in a maximum k number of stops
 *  Complexity: O(n^2)
 * @param airport airport we want to know the reachable airports
 * @param stops maximum number of stops
 * @return number of reachable airport
 */
int AirTravelManSys::numberOfReachableAirports(const Airport &airport, int stops) {
    this->cleanProcessState();
    this->cleanVisitedState();
    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);

    if(networkAirport == nullptr){
        cout << "Airport not found" << endl;
        return 0;
    }

    queue<pair<NetworkAirport*,int>> q;
    q.emplace(networkAirport,0);

    networkAirport->setVisited(true);
    int counter = 0;

    while(!q.empty()) {
        pair<NetworkAirport *, int> na = q.front();
        q.pop();

        if(na.second > stops){
            break;
        }

        for (auto it = na.first->getFlightsFromAirport().begin(); it != na.first->getFlightsFromAirport().end(); it++) {

            NetworkAirport *nb = it->getDestination();
            if (!nb->isVisited()) {

                int distance = na.second + 1;
                q.emplace(nb, distance);
                nb->setVisited(true);

                if (distance - 1 <= stops) {
                    counter++;
                }
            }

        }
    }
    return counter;
}

/** Gets the number of reachable cities from a given airport in a maximum k number of stops.
 *  Complexity: O(n^2log(n))
 * @param airport airport we want to know the reachable cities
 * @param stops maximum number of stops
 * @return number of reachable cities
 */

int AirTravelManSys::numberOfReachableCities(const Airport &airport, int stops) {
    this->cleanProcessState();
    this->cleanVisitedState();
    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);

    if(networkAirport == nullptr){
        cout << "Airport not found" << endl;
        return 0;
    }

    set<string> citiesVisited;

    queue<pair<NetworkAirport*,int>> q;
    q.emplace(networkAirport,0);

    networkAirport->setVisited(true);
    //citiesVisited.insert(networkAirport->getAirport().getCity());
    int counter = 0;

    while(!q.empty()){
        pair<NetworkAirport*,int> na = q.front();
        q.pop();

        if(na.second > stops){
            break;
        }

        for(auto it = na.first->getFlightsFromAirport().begin(); it!= na.first->getFlightsFromAirport().end(); it++){

            NetworkAirport* nb = it->getDestination();
            if(!nb->isVisited()){

                int distance = na.second + 1;
                q.emplace(nb,distance);
                nb->setVisited(true);

                string city = nb->getAirport().getCity();
                auto iter = citiesVisited.find(city);

                if(iter == citiesVisited.end()){
                    if(distance - 1 <= stops )
                        counter++;
                    citiesVisited.insert(city);
                }
            }
        }

    }
    return counter;
}

/** Gets the number of reachable countries from a given airport in a maximum k number of stops.
 *  Complexity: O(n^2log(n))
 * @param airport airport we want to know the reachable countries
 * @param stops maximum number of stops
 * @return number of reachable countries
 */
int AirTravelManSys::numberOfReachableCountries(const Airport &airport, int stops) {
    this->cleanProcessState();
    this->cleanVisitedState();
    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);

    if(networkAirport == nullptr){
        cout << "Airport not found" << endl;
        return 0;
    }

    set<string> countriesVisited;
    queue<pair<NetworkAirport*,int>> q;
    q.emplace(networkAirport,0);

    networkAirport->setVisited(true);
    //countriesVisited.insert(networkAirport->getAirport().getCountry());
    int counter = 0;

    while(!q.empty()){
        pair<NetworkAirport*,int> na = q.front();
        q.pop();

        if(na.second > stops){
            break;
        }

        for(auto it = na.first->getFlightsFromAirport().begin(); it!= na.first->getFlightsFromAirport().end(); it++){

            NetworkAirport* nb = it->getDestination();
            if(!nb->isVisited()){

                int distance = na.second + 1;
                q.emplace(nb, distance);
                nb->setVisited(true);

                string country = nb->getAirport().getCountry();
                auto iter = countriesVisited.find(country);

                if(iter == countriesVisited.end()){
                    if(distance - 1 <= stops)
                        counter++;
                    countriesVisited.insert(country);
                }
            }
        }

    }
    return counter;
}

/** Gets the number of reachable airports from a given airport in an unlimited number of stops
 *  Complexity: O(n^2)
 * @param airport airport we want to know the reachable airports
 * @return number of reachable airports
 */
int AirTravelManSys::numberOfReachableAirportsFromAirport(const Airport &airport) {
    this->cleanVisitedState();
    queue<NetworkAirport*> q;
    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);
    networkAirport->setVisited(true);
    vector<Airport> reachableAirports;
    q.push(networkAirport);

    while(!q.empty()){
        NetworkAirport* targetNetworkAirport = q.front();
        q.pop();

        for(const auto& flight : targetNetworkAirport->getFlightsFromAirport()){
            if(!flight.getDestination()->isVisited()){
                flight.getDestination()->setVisited(true);
                q.push(flight.getDestination());
                reachableAirports.push_back(targetNetworkAirport->getAirport());
            }
        }
    }

    return reachableAirports.size();
}

/** Gets the number of reachable cities from a given airport in an unlimited number of stops
 *  Complexity: O(n^2log(n))
 * @param airport airport we want to know the reachable cities
 * @return number of reachable cities
 */
int AirTravelManSys::numberOfReachableCitiesFromAirport(const Airport &airport) {
    this->cleanVisitedState();
    queue<NetworkAirport*> q;
    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);
    networkAirport->setVisited(true);
    unordered_set<string> reachableCities;
    q.push(networkAirport);

    while(!q.empty()){
        NetworkAirport* targetNetworkAirport = q.front();
        q.pop();

        for(const auto& flight : targetNetworkAirport->getFlightsFromAirport()){

            if(!flight.getDestination()->isVisited()){
                flight.getDestination()->setVisited(true);
                q.push(flight.getDestination());

                if(reachableCities.find(flight.getDestination()->getAirport().getCity()) == reachableCities.end()){
                    reachableCities.insert(flight.getDestination()->getAirport().getCity());
                }
            }
        }
    }

    return reachableCities.size();
}

/** Gets the number of reachable countries from a given airport in an unlimited number of stops
 *  Complexity: O(n^2log(n))
 * @param airport airport we want to know the reachable countries
 * @return number of reachable countries
 */
int AirTravelManSys::numberOfReachableCountriesFromAirport(const Airport &airport) {
    this->cleanVisitedState();
    queue<NetworkAirport*> q;
    NetworkAirport* networkAirport = flightNetwork.findAirport(airport);
    networkAirport->setVisited(true);
    unordered_set<string> reachableCountries;
    q.push(networkAirport);

    while(!q.empty()){
        NetworkAirport* targetNetworkAirport = q.front();
        q.pop();

        for(const auto& flight : targetNetworkAirport->getFlightsFromAirport()){
            if(!flight.getDestination()->isVisited()){
                flight.getDestination()->setVisited(true);
                q.push(flight.getDestination());

                if(reachableCountries.find(flight.getDestination()->getAirport().getCountry()) == reachableCountries.end()){
                    reachableCountries.insert(flight.getDestination()->getAirport().getCountry());
                }
            }
        }
    }

    return reachableCountries.size();
}


/** BFS used to help find the maximum distance between airports.
 *  Complexity: O(n^2)
 * @param networkAirport  Airport from where the visit starts
 * @return Vector with a pairs  of airports  and distances from the airport source
 */
vector<pair<NetworkAirport*,int>> bfsAirportVisit(NetworkAirport *networkAirport){
    vector<pair<NetworkAirport*,int>> v;
    vector<pair<NetworkAirport*,int>> distanceToDestination;
    networkAirport->setVisited(true);
    queue<pair<NetworkAirport*,int>> q;
    q.emplace(networkAirport,0);
    NetworkAirport* targetAirport;
    int distance;

    while(!q.empty()){
        targetAirport = q.front().first;
        distance = q.front().second;
        q.pop();
        v.emplace_back(targetAirport,distance);

        for(const auto& flight : targetAirport->getFlightsFromAirport()){
            if(!flight.getDestination()->isVisited()){

                flight.getDestination()->setVisited(true);
                q.emplace(flight.getDestination(),distance + 1);
            }
        }
    }

    for(auto pair : v){

        if(pair.second == distance){
            distanceToDestination.emplace_back(pair.first,pair.second);
        }
    }
    return distanceToDestination;
}

/** Gets the maximum trip possible in the network.
 *  Complexity: O(n^3)
 * @param maxTripAirportPairs Vector with the pair of airports(source, destination) with the maximum trip value
 * @return Maximum trip value
 */
int AirTravelManSys::maxTrip(vector<pair<Airport, Airport>>& maxTripAirportPairs) {
  int maxTrip = 0;
  vector<pair<NetworkAirport*,int>> distanceToDestination;

  for(auto networkAirport : flightNetwork.getFlightNetwork()){
      cleanVisitedState();
      cleanProcessState();
      distanceToDestination = bfsAirportVisit(networkAirport);

      if(!distanceToDestination.empty()){

          if(distanceToDestination.at(0).second >= maxTrip){

              if(distanceToDestination.at(0).second > maxTrip){
                  maxTripAirportPairs.clear();
              }

              maxTrip = distanceToDestination.at(0).second;

              for(auto pair : distanceToDestination){
                  maxTripAirportPairs.emplace_back(networkAirport->getAirport(),pair.first->getAirport());
              }
          }
      }
  }
  return maxTrip;
}

/** Auxiliary function to compare to airports by their number of flights
 *  Complexity: O(1)
 * @param networkAirport1 airport to compare
 * @param networkAirport2 airport to compare
 * @return comparison between the number of flights
 */
bool compAirportByFlights(NetworkAirport* networkAirport1, NetworkAirport* networkAirport2){
    return (networkAirport1->getNumberOfFlightsFromAirport()+networkAirport1->getNumberOfFlightsToAirport()) >
            (networkAirport2->getNumberOfFlightsFromAirport()+networkAirport2->getNumberOfFlightsToAirport());
}

/** Gets the top k airport with most air traffic(flights)
 *  Complexity: O(nlog(n))
 * @param k  number of top airports
 */
vector<NetworkAirport*> AirTravelManSys::topKAirportCapacity(int k) {
    vector<NetworkAirport*> networkAirports {flightNetwork.getFlightNetwork().begin(), flightNetwork.getFlightNetwork().end()};
    sort(networkAirports.begin(), networkAirports.end(), compAirportByFlights);

    if(k > networkAirports.size())
        k = networkAirports.size();

    vector<NetworkAirport*> subVector {networkAirports.begin(), networkAirports.begin() + k};

    return subVector;
}

/** Auxiliary recursive function that does a dfs searches in order to help compute the articulation points of the network
 *  Complexity: O(n^2)   (O(V + E) where V is the number of airports in the network and E the number of flights)
 * @param networkAirport pointer to the airport where the dfs search is meant to start
 * @param airportStack auxiliary stack to store the airports that are traversed during the search
 * @param essentialAirports unordered set that is passed to the method by reference and is used to store the essential airports of the network
 * @param i auxiliary counter
 * @return unordered set of the essential airports in the network
 */
void dfsForEssentialAirports(NetworkAirport* networkAirport, stack<Airport>& airportStack, unordered_set<Airport>& essentialAirports, int& i){
    i++;
    int children = 0;
    networkAirport->setNum(i);
    networkAirport->setLow(i);
    airportStack.push(networkAirport->getAirport());

    for(const auto& flight : networkAirport->getFlightsFromAirport()){

        if(flight.getDestination()->getNum() == 0){
            children++;
            dfsForEssentialAirports(flight.getDestination(),airportStack,essentialAirports,i);
            networkAirport->setLow(min(networkAirport->getLow(),flight.getDestination()->getLow()));

            if(networkAirport->getNum() != 1 && flight.getDestination()->getLow() >= networkAirport->getNum()){
                essentialAirports.insert(networkAirport->getAirport());
            }
        }

        else if(flight.getDestination()->getNum() > 0){
            networkAirport->setLow(min(networkAirport->getLow(),flight.getDestination()->getNum()));
        }

    }

    airportStack.pop();

    if(networkAirport->getNum() == 1 && children > 1){
        essentialAirports.insert(networkAirport->getAirport());
    }

}

/** Auxiliary  function that duplicates the flights in the flight system
 *  Complexity: O(N^2)
 * @param flightNetwork targetFlightNetwork
 */
void doubleNetworkFlights(unordered_set<NetworkAirport *, HashNetworkAirport, EqualityNetworkAirport>& flightNetwork){
    for(auto networkAirport : flightNetwork){
        for(const auto& flight : networkAirport->getFlightsFromAirport()){
            flight.getDestination()->addFlight(networkAirport,flight.getAirLine());
        }
    }
}

/** Auxiliary function that reAdds temporarily removed airports to the network
 *  Complexity: O(n)
 */
void AirTravelManSys::reAddAirportsToFlightNetwork(){
    for(const Airport& airport : Airports){
        flightNetwork.addNetworkAirport(airport);
    }
}

/** Gets the essential airports in the flight network(articulation points)
 *  Complexity:  O(n^2) (O(V + E) where V is the number of airports in the network and E the number of flights)
 * @return unordered set of the essential airports in the network
 */
unordered_set<Airport> AirTravelManSys::essentialAirports() {
    int i = 0;
    unordered_set<Airport> essentialAirports;
    stack<Airport> airportStack;
    Airline airline;
    cleanVisitedState();
    unordered_set<NetworkAirport *, HashNetworkAirport, EqualityNetworkAirport> copyFlightNetwork = flightNetwork.getFlightNetwork();
    doubleNetworkFlights(copyFlightNetwork);

    for(auto networkAirport : copyFlightNetwork){

        if(networkAirport->getNum() == 0){
            dfsForEssentialAirports(networkAirport,airportStack,essentialAirports,i);
        }

    }

    flightNetwork.resetFlightNetwork();
    reAddAirportsToFlightNetwork();
    readFlightsDataFile();
    return essentialAirports;
}

// Best Flight Options -------------------------------------------------------------------------------------------


/** Gets all the airport in a city
 * Complexity: O(1)
 * @param city Name of the city
 * @return Vector with all the airport found
 */
vector<NetworkAirport*> AirTravelManSys::convertCityToAirports(const std::string& city, const FlightNetwork& flightNetwork1) {
    auto it = cityToAirport.find(city);
    vector<Airport> airports1;
    vector<NetworkAirport*> networkAirports;
    if(it == cityToAirport.end()){
        cout << "City not found" << endl;
        return networkAirports;
    }
    else{
        airports1 = it->second;
        for(const Airport& airport: airports1){
            NetworkAirport* networkAirport = flightNetwork1.findAirport(airport);
            networkAirports.push_back(networkAirport);
        }
        return networkAirports;
    }
}


/** Auxiliary function to calculate the distance.
 *  Complexity: O(log(n))
 * @param latitude Latitude of the location
 * @param longitude Longitude of the location
 * @param airportLocation Location of the airport we want to calculate the distance
 * @return  Distance
 */
double distanceCoordinates(double latitude, double longitude, Location airportLocation){
    // distance between latitudes
    // and longitudes
    double dLat = (latitude - airportLocation.getLatitude()) *
                  M_PI / 180.0;
    double dLon = (longitude - airportLocation.getLongitude()) *
                  M_PI / 180.0;

    // convert to radians
    double lat1 = (latitude) * M_PI / 180.0;
    double lat2 = (airportLocation.getLatitude()) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

/** Gets the nearest airport to a certain location.
 *  Complexity: O(nlog(n))
 * @param latitude Latitude of the location
 * @param longitude Longitude of the location
 * @return  Vector with the airports found
 */
vector<NetworkAirport*> AirTravelManSys::convertLocationToAirports(const double& latitude, const double& longitude, const FlightNetwork& flightNetwork1) {
    auto distance = DBL_MAX;
    vector<NetworkAirport*> networkAirports;

    for(NetworkAirport* networkAirport: flightNetwork1.getFlightNetwork()){
        double airportDistance = distanceCoordinates(latitude, longitude, networkAirport->getAirport().getLocation());
        if(airportDistance < distance){
            distance = airportDistance;
        }
    }

    for(NetworkAirport* networkAirport: flightNetwork1.getFlightNetwork()) {
        double airportDistance = distanceCoordinates(latitude, longitude, networkAirport->getAirport().getLocation());
        if (airportDistance == distance) {
            networkAirports.push_back(networkAirport);
        }
    }
        return networkAirports;
}

/** Converts code to airport.
 * Complexity: O(1)
 * @param code Code of the airport
 * @return  Airport found
 */
NetworkAirport* AirTravelManSys::convertCodeToAirport(const std::string& code, const FlightNetwork& flightNetwork1) {
    auto it = codeToAirport.find(code);

    if(it == codeToAirport.end()){
        cout << "Airport not found" << endl;
        return nullptr;
    }

    else{
        Airport airport = codeToAirport.at(code);
        NetworkAirport* networkAirport = flightNetwork1.findAirport(airport);
        return networkAirport;
    }
}

/** Converts a name into an airport.
 *  Complexity: O(n)
 * @param name  Name of the airport to convert
 * @return  Airport found
 */
NetworkAirport* AirTravelManSys::convertNameToAirport(const std::string& name, const FlightNetwork& flightNetwork1) {
    for(NetworkAirport* networkAirport : flightNetwork1.getFlightNetwork()){
        if(networkAirport->getAirport().getName() == name){
            return networkAirport;
        }
    }
    cout << "Airport not found" << endl;
    return nullptr;
}

/** Gets minimum distance/stops between two airport using a DFS approach.
 *  Complexity: O(n^2)
 * @param source  Source of the flight
 * @param destination   Destination of the flight
 * @param minDist   Minimum distance/stops found from the source to the destination
 * @param countDist     Counts the distance from the source to the destination
 */
void AirTravelManSys::findMinDistDFS(NetworkAirport* source, NetworkAirport* destination,int& minDist, int& countDist){
    source->setVisited(true);

    if(source->getAirport() == destination->getAirport()){
        if(minDist > countDist){
            minDist = countDist;
        }
    }

    else{

        for(auto it = source->getFlightsFromAirport().begin(); it != source->getFlightsFromAirport().end(); it++){
            NetworkAirport* networkAirport = it->getDestination();

            if(!networkAirport->isVisited()){
                countDist++;
                findMinDistDFS(networkAirport,destination,minDist,countDist);
            }
        }

    }

    source->setVisited(false);
    countDist--;
}

/** Gets minimum distance/stops between two airport using a BFS approach.
 *  Complexity: O(n^2)
 * @param source  Source of the flight
 * @param destination   Destination of the flight
 * @param minDist   Minimum distance/stops found from the source to the destination
 */
void AirTravelManSys::findMinDistBFS(NetworkAirport *source, NetworkAirport *destination, int &minDist, int maxMinDist) {

    queue<pair<NetworkAirport*,int>> q;
    q.emplace(source,0);

    source->setVisited(true);

    while(!q.empty()){
        pair<NetworkAirport*,int> na = q.front();
        q.pop();


        for(auto it = na.first->getFlightsFromAirport().begin(); it!= na.first->getFlightsFromAirport().end(); it++){

            NetworkAirport* nb = it->getDestination();
            if(!nb->isVisited()){

                int distance = na.second + 1;
                q.emplace(nb,distance);
                nb->setVisited(true);

                if(nb->getAirport() == destination->getAirport()){
                    //min distance found
                    minDist = distance;
                }
            }
        }

        if(minDist == na.second + 1 || na.second + 1 > maxMinDist){
            // Exist loop when min distance is found or when distance exceeds the diameter of the network
            break;
        }
    }
}

/** Gets the flight options with a certain number of stops using a DFS approach.
 *  Complexity: O(n^2)
 * @param source  Source of the flight
 * @param destination   Destination of the flight
 * @param flightOption  One of the possible flight options
 * @param flightOptions  Set of different flight options
 * @param dist  Maximum number of stops/distance from the source
 */
void AirTravelManSys::findFlightOptionsDFS(NetworkAirport* source, NetworkAirport* destination, vector<NetworkAirport*> flightOption, set<vector<NetworkAirport*>> &flightOptions, int dist){
    source->setVisited(true);
    flightOption.push_back(source);

    if(dist == 0){
        if(destination->getAirport() == source->getAirport()){
            flightOptions.insert(flightOption);
        }
    }
    else if(dist < 0){
        //stops the search
    }
    else{

        for(auto it = source->getFlightsFromAirport().begin(); it != source->getFlightsFromAirport().end(); it++ ){
            NetworkAirport* networkAirport = it->getDestination();

            if(!networkAirport->isVisited()){
                findFlightOptionsDFS(networkAirport, destination,flightOption,flightOptions, dist - 1);
            }
        }
    }

    source->setVisited(false);
}

/** Gets the flight options with a certain number of stops using a BFS approach.
 *  Complexity: O(n^2) (O(n^3) when a flight path is found (worst case))
 * @param source  Source of the flight
 * @param destination   Destination of the flight
 * @param flightOptions  Set of different flight options
 * @param dist  Maximum number of stops/distance from the source
 */
void AirTravelManSys::findFlightOptionsBFS(NetworkAirport *source, NetworkAirport *destination, set<vector<NetworkAirport *>> &flightOptions, int dist){
    vector<ParentChild> parents;
    queue<ParentChild> q; //pair parents index and child index and child source and distance
    ParentChild node = make_pair(make_pair(-1,0), make_pair(source,0));
    parents.push_back(node);
    q.push(node);

    int i = 0;
    source->setVisited(true);

    while(!q.empty()){
        //BFS loop

        ParentChild na = q.front();
        q.pop();


        for(auto it = na.second.first->getFlightsFromAirport().begin(); it!= na.second.first->getFlightsFromAirport().end(); it++){
            NetworkAirport* nb = it->getDestination();

            if(!nb->isVisited()){
                i++; //index for the parents vector
                int distance = na.second.second + 1; //distance from the source
                node = make_pair((make_pair(na.first.second,i)), make_pair(nb, distance)); //node(pair) to insert in the queue and parents vector
                q.emplace(node);
                nb->setVisited(true);

                if(nb->getAirport() == destination->getAirport() && distance == dist){
                    //found one flight option
                    buildFlightOption(node,parents,flightOptions);
                    nb->setVisited(false);
                }

                parents.push_back(node);
            }
        }

        na.second.first->setVisited(false);
        if(dist < na.second.second){
            //every flight option in the minimum distance range was found
            break;
        }
    }

}

/** Builds the flight path and puts it in the set with the other flight paths.
 *  Complexity: O(n)
 * @param root Destination of the flight path and source for search the other stops
 * @param parents Vector with the parent nodes
 * @param flightOptions Set of different flight options
 */
void AirTravelManSys::buildFlightOption(ParentChild root, vector<ParentChild> parents, set<vector<NetworkAirport *>> &flightOptions) {
    vector<NetworkAirport*> flightOption;
    while(true){
        auto it = flightOption.begin();
        flightOption.insert(it,root.second.first);
        int pos = root.first.first;
        if(pos == -1){
            break;
        }
        root = parents.at(pos);

    }
    flightOptions.insert(flightOption);
}

/** Finds the best flight path (minimum stops) with no filters
 *  Complexity: O(n^3) (O(n^4) only if we have a lot of possible sources and destinations)
 * @param sources
 * @param destinations
 * @return Set of flight paths
 */
set<vector<NetworkAirport *>> AirTravelManSys::bestFlightOption(const vector<NetworkAirport *>& sources, const vector<NetworkAirport *>& destinations) {
    int maxMinDist = flightNetwork.maxTrip();
    cleanVisitedState();
    cleanProcessState();

    int minDist = INT_MAX;


    //find the minimum distance between the airports
    for(NetworkAirport* source: sources){
        for(NetworkAirport* destination: destinations){
            findMinDistBFS(source, destination,minDist,maxMinDist);
        }
    }

    set<vector<NetworkAirport*>> flightOptions;

    if(minDist > maxMinDist){
        return flightOptions;
    }

    //find the different flight options from the possible sources to the destination
    for(NetworkAirport* source: sources){
        for(NetworkAirport* destination: destinations){
            cleanVisitedState();
            findFlightOptionsBFS(source, destination,flightOptions, minDist);
        }
    }

return flightOptions;
}


/** Filter the flights in order to only include certain airlines.
 *  Complexity: O(n^2)
 * @param airlines Set of desired airlines
 * @return  Filtered flight network
 */
FlightNetwork AirTravelManSys::flightNetworkFilteredByDesiredAirlines(unordered_set<Airline> airlines) {
    FlightNetwork filteredFlightNetwork;

    for (auto networkAirport: flightNetwork.getFlightNetwork()) {
        filteredFlightNetwork.addNetworkAirport(networkAirport->getAirport());
    }

    for (auto networkAirport: flightNetwork.getFlightNetwork()) {

        for (const auto &flight: networkAirport->getFlightsFromAirport()) {

            if (airlines.find(flight.getAirLine()) != airlines.end()) {
                filteredFlightNetwork.addFlight(networkAirport->getAirport(), flight.getDestination()->getAirport(),
                                                flight.getAirLine());
            }
        }
    }
    return filteredFlightNetwork;
}

/** Filter the flights in order to exclude undesired airlines.
 *  Complexity: O(n^2)
 * @param airlines Set of undesired airlines
 * @return  Filtered flight network
 */
FlightNetwork AirTravelManSys::flightNetworkFilteredByUndesiredAirlines(unordered_set<Airline> airlines) {
    FlightNetwork filteredFlightNetwork;
    for (auto networkAirport: flightNetwork.getFlightNetwork()) {
        filteredFlightNetwork.addNetworkAirport(networkAirport->getAirport());
    }
    for (auto networkAirport: flightNetwork.getFlightNetwork()) {
        for (const auto &flight: networkAirport->getFlightsFromAirport()) {
            if (airlines.find(flight.getAirLine()) == airlines.end()) {
                filteredFlightNetwork.addFlight(networkAirport->getAirport(), flight.getDestination()->getAirport(),
                                                flight.getAirLine());
            }
        }
    }
    return filteredFlightNetwork;
}

/** Finds the best flight path (minimum stops) with filters
 *  Complexity: O(n^3) (O(n^4) only if we have a lot of possible sources and destinations)
 * @param sources
 * @param destinations
 * @param flightNetwork1 Filtered flightNetwork.
 * @return Set of flight paths
 */
set<vector<NetworkAirport *>> AirTravelManSys::bestFlightOptionInFilteredNetwork(const vector<NetworkAirport *>& sources, const vector<NetworkAirport *>& destinations, FlightNetwork& flightNetwork1) {
    int maxMinDist = flightNetwork1.maxTrip();
    flightNetwork1.cleanVisitedState();
    flightNetwork1.cleanProcessState();

    int minDist = INT_MAX;

    //find the minimum distance between the airports
    for(NetworkAirport* source: sources){
        for(NetworkAirport* destination: destinations){
            flightNetwork1.cleanVisitedState();
            findMinDistBFS(source, destination,minDist,maxMinDist);
        }
    }

    set<vector<NetworkAirport*>> flightOptions;

    if(minDist > maxMinDist){
        return flightOptions;
    }

    //find the different flight options from the possible sources to the destination
    for(NetworkAirport* source: sources){
        for(NetworkAirport* destination: destinations){
            flightNetwork1.cleanVisitedState();
            findFlightOptionsBFS(source, destination,flightOptions, minDist);
        }
    }

    return flightOptions;
}

void AirTravelManSys::findMinDistDFSWithAirlineLimit(NetworkAirport* source, NetworkAirport* destination,int& minDist, int& countDist, int& airlineCount, const int& airlineLimit,Airline airline){
    source->setVisited(true);


    if(source->getAirport() == destination->getAirport()){
        if(minDist > countDist){
            minDist = countDist;
        }
    }

    else{

        for(auto it = source->getFlightsFromAirport().begin(); it != source->getFlightsFromAirport().end(); it++){
            NetworkAirport* networkAirport = it->getDestination();

            if(!networkAirport->isVisited()){
                if(it->getAirLine() == airline){
                    countDist++;
                    findMinDistDFSWithAirlineLimit(networkAirport,destination,minDist,countDist,airlineCount,airlineLimit,airline);
                }
                else{
                    if(airlineCount < airlineLimit){
                        countDist++;
                        int newAirlineCount = airlineCount + 1;
                        Airline newAirline = it->getAirLine();
                        findMinDistDFSWithAirlineLimit(networkAirport,destination,minDist,countDist,newAirlineCount,airlineLimit,newAirline);
                    }
                }
            }
        }

    }
    source->setVisited(false);
    countDist--;
}

void AirTravelManSys::findFlightOptionsDFSWithAirlineLimit(NetworkAirport* source, NetworkAirport* destination, vector<pair<NetworkAirport*,Airline>> flightOption, set<vector<pair<NetworkAirport*,Airline>>> &flightOptions, int dist, int airlineCount, const int& airlineLimit, Airline airline){
    source->setVisited(true);
    flightOption.emplace_back(source,airline);

    if(dist == 0){
        if(destination->getAirport() == source->getAirport()){
            flightOptions.insert(flightOption);
        }
    }
    else if(dist < 0){
        //stops the search
    }
    else{

        for(auto it = source->getFlightsFromAirport().begin(); it != source->getFlightsFromAirport().end(); it++ ){
            NetworkAirport* networkAirport = it->getDestination();

            if(!networkAirport->isVisited()){
                if(airline == it->getAirLine()){
                    findFlightOptionsDFSWithAirlineLimit(networkAirport, destination,flightOption,flightOptions, dist - 1,airlineCount,airlineLimit,airline);
                }
                else{
                    if(airlineCount < airlineLimit){
                        Airline newAirline = it->getAirLine();
                        int newAirlineCount = airlineCount + 1;
                        findFlightOptionsDFSWithAirlineLimit(networkAirport, destination,flightOption,flightOptions, dist - 1,newAirlineCount,airlineLimit,newAirline);
                    }
                }
            }
        }
    }
    source->setVisited(false);
}

void AirTravelManSys::findMinDistBFSWithAirlineLimit(NetworkAirport *source, NetworkAirport *destination, int &minDist, const int &airlineLimit) {
    queue<pair<pair<NetworkAirport*,Airline>,pair<int,int>>> q;
    Airline airline{"FFFF","FFFF","FFFF","FFFF"};
    q.emplace(make_pair(source,airline), make_pair(0,0));
    source->setVisited(true);
    while(!q.empty()){
        NetworkAirport* targetAirport = q.front().first.first;
        airline = q.front().first.second;
        int distance = q.front().second.first;
        int airlineCounter = q.front().second.second;
        q.pop();
        bool canBeDestAirport = false;
        for(const auto& flight : targetAirport->getFlightsFromAirport()){
            if(!flight.getDestination()->isVisited()){
                if(flight.getAirLine() == airline){
                    q.emplace(make_pair(flight.getDestination(),flight.getAirLine()), make_pair(distance,airlineCounter));
                    flight.getDestination()->setVisited(true);
                    canBeDestAirport = true;
                }
                else{
                    if(airlineCounter < airlineLimit){
                        q.emplace(make_pair(flight.getDestination(),flight.getAirLine()), make_pair(distance,airlineCounter + 1));
                        flight.getDestination()->setVisited(true);
                        canBeDestAirport = true;
                    }
                }
                if(canBeDestAirport && flight.getDestination()->getAirport() == destination->getAirport()){
                    minDist = distance;
                }
            }
        }
        if(minDist == distance + 1){
            break;
        }
    }
}

void AirTravelManSys::findFlightOptionsBFSWithAirlineLimit(NetworkAirport *source, NetworkAirport *destination, set<vector<NetworkAirport *>> &flightOptions, int dist, int airlineLimit){
    vector<ParentChild> parents;
    queue<pair<ParentChild,pair<Airline,int>>> q; //pair parents index and child index and child source and distance with airline counter
    ParentChild node = make_pair(make_pair(-1,0), make_pair(source,0));
    Airline airline;
    parents.emplace_back(node);
    q.emplace(node, make_pair(airline,0));

    int i = 0;
    source->setVisited(true);

    while(!q.empty()){
        //BFS loop

        ParentChild na = q.front().first;

        airline = q.front().second.first;

        int airlineCounter = q.front().second.second;


        q.pop();


        for(auto it = na.second.first->getFlightsFromAirport().begin(); it!= na.second.first->getFlightsFromAirport().end(); it++){
            NetworkAirport* nb = it->getDestination();

            if(!nb->isVisited()){
                if(airline == it->getAirLine()){
                    i++; //index for the parents vector
                    int distance = na.second.second + 1; //distance from the source
                    node = make_pair((make_pair(na.first.second,i)), make_pair(nb, distance)); //node(pair) to insert in the queue and parents vector
                    q.emplace(node, make_pair(airline,airlineCounter));
                    nb->setVisited(true);
                    if(nb->getAirport() == destination->getAirport() && distance == dist){
                        //found one flight option
                        buildFlightOption(node,parents,flightOptions);
                        nb->setVisited(false);
                    }
                    parents.push_back(node);
                }
                else{
                    if(airlineCounter < airlineLimit){
                        i++; //index for the parents vector
                        int distance = na.second.second + 1; //distance from the source
                        node = make_pair((make_pair(na.first.second,i)), make_pair(nb, distance)); //node(pair) to insert in the queue and parents vector
                        q.emplace(node, make_pair(it->getAirLine(),airlineCounter + 1));
                        nb->setVisited(true);
                        if(nb->getAirport() == destination->getAirport() && distance == dist){
                            //found one flight option
                            buildFlightOption(node,parents,flightOptions);
                            nb->setVisited(false);
                        }
                        parents.push_back(node);
                    }
                }
            }
        }
        na.second.first->setVisited(false);
        if(dist < na.second.second){
            //every flight option in the minimum distance range was found
            break;
        }
    }

}

set<vector<pair<NetworkAirport *,Airline>>> AirTravelManSys::bestFlightOptionWithAirlineLimit(const vector<NetworkAirport *> &sources,const vector<NetworkAirport *> &destinations, const int &airlineLimit) {
    int maxMinDist = flightNetwork.maxTrip();
    cleanVisitedState();
    cleanProcessState();
    int minDist = INT_MAX;
    Airline mockAirline{"FFFF","FFFF","FFFF","FFFF"};
    for(auto source : sources){
        for(auto destination : destinations){
            int countDist = 0;
            int airlineCount = 0;
            findMinDistDFSWithAirlineLimit(source,destination,minDist,countDist,airlineCount,airlineLimit,mockAirline);
        }
    }
    set<vector<pair<NetworkAirport *,Airline>>> bestFlightOptions;
    if(minDist == INT_MAX){
        return bestFlightOptions;
    }
    for(auto source : sources){
        for(auto destination : destinations){
            vector<pair<NetworkAirport*,Airline>> flightOption;
            int airlineCount = 0;
            findFlightOptionsDFSWithAirlineLimit(source,destination,flightOption,bestFlightOptions,minDist,airlineCount,airlineLimit,mockAirline);
        }
    }

    return bestFlightOptions;
}







