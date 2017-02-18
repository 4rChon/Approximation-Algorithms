#include <ant.h>
#include <city.h>
#include <tour.h>
#include <tour_manager.h>
#include <world.h>
#include <vector>       // std::vector
#include <cstdlib>      // rand
#include <random>       // std::discrete_distribution, std::mt19937
#include <algorithm>    // std::max_element
#include <iterator>     // std::distance
#include <cmath>        // pow


Ant::Ant()
{
    this->tabuList.push_city(TM::get_city(rand()%TM::city_count()));
}

void Ant::move(unsigned seed)
{
    float q = ((double) rand() / RAND_MAX);
    float bias = 0.9;
    std::vector<float> distribution;
    for(std::size_t i = 0; i < TM::city_count(); i++)
    {
        float probability = 0;
        if(!tabuList.contains(TM::get_city(i)))
        {
            float visibility = pow(get_visibility(TM::get_city(i)), World::VALUE_WEIGHT);
            World::set_visibility(this->current_city().get_id(), TM::get_city(i).get_id(), visibility);
            probability = World::get_product(this->current_city().get_id(), TM::get_city(i).get_id());
        }
        distribution.push_back(probability);
    }
    
    int index;
    
    if(q < bias)
        index = std::distance(distribution.begin(), std::max_element(distribution.begin(), distribution.end()));
    else
    {
        std::mt19937 gen(seed);
        std::discrete_distribution<int> dist(distribution.begin(), distribution.end());
        index = dist(gen);
        float change = World::NN_Coefficient;
        World::update_pheromone(this->current_city().get_id(), index, change*2);
    }
    
    this->tabuList.push_city(TM::get_city(index));
}

City Ant::current_city() const
{
    return this->tabuList.get_city(this->tabuList.get_size()-1);
}

std::size_t Ant::get_size() const
{
    return this->tabuList.get_size();
}

float Ant::get_visibility(City city) const
{
    return 1/(this->current_city().distance_to(city));
}

float Ant::get_distance()
{
    return this->tabuList.calc_distance();
}

City Ant::get_city(int index) const
{
    return this->tabuList.get_city(index);
}

Tour Ant::get_tour() const
{
    return this->tabuList;
}
