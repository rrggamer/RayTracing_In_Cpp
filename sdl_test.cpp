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
    Uint32 color;

    /* Circle(float X_, float Y_, float radius_){
        this->x = X_;
        this->y = Y_;
        this->radius = radius_;
    }*/

    Circle(float X_, float Y_, float radius_, Uint32  color_)
        : x(X_), y(Y_), radius(radius_), color(color_){}

};


// void drawCircle(SDL_Surface *surface, Circle& circle ){
    
//     double radius_squared = (circle.radius) * (circle.radius);

//     for(int x = circle.x - circle.radius; x <= circle.x+circle.radius; x++){
//         for(double y = circle.y - circle.radius; y <= circle.y+circle.radius; y++){

//             double distance_squared = (x-circle.x)*(x-circle.x) + (y-circle.y) * (y-circle.y);
//             if( distance_squared < radius_squared){

//                 SDL_Rect pixel = {x,y,1,1};
//                 SDL_FillRect(surface, &pixel, circle.color);

//             }

//         } 

//     }
// }

static inline void putPixel(SDL_Surface* s, int x, int y, Uint32 color) {
    if ((unsigned)x >= (unsigned)s->w || (unsigned)y >= (unsigned)s->h) return;
    Uint32* pixels = (Uint32*)s->pixels;
    int pitchPixels = s->pitch / 4;           // 4 bytes per pixel (ARGB8888/RGBA8888)
    pixels[y * pitchPixels + x] = color;      // 2D -> 1D
}


void drawFilledCircle(SDL_Surface* s, int cx, int cy, int r, Uint32 color) {
    if (SDL_MUSTLOCK(s)) SDL_LockSurface(s);

    int r2 = r * r;

    for (int y = cy - r; y <= cy + r; ++y) {
        int dy = y - cy;
        for (int x = cx - r; x <= cx + r; ++x) {
            int dx = x - cx;
            if (dx*dx + dy*dy <= r2) {
                putPixel(s, x, y, color);
            }
        }
    }

    if (SDL_MUSTLOCK(s)) SDL_UnlockSurface(s);
}



int main(){
   
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
    SDL_Surface* winSurface = SDL_GetWindowSurface(win);
    

    SDL_FillRect(winSurface, NULL, BLACK_COLOR);
    
    Circle circle(200, 200, 80, WHITE_COLOR);

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
        drawFilledCircle(winSurface, (int)circle.x, (int)circle.y, (int)circle.radius, WHITE_COLOR);
        SDL_UpdateWindowSurface(win);
    }

}