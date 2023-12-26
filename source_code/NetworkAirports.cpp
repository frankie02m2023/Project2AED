//
// Created by franc on 18/12/2023.
//
#include "FlightNetwork.h"

/** @file NetworkAirport.cpp
 *  @brief Implementation of NetworkAirport class
 */

NetworkAirport::NetworkAirport(Airport airport) {
    this->airport = airport;
    visited = false;
    processed = false;
    num = 0;
    low = 0;
    numberOfFlightsFromAirport = 0;
    numberOfFlightsToAirport = 0;
}

/** Gets the flights from the airport.
 *  Complexity: O(1)
 * @return flights from the airport
 */
const vector<Flight> &NetworkAirport::getFlightsFromAirport() const {
    return flightsFromAirport;
}

/** Gets the number of flights to the airport.
 *  Complexity: O(1)
 * @return number of flights to the airport
 */
int NetworkAirport::getNumberOfFlightsToAirport() const {
    return numberOfFlightsToAirport;
}

/** Gets the number of flights from the airport.
 *  Complexity: O(1)
 * @return number of flights from the airport
 */
int NetworkAirport::getNumberOfFlightsFromAirport() const {
    return numberOfFlightsFromAirport;
}

/** Gets the visited state.
 *  Complexity: O(1)
 * @return visited state value
 */
bool NetworkAirport::isVisited() const {
    return visited;
}

/** Sets the visited state value.
 *  Complexity: O(1)
 * @param b value to set the visited state
 */
void NetworkAirport::setVisited(bool b) {
    visited = b;
}

/** Gets the processing state.
 *  Complexity: O(1)
 * @return processing state
 */
bool NetworkAirport::isProcessing() const {
    return processed;
}

/** Sets the processing state value.
 *  Complexity: O(1)
 * @param b value to set the processing state
 */
void NetworkAirport::setProcessing(bool b) {
    processed = b;
}

/** Adds a flight to the network airport
 *
 * @param networkAirport destination airport
 * @param airline airline that will do the flight
 */
void NetworkAirport::addFlight(NetworkAirport* networkAirport, Airline airline) {
    Flight flight;
    flight.setDestination(networkAirport);
    flight.setAirline(airline);
    flightsFromAirport.push_back(flight);
    networkAirport->numberOfFlightsToAirport++;
    this->numberOfFlightsFromAirport++;
}

/** removes a flight to the network airport
 *
 * @param networkAirport destination airport
 * @param airline airline that does the flight
 */
void NetworkAirport::removeFlightTo(NetworkAirport* destinationAirport, Airline airline) {
    Flight flight;
    flight.setDestination(destinationAirport);
    flight.setAirline(airline);
    auto it = std::find(flightsFromAirport.begin(), flightsFromAirport.end(),flight);
    flightsFromAirport.erase(it);
    destinationAirport->numberOfFlightsToAirport--;
    this->numberOfFlightsFromAirport--;
}

/** Gets the num value.
 *  Complexity: O(1)
 * @return num value
 */
int NetworkAirport::getNum() const {
    return num;
}

/** Sets the num value.
 *  Complexity: O(1)
 * @param num num value
 */
void NetworkAirport::setNum(int num) {
    this->num = num;
}

/** Gets the low value.
 *  Complexity: O(1)
 * @return low value
 */
int NetworkAirport::getLow() const {
    return low;
}

/** Sets the low value.
 *  Complexity: O(1)
 * @param low low value
 */
void NetworkAirport::setLow(int low) {
    this->low = low;
}

bool NetworkAirport::operator==(const NetworkAirport &networkAirport) const {
    return airport == networkAirport.airport;
}

/** Gets the airport (info).
 *  Complexity: O(1)
 * @return airport (info)
 */
Airport NetworkAirport::getAirport() const {
    return airport;
}




