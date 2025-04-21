#include "main.h"

int main(){
    State state;
    //Init Sdl
    State_Init(&state);

    for (int i = 0;i<360;i++){
        M.sin[i] = sin(i/180.0f * M_PI);
        M.cos[i] = cos(i/180.0f * M_PI);
    } 
    //Main Loop
    SDL_Event ev;
    Player player = {70, -110, 20, 0, 0, 100,80};
    float dx,dy;
    dx = M.sin[player.angle];
    dy = M.cos[player.angle];
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
void pixel(State *state,int x,int y){
    State_Square(state,x-1,y-1,2,COLOR_WHITE);
}
void draw3D(State *state,Player *player){
    // Wall wall[2];
    // wall[0] = (Wall){40, 10, 0};
    // wall[1] = (Wall){ 40, 290, 0};
    // float x1,x2,y1,y2;
    // for(int i = 0;i<2;i++){
    //     float cs = M.cos[player->angle];
    //     float sn = M.sin[player->angle];
        
    //     float RelativeX = wall[i].x - player->x;
    //     float RelativeY = wall[i].y - player->y;
    //     float RelativeZ = wall[i].z - player->z;

    //     float x = RelativeX * cs - RelativeY * sn;
    //     float y = RelativeX * sn + RelativeY * cs;
    //     float z = RelativeZ + (player->look * y) / 32.0f; 

    //     if(y <= 0.1f) continue;
    //     float fov = 400.0f;
    //     x = x * fov / y + SW2;
    //     y = z * fov / y + SH2;

    //     if(i == 0){
    //         x1 = x;
    //         y1 = y;
    //     }else{
    //         x2 = x;
    //         y2 = y;
    //     }
    //     //printf("Wall X: %f\n",x);
    //     if(x > 0 && x < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT){
    //         State_Square(state,x - 5,y - 5,10,COLOR_GREEN);
    //     }
    // }
    // drawWall(state,x1,y1,x2,y2,100);
    //printf("Wall Y: %f\n",y);
    int wx[4];int wy[4];int wz[4];float CS = M.cos[player->angle];float SN = M.sin[player->angle];
    int x1 = 40-player->x; int y1 = 10-player->y;
    int x2 = 40-player->x; int y2 = 290-player->y;

    //World X-Pos
    wx[0] = x1 * CS - y1 * SN;
    wx[1] = x2 * CS - y2 * SN;
    wx[2] = wx[0];
    wx[3] = wx[1];

    //World Y-Pos
    wy[0] = x1 * SN + y1 * CS;
    wy[1] = x2 * SN + y2 * CS;
    wy[2] = wy[0];
    wy[3] = wy[1];

    //World Z-Pos
    wz[0] = 0 - player->z + (player->look * player->y)/32.0f;
    wz[1] = 0 - player->z + (player->look * player->y)/32.0f;
    wz[2] = wz[0] + 40;
    wz[3] = wz[1] + 40;

    wx[0] = wx[0] * 200/ wy[0] + SW2;wy[0] = wz[0] * 200/ wy[0] + SH2;
    wx[1] = wx[1] * 200/ wy[1] + SW2;wy[1] = wz[1] * 200/ wy[1] + SH2;
    wx[2] = wx[2] * 200/ wy[2] + SW2;wy[2] = wz[2] * 200/ wy[2] + SH2;
    wx[3] = wx[3] * 200/ wy[3] + SW2;wy[3] = wz[3] * 200/ wy[3] + SH2;
    // if(wy[0] > 0){
    //     if(wx[0] > 0 && wx[0] < SCREEN_WIDTH && wy[0] > 0 && wy[0] < SCREEN_HEIGHT){pixel(state,wx[0],wy[0]);}
    // }

    // if(wy[1]  > 0){
    //     if(wx[1] > 0 && wx[1] < SCREEN_WIDTH && wy[1] > 0 && wy[1] < SCREEN_HEIGHT){pixel(state,wx[1],wy[1]);}
    // }
    drawWall(state,wx[0],wx[1],wy[0],wy[1],wy[2],wy[3]);
    
}
void drawWall(State *state,float x1,float x2,float b1,float b2,float t1,float t2){
    float dx = (x2 - x1); if(dx == 0) dx = 1;
    float dyb = (b2-b1); // delta y bottom line
    float dyt = (t2-t1); // delta y top line
    float xs = x1;
    for(int x = x1; x < x2;x++){
        int y1 = dyb * (x-xs + 0.5f) / dx + b1;
        int y2 = dyt * (x-xs + 0.5f) / dx + t1;


        for (int  y = y1; y < y2; y++){
            State_Square(state,x,y,1,COLOR_WHITE);
        }
        
    }
}
void  playerMovement(float *dx,float *dy,Player *player,float dt){
    *dx = M.sin[player->angle] * player->speed;
    *dy = M.cos[player->angle] * player->speed;
    if(keysDown.d){
        if(keysDown.shift){
            player->x += *dy * dt;
            player->y -= *dx * dt;
        }else{
            player->angle += player->cameraSpeed * dt;
            if(player->angle > 359){
                player->angle -= 360;
            }
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