//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_NETWORKAIRPORTS_H
#define TRABALHOAED2_NETWORKAIRPORTS_H
#include <string>
#include "Flight.h"
#include <unordered_set>

using namespace std;

class NetworkAirport{
 private:
    Airport airport;
    unordered_set<Flight> flightsFromAirport;
    int numberOfFlightsToAirport;
    int numberOfFlightsFromAirport;
    bool visited;
    bool processed;
    int num;
    int low;
public:
    NetworkAirport(Airport airport);
    const unordered_set<Flight> &getFlightsFromAirport() const;
    Airport getAirport() const;
    int getNumberOfFlightsToAirport() const;
    int getNumberOfFlightsFromAirport() const;
    int setNumberOfFlightsToAirport();
    bool isVisited() const;
    bool setVisited(bool b);
    bool isProcessing() const;
    void setProcessing(bool b);
    void addFlight(NetworkAirport* airport,Airline airline);
    void removeFlight(Flight* flight);
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
};
#endif //TRABALHOAED2_NETWORKAIRPORTS_H
