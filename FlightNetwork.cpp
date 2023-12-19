//
// Created by franc on 19/12/2023.
//
#include "FlightNetwork.h"

NetworkAirport* FlightNetwork::findAirport(Airport airport) const {
    NetworkAirport networkAirport(airport);
    NetworkAirport* pNetworkAirport = &networkAirport;
    auto it = flightNetwork.find(pNetworkAirport);
    return *it;
}

bool FlightNetwork::addNetworkAirport(Airport airport) {
    if(findAirport(airport) == NULL){
        return false;
    }
    flightNetwork.insert(new NetworkAirport(airport));
    return true;
}

bool FlightNetwork::removeNetworkAirport(Airport airport) {
   if(findAirport(airport) == NULL){
       return false;
   }
   NetworkAirport *networkAirport = findAirport(airport);
   flightNetwork.erase(networkAirport);
}

unordered_set<NetworkAirport *> FlightNetwork::getFlightNetwork() const {
    return flightNetwork;
}

bool FlightNetwork::addFlight(Airport departureAirport, Airport destinationAirport, Airline airline) {
    NetworkAirport *departureNetworkAirport = findAirport(departureAirport);
    NetworkAirport *destinationNetworkAirport = findAirport(destinationAirport);
    if(departureNetworkAirport == NULL || destinationNetworkAirport == NULL){
        return false;
    }
    departureNetworkAirport->addFlight(destinationNetworkAirport,airline);
}

bool FlightNetwork::removeFlight(Airport departureAirport,Airport destinationAirport,Airline airline) {
    NetworkAirport *departureNetworkAirport = findAirport(departureAirport);
    NetworkAirport *destinationNetworkAirport = findAirport(destinationAirport);
    if(departureNetworkAirport == NULL || destinationNetworkAirport == NULL){
        return false;
    }
    departureNetworkAirport->removeFlightTo(destinationNetworkAirport,airline);
    return true;
}

