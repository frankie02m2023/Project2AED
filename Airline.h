//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_AIRLINE_H
#define TRABALHOAED2_AIRLINE_H
#include<string>
#include <utility>

using namespace std;


/**
 * @file AirLine.h
 * @brief Definition of class Airline.
 *
 * \class Airline
 * Where are preformed functions related to the airlines.
 * Stores the code, name, call sign and country of the airline.
 */

class Airline{
 private:
    string code;
    string name;
    string callSign;
    string country;
 public:
    Airline(string code, string name, string callSign, string country){
        this->code = code;
        this->name = name;
        this->callSign = callSign;
        this->country = country;
    }
    Airline(){}
    string getCode() const;
    string getName() const;
    string getCallSign() const;
    string getCountry() const;
    bool operator==(const Airline& otherAirline) const;
};

namespace std
{
    template <>
    struct hash<Airline>
    {
        size_t operator()(const Airline& airline) const
        {
            size_t codeHash = hash<string>()(airline.getCode());
            size_t nameHash = hash<string>()(airline.getName());
            size_t countryHash = hash<string>()(airline.getCountry());
            return (codeHash ^ nameHash ^ countryHash) >> 1;
        }

        bool operator()(const Airline& airline1, const Airline& airline2){
            return airline1.getCode() == airline1.getCode() && airline1.getCountry() == airline2.getCountry()
                && airline1.getCallSign() == airline2.getCallSign()  && airline1.getName() == airline2.getName();
        }
    };
}




#endif //TRABALHOAED2_AIRLINE_H
