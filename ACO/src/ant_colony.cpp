#include <ant_colony.h>
#include <ant.h>
#include <tour_manager.h>
#include <world.h>
#include <vector> // std::vector

std::vector<Ant> AC::antList;

void AC::push_ant(Ant ant)
{
    antList.push_back(ant);    
}

void AC::set_ant(Ant ant, int index)
{
    antList[index] = ant;
}

Ant& AC::get_ant(int index)
{
    return antList[index];
}

std::size_t AC::ant_count()
{
    return antList.size();
}

void AC::step(unsigned seed)
{
    bool bestSet = false;
    Tour bestTour;
    for(std::size_t i = 0; i < AC::ant_count(); i++)
    {
        Ant ant = AC::get_ant(i);
        
        while(ant.get_size() < TM::city_count())
            ant.move(seed);
        
        if(!bestSet)
        {
            bestTour = ant.get_tour();
            bestSet = true;
        }
        
        if(ant.get_distance() < bestTour.calc_distance())
            bestTour = ant.get_tour();
        
        antList[i] = Ant();
    }
    World::update_pheromones(bestTour);
}
