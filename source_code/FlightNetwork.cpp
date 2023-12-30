//
// Created by franc on 19/12/2023.
//
#include <queue>
#include "FlightNetwork.h"

/** @file FlightNetwork.cpp
 *  @brief Implementation of FlightNetwork class
 */


/** Finds the airport in the flight network.
 * Complexity: O(1) (O(n) in the worst case scenario)
 * @param airport airport we want to find
 * @return pointer to the networkAirport
 */
NetworkAirport* FlightNetwork::findAirport(Airport airport) const {
    NetworkAirport networkAirport(airport);
    NetworkAirport* pNetworkAirport = &networkAirport;
    auto it = flightNetwork.find(pNetworkAirport);
    if(it == nullptr)
        return nullptr;
    return *it;
}

/** Adds a NetworkAirport to the flight Network.
 *  Complexity: O(1) (O(n) in the worst case scenario)
 * @param airport airport we want to add
 * @return bool value indicating if the addition was successful
 */
bool FlightNetwork::addNetworkAirport(Airport airport) {
    if(findAirport(airport) != nullptr){
        return false;
    }
    flightNetwork.insert(new NetworkAirport(airport));
    return true;
}

/** Removes a NetworkAirport from the flight network.
 *  Complexity: O(1) (O(n) in the worst case scenario)
 * @param airport airport we want to remove
 * @return bool value indicating if the removal was successful
 */
bool FlightNetwork::removeNetworkAirport(Airport airport) {
   if(findAirport(airport) == nullptr){
       return false;
   }
   NetworkAirport *networkAirport = findAirport(airport);
   flightNetwork.erase(networkAirport);
   return true;
}

/** Gets the flight network
 *  Complexity: O(1)
 * @return flight network
 */
unordered_set<NetworkAirport *,HashNetworkAirport,EqualityNetworkAirport> FlightNetwork::getFlightNetwork() const {
    return flightNetwork;
}

/** Adds flight to the flight network.
 *  Complexity: O(1)
 * @param departureAirport departure airport
 * @param destinationAirport destination airport
 * @param airline airline that does the flight
 * @return bool value indicating if the addiction was successful
 */
bool FlightNetwork::addFlight(Airport departureAirport, Airport destinationAirport, Airline airline) const {
    NetworkAirport *departureNetworkAirport = findAirport(departureAirport);
    NetworkAirport *destinationNetworkAirport = findAirport(destinationAirport);
    if(departureNetworkAirport == nullptr || destinationNetworkAirport == nullptr){
        return false;
    }
    departureNetworkAirport->addFlight(destinationNetworkAirport,airline);
    return true;
}

/** Removes flight from the flight network.
 *  Complexity: O(1)
 * @param departureAirport departure airport
 * @param destinationAirport destination airport
 * @param airline airline that does the flight
 * @return bool value indicating if the removal was successful
 */
bool FlightNetwork::removeFlight(Airport departureAirport,Airport destinationAirport,Airline airline) const {
    NetworkAirport *departureNetworkAirport = findAirport(departureAirport);
    NetworkAirport *destinationNetworkAirport = findAirport(destinationAirport);
    if(departureNetworkAirport == NULL || destinationNetworkAirport == NULL){
        return false;
    }
    departureNetworkAirport->removeFlightTo(destinationNetworkAirport,airline);
    return true;
}

void FlightNetwork::resetFlightNetwork() {
    flightNetwork.clear();
}

void FlightNetwork::cleanProcessState() {
    for(NetworkAirport* networkAirport: flightNetwork){
        networkAirport->setProcessing(false);
    }
}

void FlightNetwork::cleanVisitedState() {
    for(NetworkAirport* networkAirport: flightNetwork){
        networkAirport->setVisited(false);
    }
}

/** BFS used to help find the maximum distance between airports.
 *  Complexity: O(n^2)
 * @param networkAirport  Airport from where the visit starts
 * @return Vector with a pairs  of airports  and distances from the airport source
 */
int bfsAirportVisit1(NetworkAirport *networkAirport){
    vector<pair<NetworkAirport*,int>> v;
    int distanceToDestination;
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
            distanceToDestination = distance;
        }
    }
    return distanceToDestination;
}

/** Gets the maximum trip possible in a flight network.
 *  Complexity: O(n^3)
 * @param maxTripAirportPairs Vector with the pair of airports(source, destination) with the maximum trip value
 * @return Maximum trip value
 */
int FlightNetwork::maxTrip() {
    int maxTrip = 0;
    int distanceToDestination;

    for(auto networkAirport : flightNetwork){
        cleanVisitedState();
        cleanProcessState();
        distanceToDestination = bfsAirportVisit1(networkAirport);


            if(distanceToDestination >= maxTrip){

                maxTrip = distanceToDestination;

            }
        }

    return maxTrip;
}

