//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_LOCATION_H
#define TRABALHOAED2_LOCATION_H

class Location{
 private:
    double latitude;
    double longitude;
public:
    double getLatitude() const;
    double getLongitude() const;
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void operator=(Location otherLocation);
    bool operator==(Location otherLocation) const;
};

#endif //TRABALHOAED2_LOCATION_H
