#include "state.h"

int State_Init(State *state){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL Init Error: %s\n!",SDL_GetError());
        return -1;
    }
    state->window = SDL_CreateWindow("DOOOM!",SDL_WINDOWPOS_CENTERED_DISPLAY(1),SDL_WINDOWPOS_CENTERED_DISPLAY(1),SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(state->window == NULL){
        printf("Couldnt create Window: %s\n!",SDL_GetError());
        return -1;
    }
    state->renderer = SDL_CreateRenderer(state->window,-1,SDL_RENDERER_PRESENTVSYNC); 
    if(state->renderer == NULL){
        printf("Couldnt create Renderer: %s\n!",SDL_GetError());
        return -1;
    }
    state->texture = SDL_CreateTexture(state->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH,SCREEN_HEIGHT);
    if(state->texture == NULL){
        printf("Couldnt create Texture: %s\n!",SDL_GetError());
        return -1;
    }
    State_ClearTexture(state);
}

void State_ClearTexture(State *state){
    for(int i = 0;i<SCREEN_HEIGHT;i++){
        for(int j = 0;j<SCREEN_WIDTH;j++){
            state->pixels[j + i * SCREEN_WIDTH] = COLOR_BLACK;
        }
    }
}
void State_DrawPixels(State *state){
    SDL_UpdateTexture(state->texture,NULL,state->pixels,SCREEN_WIDTH * 4);
    SDL_RenderCopyEx(state->renderer,state->texture,NULL,NULL,0.0,NULL,SDL_FLIP_VERTICAL);
    SDL_RenderPresent(state->renderer);
    State_ClearTexture(state);
}
void State_VertLine(State *state,int x,int y,int height,Uint32 color){
    for(int i = 0; i < height; i++){
        state->pixels[x + SCREEN_WIDTH * y + SCREEN_WIDTH * i] = color;
    }
}
void State_Square(State *state,int x,int y,int size,Uint32 color){
    if(x < 0 || x + size > SCREEN_WIDTH || y < 0 || y + size > SCREEN_HEIGHT){
        printf("Square out of Bounds of Screen\n");
        return;
    }
    for(int i = 0; i < size; i++){
        for (size_t j = 0; j < size; j++)
        {
            state->pixels[x + j + SCREEN_WIDTH * y + SCREEN_WIDTH * i ] = color;
        }
    }
}

