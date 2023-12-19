//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_AIRLINE_H
#define TRABALHOAED2_AIRLINE_H
#include<string>

using namespace std;

class Airline{
 private:
    string code;
    string name;
    string callSign;
    string country;
 public:
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
    };
}




#endif //TRABALHOAED2_AIRLINE_H
