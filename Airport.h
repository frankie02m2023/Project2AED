//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_AIRPORT_H
#define TRABALHOAED2_AIRPORT_H
#include <string>
#include "Location.h"
#include "Flight.h"

using namespace std;

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
};

#endif //TRABALHOAED2_AIRPORT_H
