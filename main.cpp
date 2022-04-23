#include<SDL.h>
#include<SDL_image.h>

bool quit=false;

SDL_Event event;

SDL_Window *window;
                                          
SDL_Renderer *renderer ;

SDL_Surface *brick;
SDL_Surface *ball;
SDL_Surface *bk;
SDL_Surface *bat;

SDL_Texture *bricktexture;
SDL_Texture *balltexture;
SDL_Texture *bktexture;
SDL_Texture *battexture;

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

int delete_brick_count=0;
int no_of_brick=21; // do có 21 viên gạch trong game

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

bool ball_brick_collision_detect(SDL_Rect rect1,SDL_Rect rect2){
    if(rect1.x>rect2.x+rect2.w){
        return false;
    }
    if(rect1.x+rect1.w<rect2.x){
        return false;
    }
    if(rect1.y>rect2.y+rect2.h){
        return false;
    }
    if(rect1.y+rect1.h<rect2.y){
        return false;
    }
}

void ball_brick_collision(){
    bool a;
    for(int i=0;i<3;i++){
        for(int j=0;j<7;j++){
            a=ball_brick_collision_detect(brickrect[i][j],ballrect);
            if(a==true){
            brickrect[i][j].x=30000;
            ballvely=-ballvely;
            delete_brick_count++;
            }
            a=false;
        }
    }
}

void ball_collision(){
    if(ballx<bkwmin||ballx>bkw-20){
        ballvelx*=-1;
    }
    if(bally<bkhmin){
        ballvely*=-1;
    }
    int ballscaling=22;// hoặc bằng 20 check sau đoạn này 
    if(bally+ballscaling>baty&&bally<baty+22&&ballx>batx&&ballx<batx+91){
        ballvely*=-1;
    }
}

void Destroy(){
    SDL_DestroyTexture(battexture);
    SDL_DestroyTexture(bricktexture);
    SDL_DestroyTexture(bktexture);
    SDL_DestroyTexture(balltexture);
    SDL_FreeSurface(bat);
    SDL_FreeSurface(brick);
    SDL_FreeSurface(bk);
    SDL_FreeSurface(ball);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void winning(){
    SDL_Surface *win=IMG_Load("win.png");
    SDL_Texture *wintexture=SDL_CreateTextureFromSurface(renderer,win);
    SDL_Rect winrect={250,100,350,350};
    SDL_RenderCopy(renderer,wintexture,NULL,&winrect);
    SDL_RenderPresent(renderer);
    while(1){
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT){
            quit = true;
            break;
        }
    }
    Destroy();
    SDL_Quit();
}
int main(int argc, char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("My Game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window, -1, 0);// thiếu có dòng này mà fix mãi chả biết lỗi ở đâu :v
    SDL_Rect bkrect ={0,0,800,600};
    InitializeBrick();
    
    ball= IMG_Load("ball.png");
    bk = IMG_Load("bg.jpg");
    bat = IMG_Load("batdone.png");
    brick=IMG_Load("img/bricks/violet.png");
    
    balltexture = SDL_CreateTextureFromSurface(renderer, ball);
    bktexture = SDL_CreateTextureFromSurface(renderer, bk);
    battexture = SDL_CreateTextureFromSurface(renderer, bat);
    bricktexture=SDL_CreateTextureFromSurface(renderer,brick);
    SDL_RenderCopy(renderer,bktexture,NULL,&bkrect);
    while(!quit){
        EnvenHandler();
        ballrect ={ballx,bally,20,20};
        SDL_Rect batrect ={batx,baty,91,22};
        moveBall();
        ball_collision();
        ball_brick_collision();
        if(delete_brick_count==no_of_brick){
            winning();
        }
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
    Destroy();
    SDL_Quit();
}