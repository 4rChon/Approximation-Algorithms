#ifndef __POP_H__
#define __POP_H__

#include <tour.h>

class Population
{
    private:
        std::vector<Tour> tours;
        
    public:
        Population();
        Population(std::size_t popSize);
        
        void push_tour(Tour tour);
        void set_tour(std::size_t index, Tour tour);
        Tour get_tour(std::size_t index) const;
        Tour get_fittest();
        std::size_t get_size() const;
        void sort_pop();
        bool contains(Tour tour) const;
};

#endif
