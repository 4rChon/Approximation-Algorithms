#include <tsp.h>
#include <population.h>
#include <stdio.h>
#include <tour.h>
#include <tour_manager.h>
#include <cstdlib>  //rand
#include <iostream> //std::cout, std;:endl
#include <time.h>   //time
#include <vector>   //std::vector

const std::size_t TSP::TOURNEY_SIZE = 25;
const bool TSP::ELITISM = true;
const int TSP::ELITE_COUNT = 10;
const int TSP::MUTATION_RATE = 15;
const int TSP::PMX_N_POINT = 2;

void TSP::mutate(Tour &tour)
{
    std::size_t cut = rand()%(TM::city_count()),
                max = rand()%(TM::city_count()-cut)+cut;
                //pos_2 = rand()%(TM::city_count()-pos_1);
    
    for(std::size_t i = cut; i < max; i++)
    {    
        std::size_t cityIndex = rand()%TM::city_count();
        if(cityIndex != i)
            tour.swap(tour.get_city(i), tour.get_city(cityIndex));
    }
    
    tour.calc_distance();
}

Tour TSP::tournament_selection(Population pop)
{
    Population tournament;
    for(std::size_t i = 0; i < TOURNEY_SIZE; i++)
    {
        std::size_t index = rand()%pop.get_size();
        tournament.push_tour(pop.get_tour(index));
    }
    
    Tour fittest = tournament.get_fittest();
    return fittest;
}

void TSP::evolve_pop(Population &pop)
{
    
    Population newPop;
    int elitismOffset = 0;
    if(ELITISM)
    {
        pop.sort_pop();
        while(elitismOffset < ELITE_COUNT)
        {
            newPop.push_tour(pop.get_tour(elitismOffset));
            elitismOffset++;
        }
    }

    while(newPop.get_size() < pop.get_size())
    {
        Tour parent_1 = tournament_selection(pop);
        Tour parent_2 = tournament_selection(pop);

        Population children = crossover(parent_1, parent_2);
        newPop.push_tour(children.get_tour(0));
        if(newPop.get_size() < pop.get_size())
            newPop.push_tour(children.get_tour(1));
    }
    for(std::size_t i = elitismOffset; i < newPop.get_size(); i++)
    {
        int chance = rand()%1000;
        if(chance <= MUTATION_RATE)
        {
            Tour newTour = newPop.get_tour(i);
            TSP::mutate(newTour);
            newPop.set_tour(i, newTour);
        }
    }
    pop = newPop;
}

Population TSP::crossover(Tour parent_1, Tour parent_2)
{
    Tour child_1 = parent_1,
         child_2 = parent_2;
         
    
    std::size_t pos_1, pos_2;
    for(int i = 0; i < PMX_N_POINT; i++)
    {
        pos_1 = rand()%(TM::city_count()-1);
        pos_2 = (rand()%(TM::city_count() - pos_1)) + pos_1+1;
        
        for(std::size_t i = pos_1; i < pos_2; i++)
        {
            child_1.swap(parent_1.get_city(i), parent_2.get_city(i));
            child_2.swap(parent_1.get_city(i), parent_2.get_city(i));
        }
    }
    
    Population children;
    child_1.calc_distance();
    child_2.calc_distance();
    children.push_tour(child_1);
    children.push_tour(child_2);
    
    return children;
}
