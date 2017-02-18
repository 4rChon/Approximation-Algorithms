#include <city.h>
#include <cmath>    // sqrt, pow
#include <cstdlib>  // rand
#include <sstream>  // std::ostringstream
#include <time.h>   // time

City::City()
{
    this->x = rand()%100;
    this->y = rand()%100;
}

City::City(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool City::operator==(const City &rhs) const
{ 
    return this->get_x() == rhs.get_x() && this->get_y() == rhs.get_y(); 
}

float City::get_x() const
{
    return this->x;
}

float City::get_y() const
{
    return this->y;
}

float City::distance_to(City city) const
{
    return sqrt(pow((this->get_x() - city.get_x()),2) + pow((this->get_y() - city.get_y()),2));
}

std::string City::str() const
{ 
    std::ostringstream s;
    s << " " << this->get_x() << " " << this->get_y() << " | ";
    return s.str();
}
