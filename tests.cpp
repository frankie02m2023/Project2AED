//
// Created by lucas on 20/12/2023.
//

#include <gtest/gtest.h>
#include "Airline.h"
#include "Airport.h"
#include "AirTravelManSys.h"
#include "Location.h"



FlightNetwork flightNetworkTest;
unordered_map<std::string, std::vector<Airport>> cityToAirportTest;

void setup1() {

    Airport airportTest1{"t1", "test1", "co1", "ci2", Location{1.0, 2.0}};
    Airport airportTest2{"t2", "test2", "co1", "ci2", Location{2.0, 3.0}};
    Airport airportTest3{"t3", "test3", "co2", "ci3", Location{20.0, 30.0}};
    Airport airportTest4{"t1", "test4", "co3", "ci8", Location{10.0, 11.0}};
    Airport airportTest5{"t1", "test5", "co2", "ci1", Location{50.0, 9.0}};
    Airport airportTest6{"t1", "test6", "co2", "ci1", Location{51.0, 52.0}};
    Airport airportTest7{"t1", "test7", "co4", "ci6", Location{30.0, 70.0}};
    Airport airportTest8{"t1", "test8", "co1", "ci7", Location{100.0, 8.0}};
    Airport airportTest9{"t1", "test9", "co1", "ci7", Location{22.0, 9.0}};
    Airport airportTest10{"t1", "test10", "co1", "ci7", Location{13.0, 79.0}};

    cityToAirportTest.insert({"ci2",{airportTest1,airportTest2}});
    cityToAirportTest.insert({"ci3",{airportTest3}});
    cityToAirportTest.insert({"ci8",{airportTest4}});
    cityToAirportTest.insert({"ci1",{airportTest5,airportTest6}});
    cityToAirportTest.insert({"ci6",{airportTest7}});
    cityToAirportTest.insert({"ci7",{airportTest8,airportTest9, airportTest10}});

    Airline airlineTest1{"at1", "airline1", "ca1", "co1"};
    Airline airlineTest2{"at2", "airline2", "ca2", "co1"};
    Airline airlineTest3{"at3", "airline3", "ca3", "co3"};
    Airline airlineTest4{"at4", "airline4", "ca4", "co2"};
    Airline airlineTest5{"at5", "airline5", "ca5", "co3"};


    flightNetworkTest.addNetworkAirport(airportTest1);
    flightNetworkTest.addNetworkAirport(airportTest2);
    flightNetworkTest.addNetworkAirport(airportTest3);
    flightNetworkTest.addNetworkAirport(airportTest4);
    flightNetworkTest.addNetworkAirport(airportTest5);
    flightNetworkTest.addNetworkAirport(airportTest6);
    flightNetworkTest.addNetworkAirport(airportTest7);
    flightNetworkTest.addNetworkAirport(airportTest8);
    flightNetworkTest.addNetworkAirport(airportTest9);
    flightNetworkTest.addNetworkAirport(airportTest10);

    //airport1 flights------------------------------------------
    flightNetworkTest.addFlight(airportTest1, airportTest2, airlineTest2);
    flightNetworkTest.addFlight(airportTest2, airportTest1, airlineTest2);

    flightNetworkTest.addFlight(airportTest1, airportTest4, airlineTest1);
    flightNetworkTest.addFlight(airportTest4,airportTest1,airlineTest1);
    flightNetworkTest.addFlight(airportTest1, airportTest4, airlineTest2);
    flightNetworkTest.addFlight(airportTest4,airportTest1,airlineTest2);

    flightNetworkTest.addFlight(airportTest1, airportTest3, airlineTest1);
    flightNetworkTest.addFlight(airportTest3,airportTest1, airlineTest1);
    flightNetworkTest.addFlight(airportTest1, airportTest3, airlineTest3);
    flightNetworkTest.addFlight(airportTest3,airportTest1, airlineTest3);

    flightNetworkTest.addFlight(airportTest1, airportTest9, airlineTest5);
    flightNetworkTest.addFlight(airportTest9, airportTest1, airlineTest5);

    //airport2 flights-------------------------------------------
    flightNetworkTest.addFlight(airportTest2, airportTest4, airlineTest2);
    flightNetworkTest.addFlight(airportTest4, airportTest2, airlineTest2);

    flightNetworkTest.addFlight(airportTest2, airportTest6, airlineTest2);
    flightNetworkTest.addFlight(airportTest6, airportTest2, airlineTest2);
    flightNetworkTest.addFlight(airportTest2, airportTest6, airlineTest5);
    flightNetworkTest.addFlight(airportTest6, airportTest2, airlineTest5);
    flightNetworkTest.addFlight(airportTest2, airportTest6, airlineTest3);
    flightNetworkTest.addFlight(airportTest6, airportTest2, airlineTest3);

    flightNetworkTest.addFlight(airportTest2, airportTest7, airlineTest3);
    flightNetworkTest.addFlight(airportTest7, airportTest2, airlineTest3);

    //airport4 flights-----------------------------------------
    flightNetworkTest.addFlight(airportTest4, airportTest6, airlineTest5);
    flightNetworkTest.addFlight(airportTest6, airportTest4, airlineTest5);

    flightNetworkTest.addFlight(airportTest4, airportTest3, airlineTest3);
    flightNetworkTest.addFlight(airportTest3, airportTest4, airlineTest3);

    flightNetworkTest.addFlight(airportTest4, airportTest8, airlineTest1);
    flightNetworkTest.addFlight(airportTest8, airportTest4, airlineTest1);

    flightNetworkTest.addFlight(airportTest4, airportTest9, airlineTest2);
    flightNetworkTest.addFlight(airportTest9, airportTest4, airlineTest2);

    //airport5 flights--------------------------------------------
    flightNetworkTest.addFlight(airportTest5, airportTest3, airlineTest1);
    flightNetworkTest.addFlight(airportTest3, airportTest5, airlineTest1);
    flightNetworkTest.addFlight(airportTest5, airportTest3, airlineTest2);
    flightNetworkTest.addFlight(airportTest3, airportTest5, airlineTest2);
    flightNetworkTest.addFlight(airportTest5, airportTest3, airlineTest5);
    flightNetworkTest.addFlight(airportTest3, airportTest5, airlineTest5);

    flightNetworkTest.addFlight(airportTest5, airportTest10, airlineTest3);
    flightNetworkTest.addFlight(airportTest10, airportTest5, airlineTest3);
    flightNetworkTest.addFlight(airportTest5, airportTest10, airlineTest4);
    flightNetworkTest.addFlight(airportTest10, airportTest5, airlineTest4);

    flightNetworkTest.addFlight(airportTest5, airportTest8, airlineTest4);
    flightNetworkTest.addFlight(airportTest8, airportTest5, airlineTest4);

    flightNetworkTest.addFlight(airportTest5, airportTest9, airlineTest2);
    flightNetworkTest.addFlight(airportTest9, airportTest5, airlineTest2);

    //airport10 flights----------------------------------------------------
    flightNetworkTest.addFlight(airportTest10, airportTest3, airlineTest1);
    flightNetworkTest.addFlight(airportTest3, airportTest10, airlineTest1);

    flightNetworkTest.addFlight(airportTest10, airportTest8, airlineTest5);
    flightNetworkTest.addFlight(airportTest8, airportTest10, airlineTest5);

}

void setup2(){
    Airport airportTest1("A","A","co1","ci1",Location{0.0,0.0});
    Airport airportTest2("B","B","co1","ci2",Location{1.0,1.0});
    Airport airportTest3("C","C","co2","ci3",Location{11.0,16.0});
    Airport airportTest4("D","D","co2","ci4",Location{11.0,18.0});

    flightNetworkTest.addNetworkAirport(airportTest1);
    flightNetworkTest.addNetworkAirport(airportTest2);
    flightNetworkTest.addNetworkAirport(airportTest3);
    flightNetworkTest.addNetworkAirport(airportTest4);

    Airline airlineTest1{"a1", "airline1", "ca1", "co2"};
    Airline airlineTest2{"a2", "airline2", "ca2", "co1"};
    Airline airlineTest3{"a3", "airline3", "ca3", "co3"};
    Airline airlineTest4{"a4", "airline4", "ca4", "co6"};
    Airline airlineTest5{"a5", "airline5", "ca5", "co3"};

    flightNetworkTest.addFlight(airportTest1,airportTest2,airlineTest1);
    flightNetworkTest.addFlight(airportTest2,airportTest3,airlineTest3);
    flightNetworkTest.addFlight(airportTest3,airportTest4,airlineTest4);
    flightNetworkTest.addFlight(airportTest4,airportTest1,airlineTest1);
}

void setup3(){
    Airport airportTest1("A","A","co1","ci1",Location{0.0,0.0});
    Airport airportTest2("B","B","co1","ci2",Location{1.0,1.0});
    Airport airportTest3("C","C","co2","ci3",Location{11.0,16.0});
    Airport airportTest4("D","D","co2","ci4",Location{11.0,18.0});
    Airport airportTest5("E","E","co2","ci3",Location{11.0,17.0});
    Airport airportTest6("F","F","co3","ci6",Location{5.0,24.0});

    flightNetworkTest.addNetworkAirport(airportTest1);
    flightNetworkTest.addNetworkAirport(airportTest2);
    flightNetworkTest.addNetworkAirport(airportTest3);
    flightNetworkTest.addNetworkAirport(airportTest4);
    flightNetworkTest.addNetworkAirport(airportTest5);
    flightNetworkTest.addNetworkAirport(airportTest6);

    Airline airlineTest1{"a1", "airline1", "ca1", "co2"};
    Airline airlineTest2{"a2", "airline2", "ca2", "co1"};
    Airline airlineTest3{"a3", "airline3", "ca3", "co3"};
    Airline airlineTest4{"a4", "airline4", "ca4", "co6"};
    Airline airlineTest5{"a5", "airline5", "ca5", "co3"};


    flightNetworkTest.addFlight(airportTest1,airportTest2,airlineTest1);
    flightNetworkTest.addFlight(airportTest1,airportTest2,airlineTest2);
    flightNetworkTest.addFlight(airportTest1,airportTest3,airlineTest2);
    flightNetworkTest.addFlight(airportTest1,airportTest6,airlineTest5);

    flightNetworkTest.addFlight(airportTest2,airportTest1,airlineTest1);
    flightNetworkTest.addFlight(airportTest2,airportTest3,airlineTest1);
    flightNetworkTest.addFlight(airportTest2,airportTest5,airlineTest1);
    flightNetworkTest.addFlight(airportTest2,airportTest6,airlineTest1);

    flightNetworkTest.addFlight(airportTest3,airportTest2,airlineTest1);
    flightNetworkTest.addFlight(airportTest3,airportTest4,airlineTest1);
    flightNetworkTest.addFlight(airportTest3,airportTest4,airlineTest5);

    flightNetworkTest.addFlight(airportTest4,airportTest2,airlineTest2);
    flightNetworkTest.addFlight(airportTest4,airportTest5,airlineTest5);

    flightNetworkTest.addFlight(airportTest5,airportTest2,airlineTest1);
    flightNetworkTest.addFlight(airportTest5,airportTest2,airlineTest1);

    flightNetworkTest.addFlight(airportTest6,airportTest1,airlineTest2);
    flightNetworkTest.addFlight(airportTest6,airportTest1,airlineTest3);
    flightNetworkTest.addFlight(airportTest6,airportTest4,airlineTest4);
}

void setup4(){
    Airport airportTest1("A","A","co1","ci1",Location{0.0,0.0});
    Airport airportTest2("B","B","co1","ci2",Location{1.0,1.0});
    Airport airportTest3("C","C","co2","ci3",Location{11.0,16.0});
    Airport airportTest4("D","D","co2","ci4",Location{11.0,18.0});
    Airport airportTest5("E","E","co2","ci3",Location{11.0,17.0});
    Airport airportTest6("F","F","co3","ci6",Location{5.0,24.0});

    flightNetworkTest.addNetworkAirport(airportTest1);
    flightNetworkTest.addNetworkAirport(airportTest2);
    flightNetworkTest.addNetworkAirport(airportTest3);
    flightNetworkTest.addNetworkAirport(airportTest4);
    flightNetworkTest.addNetworkAirport(airportTest5);
    flightNetworkTest.addNetworkAirport(airportTest6);

    Airline airlineTest1{"a1", "airline1", "ca1", "co2"};
    Airline airlineTest2{"a2", "airline2", "ca2", "co1"};
    Airline airlineTest3{"a3", "airline3", "ca3", "co3"};
    Airline airlineTest4{"a4", "airline4", "ca4", "co6"};
    Airline airlineTest5{"a5", "airline5", "ca5", "co3"};


    flightNetworkTest.addFlight(airportTest1,airportTest2,airlineTest3);
    flightNetworkTest.addFlight(airportTest1,airportTest4,airlineTest3);

    flightNetworkTest.addFlight(airportTest2,airportTest3,airlineTest3);
    flightNetworkTest.addFlight(airportTest2,airportTest4,airlineTest3);
    flightNetworkTest.addFlight(airportTest2,airportTest5,airlineTest1);
    flightNetworkTest.addFlight(airportTest2,airportTest5,airlineTest4);

    flightNetworkTest.addFlight(airportTest3,airportTest5,airlineTest4);

    flightNetworkTest.addFlight(airportTest4,airportTest1,airlineTest1);
    flightNetworkTest.addFlight(airportTest4,airportTest1,airlineTest2);
    flightNetworkTest.addFlight(airportTest4,airportTest1,airlineTest3);
    flightNetworkTest.addFlight(airportTest4,airportTest2,airlineTest1);
    flightNetworkTest.addFlight(airportTest4,airportTest6,airlineTest1);

    flightNetworkTest.addFlight(airportTest5,airportTest2,airlineTest1);
    flightNetworkTest.addFlight(airportTest5,airportTest2,airlineTest4);
}



void cleanSetup(){
    FlightNetwork cleanFlightNetwork;
    flightNetworkTest = cleanFlightNetwork;
}

TEST(Data_Readers, readAirlinesDataFile) {
    AirTravelManSys system;
    system.readAirlinesDataFile();
    EXPECT_EQ(system.getCodeToAirlines().size(), 444);

    Airline airline1 {"IBE","Iberia Airlines","IBERIA","Spain"};
    EXPECT_EQ(system.getCodeToAirlines().at("IBE"),airline1);

    Airline airline2 {"GMI","Germania","GERMANIA","Germany"};
    EXPECT_EQ(system.getCodeToAirlines().at("GMI"),airline2);

    Airline airline3 {"GWI","Germanwings","GERMAN WINGS","Germany"};
    EXPECT_EQ(system.getCodeToAirlines().at("GWI"), airline3);
}

TEST(Data_Readers, readAirportsDataFile){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    EXPECT_EQ(system.getFlightNetwork().getFlightNetwork().size(), 3019);

    EXPECT_EQ(system.getCodeToAirport().size(),3019);

    EXPECT_EQ(system.getCityToAirport().at("Paris").size(),2);

    EXPECT_EQ(system.getCountryToAirport().at("France").size(), 55);
}

TEST(Data_Readers, readFlightDataFile){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    unsigned long i = 0;
    for(NetworkAirport* na: system.getFlightNetwork().getFlightNetwork()){
        i += na->getFlightsFromAirport().size();
    }

    EXPECT_EQ(i,63832);

    Airport airport = system.getCodeToAirport().at("LAE");
    NetworkAirport *networkAirport = system.getFlightNetwork().findAirport(airport);

    EXPECT_NE(networkAirport, nullptr);
    EXPECT_EQ(networkAirport->getFlightsFromAirport().size(),11);


    Airport airportDest;
    Airline airline;
    for(const Flight& flight: networkAirport->getFlightsFromAirport()){
        if(flight.getDestination()->getAirport().getCode() == "POM"){
            if(flight.getAirLine().getCode() == "TOK"){
                airportDest = flight.getDestination()->getAirport();
                airline = flight.getAirLine();
            }
        }
    }

    EXPECT_EQ(airportDest.getCode(), "POM");
    EXPECT_EQ(airline.getCode(), "TOK");
}

TEST(Network_Statistics,numberOfTotalAirports){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    int numberOfTotalAirports = system.totalNumberOfAirports();

    EXPECT_EQ(numberOfTotalAirports,3019);
}

TEST(Network_Statistics,numberOfTotalFlights){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    int numberOfTotalAirports = system.totalNumberOfFlights();

    EXPECT_EQ(numberOfTotalAirports,63832);
}

TEST(Network_Statistics, numberFlightsFromAirport){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    Airport airport1 = system.getCodeToAirport().at("LAE");
    int numberOfFlights = system.numberFlightsFromAirport(airport1);

    EXPECT_EQ(11,numberOfFlights);

    Airport airport2 = system.getCodeToAirport().at("GKA");
    numberOfFlights = system.numberFlightsFromAirport(airport2);

    EXPECT_EQ(5, numberOfFlights);

}

TEST(Network_Statistics, numberOfAirlinesInAirport){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    Airport airport1 = system.getCodeToAirport().at("LAE");
    int numberOfAirlines = system.numberOfAirlinesInAirport(airport1);

    EXPECT_EQ(2, numberOfAirlines);

    Airport airport2 = system.getCodeToAirport().at("TRF");
    numberOfAirlines = system.numberOfAirlinesInAirport(airport2);

    EXPECT_EQ(numberOfAirlines,8);

}

TEST(Network_Statistics, numberOfFlightsToCity){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    string city1 = "Paris";
    int numberOfFlightsToCity = system.numberOfFlightsToCity(city1);

    EXPECT_EQ(714,numberOfFlightsToCity);

    string city2 = "Porto";
    numberOfFlightsToCity = system.numberOfFlightsToCity(city2);

    EXPECT_EQ(numberOfFlightsToCity,102);

    string city3 = "Los Angeles";
    numberOfFlightsToCity = system.numberOfFlightsToCity(city3);

    EXPECT_EQ(numberOfFlightsToCity,497);
}

TEST(Network_Statistics, numberOfFlightsFromCity){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    string city1 = "Paris";
    int numberOfFlightsFromCity = system.numberOfFlightsFromCity(city1);

    EXPECT_EQ(719,numberOfFlightsFromCity);

    string city2 = "Porto";
    numberOfFlightsFromCity = system.numberOfFlightsFromCity(city2);

    EXPECT_EQ(numberOfFlightsFromCity,100);

    string city3 = "Los Angeles";
    numberOfFlightsFromCity = system.numberOfFlightsFromCity(city3);

    EXPECT_EQ(numberOfFlightsFromCity,491);
}


TEST(Network_Statistics, numberOfFlightsPerAirline){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    Airline airline1("RYR","Ryanair","RYANAIR","Ireland");
    int numberOfFlightsPerAirline1 = system.numberOfFlightsPerAirline(airline1);

    EXPECT_EQ(numberOfFlightsPerAirline1,2484);

    Airline airline2("ETD","Etihad Airways","ETIHAD","United Arab Emirates");
    int numberOfFlightsPerAirline2 = system.numberOfFlightsPerAirline(airline2);

    EXPECT_EQ(numberOfFlightsPerAirline2,228);

    Airline airline3("QTR","Qatar Airways","QATARI","Qatar");
    int numberOfFlightsPerAirline3 = system.numberOfFlightsPerAirline(airline3);

    EXPECT_EQ(numberOfFlightsPerAirline3,278);

}

TEST(Network_Statistics, numberOfCountriesFromAirport){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();
    setup1();

    Airport airport1 = system.getCodeToAirport().at("LAE");
    int numberOfCountries = system.numberOfCountriesFromAirport(airport1);

    EXPECT_EQ(numberOfCountries,1);

    Airport airport2 {"t1", "test1", "co1", "ci2", Location{1.0, 2.0}}; //AirportTest1
    system.setFlightNetwork(flightNetworkTest);
    numberOfCountries = system.numberOfCountriesFromAirport(airport2);

    EXPECT_EQ(3,numberOfCountries);

    Airport airport3 {"t1", "test4", "co3", "ci8", Location{10.0, 11.0}};  //AirportTest4
    numberOfCountries = system.numberOfCountriesFromAirport(airport3);

    EXPECT_EQ(2,numberOfCountries);

    cleanSetup();
}

TEST(Network_Statistics, numberOfCountriesFromCity){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();
    setup1();
    system.setFlightNetwork(flightNetworkTest);
    system.setCityToAirport(cityToAirportTest);

    string city = "ci7";
    int numberOfCountries = system.numberOfCountriesFromCity(city);

    EXPECT_EQ(3,numberOfCountries);

    string city2 = "ci1";
    numberOfCountries = system.numberOfCountriesFromCity(city2);

    EXPECT_EQ(3,numberOfCountries);
    cleanSetup();
}

TEST(Network_Statistics, numberOfCitiesFromAirport){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();
    setup1();

    system.setFlightNetwork(flightNetworkTest);
    Airport airport1 {"t1", "test1", "co1", "ci2", Location{1.0, 2.0}}; //AirportTest1
    int numberOfCities = system.numberOfCitiesFromAirport(airport1);

    EXPECT_EQ(4,numberOfCities);

    Airport airport2 {"t1", "test5", "co2", "ci1", Location{50.0, 9.0}};  //AirportTest5
    numberOfCities = system.numberOfCitiesFromAirport(airport2);

    EXPECT_EQ(2,numberOfCities);

    cleanSetup();
}

TEST(Network_Statistics, numberOfAirportsFromAirport){
AirTravelManSys system;
system.readAirlinesDataFile();
system.readAirportsDataFile();
system.readFlightsDataFile();
setup1();

system.setFlightNetwork(flightNetworkTest);
Airport airport1 {"t2", "test2", "co1", "ci2", Location{2.0, 3.0}}; //AirportTest1
int numberOfAirports = system.numberOfAirportsFromAirport(airport1);

EXPECT_EQ(4,numberOfAirports);

Airport airport2 {"t1", "test10", "co1", "ci7", Location{13.0, 79.0}};  //AirportTest5
numberOfAirports = system.numberOfAirportsFromAirport(airport2);

EXPECT_EQ(3,numberOfAirports);

cleanSetup();
}

TEST(Network_Statistics, numberOfReachableAirports){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    Airport airport1 = system.getCodeToAirport().at("LAE");
    int numberOfReachableAirports = system.numberOfReachableAirports(airport1,0);

    EXPECT_EQ(9,numberOfReachableAirports);

    setup1();
    system.setFlightNetwork(flightNetworkTest);
    Airport airport2 {"t1", "test1", "co1", "ci2", Location{1.0, 2.0}}; //airportTest1

    numberOfReachableAirports = system.numberOfReachableAirports(airport2,0);
    EXPECT_EQ(4,numberOfReachableAirports);

    numberOfReachableAirports = system.numberOfReachableAirports(airport2,1);
    EXPECT_EQ(9,numberOfReachableAirports);

    numberOfReachableAirports = system.numberOfReachableAirports(airport2,2);
    EXPECT_EQ(9,numberOfReachableAirports);

    Airport airport3 {"t2", "test2", "co1", "ci2", Location{2.0, 3.0}}; //airportTest2
    Airport airport4 {"t1", "test6", "co2", "ci1", Location{51.0, 52.0}};//airportTest6
    Airport airport5 {"t1", "test7", "co4", "ci6", Location{30.0, 70.0}};//airportTest7
    Airline airline1{"at3", "airline3", "ca3", "co3"}; //airlineTest3

    system.getFlightNetwork().removeFlight(airport3,airport5,airline1);

    numberOfReachableAirports = system.numberOfReachableAirports(airport2, 1);
    EXPECT_EQ(8,numberOfReachableAirports);

    system.getFlightNetwork().addFlight(airport4, airport5,airline1);

    numberOfReachableAirports = system.numberOfReachableAirports(airport2, 1);
    EXPECT_EQ(8,numberOfReachableAirports);

    numberOfReachableAirports = system.numberOfReachableAirports(airport2, 2);
    EXPECT_EQ(9,numberOfReachableAirports);

    cleanSetup();
}

TEST(Network_Statistics, numberOfReachableCities){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();


    setup1();
    system.setFlightNetwork(flightNetworkTest);
    Airport airport2 {"t1", "test1", "co1", "ci2", Location{1.0, 2.0}}; //airportTest1

    int numberOfReachableCities = system.numberOfReachableCities(airport2, 0);
    EXPECT_EQ(4, numberOfReachableCities);

    numberOfReachableCities = system.numberOfReachableCities(airport2, 1);
    EXPECT_EQ(6, numberOfReachableCities);

    numberOfReachableCities = system.numberOfReachableCities(airport2, 2);
    EXPECT_EQ(6, numberOfReachableCities);

    Airport airport3 {"t2", "test2", "co1", "ci2", Location{2.0, 3.0}}; //airportTest2
    Airport airport4 {"t1", "test6", "co2", "ci1", Location{51.0, 52.0}};//airportTest6
    Airport airport5 {"t1", "test7", "co4", "ci6", Location{30.0, 70.0}};//airportTest7
    Airline airline1{"at3", "airline3", "ca3", "co3"}; //airlineTest3

    system.getFlightNetwork().removeFlight(airport3,airport5,airline1);

    numberOfReachableCities = system.numberOfReachableCities(airport2, 1);
    EXPECT_EQ(5, numberOfReachableCities);

    system.getFlightNetwork().addFlight(airport4, airport5,airline1);

    numberOfReachableCities = system.numberOfReachableCities(airport2, 1);
    EXPECT_EQ(5, numberOfReachableCities);

    numberOfReachableCities = system.numberOfReachableCities(airport2, 2);
    EXPECT_EQ(6, numberOfReachableCities);

    cleanSetup();


}

TEST(Network_Statistics, numberOfReachableCountries){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();


    setup1();
    system.setFlightNetwork(flightNetworkTest);
    Airport airport2 {"t1", "test1", "co1", "ci2", Location{1.0, 2.0}}; //airportTest1

    int numberOfReachableCountries = system.numberOfReachableCountries(airport2, 0);
    EXPECT_EQ(3, numberOfReachableCountries);

    numberOfReachableCountries = system.numberOfReachableCountries(airport2, 1);
    EXPECT_EQ(4, numberOfReachableCountries);

    numberOfReachableCountries = system.numberOfReachableCountries(airport2, 2);
    EXPECT_EQ(4, numberOfReachableCountries);

    Airport airport3 {"t2", "test2", "co1", "ci2", Location{2.0, 3.0}}; //airportTest2
    Airport airport4 {"t1", "test6", "co2", "ci1", Location{51.0, 52.0}};//airportTest6
    Airport airport5 {"t1", "test7", "co4", "ci6", Location{30.0, 70.0}};//airportTest7
    Airline airline1{"at3", "airline3", "ca3", "co3"}; //airlineTest3

    system.getFlightNetwork().removeFlight(airport3,airport5,airline1);

    numberOfReachableCountries = system.numberOfReachableCountries(airport2, 1);
    EXPECT_EQ(3, numberOfReachableCountries);

    system.getFlightNetwork().addFlight(airport4, airport5,airline1);

    numberOfReachableCountries = system.numberOfReachableCountries(airport2, 1);
    EXPECT_EQ(3, numberOfReachableCountries);

    numberOfReachableCountries = system.numberOfReachableCountries(airport2, 2);
    EXPECT_EQ(4, numberOfReachableCountries);

    cleanSetup();

}

TEST(Network_Statistics, maxTrip){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    setup2();
    system.setFlightNetwork(flightNetworkTest);

    int maxTrip = 3;
    vector<pair<Airport,Airport>> maxTripAirportPairs;
    Airport a1_1("A","A","co1","ci1",Location{0.0,0.0});
    Airport a2_1("B","B","co1","ci2",Location{1.0,1.0});
    Airport a3_1("C","C","co2","ci3",Location{11.0,16.0});
    Airport a4_1("D","D","co2","ci4",Location{11.0,18.0});

    EXPECT_EQ(maxTrip,system.maxTrip(maxTripAirportPairs));
    EXPECT_EQ(maxTripAirportPairs.size(),4);
    EXPECT_TRUE(std::find(maxTripAirportPairs.begin(), maxTripAirportPairs.end(), make_pair(a1_1,a4_1)) != maxTripAirportPairs.end());
    EXPECT_TRUE(std::find(maxTripAirportPairs.begin(), maxTripAirportPairs.end(), make_pair(a2_1,a1_1)) != maxTripAirportPairs.end());
    EXPECT_TRUE(std::find(maxTripAirportPairs.begin(), maxTripAirportPairs.end(), make_pair(a3_1,a2_1)) != maxTripAirportPairs.end());
    EXPECT_TRUE(std::find(maxTripAirportPairs.begin(), maxTripAirportPairs.end(), make_pair(a4_1,a3_1)) != maxTripAirportPairs.end());

    maxTripAirportPairs.clear();
    cleanSetup();

    setup3();
    system.setFlightNetwork(flightNetworkTest);

    maxTrip = 3;
    Airport a1_2("E","E","co2","ci3",Location{11.0,17.0});
    Airport a2_2("D","D","co2","ci4",Location{11.0,18.0});

    EXPECT_EQ(maxTrip,system.maxTrip(maxTripAirportPairs));
    EXPECT_EQ(maxTripAirportPairs.size(),1);
    EXPECT_EQ(maxTripAirportPairs.at(0), make_pair(a1_2,a2_2));

    maxTripAirportPairs.clear();
    cleanSetup();

    setup4();
    system.setFlightNetwork(flightNetworkTest);

    maxTrip = 4;

    Airport a1("A","A","co1","ci1",Location{0.0,0.0});
    Airport a3("C","C","co2","ci3",Location{11.0,16.0});
    Airport a6("F","F","co3","ci6",Location{5.0,24.0});

    EXPECT_EQ(maxTrip,system.maxTrip(maxTripAirportPairs));
    EXPECT_EQ(2,maxTripAirportPairs.size());
    EXPECT_TRUE(find(maxTripAirportPairs.begin(),maxTripAirportPairs.end(), make_pair(a3,a1)) != maxTripAirportPairs.end());
    EXPECT_TRUE(find(maxTripAirportPairs.begin(),maxTripAirportPairs.end(), make_pair(a3,a6)) != maxTripAirportPairs.end());
}

TEST(Network_Statistics, topKAirportCapacity){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();


    setup1();
    system.setFlightNetwork(flightNetworkTest);

    system.topKAirportCapacity(100);
    cleanSetup();
}




