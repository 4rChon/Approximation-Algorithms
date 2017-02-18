#include <tour.h>
#include <tour_manager.h>
#include <util.h>
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

bool Tour::operator==(const Tour &rhs) const
{ 
    if(this->get_distance() != rhs.get_distance() && this->get_size() != rhs.get_size())
        return false;
    for(std::size_t i = 0; i < this->get_size(); i++)
        if(!(this->get_city(i) == rhs.get_city(i)))
            return false;
    return true;
}

void Tour::generate_tour()
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

void Tour::push_city(City city)
{
    this->tour.push_back(city);
    this->distance = 0;
}

void Tour::set_city(std::size_t tourPosition, City city)
{
    this->tour[tourPosition] = city;
    this->distance = 0;
}

City Tour::get_city(std::size_t tourPosition) const
{
    return this->tour[tourPosition];
}

float Tour::calc_distance()
{
    float tourDistance = 0;
    for(std::size_t i = 1; i < this->get_size(); i++)
    {
        tourDistance += this->tour[i].distance_to(this->tour[i-1]);
        if(i == this->get_size()-1)
            tourDistance += this->tour[i].distance_to(this->tour[0]);
    }
    this->distance = tourDistance;
    
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

bool Tour::contains(City city) const
{
    return std::find(this->tour.begin(), this->tour.end(), city) != this->tour.end();
}

void Tour::swap(City city_1, City city_2)
{
    std::size_t index_1 = std::distance(this->tour.begin(), std::find(this->tour.begin(), this->tour.end(), city_1));
    std::size_t index_2 = std::distance(this->tour.begin(), std::find(this->tour.begin(), this->tour.end(), city_2));
    if(index_1 != index_2)
    {
        this->set_city(index_1, city_2);
        this->set_city(index_2, city_1);
    }
}

std::string Tour::str() const
{
    std::ostringstream s;
    for(std::size_t i = 0; i < this->get_size(); i++)
        s << this->tour[i].str();
    return s.str();
}

void Tour::shuffle()
{
    std::vector<City> shuffledTour = this->tour;
    std::random_shuffle(shuffledTour.begin(), shuffledTour.end());
    this->tour = shuffledTour;
    this->calc_distance();
}
