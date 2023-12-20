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
#endif //TRABALHOAED2_NETWORKAIRPORTS_H
