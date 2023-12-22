//
// Created by franc on 18/12/2023.
//


#include "Location.h"

/** @file AirTravelManSys.cpp
 *  @brief Implementation of AirTravelManSys class
 */

Location::Location() {
    latitude = 0;
    longitude = 0;
}

Location::Location(double x, double y) {
    this->latitude = x;
    this->longitude = y;
}

/** Gets the latitude.
 *  Complexity: O(1)
 * @return latitude value
 */
double Location::getLatitude() const {
    return latitude;
}

/** Gets the longitude.
 *  Complexity: O(1)
 * @return longitude value
 */
double Location::getLongitude() const {
    return longitude;
}

/** Sets the latitude.
 *  Complexity: O(1)
 * @param latitude latitude value
 */
void Location::setLatitude(const double latitude) {
    this->latitude = latitude;
}

/** Gets the longitude.
 *  Complexity: O(1)
 * @param longitude longitude value
 */
void Location::setLongitude(const double longitude) {
    this->longitude = longitude;
}

void Location::operator=(Location otherLocation) {
    this->latitude = otherLocation.latitude;
    this->longitude = otherLocation.longitude;
}

bool Location::operator==(Location otherLocation) const {
    return latitude == otherLocation.latitude && longitude == otherLocation.longitude;
}

