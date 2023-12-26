//
// Created by lucas on 26/12/2023.
//

#include <iostream>
#include <limits>
#include "UI.h"

UI::UI() {
    AirTravelManSys airTravelManSys;
    airTravelManSys.readAirlinesDataFile();
    airTravelManSys.readAirportsDataFile();
    airTravelManSys.readFlightsDataFile();

    airTravelSys = airTravelManSys;
}

int UI::optionSelection(int &option, int min, int max){
    while(std::cout << "Enter your Option:" ){
        if(not(std::cin >> option)) {
            if (std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
                std::cout << "Aborted\n";
                return 1;
            }
            std::cout << "Please enter a valid Option (not an integer)\n";
            std::cin.clear();                            // clear the fail state
            // remove any lingering characters in the istream:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(option > max || option < min){
            std::cout << "Please enter a valid Option (integer out of range)\n";
            std::cin.clear();                            // clear the fail state
            // remove any lingering characters in the istream:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{
            //valid option inserted
            break;
        }
    }

    return 0;
}

//Menus -----------------------------------------------
int UI::mainMenu() {
    cout << "WELCOME TO THE AED AIR TRAVEL SYSTEM\n\n";

    cout << "Please insert the number corresponding to the option you want to select\n\n";

    cout << "1.Network Statistics\n";
    cout << "2.Best Flight Options\n";
    cout << "3.Best Flight Options With Filters\n";
    cout << "4.Exit\n\n";

    int option;

    int s = optionSelection(option,1,4); cout << '\n';

    if(s != 0){
        cout << "Error found\n";
        return s;
    }

    switch(option){
        case 1:
            s = networkStatisticsMenu();
            break;

        case 2:
            s = bestFlightOptionsMenu();
            break;

        case 3:
            s = bestFlightOptionsWithFiltersMenu();
            break;

        case 4:
            return 2;

        default:
            cout << "Error found\n";
            return 1;
    }

    return s;
}

int UI::networkStatisticsMenu() {
    while(true) {
        cout << "FLIGHT NETWORK STATISTICS\n\n";

        cout << "Please insert the number corresponding to the option you want to select\n\n";

        cout << "1.Global numbers (airports, flights)\n";
        cout << "2.Number of airlines that fly out of an airport\n";
        cout << "3.Number of flights per (airport, city, airline)\n";
        cout << "4.Number of different countries a city flies to\n";
        cout << "5.Number of destinations from airport (cities, airports and countries)\n";
        cout << "6.Number of reachable destinations (airports, cities, countries) from an airport in k stops\n";
        cout << "7.Maximum trip possible (greater amount of stops)\n";
        cout << "8.Top k airports with the highest air traffic (in and out flights)\n";
        cout << "9.Airports essential to the network\n";
        cout << "10.Exit to the main Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 10); cout << '\n';

        if(s != 0){
            cout << "Error found\n";
            return s;
        }

        switch(option){
            case 1:
                s = globalNumbers();
                break;

            case 2:
                s = numberOfAirlinesFromAirport();
                break;

            case 3:
                s = numberOfFlights();
                break;

            case 4:
                s = numberOfCountriesFromCity();
                break;

            case 5:
                s = numberOfDestinations();
                break;

            case 6:
                s = numberOfDestinationsInKStops();
                break;

            case 7:
                s = maximumTrip();
                break;

            case 8:
                s = topKAirportTraffic();
                break;

            case 9:
                s = essentialAirports();
                break;

            case 10:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }
    }

}

int UI::bestFlightOptionsMenu() {
    return 0;
}

int UI::bestFlightOptionsWithFiltersMenu() {
    return 0;
}


//Handlers ------------------------

int UI::globalNumbers() {
    while(true) {
        cout << "1.Airports\n";
        cout << "2.Flights\n";
        cout << "3.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 3); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        switch (option) {
            case 1:
                cout << "Total Number of Airports: " << airTravelSys.totalNumberOfAirports() << "\n\n";
                break;

            case 2:
                cout << "Total Number of Flights: " << airTravelSys.totalNumberOfFlights() << "\n\n";
                break;

            case 3:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }
    }
}

int UI::numberOfAirlinesFromAirport() {
    while(true){
        cout << "1.Number of airlines from airport\n";
        cout << "2.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 2); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        Airport airport;
        switch (option) {
            case 1:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Airports: " << airTravelSys.numberOfAirlinesInAirport(airport) << "\n\n";
                break;

            case 2:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }

    }
}

int UI::numberOfFlights() {
    while(true){
        cout << "1.Per airport\n";
        cout << "2.Per airline\n";
        cout << "3.Per city\n";
        cout << "4.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 4); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        Airport airport;
        Airline airline;
        string cityName;
        switch (option) {
            case 1:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of flights in airport " << airport.getName() << ": " << airTravelSys.numberOfAirportsFromAirport(airport) << "\n\n";
                break;

            case 2:
                s = airlineFinderCode(airline);
                if(s == 1) break; //airline not found
                cout << "Total number of flights in airline "<< airline.getName() << ":" << airTravelSys.numberOfFlightsPerAirline(airline) << "\n\n";
                break;
            case 3:
                s = cityFinder(cityName);
                if(s == 1) break; //city not found
                cout << "Total number of flights from city " << cityName << ":" << airTravelSys.numberOfFlightsFromCity(cityName) << "\n";
                cout << "Total number of flights to city " << cityName << ":" << airTravelSys.numberOfFlightsToCity(cityName) << "\n\n";
                break;

            case 4:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }

    }
}

int UI::numberOfCountriesFromCity() {
    return 0;
}

int UI::numberOfDestinations() {
    return 0;
}

int UI::numberOfDestinationsInKStops() {
    return 0;
}

int UI::maximumTrip() {
    return 0;
}

int UI::topKAirportTraffic() {
    return 0;
}

int UI::essentialAirports() {
    return 0;
}

// Auxiliary functions ----------------------------
int UI::airportFinder(Airport& airport) {
        cout << "Choose one of the options(number) to find the airport:\n\n";

        cout << "1.Code\n";
        cout << "2.Name (Some airports may have equal names, be careful)\n\n";

        int option;

        int s = optionSelection(option, 1, 2); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        switch (option) {
            case 1:
                s = airportFinderCode(airport);
                break;

            case 2:
                s = airportFinderName(airport);
                break;

            default:
                cout << "Error found\n";
                return 1;
        }


        return s;
}

int UI::airportFinderName(Airport& airport) {
    cout << "Please insert the airport name (be careful, some airports may have the same name):\n";
    string name;
    cin >> name;

    if (std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
        std::cout << "Aborted\n";
        return 1;
    }

    NetworkAirport* networkAirport = airTravelSys.convertNameToAirport(name);

    if(networkAirport == nullptr){
        return 1;
    }
    airport = networkAirport->getAirport();
    return 0;
}

int UI::airportFinderCode(Airport& airport) {
    cout << "Please insert the airport code:\n";
    string code;
    cin >> code;

    if (std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
        std::cout << "Aborted\n";
        return 1;
    }

    auto it = airTravelSys.getCodeToAirport().find(code);
    if(it == airTravelSys.getCodeToAirport().end()){
        cout << "Airport not found\n\n";
        return 1;
    }
    else{
        airport = it->second;
    }
    return 0;
}

int UI::cityFinder(string& name){
    cout << "Please insert the name of the city:\n";
    cin >> name;

    if (std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
        std::cout << "Aborted\n";
        return 1;
    }

    auto it = airTravelSys.getCityToAirport().find(name);
    if(it == airTravelSys.getCityToAirport().end()){
        cout << "City not found\n";
        return 1;
    }
    return 0;
}

int UI::airlineFinderCode(Airline& airline) {
    cout << "Please insert the airline code:\n";
    string code;
    cin >> code;

    if (std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
        std::cout << "Aborted\n";
        return 1;
    }

    auto it = airTravelSys.getCodeToAirlines().find(code);
    if(it == airTravelSys.getCodeToAirlines().end()){
        cout << "Airline not found\n";
        return 1;
    }
    else{
        airline = it->second;
    }
    return 0;
}


