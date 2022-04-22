#include<SDL.h>
#include<SDL_image.h>

bool quit=false;

SDL_Event event;

void EnvenHandler(){
    // do something
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        quit = true;
    }
}
int main(int argc, char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("My Game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Rect ballrect ={20,20,20,20};
    SDL_Surface *ball = IMG_Load("ball.png");
    SDL_Texture *balltexture = SDL_CreateTextureFromSurface(renderer, ball);
    SDL_RenderCopy(renderer, balltexture, NULL, &ballrect);
    SDL_RenderPresent(renderer);
    while(!quit){
        EnvenHandler();
    }
    SDL_Quit();
}