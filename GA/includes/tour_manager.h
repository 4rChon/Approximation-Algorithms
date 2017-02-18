#ifndef __TOURMAN_H__
#define __TOURMAN_H__

#include <city.h>
#include <vector> //std::vector

class TM
{
    private:
        static std::vector<City> destinationCities;
    
    public:
        static void add_city(City city);
        static City get_city(std::size_t index);
        static std::size_t city_count();
};

#endif
