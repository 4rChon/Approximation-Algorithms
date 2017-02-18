#include <tour_manager.h>
#include <city.h>

std::vector<City> TM::destinationCities;

void TM::add_city(City city)
{
    destinationCities.push_back(city);
}

City TM::get_city(std::size_t index)
{
    return destinationCities[index];
}

std::size_t TM::city_count()
{
    return destinationCities.size();
}
