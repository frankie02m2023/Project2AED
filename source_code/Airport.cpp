//
// Created by franc on 18/12/2023.
//
#include "Airport.h"

/** @file Airport.cpp
 *  @brief Implementation of Airport class
 */

Airport::Airport() {}

Airport::Airport(const string code, const string name, const string country, const string city, const Location location) {
    this->code = code;
    this->name = name;
    this->country = country;
    this->city = city;
    this->location = location;
}

/** Gets the airport code.
 *  Complexity: O(1)
 * @return airport code
 */
string Airport::getCode() const {
    return code;
}

/** Gets the airport name.
 *  Complexity: O(1)
 * @return airport name
 */
string Airport::getName() const {
    return name;
}

/** Gets the airport country.
 *  Complexity: O(1)
 * @return airport country
 */
string Airport::getCountry() const {
    return country;
}

/** Gets the airport city.
 *  Complexity: O(1)
 * @return airport city
 */
string Airport::getCity() const {
    return city;
}

/** Gets the airport location.
 *  Complexity: O(1)
 * @return airport location
 */
Location Airport::getLocation() const {
    return location;
}

/** Sets the airport code.
 *  Complexity: O(1)
 */
void Airport::setCode(const string code) {
    this->code = code;
}

/** Sets the airport name.
 *  Complexity: O(1)
 */
void Airport::setName(const string name) {
    this->code = name;
}

/** Sets the airport country.
 *  Complexity: O(1)
 */
void Airport::setCountry(const string country) {
    this->country = country;
}

/** Sets the airport city.
 *  Complexity: O(1)
 */
void Airport::setCity(const string city) {
    this->city = city;
}

/** Sets the airport location.
 *  Complexity: O(1)
 */
void Airport::setLocation(const Location location) {
    this->location = location;
}

bool Airport::operator==(const Airport &otherAirport) const {
    return code == otherAirport.code && name == otherAirport.name && country == otherAirport.country && city == otherAirport.city;
}
