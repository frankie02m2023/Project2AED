//
// Created by franc on 18/12/2023.
//


#include "Location.h"

Location::Location() {
    latitude = 0;
    longitude = 0;
}

Location::Location(double x, double y) {
    this->latitude = x;
    this->longitude = y;
}

double Location::getLatitude() const {
    return latitude;
}

double Location::getLongitude() const {
    return longitude;
}

void Location::setLatitude(const double latitude) {
    this->latitude = latitude;
}

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

