#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <SDL.h>
#include <SDL_image.h>
#include <tour.h>

class Display {
    private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        SDL_Renderer* gRenderer;
        SDL_Window* gWindow;
        
        bool init();
        int draw(Tour tour, bool showSolution, bool showPheromones);
    public:        
        Display(int, int);
        void close();
        int draw_tsp(unsigned seed);
};

#endif
