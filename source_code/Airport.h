//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_AIRPORT_H
#define TRABALHOAED2_AIRPORT_H
#include <string>
#include "Location.h"

using namespace std;

/**
 * @file Airport.h
 * @brief Definition of class Airport.
 *
 * \class Airport
 * Where are preformed functions related to the airports.
 * Stores the code, name, country, and location of the airport
 */

class Airport{
private:
    string code;
    string name;
    string country;
    string city;
    Location location{};
public:
    Airport();
    Airport(string code,string name,string country,string city,Location location);
    string getCode() const;
    string getName() const;
    string getCountry() const;
    string getCity() const;
    Location getLocation() const;
    void setCode(string code);
    void setName(string name);
    void setCountry(string country);
    void setCity(string city);
    void setLocation(Location location);
    bool operator==(const Airport& otherAirport) const;
};

namespace std
{
    template <>
    struct hash<Airport>
    {
        size_t operator()(const Airport& airport) const
        {
            size_t codeHash = hash<string>()(airport.getCode());
            size_t nameHash = hash<string>()(airport.getName());
            size_t countryHash = hash<string>()(airport.getCountry());
            size_t cityHash = hash<string>()(airport.getCity());
            size_t locationHash = hash<Location>()(airport.getLocation());
            return (codeHash ^ nameHash ^ countryHash ^ cityHash ^ locationHash) >> 1;
        }
    };
}

#endif //TRABALHOAED2_AIRPORT_H
