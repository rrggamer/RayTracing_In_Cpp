#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>


#define WHITE_COLOR 0xffffffff 
#define BLACK_COLOR 0x00000000
#define YELLOW_COLOR 0xFFFF00

const int WIDTH = 1920;
const int HEIGHT = 1200;


struct Circle
{
    float x;
    float y;
    float radius;
    Uint32 color;

    Circle(float X_, float Y_, float radius_, Uint32  color_)
        : x(X_), y(Y_), radius(radius_), color(color_){}

};

static inline void putPixel(SDL_Surface* s, int x, int y, Uint32 color) {
    if ((unsigned)x >= (unsigned)s->w || (unsigned)y >= (unsigned)s->h) return;
    Uint32* pixels = (Uint32*)s->pixels;
    int pitchPixels = s->pitch / 4;          
    pixels[y * pitchPixels + x] = color;      
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

static void blitText(SDL_Surface* dst, TTF_Font* font,
                     const char* text, int x, int y)
{
    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, white);
    if (!textSurface) return;

    SDL_Rect pos = { x, y, textSurface->w, textSurface->h };
    SDL_BlitSurface(textSurface, nullptr, dst, &pos);

    SDL_FreeSurface(textSurface);
}

int main(){
   

    //SDL_Init Window and Surface
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Surface* winSurface = SDL_GetWindowSurface(win);
    
    //SDL_ttf Init
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("Font.ttf",26);
    if(!font){
        printf("TTF Error: %s\n", TTF_GetError());
    };


    SDL_FillRect(winSurface, NULL, BLACK_COLOR);
    
    Circle circle(200, 200, 80, WHITE_COLOR);
    Circle circle2(200,200,100,YELLOW_COLOR);

    Uint64 last_counter = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();

    int frames = 0;
    double fps_timer = 0.0;
    double fps_display = 0.0;

    int app_is_running = 1;
    while (app_is_running){
        SDL_Event event;

        Uint64 current_counter = SDL_GetPerformanceCounter();
        // printf("Current_counter: %ld \n",current_counter);
        // printf("Frequency: %ld \n",frequency);
        
        double delta_time =
            (double)(current_counter - last_counter) / frequency;
        last_counter = current_counter;

        fps_timer += delta_time;
        frames++;


        if(fps_timer >= 1.0) {

            fps_display = frames / fps_timer;
            printf("FPS: %.2f\n", fps_display);
            frames = 0;
            fps_timer = 0.0;
        }

        while(SDL_PollEvent(&event)){

            // printf("event type = %d\n", event.type);
            
            if(event.type == SDL_QUIT){
                app_is_running = 0;
            }
           
            if(event.type == SDL_MOUSEMOTION){

                // printf("x: %d y: %d \n",event.motion.x ,event.motion.y);
                circle.x = event.motion.x;
                circle.y = event.motion.y;
            }

            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_w)
                    circle2.y = circle2.y - 3;
                
                if(event.key.keysym.sym == SDLK_s)
                    circle2.y =circle2.y + 3;
            
                if(event.key.keysym.sym == SDLK_a)
                    circle2.x = circle2.x - 3;
                
                if(event.key.keysym.sym == SDLK_d)
                    circle2.x =circle2.x + 3;
            }

        }

        SDL_FillRect(winSurface, NULL, BLACK_COLOR);
        drawFilledCircle(winSurface, static_cast<int>(circle2.x), static_cast<int>(circle2.y), static_cast<int>(circle2.radius), YELLOW_COLOR);
        drawFilledCircle(winSurface, static_cast<int>(circle.x), static_cast<int>(circle.y), static_cast<int>(circle.radius), WHITE_COLOR);
        
        char buf[64];
        std::snprintf(buf, sizeof(buf), "FPS: %.1f", fps_display);
        blitText(winSurface, font, buf, 10, 10);

        SDL_UpdateWindowSurface(win);
  
  
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(win);
    SDL_Quit();
    
    return 0;
}