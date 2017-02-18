#include <city.h>
#include <display.h>
#include <population.h>
#include <tour_manager.h>
#include <tsp.h>
#include <util.h>
#include <iostream>     // std::cout, std::end
#include <cstdlib>      // srand
#include <ctime>        // time

int main(int argc, char *argv[])
{
    srand(time(NULL));
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
    
    Population pop = Population(100);
    
    Display disp = Display(500, 500);
    disp.draw_tsp(pop);
    
    return 0;
}
    
