//
// Created by franc on 19/12/2023.
//

#ifndef TRABALHOAED2_FLIGHTNETWORK_H
#define TRABALHOAED2_FLIGHTNETWORK_H

#endif //TRABALHOAED2_FLIGHTNETWORK_H
#include "unordered_set"
#include "NetworkAirports.h"

using namespace std;

class FlightNetwork{
 private:
    unordered_set<NetworkAirport*> flightNetwork;
 public:
    NetworkAirport* findAirport(Airport airport) const;
    bool addNetworkAirport(Airport airport);
    bool removeNetworkAirport(Airport airport);
    unordered_set<NetworkAirport*> getFlightNetwork() const;
    bool addFlight(Airport departureAirport, Airport destinationAirport, Airline airline);
    bool removeFlight(Airport departureAirport,Airport destinationAirport, Airline airline);


};
