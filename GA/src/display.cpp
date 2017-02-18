#include <display.h>
#include <population.h>
#include <tour.h>
#include <tour_manager.h>
#include <tsp.h>
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
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

int Display::draw(Tour tour)
{   
    float max_x = 0;
    float max_y = 0;
    float max;
    for(std::size_t i=0; i < TM::city_count(); i++)
    {
        if(tour.get_city(i).get_x() > max_x)
            max_x = tour.get_city(i).get_x();
        if(TM::get_city(i).get_y() > max_y)
            max_y = TM::get_city(i).get_y();
    }
    
    if(max_x > max_y)
        max = max_x;
    else max = max_y;
    
    for(std::size_t i=0; i < TM::city_count(); i++)
    {
        float x1 = (tour.get_city(i).get_x()/max * (SCREEN_WIDTH  - SCREEN_MARGIN) - NODE_RADIUS),
              y1 = (SCREEN_HEIGHT - (tour.get_city(i).get_y()/max * (SCREEN_HEIGHT - SCREEN_MARGIN) - NODE_RADIUS));
        if(i != TM::city_count()-1)
        {
            float x2 = (tour.get_city(i+1).get_x()/max * (SCREEN_WIDTH  - SCREEN_MARGIN) - NODE_RADIUS),
                  y2 = (SCREEN_HEIGHT - (tour.get_city(i+1).get_y()/max * (SCREEN_HEIGHT - SCREEN_MARGIN) - NODE_RADIUS));
            
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);        
        }
        else if(i == TM::city_count()-1)
        {
            float x2 = (tour.get_city(0).get_x()/max * (SCREEN_WIDTH  - SCREEN_MARGIN) - NODE_RADIUS),
                  y2 = (SCREEN_HEIGHT - (tour.get_city(0).get_y()/max * (SCREEN_HEIGHT - SCREEN_MARGIN) - NODE_RADIUS));
                  
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
        }
    
        SDL_Rect fillRect = {int(x1)-NODE_RADIUS, int(y1)-NODE_RADIUS, 4, 4};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &fillRect);
    }

    return 0;
}

int Display::draw_tsp(Population pop)
{
    float initDist = pop.get_fittest().calc_distance();
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
            
            clock_t before = clock();
            
            TSP::evolve_pop(pop);            
            
            totalTime += clock() - before;
            
            //printf("Current Best: %f\n", pop.get_fittest().calc_distance());
            
            SDL_SetRenderDrawColor(gRenderer, 10, 10, 50, 0xFF);
            SDL_RenderClear(gRenderer);
                        
            this->draw(pop.get_fittest());
                        
            SDL_RenderPresent(gRenderer);
            SDL_UpdateWindowSurface(gWindow);
        }
        float avgTime = generations/(totalTime/1000);
        printf("Done\n");
        printf("Initial: %f\n", initDist);
        printf("Final: %f\n", pop.get_fittest().calc_distance());
        printf("Generations: %d\n", generations);
        printf("Time: %.f\n", totalTime/1000);      
        printf("Gens/Second: %.2f", avgTime);
    }
    return 0;
}
