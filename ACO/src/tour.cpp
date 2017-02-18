#include <tour.h>
#include <tour_manager.h>
#include <algorithm>    // std::random_shuffle, std::find
#include <cstdlib>      // rand
#include <limits>       // std::numeric_limits
#include <string>       // std::string
#include <sstream>      // std::ostringstream

Tour::Tour()
{
    this->distance = 0;
}

Tour::Tour(std::vector<City> tour)
{
    this->tour = tour;
    this->calc_distance();
}

void Tour::push_city(City city)
{
    this->tour.push_back(city);
    this->distance = 0;
}

City Tour::get_city(std::size_t tourPosition) const
{
    return this->tour[tourPosition];
}

float Tour::calc_distance()
{
    if(this->distance == 0)
    {
        float tourDistance;
        for(std::size_t i = 1; i < this->get_size(); i++)
        {
            tourDistance += this->tour[i].distance_to(this->tour[i-1]);
            if(i == this->get_size()-1)
                tourDistance += this->tour[i].distance_to(this->tour[0]);
        }
        this->distance = tourDistance;
    }
    
    return this->distance;
}


float Tour::get_distance() const
{
    return this->distance;
}
std::size_t Tour::get_size() const
{
    return this->tour.size();
}

std::vector<City> Tour::get_tour()
{
    return this->tour;
}

bool Tour::contains(City city) const
{
    return std::find(this->tour.begin(), this->tour.end(), city) != this->tour.end();
}

void Tour::NN_heuristic()
{
    std::size_t currentIndex = 0;
    std::size_t nextIndex = 1;
    
    while(this->get_size() < TM::city_count())
    {
        float shortestDist = std::numeric_limits<float>::infinity();
        for(std::size_t i = 0; i < TM::city_count(); i++)
        {
            if(!this->contains(TM::get_city(i)))
            {
                float candidateDist = TM::get_city(currentIndex).distance_to(TM::get_city(i));
                if(candidateDist < shortestDist)
                {
                    shortestDist = candidateDist;
                    nextIndex = i;
                }
            }
        }
        this->push_city(TM::get_city(nextIndex));
        currentIndex = nextIndex;        
    }
    this->calc_distance();
}

std::string Tour::str() const
{
    std::ostringstream s;
    for(std::size_t i = 0; i < this->get_size(); i++)
        s << this->tour[i].str();
    return s.str();
}
