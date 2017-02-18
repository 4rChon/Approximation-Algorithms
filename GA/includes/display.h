#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <tour.h>
#include <population.h>
#include <SDL.h>
#include <SDL_image.h>

class Display {
    private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        SDL_Renderer* gRenderer;
        SDL_Window* gWindow;
        
        bool init();
        int draw(Tour tour);
    public:        
        Display(int, int);
        void close();
        int draw_tsp(Population pop);
};

#endif
