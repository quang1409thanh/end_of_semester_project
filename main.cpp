#include<SDL.h>
#include<SDL_image.h>

bool quit=false;

SDL_Event event;

int ballx=10;
int bally=500;
int ballvelx=1;
int ballvely=1;

int brickw=80;
int brickh=35;

int bkw=800;
int bkh=600;

int bkwmin=0;
int bkhmin=0;

int batx=bkw/2;
int baty=bkh-22;

SDL_Surface *brick;
SDL_Texture *bricktexture;
SDL_Rect brickrect[3][7];
SDL_Rect ballrect;
void InitializeBrick(){
    brickrect[0][0]={50,50,brickw,brickh};
    brickrect[0][1]={150,50,brickw,brickh};
    brickrect[0][2]={250,50,brickw,brickh};
    brickrect[0][3]={350,50,brickw,brickh};
    brickrect[0][4]={450,50,brickw,brickh};
    brickrect[0][5]={550,50,brickw,brickh};
    brickrect[0][6]={650,50,brickw,brickh};
    brickrect[1][0]={50,150,brickw,brickh};
    brickrect[1][1]={150,150,brickw,brickh};
    brickrect[1][2]={250,150,brickw,brickh};
    brickrect[1][3]={350,150,brickw,brickh};
    brickrect[1][4]={450,150,brickw,brickh};
    brickrect[1][5]={550,150,brickw,brickh};
    brickrect[1][6]={650,150,brickw,brickh};
    brickrect[2][0]={50,250,brickw,brickh};
    brickrect[2][1]={150,250,brickw,brickh};
    brickrect[2][2]={250,250,brickw,brickh};
    brickrect[2][3]={350,250,brickw,brickh};
    brickrect[2][4]={450,250,brickw,brickh};
    brickrect[2][5]={550,250,brickw,brickh};
    brickrect[2][6]={650,250,brickw,brickh};
}

void EnvenHandler(){
    // do something
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        quit = true;
    }
    else if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_LEFT&&batx>0){
            batx=batx-2;
        }
        else if(event.key.keysym.sym == SDLK_RIGHT&&batx<bkw-91){
            batx=batx+2;
        }
    }
}

void moveBall(){
    ballx+=ballvelx;
    bally+=ballvely;
}


void ball_collision(){
    if(ballx<bkwmin||ballx>bkw-20){
        ballvelx*=-1;
    }
    if(bally<bkhmin||bally>bkh-20){
        ballvely*=-1;
    }
    int ballscaling=22;// hoặc bằng 20 check sau đoạn này 
    if(bally+ballscaling>baty&&bally<baty+22&&ballx>batx&&ballx<batx+91){
        ballvely*=-1;
    }
}
int main(int argc, char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("My Game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_Rect bkrect ={0,0,800,600};
    InitializeBrick();
    
    SDL_Surface *ball = IMG_Load("ball.png");
    SDL_Surface *bk = IMG_Load("bg.jpg");
    SDL_Surface *bat = IMG_Load("batdone.png");
    brick=IMG_Load("img/bricks/violet.png");
    
    SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer, ball);
    SDL_Texture *bktexture = SDL_CreateTextureFromSurface(renderer, bk);
    SDL_Texture *battexture = SDL_CreateTextureFromSurface(renderer, bat);
    bricktexture=SDL_CreateTextureFromSurface(renderer,brick);
    while(!quit){
        EnvenHandler();
        ballrect ={ballx,bally,20,20};
        SDL_Rect batrect ={batx,baty,91,22};
        moveBall();
        ball_collision();
    
        SDL_RenderCopy(renderer, bktexture, NULL,&bkrect);
        SDL_RenderCopy(renderer, balltexture, NULL, &ballrect);
        SDL_RenderCopy(renderer, battexture, NULL, &batrect);
        for(int i=0;i<3;i++){
            for(int j=0;j<7;j++){
                SDL_RenderCopy(renderer,bricktexture,NULL,&brickrect[i][j]);
            }
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    SDL_Quit();
}