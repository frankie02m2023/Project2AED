//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_FLIGHT_H
#define TRABALHOAED2_FLIGHT_H
#include "Graph.h"
#include "Airport.h"
#include "Airline.h"
#include "NetworkAirports.h"

class Airport;

class Flight{
 private:
    NetworkAirport* destination;
    Airline airline;
    double distance;
public:
    Flight(){};
    Flight(NetworkAirport* airport,Airline airline);
    Flight(const Flight& otherFlight);
    NetworkAirport* getDestination() const;
    Airline getAirLine() const;
    void setDestination(NetworkAirport* airport);
    void setAirline(Airline airline);
    void operator=(Flight otherFlight);
    bool operator==(const Flight& otherFlight) const;
    bool operator<(const Flight& otherFlight);
};

namespace std{
    template<>
    struct hash<Flight>
    {
        size_t operator()(const Flight& flight) const
        {
            // Compute individual hash values for two data members and combine them using XOR and bit shifting
            return ((hash<Airline>()(flight.getAirLine()) ^ (hash<Airport>()(flight.getDestination()->getAirport()) << 1)) >> 1);
        }
    };

};

#endif //TRABALHOAED2_FLIGHT_H
