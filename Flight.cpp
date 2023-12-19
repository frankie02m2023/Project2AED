//
// Created by franc on 18/12/2023.
//
#include "Flight.h"

Flight::Flight(NetworkAirport *airport, Airline airline) {
    this->destination = airport;
    this->airline = airline;
}

NetworkAirport *Flight::getDestination() const {
    return destination;
}

Airline Flight::getAirLine() const {
    return airline;
}

void Flight::operator=(const Flight otherFlight){
    this->destination = otherFlight.destination;
    this->airline = otherFlight.airline;
}

Flight::Flight(const Flight &otherFlight) {
    this->destination = otherFlight.destination;
    this->airline = otherFlight.airline;
}

bool Flight::operator==(const Flight& otherFlight) const {
    return destination == otherFlight.destination && airline == otherFlight.airline;
}

bool Flight::operator<(const Flight &otherFlight) {
    return false;
}

void Flight::setDestination(NetworkAirport *airport) {
    destination = airport;
}

void Flight::setAirline(Airline airline) {
    this->airline = airline;
}



