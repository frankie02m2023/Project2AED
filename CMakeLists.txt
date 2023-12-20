cmake_minimum_required(VERSION 3.26)
project(TrabalhoAED2)

set(CMAKE_CXX_STANDARD 17)

set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)
set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(googletest tests.cpp Airline.cpp Airport.cpp AirTravelManSys.cpp Flight.cpp FlightNetwork.cpp Location.cpp NetworkAirports.cpp)

target_link_libraries(googletest gtest gtest_main)

set(SOURCE_FILES main.cpp
        Airport.h
        Airport.cpp
        Airline.h
        Airline.cpp
        Location.h
        Location.cpp
        Graph.h
        Flight.cpp
        NetworkAirports.cpp
        FlightNetwork.h
        FlightNetwork.cpp
        AirTravelManSys.h
        AirTravelManSys.cpp
)

file(COPY dataset/airlines.csv dataset/airports.csv dataset/flights.csv DESTINATION ${CMAKE_BINARY_DIR})

# Define the executable target
add_executable(main ${SOURCE_FILES})
