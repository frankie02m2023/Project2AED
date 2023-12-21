//
// Created by lucas on 20/12/2023.
//

#include <gtest/gtest.h>
#include "Airline.h"
#include "Airport.h"
#include "AirTravelManSys.h"
#include "Location.h"

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


