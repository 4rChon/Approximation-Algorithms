#ifndef __TOUR_H__
#define __TOUR_H__

#include <vector> // std::vector
#include <city.h>

class Tour
{
    private:
        std::vector<City> tour;
        float distance;
        
    public:
        Tour();
        Tour(std::vector<City> tour);
        
        bool operator==(const Tour &rhs) const;
        void generate_tour();
        void push_city(City city);
        void set_city(std::size_t tourPosition, City city);
        City get_city(std::size_t tourPosition) const;
        float calc_distance();
        float get_distance() const;
        std::size_t get_size() const;
        bool contains(City city) const;
        void swap(City city_1, City city_2);
        std::string str() const;
        void shuffle();
};

#endif
