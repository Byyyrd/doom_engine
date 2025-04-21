#include "state.h"
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <sys/time.h>
#include <stdbool.h>
#define M_PI 3.14159265358979323846f
typedef struct
{
    float sin[360];
    float cos[360];
}maths;maths M;
typedef struct Player{
    float x,y,z;
    int angle;
    float look;
    float speed;
    float cameraSpeed;
} Player;
struct KeysDown{
    bool w,a,s,d,shift;
};
// #define sin(value) sinf(value * M_PI/180.0f)
// #define cos(value) cosf(value * M_PI/180.0f)
struct KeysDown keysDown;
void setKeyDown(SDL_Keycode code,bool value);
void handleInput(SDL_Event *ev,State *state);
void draw3D(State *state,Player *player);
void playerMovement(float *dx,float *dy,Player *player,float dt);
void drawWall(State *state,float x1,float y1,float x2,float y2,float y3,float y4);
long long timeInMilliseconds();