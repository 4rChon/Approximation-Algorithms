#ifndef __TSP_H__
#define __TSP_H__

#include <population.h>

class TSP
{
    private:
        const static std::size_t TOURNEY_SIZE;
        const static bool ELITISM;
        const static int ELITE_COUNT;
        const static int MUTATION_RATE;
        const static int PMX_N_POINT;
        
        static Tour tournament_selection(Population pop);
        
    public:
        static void mutate(Tour &tour);
        static void evolve_pop(Population &pop);
        static Population crossover(Tour parent_1, Tour parent_2);
        
};

#endif
