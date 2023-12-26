cmake_minimum_required(VERSION 3.26)
project(TrabalhoAED2)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)
set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(googletest testing/tests.cpp source_code/Airline.cpp source_code/Airport.cpp source_code/AirTravelManSys.cpp source_code/Flight.cpp source_code/FlightNetwork.cpp source_code/Location.cpp source_code/NetworkAirports.cpp
        source_code/UI.cpp)

target_link_libraries(googletest gtest gtest_main)

set(SOURCE_FILES source_code/main.cpp
        source_code/Airport.h
        source_code/Airport.cpp
        source_code/Airline.h
        source_code/Airline.cpp
        source_code/Location.h
        source_code/Location.cpp
        source_code/Graph.h
        source_code/Flight.cpp
        source_code/NetworkAirports.cpp
        source_code/FlightNetwork.h
        source_code/FlightNetwork.cpp
        source_code/AirTravelManSys.h
        source_code/AirTravelManSys.cpp
        source_code/UI.h
        source_code/UI.cpp
)

file(COPY dataset/airlines.csv dataset/airports.csv dataset/flights.csv DESTINATION ${CMAKE_BINARY_DIR})

# Define the executable target
add_executable(main ${SOURCE_FILES})

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
