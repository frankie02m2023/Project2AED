//
// Created by franc on 18/12/2023.
//
#include "Airport.h"

Airport::Airport() {}

Airport::Airport(const string code, const string name, const string country, const string city, const Location location) {
    this->code = code;
    this->name = name;
    this->country = country;
    this->city = city;
    this->location = location;
}

string Airport::getCode() const {
    return code;
}

string Airport::getName() const {
    return name;
}

string Airport::getCountry() const {
    return country;
}

string Airport::getCity() const {
    return city;
}

Location Airport::getLocation() const {
    return location;
}

void Airport::setCode(const string code) {
    this->code = code;
}

void Airport::setName(const string name) {
    this->code = name;
}

void Airport::setCountry(const string country) {
    this->country = country;
}

void Airport::setCity(const string city) {
    this->city = city;
}

void Airport::setLocation(const Location location) {
    this->location = location;
}
