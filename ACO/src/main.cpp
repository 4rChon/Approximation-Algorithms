#include <adj_matrix.h>
#include <ant.h>
#include <ant_colony.h>
#include <display.h>
#include <tour_manager.h>
#include <util.h>
#include <world.h>
#include <chrono>   // std::chrono
#include <iostream> // std::cout, std::enl
#include <string>   // stoi
#include <sstream>  // istringstream
#include <random>   // srand

int main(int argc, char* argv[])
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    if(argc < 2)
    {
        std::cout << "Not Enough Arguments. Expected tsp [filename]." << std::endl;        
        return 1;
    }
         
    if(load_tsp(argv[1]))
    {
        std::cout << "Unable to open file. Invalid filename." << std::endl;
        return 1;
    }

    std::size_t ant_count = 10;
    
    if(argc < 3)
        std::cout << "Ant Count not given. Setting to default." << std::endl;
    else
        std::istringstream(std::string(argv[2])) >> ant_count;
        
    std::cout << "Ant Count = " << ant_count << std::endl;
    
    World::init_world();
    while(AC::ant_count() < ant_count)
        AC::push_ant(Ant());
    Display display = Display(800, 800);
    display.draw_tsp(seed);
    return 0;
}
