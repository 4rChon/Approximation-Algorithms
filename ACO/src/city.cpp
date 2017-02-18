#include <city.h>
#include <cmath>    // sqrt, pow
#include <cstdlib>  // rand
#include <ctime>    // time
#include <sstream>  // std::ostringstream

City::City(int id)
{
    this->id = id;
    this->x = rand()%500;
    this->y = rand()%500;
}

City::City(int id, float x, float y)
{
    this->id = id;
    this->x = x;
    this->y = y;
}

bool City::operator==(const City &rhs) const
{ 
    return this->get_id() == rhs.get_id();
}

bool City::operator!=(const City &rhs) const
{
    return !(*this == rhs);
}

float City::get_id() const
{
    return this->id;
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
    s << " " << this->get_id() << " " << this->get_x() << " " << this->get_y() << " | ";
    return s.str();
}
