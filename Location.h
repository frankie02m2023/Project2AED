//
// Created by franc on 18/12/2023.
//

#ifndef TRABALHOAED2_LOCATION_H
#define TRABALHOAED2_LOCATION_H
#include<functional>
using namespace std;

class Location{
 private:
    double latitude;
    double longitude;
public:
    Location();
    Location(double x, double y);
    double getLatitude() const;
    double getLongitude() const;
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void operator=(Location otherLocation);
    bool operator==(Location otherLocation) const;
};

namespace std
{
    template <>
    struct hash<Location>
    {
        size_t operator()(const Location& location) const
        {
            size_t latitude = hash<double>()(location.getLatitude());
            size_t longitude = hash<double>()(location.getLongitude());
            return latitude ^ longitude;
        }
    };
}



#endif //TRABALHOAED2_LOCATION_H
