//
// Created by lucas on 26/12/2023.
//

#include <iostream>
#include <limits>
#include "UI.h"


/** @file UI.cpp
 *  @brief Implementation of UI class
 */

UI::UI() {
    AirTravelManSys airTravelManSys;
    airTravelManSys.readAirlinesDataFile();
    airTravelManSys.readAirportsDataFile();
    airTravelManSys.readFlightsDataFile();

    airTravelSys = airTravelManSys;
}

/** Asks for an option (integer) and the user needs to write the option on the keyboard.
 * Complexity: O(1) (worst case is O(n) were n is the time the user writes wrong options)
 * @param option Were the option value is going to be stored
 * @param min   Minimum value accepted
 * @param max   Maximum value accepted
 * @return  If there was not any error 0. Else 1.
 */
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
/** Main Menu of the system.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 * @return If there was not any error 0. Else 1.
 */
int UI::mainMenu() {
    cout << "\nWELCOME TO THE AED AIR TRAVEL SYSTEM\n\n";

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

/** Network Menu were the user chooses the options related to the network statistics.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::networkStatisticsMenu() {
    while(true) {
        cout << "\nFLIGHT NETWORK STATISTICS\n\n";

        cout << "Please insert the number corresponding to the option you want to select\n\n";

        cout << "1.Global numbers (airports, flights)\n";
        cout << "2.Number of airlines that fly out of an airport\n";
        cout << "3.Number of flights per (airport, city, airline)\n";
        cout << "4.Number of different countries a city flies to\n";
        cout << "5.Number of destinations from airport (cities, airports and countries)\n";
        cout << "6.Number of reachable destinations (airports, cities, countries) from an airport in k stops\n";
        cout << "7.Number of reachable destinations (airports, cities, countries) from an airport in unlimited stops\n";
        cout << "8.Maximum trip possible (greater amount of stops)\n";
        cout << "9.Top k airports with the highest air traffic (in and out flights)\n";
        cout << "10.Airports essential to the network\n";
        cout << "11.Exit to the main Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 11); cout << '\n';

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
                s = numberOfDestinationsDirect();
                break;

            case 6:
                s = numberOfDestinationsInKStops();
                break;

            case 7:
                s = numberOfDestinationsInUnlimitedStops();
                break;

            case 8:
                s = maximumTrip();
                break;

            case 9:
                s = topKAirportTraffic();
                break;

            case 10:
                s = essentialAirports();
                break;

            case 11:
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

/** Best Flight Option Menu were the options related to the choice of the criteria for calling the bestFlightOption method are chosen.
*  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::bestFlightOptionsMenu() {
    while(true) {
        cout << "\n BEST FLIGHT OPTION\n\n";

        cout << "Please insert the number corresponding to the criteria you want to select to choose your departure location\n\n";

        cout << "1.Airport\n";
        cout << "2.City\n";
        cout << "3.Location\n";
        cout << "4.Return to the Main Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 4);
        cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        string cityNameD;
        Airport airportD;
        Location locationD;
        vector<NetworkAirport *> networkAirportsD;
        NetworkAirport *networkAirportD;
        switch (option) {
            case 1:
                s = airportFinder(airportD);
                networkAirportD = airTravelSys.getFlightNetwork().findAirport(airportD);
                networkAirportsD.push_back(networkAirportD);
                break;

            case 2:
                s = cityFinder(cityNameD);
                networkAirportsD = airTravelSys.convertCityToAirports(cityNameD,airTravelSys.getFlightNetwork());
                break;

            case 3:
                s = locationBuilder(locationD);
                networkAirportsD = airTravelSys.convertLocationToAirports(locationD.getLatitude(),
                                                                          locationD.getLongitude(),airTravelSys.getFlightNetwork());
                break;

            case 4:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }

        cout << "Please insert the number corresponding to the criteria you want to select to choose your arrival location\n\n";

        cout << "1.Airport\n";
        cout << "2.City\n";
        cout << "3.Location\n";
        cout << "4.Return to the Main Menu\n\n";


        s = optionSelection(option, 1, 4);
        cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        string cityNameA;
        Airport airportA;
        Location locationA;
        vector<NetworkAirport *> networkAirportsA;
        NetworkAirport *networkAirportA;
        switch (option) {
            case 1:
                s = airportFinder(airportA);
                networkAirportA = airTravelSys.getFlightNetwork().findAirport(airportA);
                networkAirportsA.push_back(networkAirportA);
                break;

            case 2:
                s = cityFinder(cityNameA);
                networkAirportsA = airTravelSys.convertCityToAirports(cityNameA,airTravelSys.getFlightNetwork());
                break;

            case 3:
                s = locationBuilder(locationA);
                networkAirportsA = airTravelSys.convertLocationToAirports(locationA.getLatitude(),
                                                                          locationA.getLongitude(),airTravelSys.getFlightNetwork());
                break;

            case 4:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }

        set<vector<NetworkAirport*>> flightOptions = airTravelSys.bestFlightOption(networkAirportsD, networkAirportsA);
        int i = 1;
        for(const vector<NetworkAirport*>& opt: flightOptions){
            cout << '\n';
            cout << "Option " << i <<" : -------------" << endl;
            i++;
            for(NetworkAirport* networkAirport: opt){
                cout << "Airport code: " << networkAirport->getAirport().getCode() << "  Airport name: " << networkAirport->getAirport().getName() << endl;
            }
        }


    }
}

int UI::bestFlightOptionsWithFiltersMenu() {
    return 0;
}


//Handlers ------------------------
//NetworkStatistics handlers-------------------------

/** Shows the global Number of flights or airports.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
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

/** Shows the Number of airlines in an airport.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
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

/** Shows the Number of flights per airport , per airline or per city.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
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

/** Shows the Number of countries that can be reached directly from a city.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::numberOfCountriesFromCity() {
    while(true){
        cout << "1.Number of countries from City\n";
        cout << "2.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 2); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        string cityName;
        switch (option) {
            case 1:
                s = cityFinder(cityName);
                if(s == 1) break; //city not found
                cout << "Total Number of Countries from" << cityName << ": " <<  airTravelSys.numberOfCountriesFromCity(cityName) << "\n\n";
                break;

            case 2:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }

    }
}

/** Shows the Number of destinations (airports, cities or countries) from an airport.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::numberOfDestinationsDirect(){
    while(true) {
        cout << "1.Countries\n";
        cout << "2.Cities\n";
        cout << "3.Airports\n";
        cout << "4.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 4); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        Airport airport;
        switch (option) {
            case 1:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Countries from airport" << airport.getName() << ": " <<  airTravelSys.numberOfCountriesFromAirport(airport) << "\n\n";
                break;

            case 2:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Cities from airport" << airport.getName() << ": " <<  airTravelSys.numberOfCitiesFromAirport(airport) << "\n\n";
                break;

            case 3:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Airports from airport" << airport.getName() << ": " <<  airTravelSys.numberOfAirportsFromAirport(airport) << "\n\n";
                break;
            case 4:
                return 0;
            default:
                cout << "Error found\n";
                return 1;
        }
    }
}

/** Shows the Number of destinations (airport, countries or cities) in k stops from an airport.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::numberOfDestinationsInKStops() {
    while(true) {
        cout << "1.Countries\n";
        cout << "2.Cities\n";
        cout << "3.Airports\n";
        cout << "4.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 4); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        cout << "Select the number of stops\n\n";
        int stops;
        s = optionSelection(stops,0, 3018);

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        Airport airport;
        switch (option) {
            case 1:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Countries from airport " << airport.getName() << " in " << stops << " stops: " <<  airTravelSys.numberOfReachableCountries(airport,stops) << "\n\n";
                break;

            case 2:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Cities from airport " << airport.getName() << " in " << stops << " stops: " <<  airTravelSys.numberOfReachableCities(airport,stops) << "\n\n";
                break;

            case 3:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Airports from airport " << airport.getName() << " in " << stops << " stops: " << airTravelSys.numberOfReachableAirports(airport,stops) << "\n\n";
                break;
            case 4:
                return 0;
            default:
                cout << "Error found\n";
                return 1;
        }
    }
}

int UI::numberOfDestinationsInUnlimitedStops() {
    while(true) {
        cout << "1.Countries\n";
        cout << "2.Cities\n";
        cout << "3.Airports\n";
        cout << "4.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 4); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        Airport airport;
        switch (option) {
            case 1:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Countries from airport " << airport.getName() << " in unlimited stops : " <<  airTravelSys.numberOfReachableCountriesFromAirport(airport) << "\n\n";
                break;

            case 2:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Cities from airport " << airport.getName() << " in unlimited stops : " <<  airTravelSys.numberOfReachableCitiesFromAirport(airport) << "\n\n";
                break;

            case 3:
                s = airportFinder(airport);
                if(s == 1) break; //airport not found
                cout << "Total Number of Airports from airport " << airport.getName() << " in unlimited stops: " << airTravelSys.numberOfReachableAirportsFromAirport(airport) << "\n\n";
                break;
            case 4:
                return 0;
            default:
                cout << "Error found\n";
                return 1;
        }
    }
}

/** Shows the Maximum trip possible and the source and destination airports.
 *  Complexity: Varies on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::maximumTrip() {
    while(true){
        cout <<"1.Maximum trip\n";
        cout <<"2.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 2); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        vector<pair<Airport,Airport>> airportsPair;
        int distance;
        switch (option) {
            case 1:
                distance = airTravelSys.maxTrip(airportsPair);
                cout << "Distance: " << distance << '\n';
                for(const auto& pair: airportsPair)
                    cout << "Airport 1: " << pair.first.getName()  << " <----------> Airport 2: "<< pair.second.getName() << "\n";
                cout << '\n';
                break;

            case 2:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }

    }
}

/** Shows top k airports in terms of air traffic.
 *  Complexity: Variess on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::topKAirportTraffic() {
    while(true){
        cout <<"1.Top k Airports with the greatest air traffic capacity\n";
        cout <<"2.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option, 1, 2); cout << '\n';

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }

        cout << "Select the number of top airports you want to see\n\n";
        int k;
        s = optionSelection(k,0, 3019);

        if (s != 0) {
            cout << "Error found\n";
            return s;
        }


        vector<NetworkAirport*> topK;
        int i = 1;
        switch (option) {
            case 1:
                topK = airTravelSys.topKAirportCapacity(k);
                cout << "Top: " << k << '\n';
                for(const auto& networkAirport: topK) {
                    cout << i << ". Airport name: " << networkAirport->getAirport().getName() << " Capacity: "<< networkAirport->getNumberOfFlightsToAirport() + networkAirport->getNumberOfFlightsFromAirport() << "\n\n";
                    i++;
                }
                    cout << '\n';
                break;

            case 2:
                return 0;

            default:
                cout << "Error found\n";
                return 1;
        }

    }
}

/** Shows the airports that are essential to the network (articulation points).
 *  Complexity: Varies between on the functions called and how many times some of them are called.
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::essentialAirports() {
    while(true){
        cout <<"1.Essential Airports\n";
        cout <<"2.Return to the Network Statistics Menu\n\n";

        int option;

        int s = optionSelection(option,1,2);

        if(s != 0){
            cout << "Error found\n";
            return s;
        }

        unordered_set<Airport> essentialAirports;

        switch(option){
            case 1:
               essentialAirports = airTravelSys.essentialAirports();
               cout << "Number of essential airports : " << essentialAirports.size() << '\n'; cout << '\n';
               cout << "Essential Airports: " << '\n';
               for(const auto& airport : essentialAirports){
                   cout << airport.getCode() << ':' << airport.getName() << ',' << airport.getCity() << ',' << airport.getCountry();
                   cout << '\n';
               }
               cout << '\n';
               break;


            case 2:
               return 0;


            default:
                cout << "Error found" << '\n';
                return 1;
        }
    }
}

// Auxiliary functions ----------------------------
/** Finds the airport according to user input (name or code).
 *  Complexity: O(1) or O(N) depending on user input.
 *
 * @return If there was not any error 0. Else 1.
 */
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

/** Finds the airport according to user input (name).
 *  Complexity: O(N).
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::airportFinderName(Airport& airport) {
    cout << "Please insert the airport name (be careful, some airports may have the same name):\n";
    string name;
    cin >> name;

    if (std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
        std::cout << "Aborted\n";
        return 1;
    }

    NetworkAirport* networkAirport = airTravelSys.convertNameToAirport(name,airTravelSys.getFlightNetwork());

    if(networkAirport == nullptr){
        return 1;
    }
    airport = networkAirport->getAirport();
    return 0;
}

/** Finds the airport according to user input (code).
 *  Complexity: O(1) or O(N) if the code does not correspond to a airport.
 *
 * @return If there was not any error 0. Else 1.
 */
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

/** Finds a city  according to user input (name).
 *  Complexity: O(1) or O(N) if the city does not exists.
 *
 * @return If there was not any error 0. Else 1.
 */
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

/** Finds the airline according to user input (code).
 *  Complexity: O(1) or O(N) if the code does not correspond to a airline.
 *
 * @return If there was not any error 0. Else 1.
 */
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

/** Builds a location object according to the user input.
 *  Complexity: O(1) (O(N) in the worst scenario when the user inserts wrong values).
 *
 * @return If there was not any error 0. Else 1.
 */
int UI::locationBuilder(Location &location) {
    double latitude, longitude;

    while(std::cout << "Enter the latitude:" ){
        if(not(std::cin >> latitude)) {
            if (std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
                std::cout << "Aborted\n";
                return 1;
            }
            std::cout << "Please enter a valid latitude (not a double)\n";
            std::cin.clear();                            // clear the fail state
            // remove any lingering characters in the istream:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(latitude > 90 || latitude < -90){
            std::cout << "Please enter a valid latitude (double out of range)\n";
            std::cin.clear();                            // clear the fail state
            // remove any lingering characters in the istream:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{
            //valid option inserted
            break;
        }
    }

    while(std::cout << "Enter the longitude:" ){
        if(not(std::cin >> longitude)) {
            if (std::cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
                std::cout << "Aborted\n";
                return 1;
            }
            std::cout << "Please enter a valid longitude (not a double)\n";
            std::cin.clear();                            // clear the fail state
            // remove any lingering characters in the istream:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(longitude > 180 || longitude < -180){
            std::cout << "Please enter a valid longitude (double out of range)\n";
            std::cin.clear();                            // clear the fail state
            // remove any lingering characters in the istream:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{
            //valid option inserted
            break;
        }
    }

    location.setLatitude(latitude);
    location.setLongitude(longitude);
    return 0;
}

