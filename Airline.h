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
};




#endif //TRABALHOAED2_AIRLINE_H
