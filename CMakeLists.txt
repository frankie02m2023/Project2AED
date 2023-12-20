cmake_minimum_required(VERSION 3.26)
project(TrabalhoAED2)

set(CMAKE_CXX_STANDARD 17)

add_executable(TrabalhoAED2 main.cpp
        Airport.h
        Airport.cpp
        Airline.h
        Airline.cpp
        Location.h
        Location.cpp
        Graph.h
        Flight.h
        NetworkAirports.h
        Flight.cpp
        Flight.cpp
        NetworkAirports.cpp
        FlightNetwork.h
        FlightNetwork.cpp
        AirTravelManSys.h
        AirTravelManSys.cpp
)
