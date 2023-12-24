#include <iostream>
#include "AirTravelManSys.h"

int main() {
    AirTravelManSys travelsys;
    travelsys.readAirlinesDataFile();
    travelsys.readAirportsDataFile();
    travelsys.readFlightsDataFile();
    vector<pair<Airport,Airport>> v;
    int maxTrip = travelsys.maxTrip(v);
    cout << maxTrip << endl;
    cout << v.size();
    return 0;
}
