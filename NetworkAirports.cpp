//
// Created by franc on 18/12/2023.
//
#include "FlightNetwork.h"


NetworkAirport::NetworkAirport(Airport airport) {
    this->airport = airport;
    visited = false;
    processed = false;
    num = 0;
    low = 0;
}


const vector<Flight> &NetworkAirport::getFlightsFromAirport() const {
    return flightsFromAirport;
}

int NetworkAirport::getNumberOfFlightsToAirport() const {
    return numberOfFlightsToAirport;
}

int NetworkAirport::getNumberOfFlightsFromAirport() const {
    return numberOfFlightsFromAirport;
}

bool NetworkAirport::isVisited() const {
    return visited;
}

void NetworkAirport::setVisited(bool b) {
    visited = b;
}

bool NetworkAirport::isProcessing() const {
    return processed;
}

void NetworkAirport::setProcessing(bool b) {
    processed = b;
}

void NetworkAirport::addFlight(NetworkAirport* networkAirport, Airline airline) {
    Flight flight;
    flight.setDestination(networkAirport);
    flight.setAirline(airline);
    flightsFromAirport.push_back(flight);
}

void NetworkAirport::removeFlightTo(NetworkAirport* destinationAirport, Airline airline) {
    Flight flight;
    flight.setDestination(destinationAirport);
    flight.setAirline(airline);
    auto it = std::find(flightsFromAirport.begin(), flightsFromAirport.end(),flight);
    flightsFromAirport.erase(it);
}

int NetworkAirport::getNum() const {
    return num;
}

void NetworkAirport::setNum(int num) {
    this->num = num;
}

int NetworkAirport::getLow() const {
    return low;
}

void NetworkAirport::setLow(int low) {
    this->low = low;
}

bool NetworkAirport::operator==(const NetworkAirport &networkAirport) const {
    return airport == networkAirport.airport;
}

Airport NetworkAirport::getAirport() const {
    return airport;
}




