//
// Created by franc on 18/12/2023.
//
#include "FlightNetwork.h"

/** @file Flight.cpp
 *  @brief Implementation of Flight class
 */

Flight::Flight(NetworkAirport *airport, Airline airline) {
    this->destination = airport;
    this->airline = airline;
}

/** Gets the destination NetworkAirport.
 * Complexity: O(1)
 * @return destination NetworkAirport
 */
NetworkAirport *Flight::getDestination() const {
    return destination;
}

/** Gets the airline.
 * Complexity: O(1)
 * @return airline
 */
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


/** Sets the destination NetworkAirport.
 * Complexity: O(1)
 */
void Flight::setDestination(NetworkAirport *airport) {
    destination = airport;
}

/** Gets the airline.
 * Complexity: O(1)
 */
void Flight::setAirline(Airline airline) {
    this->airline = airline;
}



