#include <population.h>
#include <tour.h>
#include <tour_manager.h>
#include <tsp.h>
#include <util.h>
#include <algorithm> //std::sort
#include <vector>    //std::vector

Population::Population(){}

Population::Population(std::size_t popSize)
{
    Tour firstTour;
    //firstTour.generate_tour();  
    //firstTour.calc_distance();      
    //this->push_tour(firstTour);
    for(std::size_t i = 0; i < TM::city_count(); i++)
    {
        firstTour.push_city(TM::get_city(i));
    }
    firstTour.calc_distance();      
    this->push_tour(firstTour);
    for(std::size_t i = 1; i < popSize; i++)
    {
        Tour newTour = firstTour;// = Tour(firstTour.shuffle());
        //TSP::mutate(newTour);
        newTour.shuffle();
        this->push_tour(newTour);
    }
}

bool compare_by_length(Tour a, Tour b)
{
    return a.calc_distance() < b.calc_distance();
}

void Population::push_tour(Tour tour)
{
    this->tours.push_back(tour);
}

void Population::set_tour(std::size_t index, Tour tour)
{
    this->tours[index] = tour;
}

Tour Population::get_tour(std::size_t index) const
{
    return this->tours[index];
}

Tour Population::get_fittest()
{
    Tour fittest = this->tours[0];
    for(std::size_t i = 1; i < this->get_size(); i++)
        if(fittest.calc_distance() >= this->get_tour(i).calc_distance())
            fittest = this->get_tour(i);
        
    return fittest;
}

std::size_t Population::get_size() const 
{
    return this->tours.size();
}

void Population::sort_pop()
{
    std::sort(this->tours.begin(), this->tours.end(), compare_by_length);
}

bool Population::contains(Tour tour) const
{
    return std::find(this->tours.begin(), this->tours.end(), tour) != this->tours.end();
}

