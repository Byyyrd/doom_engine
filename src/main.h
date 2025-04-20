#include "state.h"
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <sys/time.h>
#include <stdbool.h>
#define PI 3.14159265358979323846f
typedef struct Player{
    float x,y,z;
    float angle;
    float look;
    float speed;
    float cameraSpeed;
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
void playerMovement(float *dx,float *dy,Player *player,float dt);
long long timeInMilliseconds();