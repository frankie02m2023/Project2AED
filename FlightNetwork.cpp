//
// Created by franc on 19/12/2023.
//
#include "FlightNetwork.h"

NetworkAirport* FlightNetwork::findAirport(Airport airport) const {
    NetworkAirport networkAirport(airport);
    NetworkAirport* pNetworkAirport = &networkAirport;
    auto it = flightNetwork.find(pNetworkAirport);
    if(it == nullptr)
        return nullptr;
    return *it;
}

bool FlightNetwork::addNetworkAirport(Airport airport) {
    if(findAirport(airport) != nullptr){
        return false;
    }
    flightNetwork.insert(new NetworkAirport(airport));
    return true;
}

bool FlightNetwork::removeNetworkAirport(Airport airport) {
   if(findAirport(airport) == nullptr){
       return false;
   }
   NetworkAirport *networkAirport = findAirport(airport);
   flightNetwork.erase(networkAirport);
   return true;
}

unordered_set<NetworkAirport *,HashNetworkAirport,EqualityNetworkAirport> FlightNetwork::getFlightNetwork() const {
    return flightNetwork;
}

bool FlightNetwork::addFlight(Airport departureAirport, Airport destinationAirport, Airline airline) {
    NetworkAirport *departureNetworkAirport = findAirport(departureAirport);
    NetworkAirport *destinationNetworkAirport = findAirport(destinationAirport);
    if(departureNetworkAirport == NULL || destinationNetworkAirport == NULL){
        return false;
    }
    departureNetworkAirport->addFlight(destinationNetworkAirport,airline);
    return true;
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

