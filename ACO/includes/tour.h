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
        
        void push_city(City city);
        City get_city(std::size_t tourPosition) const;
        float calc_distance();
        float get_distance() const;
        std::size_t get_size() const;
        std::vector<City> get_tour();
        bool contains(City city) const;
        void NN_heuristic();
        std::string str() const;
};

#endif
