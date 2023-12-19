//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_FLIGHT_H
#define TRABALHOAED2_FLIGHT_H
#include "Graph.h"
#include "Airport.h"
#include "Airline.h"

class Airport;

class Flight{
 private:
    Airport* destination;
    Airline airline;
    double distance;
public:
    Flight(){};
    Flight(Airport* destination,Airline airline,double distance);
    Flight(const Flight& otherFlight);
    Airport* getDestination() const;
    Airline getAirLine() const;
    void operator=(Flight otherFlight);

};

#endif //TRABALHOAED2_FLIGHT_H
