#include "main.h"

int main(){
    State state;
    //Init Sdl
    State_Init(&state);

    //Main Loop
    SDL_Event ev;
    Player player = {0, -110, 0, 0, 0, 100,80};
    float dx,dy;
    dx = sin(player.angle);
    dy = cos(player.angle);
    long long lastFrame = timeInMilliseconds();
    float dt;
    while(!state.quit){
        dt = (timeInMilliseconds() - lastFrame) / 1000.0f;
        lastFrame = timeInMilliseconds();
        while(SDL_PollEvent(&ev)){
            handleInput(&ev,&state);
        }
        playerMovement(&dx,&dy,&player,dt);
        printf("Player %f\n",player.y);
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
    Wall wall[4];
    wall[0] = (Wall){-50, 0, 0};
    wall[1] = (Wall){ 50, 0, 0};
    wall[2] = (Wall){-50, 0, 100};
    wall[3] = (Wall){ 50, 0, 100};
    for(int i = 0;i<4;i++){
        float cs = cos(player->angle);
        float sn = sin(player->angle);
        
        float RelativeX = wall[i].x - player->x;
        float RelativeY = wall[i].y - player->y;
        float RelativeZ = wall[i].z - player->z;

        float x = RelativeX * cs - RelativeY * sn;
        float y = RelativeX * sn + RelativeY * cs;
        float z = RelativeZ + (player->look * y) / 32.0f; 

        if(y <= 0.1f) continue;
        float fov = 200.0f;
        x = x * fov / y + SCREEN_WIDTH / 2.0f;
        y = z * fov / y + SCREEN_HEIGHT / 2.0f;

        //printf("Wall X: %f\n",x);
        if(x > 0 && x < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT){
            State_Square(state,x - 5,y - 5,10,COLOR_GREEN);
        }
    }
    //printf("Wall Y: %f\n",y);
    
    
}

void  playerMovement(float *dx,float *dy,Player *player,float dt){
    if(keysDown.d){
        if(keysDown.shift){
            player->x += *dy * dt;
            player->y -= *dx * dt;
        }else{
            player->angle += player->cameraSpeed * dt;
            if(player->angle > 359){
                player->angle -= 360;
            }
            *dx = sin(player->angle) * player->speed;
            *dy = cos(player->angle) * player->speed;
        }
    }
    if(keysDown.a){
        if(keysDown.shift){
            player->x -= *dy * dt;
            player->y += *dx * dt;
        }else{
            player->angle -= player->cameraSpeed * dt;
            if(player->angle < 0){
                player->angle += 360;
            }
            *dx = sin(player->angle) * player->speed;
            *dy = cos(player->angle) * player->speed;
        }
    }
    if(keysDown.w){
        if(keysDown.shift){
            player->look -= player->cameraSpeed * dt;
            if(player->look < -90) player->look = -90;
        }else{
            player->x += *dx * dt;
            player->y += *dy * dt;
        }
    }
    if(keysDown.s){
        if(keysDown.shift){
            player->look += player->cameraSpeed * dt;
            if(player->look > 90) player->look = 90;
        }else{
            player->x -= *dx * dt;
            player->y -= *dy * dt;
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
long long timeInMilliseconds() {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}