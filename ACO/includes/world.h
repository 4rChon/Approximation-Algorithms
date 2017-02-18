#ifndef __WORLD_H__
#define __WORLD_H__

#include <adj_matrix.h>
#include <tour.h>
#include <string>   // std::string

class World
{
    private:
        static AdjMatrix pheromones;
        static AdjMatrix visibility;
        static const float EVAPORATION_RATE;
        static Tour shortest;
    public:
        static float NN_Coefficient;
        static const float VALUE_WEIGHT;
        static const float DELTA_COEFFICIENT;
        static void init_world();
        static void update_pheromones(Tour bestTour);
        static float get_product(int i, int j);
        static float get_visibility(int i, int j);
        static float get_pheromone(int i, int j);
        static void set_visibility(int i, int j, float value);
        static void set_pheromone(int i, int j, float value);
        static void evaporate_pheromone(int i, int j);
        static void update_pheromone(int i, int j, float value);
        static bool update_tour(Tour tour);
        static Tour get_tour();
        static void set_tour(Tour tour);
        static std::string str();
};

#endif
