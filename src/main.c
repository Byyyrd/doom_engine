#include "state.h"
#include <math.h>
#define PI 3.14159265358979323846f
typedef struct Player{
    float x,y,z;
    float angle;
    float look;
} Player;
struct KeysDown{
    bool w,a,s,d,shift;
};
#define sin(value) sinf(value * PI/180.0f)
#define cos(value) cosf(value * PI/180.0f)
struct KeysDown keysDown;
void setKeyDown(SDL_Keycode code,bool value);
void handleInput(SDL_Event *ev,State *state);
void draw3D(State *state,Player *player);
int main(){
    State state;
    //Init Sdl
    State_Init(&state);

    //Main Loop
    SDL_Event ev;
    Player player = {70, -110, 0, 0};
    float dx,dy;
    dx = sin(player.angle);
    dy = cos(player.angle);
    while(!state.quit){
        while(SDL_PollEvent(&ev)){
            handleInput(&ev,&state);
        }
        if(keysDown.d){
            player.angle += 4;
            if(player.angle > 359){
                player.angle -= 360;
            }
            dx = sin(player.angle) * 10;
            dy = cos(player.angle) * 10;
        }
        if(keysDown.a){
            player.angle -= 4;
            if(player.angle < 0){
                player.angle += 360;
            }
            dx = sin(player.angle) * 10;
            dy = cos(player.angle) * 10;
        }
        if(keysDown.w){
            if(keysDown.shift){
                player.look -= 4;
                if(player.look < -90) player.look = -90;
            }else{
                player.x += dx;
                player.y += dy;
            }
        }
        if(keysDown.s){
            if(keysDown.shift){
                player.look += 4;
                if(player.look > 90) player.look = 90;
            }else{
                player.x -= dx;
                player.y -= dy;
            }
        }
        draw3D(&state,&player);
        State_Square(&state,SCREEN_WIDTH/2 - 5,SCREEN_HEIGHT/2 - 5,10,COLOR_RED);
        State_DrawPixels(&state);
    }
    SDL_DestroyWindow(state.window);
    SDL_DestroyTexture(state.texture);
    return 0;
}
typedef struct {
    float x,y,z;
} Wall;
void draw3D(State *state,Player *player){
    Wall wall[2];
    wall[0].x = 40;
    wall[0].y = 10;
    wall[0].z = 0;
    wall[1].x = 40;
    wall[1].y = 290; 
    wall[1].z = 0;
    for(int i = 0;i<2;i++){
        float cs = cos(player->angle);
        float sn = sin(player->angle);
        
        wall[i].x -= player->x;
        wall[i].y -= player->y;
        wall[i].z -= player->z;
        
        float x = wall[i].x;
        float y = wall[i].y;
        float z = wall[i].z;

        x = wall[i].x * cs - wall[i].y * sn;
        y = wall[i].x * sn + wall[i].y * cs;
        z = (player->look * y) / 32.0f; 

        if(y <= 0) continue;
        float fov = 200.0f;
        x = x * fov / y + SCREEN_WIDTH / 2.0f;
        y = z * fov / y + SCREEN_HEIGHT / 2.0f;

        // printf("Wall X: %f\n",x);
        // printf("Wall Y: %f\n",y);
        if(x > 0 && x < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT){
            State_Square(state,x - 5,y - 5,10,COLOR_GREEN);
        }
    }
    
    
}



void handleInput(SDL_Event *ev,State *state){
    switch (ev->type)
    {
    
    case SDL_KEYDOWN:
        //printf("%i\n",ev->key.keysym.sym);
        setKeyDown(ev->key.keysym.sym,true);
        break;
    case SDL_KEYUP:
        setKeyDown(ev->key.keysym.sym,false);
        break;
    case SDL_QUIT:
        state->quit = true;
        break;
    }
}
void setKeyDown(SDL_Keycode code,bool value){
    if(code == SDLK_LSHIFT || code == SDLK_RSHIFT){
        keysDown.shift = value;
    }
    switch (code)
    {
    case SDLK_w:
        keysDown.w = value;
        break;
    case SDLK_a:
        keysDown.a = value;
        break;
    case SDLK_s:
        keysDown.s = value;
        break;
    case SDLK_d:
        keysDown.d = value;
        break;
    }
}