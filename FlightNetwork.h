//
// Created by franc on 19/12/2023.
//

#ifndef TRABALHOAED2_FLIGHTNETWORK_H
#define TRABALHOAED2_FLIGHTNETWORK_H

#endif //TRABALHOAED2_FLIGHTNETWORK_H
#include "unordered_set"
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Flight;
class NetworkAirport;
class FlightNetwork;


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

class NetworkAirport{
private:
    Airport airport;
    vector<Flight> flightsFromAirport;
    int numberOfFlightsToAirport;
    int numberOfFlightsFromAirport;
    bool visited;
    bool processed;
    int num;
    int low;
public:
    NetworkAirport(Airport airport);
    const vector<Flight> &getFlightsFromAirport() const;
    Airport getAirport() const;
    int getNumberOfFlightsToAirport() const;
    int getNumberOfFlightsFromAirport() const;
    int setNumberOfFlightsToAirport();
    bool isVisited() const;
    void setVisited(bool b);
    bool isProcessing() const;
    void setProcessing(bool b);
    void addFlight(NetworkAirport* airport,Airline airline);
    void removeFlightTo(NetworkAirport* destinationAirport,Airline airline);
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
    bool operator==(const NetworkAirport& networkAirport) const;
};

namespace std
{
    template <>
    struct hash<NetworkAirport>
    {
        size_t operator()(const NetworkAirport& networkAirport) const
        {
            return hash<Airport>()(networkAirport.getAirport()) >> 1;
        }

        bool operator()(const NetworkAirport& networkAirport1, const NetworkAirport& networkAirport2){
            return networkAirport1 == networkAirport2;
        }
    };
}


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

