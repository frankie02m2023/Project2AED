//
// Created by lucas on 20/12/2023.
//

#include <gtest/gtest.h>
#include "Airline.h"
#include "Airport.h"
#include "AirTravelManSys.h"
#include "Location.h"



FlightNetwork flightNetworkTest;

void setup() {

    Airport airportTest1{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest2{"t2", "test2", "co2", "ci2", Location{2.0, 3.0}};
    Airport airportTest3{"t3", "test3", "co1", "ci1", Location{20.0, 30.0}};
    Airport airportTest4{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest5{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest6{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest7{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest8{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest9{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest10{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest11{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest12{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest13{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest14{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};
    Airport airportTest15{"t1", "test1", "co1", "ci1", Location{1.0, 2.0}};

    Airline airlineTest1{"at1", "airline1", "ca1", "co1"};
    Airline airlineTest2{"at2", "airline2", "ca2", "co1"};
    Airline airlineTest3{"at3", "airline3", "ca3", "co3"};
    Airline airlineTest4{"at4", "airline4", "ca4", "co2"};
    Airline airlineTest5{"at5", "airline5", "ca5", "co3"};

    NetworkAirport networkAirportTest1 {airportTest1};
    NetworkAirport networkAirportTest2 {airportTest2};
    NetworkAirport networkAirportTest3 {airportTest3};
    NetworkAirport networkAirportTest4 {airportTest4};
    NetworkAirport networkAirportTest5 {airportTest5};
    NetworkAirport networkAirportTest6 {airportTest6};
    NetworkAirport networkAirportTest7 {airportTest7};
    NetworkAirport networkAirportTest8 {airportTest8};
    NetworkAirport networkAirportTest9 {airportTest9};
    NetworkAirport networkAirportTest10 {airportTest10};
    NetworkAirport networkAirportTest11 {airportTest11};
    NetworkAirport networkAirportTest13 {airportTest12};
    NetworkAirport networkAirportTest14 {airportTest14};
    NetworkAirport networkAirportTest15 {airportTest15};


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

TEST(Network_Statistics, numberOfCountriesFromAirport){
    AirTravelManSys system;
    system.readAirlinesDataFile();
    system.readAirportsDataFile();
    system.readFlightsDataFile();

    Airport airport1 = system.getCodeToAirport().at("LAE");
    int numberOfCountries = system.numberOfCountriesFromAirport(airport1);

    EXPECT_EQ(numberOfCountries,1);

}



