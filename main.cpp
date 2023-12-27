#include <iostream>
#include "AirTravelManSys.h"

int main() {
    AirTravelManSys travelsys;
    travelsys.readAirlinesDataFile();
    travelsys.readAirportsDataFile();
    travelsys.readFlightsDataFile();
    vector<pair<Airport,Airport>> pairs;
    int maxTrip = travelsys.maxTrip(pairs);
    cout << maxTrip << endl;
    for(const auto& pair : pairs) {
        cout << pair.first.getCode() << '-' << pair.second.getCode() << endl;
    }
    return 0;
}
