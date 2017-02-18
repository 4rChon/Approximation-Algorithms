#include <display.h>
#include <ant_colony.h>
#include <tour.h>
#include <tour_manager.h>
#include <world.h>
#include <cmath>
#include <ctime>    
#include <stdio.h> //printf

const int NODE_RADIUS = 2;
const int SCREEN_MARGIN = 10;

Display::Display (int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;
    gRenderer = NULL;
    gWindow = NULL;
}

bool Display::init()
{   
    bool success = true;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Ant Colony", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

void Display::close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    
    IMG_Quit();
    SDL_Quit();
}

int Display::draw(Tour tour, bool showSolution, bool showPheromones)
{   
    //glLineWidth(2);
    float max_x = 0;
    float max_y = 0;
    float max;
    for(std::size_t i=0; i < TM::city_count(); i++)
    {
        if(TM::get_city(i).get_x() > max_x)
            max_x = TM::get_city(i).get_x();
        if(TM::get_city(i).get_y() > max_y)
            max_y = TM::get_city(i).get_y();
    }
    if(max_x > max_y)
        max = max_x;
    else max = max_y;
    
    if(showPheromones)
        for(std::size_t i=0; i < TM::city_count(); i++)
        {
            float x1 = (TM::get_city(i).get_x()/max * (SCREEN_WIDTH  - SCREEN_MARGIN)),
                  y1 = (SCREEN_HEIGHT - (TM::get_city(i).get_y()/max * (SCREEN_HEIGHT - SCREEN_MARGIN)));
            
            for(std::size_t j=0; j < TM::city_count(); j++)
            {
                float x2 = (TM::get_city(j).get_x()/max * (SCREEN_WIDTH  - SCREEN_MARGIN)),
                      y2 = (SCREEN_HEIGHT - (TM::get_city(j).get_y()/max * (SCREEN_HEIGHT - SCREEN_MARGIN)));
                
                unsigned color1 = int(World::get_product(i, j) * max * 350);
                if(color1 > 30)
                {
                    SDL_SetRenderDrawColor(gRenderer, 0, color1, color1, 0xFF);
                    SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
                }
            }
        }
    
    for(std::size_t i=0; i < TM::city_count(); i++)
    {
        float x1 = World::get_tour().get_city(i).get_x()/max * (SCREEN_WIDTH  - SCREEN_MARGIN),
              y1 = SCREEN_HEIGHT - (World::get_tour().get_city(i).get_y()/max * (SCREEN_HEIGHT - SCREEN_MARGIN));
        if(showSolution)              
        {
            if(i != TM::city_count()-1)
            {
                float x2 = World::get_tour().get_city(i+1).get_x()/max * (SCREEN_WIDTH  - SCREEN_MARGIN),
                      y2 = SCREEN_HEIGHT - (World::get_tour().get_city(i+1).get_y()/max * (SCREEN_HEIGHT - SCREEN_MARGIN));
                
                //unsigned color1 = int(World::get_product(i, i+1)*2550000);      
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
            }
            else if(i == TM::city_count()-1)
            {
                float x2 = World::get_tour().get_city(0).get_x()/max * (SCREEN_WIDTH  - SCREEN_MARGIN),
                      y2 = SCREEN_HEIGHT - (World::get_tour().get_city(0).get_y()/max * (SCREEN_HEIGHT - SCREEN_MARGIN));
                
                //unsigned color1 = int(World::get_product(i, 0)*2550000);
                
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);   
            }
        }
        SDL_Rect fillRect = {int(x1)-NODE_RADIUS, int(y1)-NODE_RADIUS, 4, 4};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &fillRect);
    }
    
    return 0;
}

int Display::draw_tsp(unsigned seed)
{
    bool showSolution = true;
    bool showPheromones = true;
    int generations = 0;
    float totalTime = 0;
    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        bool quit = false;
        
        SDL_Event e;

        while(!quit)
        {
            generations++;
            
            while(SDL_PollEvent(&e) != 0)
                if(e.type == SDL_QUIT) quit = true;
                else if( e.type == SDL_KEYDOWN )
                {
                    switch( e.key.keysym.sym)
                    {
                        case SDLK_SPACE: showSolution = !showSolution;
                        break;
                        case SDLK_x: showPheromones = !showPheromones;
                        break;
                    }    
                }            
            
            clock_t before = clock();
            
            AC::step(seed);
            totalTime += clock() - before;
            if(totalTime > 5000)
                quit = true;
            
            //printf("Current Best: %f\n", pop.get_fittest().calc_distance());
            
            SDL_SetRenderDrawColor(gRenderer, 10, 10, 50, 0xFF);
            SDL_RenderClear(gRenderer);
                        
            this->draw(World::get_tour(), showSolution, showPheromones);
                        
            SDL_RenderPresent(gRenderer);
            SDL_UpdateWindowSurface(gWindow);
        }
        float avgTime = generations/(totalTime/1000);
        printf("Done\n");
        //printf("Initial: %f\n", initDist);
        printf("Final: %f\n", World::get_tour().calc_distance());
        printf("Generations: %d\n", generations);
        printf("Time: %.f\n", totalTime/1000);      
        printf("Gens/Second: %.2f", avgTime);
    }
    return 0;
}
