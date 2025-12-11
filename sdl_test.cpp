#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>


#define WHITE_COLOR 0xffffffff 
#define BLACK_COLOR 0x00000000


struct Circle
{
    float x;
    float y;
    float radius;

    /* Circle(float X_, float Y_, float radius_){
        this->x = X_;
        this->y = Y_;
        this->radius = radius_;
    }*/

    Circle(float X_, float Y_, float radius_)
        : x(X_), y(Y_), radius(radius_){}

};


void drawCircle(SDL_Surface *surface, Circle& circle ){
    
    float x = circle.x;
    float y = circle.y;
    SDL_Rect dstRect = {x,y,circle.radius,circle.radius};
    SDL_FillRect(surface, &dstRect, WHITE_COLOR);
    printf("x: %f, y: %f\n",x,y);
    
}



int main(){
   
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
    SDL_Surface* winSurface = SDL_GetWindowSurface(win);

    SDL_FillRect(winSurface, NULL, BLACK_COLOR);
    
    Circle circle(10,50,80);

    int app_is_running = 1;
    while (app_is_running){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                app_is_running = 0;
                SDL_Quit();
                SDL_DestroyWindow(win);
            }

        }
        drawCircle(winSurface,circle);
        SDL_UpdateWindowSurface(win);
    }

}