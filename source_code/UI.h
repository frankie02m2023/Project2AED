//
// Created by lucas on 26/12/2023.
//

#ifndef TRABALHOAED2_UI_H
#define TRABALHOAED2_UI_H

#include "AirTravelManSys.h"

class UI {


/**
 * @file UI.h
 * @brief Definition of class UI.
 *
 * \class UI
 * Where are preformed functions related to the user interface(menus).
 * Stores a AirTravelManSys object.
 */

public:
    UI();
    int optionSelection(int &option,int min, int max);

    //Menus
    int mainMenu();
    int networkStatisticsMenu();
    int bestFlightOptionsMenu();
    int bestFlightOptionsWithFiltersMenu();

    //Handlers
    //NetworkStatistics handlers
    int globalNumbers();
    int numberOfAirlinesFromAirport();
    int numberOfFlights();
    int numberOfCountriesFromCity();
    int numberOfDestinationsDirect();
    int numberOfDestinationsInKStops();
    int numberOfDestinationsInUnlimitedStops();
    int maximumTrip();
    int topKAirportTraffic();
    int essentialAirports();

    //auxiliary function
    int airportFinder(Airport& airport);
    int airportFinderName(Airport& airport);
    int airportFinderCode(Airport& airport);
    int cityFinder(string& name);
    int airlineFinderCode(Airline& airline);
    int locationBuilder(Location& location);
private:
    AirTravelManSys airTravelSys;
};
#endif //TRABALHOAED2_UI_H
