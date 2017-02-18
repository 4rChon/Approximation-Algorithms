#ifndef __ANT_H__
#define __ANT_H__

#include <city.h>
#include <tour.h>

class Ant
{
    private:
        Tour tabuList;
    public:
        Ant();
        void move(unsigned seed);
        City current_city() const;
        std::size_t get_size() const;
        float get_visibility(City city) const;
        float get_distance();
        City get_city(int index) const;        
        Tour get_tour() const;
};

#endif
