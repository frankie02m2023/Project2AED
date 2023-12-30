//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_AIRLINE_CPP
#define TRABALHOAED2_AIRLINE_CPP


#include "Airline.h"



/** @file Airline.cpp
 *  @brief Implementation of Airline class
 */

/** Gets the airline code.
 * Complexity: O(1)
 * @return airline code
 */
string Airline::getCode() const {
    return code;
}

/** Gets the airline name.
 * Complexity: O(1)
 * @return airline name
 */
string Airline::getName() const {
    return name;
}

/** Gets the airline call sign.
 *  Complexity: O(1)
 * @return airline call sign
 */
string Airline::getCallSign() const {
    return callSign;
}

/** Gets the airline country.
 *  Complexity: O(1)
 * @return airline country
 */
string Airline::getCountry() const {
    return country;
}

bool Airline::operator==(const Airline& otherAirline) const {
    return code == otherAirline.code;
}

bool Airline::operator<(const Airline &otherAirline) const {
    return code < otherAirline.code;
}

#endif
