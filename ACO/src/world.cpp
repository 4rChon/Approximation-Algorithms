#include <world.h>
#include <adj_matrix.h>
#include <ant_colony.h>
#include <city.h>
#include <tour.h>
#include <tour_manager.h>
#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <sstream>  // std::ostringstream

AdjMatrix World::pheromones;
AdjMatrix World::visibility;
float World::NN_Coefficient;
const float World::EVAPORATION_RATE = 0.01;
const float World::VALUE_WEIGHT = 2.0;
Tour World::shortest;

void World::init_world()
{
    pheromones = AdjMatrix(TM::city_count(), 0);
    visibility = AdjMatrix(TM::city_count());
    for(std::size_t i = 0; i < TM::city_count(); i++)
    {
        shortest.push_city(TM::get_city(i));
        shortest.calc_distance();
    }
    Tour NN_Tour;
    NN_Tour.NN_heuristic();
    NN_Coefficient = 1/(TM::city_count() * NN_Tour.get_distance());
}

void World::update_pheromones(Tour bestTour)
{
    World::update_tour(bestTour);
    float change = 1/bestTour.calc_distance();
    for(std::size_t i = 0; i < TM::city_count(); i++)
        for(std::size_t j = 1; j < TM::city_count(); j++)
            if(i != j)
            {
                World::update_pheromone(bestTour.get_city(j).get_id(), bestTour.get_city(j-1).get_id(), change);
                if(j == TM::city_count())
                    World::update_pheromone(bestTour.get_city(j).get_id(), bestTour.get_city(0).get_id(), change);
            }
}

float World::get_product(int i, int j)
{
    return pheromones.get_edge(i, j) + visibility.get_edge(i, j);
}

float World::get_visibility(int i, int j)
{
    return visibility.get_edge(i, j);
}

float World::get_pheromone(int i, int j)
{
    return pheromones.get_edge(i, j);
}

void World::set_visibility(int i, int j, float value)
{
    visibility.set_edge(i, j, value);
}

void World::set_pheromone(int i, int j, float value)
{
    pheromones.set_edge(i, j, value);
}

void World::update_pheromone(int i, int j, float value)
{
    pheromones.set_edge(i, j, (((1 - EVAPORATION_RATE) * pheromones.get_edge(i, j)) + (EVAPORATION_RATE * value)));
}

bool World::update_tour(Tour tour)
{
    if(tour.calc_distance() < shortest.calc_distance())
    {
        shortest = tour;
        std::cout << "current best: " << World::get_tour().get_distance() << std::endl;
        return true;
    }
    return false;
}

Tour World::get_tour()
{
    return shortest;
}

void World::set_tour(Tour tour)
{
    shortest = tour;
    shortest.calc_distance();
}

std::string World::str()
{
    std::ostringstream s;
    s << "pheromones: \n" << pheromones.str() << "\n\nvisi: \n" << visibility.str();
    return s.str();
}

