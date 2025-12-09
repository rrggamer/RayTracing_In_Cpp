#include<iostream>
#include<SDL2/SDL.h>

int main(){
   
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
    SDL_Surface* winSurface = SDL_GetWindowSurface(win);

    SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format,255,90,120));

    SDL_UpdateWindowSurface(win);

    SDL_Delay(3000);
    return 0;

}