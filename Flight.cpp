//
// Created by franc on 18/12/2023.
//
#include "Flight.h"

Flight::Flight(Airport *destination, Airline airline, double distance) {
    this->destination = destination;
    this->airline = airline;
    this->distance = distance;
}

Airport *Flight::getDestination() const {
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



