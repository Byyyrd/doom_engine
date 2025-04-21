#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SW2 SCREEN_WIDTH/2
#define SH2 SCREEN_HEIGHT/2
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x00000000
#define COLOR_RED 0xFF0000FF
#define COLOR_GREEN 0x00FF00FF
#define COLOR_BLUE 0x0000FFFF
#define COLOR_YELLOW 0xFFFF00FF
#define COLOR_CYAN 0x00FFFFFF
#define COLOR_PINK 0xFF00FFFF
typedef struct state{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    bool quit; 
    Uint32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
} State;

int State_Init(State *state);
void State_ClearTexture(State *state);
void State_DrawPixels(State *state);
void State_VertLine(State *state,int x,int y,int height,Uint32 color);
void State_Square(State *state,int x,int y,int size,Uint32 color);