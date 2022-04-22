#include<SDL.h>
#include<SDL_image.h>

bool quit=false;

SDL_Event event;

int ballx=10;
int bally=10;
int ballvelx=1;
int ballvely=1;

void EnvenHandler(){
    // do something
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        quit = true;
    }
}

void moveBall(){
    ballx+=ballvelx;
    bally+=ballvely;
}

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("My Game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Rect ballrect ={20,20,20,20};
    SDL_Rect bkrect ={0,0,800,600};

    SDL_Surface *ball = IMG_Load("ball.png");
    SDL_Surface *bk = IMG_Load("bg.jpg");

    SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer, ball);
    SDL_Texture *bktexture = SDL_CreateTextureFromSurface(renderer, bk);
   
    while(!quit){
        EnvenHandler();
        SDL_Rect ballrect ={ballx,bally,20,20};
        moveBall();
        SDL_RenderCopy(renderer, bktexture, NULL,&bkrect);
        SDL_RenderCopy(renderer, balltexture, NULL, &ballrect);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    SDL_Quit();
}