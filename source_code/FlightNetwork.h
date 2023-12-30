//
// Created by franc on 19/12/2023.
//

#ifndef TRABALHOAED2_FLIGHTNETWORK_H
#define TRABALHOAED2_FLIGHTNETWORK_H


#include "unordered_set"
#include "Airport.h"
#include "Airline.h"

using namespace std;

/**
 * @file FlightNetwork.h
 * @brief Definition of class Flight (Edge), NetworkAirport (Vertex) and FlightNetwork (Graph).
 *
 */

class Flight;
class NetworkAirport;
class FlightNetwork;


/**
 *\class Flight
 * Where are preformed functions related to the Flights/edges.
 * Stores the destination NetworkAirport, airline and distance.
 */
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

};

/**
 *\class NetworkAirport
 * Where are preformed functions related to the NetworkAirports/vertexes.
 * Stores the airport (info), vector with the flights, number of flights from the airport, number of flights to the airport,
 * visited state, precessed state and auxiliary values num and low.
 */
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

    size_t hash() const
    {
            return std::hash<Airport>()(airport) >> 1;
    }

};

struct HashNetworkAirport {
    size_t operator()(const NetworkAirport *networkAirport) const {
        return networkAirport->hash();
    }
};

struct EqualityNetworkAirport{
    bool operator()(const NetworkAirport* n1, NetworkAirport* n2) const{
        return *n1 == *n2;
    }
};


/**
 *\class FlightNetwork
 * Where are preformed functions related to the FlightsNetwork/graph.
 * Stores the flightNetwork (all the NetworkAirports/vertexes).
 */
class FlightNetwork{
 private:
    unordered_set<NetworkAirport*,HashNetworkAirport,EqualityNetworkAirport> flightNetwork;
 public:
    NetworkAirport* findAirport(Airport airport) const;
    bool addNetworkAirport(Airport airport);
    bool removeNetworkAirport(Airport airport);
    unordered_set<NetworkAirport *, HashNetworkAirport, EqualityNetworkAirport> getFlightNetwork() const;
    bool addFlight(Airport departureAirport, Airport destinationAirport, Airline airline) const;
    bool removeFlight(Airport departureAirport,Airport destinationAirport, Airline airline) const;
    void resetFlightNetwork();
    void cleanProcessState();
    void cleanVisitedState();
    int maxTrip();

};

#endif