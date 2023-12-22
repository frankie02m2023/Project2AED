//
// Created by lucas on 20/12/2023.
//

#include "AirTravelManSys.h"
#include <fstream>
#include <iostream>
#include <set>
#include <queue>
#include <utility>

using namespace std;


//Basic getters
const unordered_map<std::string, Airline> &AirTravelManSys::getCodeToAirlines() const {
    return codeToAirlines;
}

const FlightNetwork &AirTravelManSys::getFlightNetwork() const {
    return flightNetwork;
}

const unordered_map<std::string, vector<Airport>> &AirTravelManSys::getCityToAirport() const {
    return cityToAirport;
}

const unordered_map<std::string, vector<Airport>> &AirTravelManSys::getCountryToAirport() const {
    return countryToAirport;
}

const unordered_map<std::string, Airport> &AirTravelManSys::getCodeToAirport() const {
    return codeToAirport;
}

void AirTravelManSys::cleanProcessState() {
    for(NetworkAirport* networkAirport: flightNetwork.getFlightNetwork()){
        networkAirport->setProcessing(false);
    }
}

void AirTravelManSys::cleanVisitedState() {
    for(NetworkAirport* networkAirport: flightNetwork.getFlightNetwork()){
        networkAirport->setVisited(false);
    }
}

void AirTravelManSys::setFlightNetwork(FlightNetwork NewFlightNetwork) {
    this->flightNetwork = std::move(NewFlightNetwork);
}

void AirTravelManSys::setCityToAirport(unordered_map<std::string, vector<Airport>> newCityToAirport) {
    this->cityToAirport = std::move(newCityToAirport);
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

/** Gets the number of Countries an airport flights to
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

/** Gets the number of Countries a city flights to
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

/** Gets the number of reachable cities from a given airport in a maximum k number of stops
 *  Complexity: O(n^2log(n))
 * @param airport airport we want to know the reachable airports
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

/** Gets the number of reachable countries from a given airport in a maximum k number of stops
 *  Complexity: O(n^2log(n))
 * @param airport airport we want to know the reachable airports
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
void AirTravelManSys::topKAirportCapacity(int k) {
    vector<NetworkAirport*> networkAirports {flightNetwork.getFlightNetwork().begin(), flightNetwork.getFlightNetwork().end()};
    sort(networkAirports.begin(), networkAirports.end(), compAirportByFlights);

    if(k > networkAirports.size())
        k = networkAirports.size();
    for(size_t i = 0; i < k; i++){
        NetworkAirport* networkAirport = networkAirports.at(i);

        cout << i + 1 << ". Airport name: " << networkAirport->getAirport().getName()
            <<"; code: " << networkAirport->getAirport().getCode()
            <<"; Capacity: " << networkAirport->getNumberOfFlightsFromAirport() + networkAirport->getNumberOfFlightsToAirport()
            << endl;
    }
}


