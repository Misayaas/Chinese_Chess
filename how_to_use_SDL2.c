#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>

SDL_Window *Window = NULL;     // 定义一个窗口
SDL_Renderer *Renderer = NULL; // 定义一个画笔

SDL_Surface *MainBackGroundSurface = NULL; // 定义一个图形
SDL_Texture *MainBackGroundTexture = NULL; // 让画笔画出来
SDL_Rect MainBackGroundRect;               // Texture的信息

SDL_Surface *PlayBackGroundSurface = NULL;
SDL_Texture *PlayBackGroundTexture = NULL;
SDL_Rect PlayBackGroundRect;

// 定义字体
TTF_Font *ScoreFont = NULL;
SDL_Surface *ScoreSurface = NULL;
SDL_Texture *ScoreTexture = NULL;
SDL_Rect ScoreRect;
SDL_Color FontColor = {255, 255, 255, 255};

void LOAD() // 加载图片函数
{
    MainBackGroundSurface = IMG_Load("Text.jpg"); // 想要的图片，输入文件名
    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);
    MainBackGroundRect.x = 0;
    MainBackGroundRect.y = 0;
    MainBackGroundRect.w = MainBackGroundSurface->w;
    MainBackGroundRect.h = MainBackGroundSurface->h;

    PlayBackGroundSurface = IMG_Load("Text2.jpg");
    PlayBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, PlayBackGroundSurface);

    ScoreFont = TTF_OpenFont("BRLNSR.TTF", 50);
}

void PLAY() // 开始游戏函数
{
    printf("You are in the Play UI!\n");
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, PlayBackGroundTexture, NULL, NULL);
    SDL_RenderPresent(Renderer);
    return;
}

void PRINTSCORE()
{
    ScoreSurface = TTF_RenderUTF8_Blended(ScoreFont, "114514", FontColor);
    ScoreTexture = SDL_CreateTextureFromSurface(Renderer, ScoreSurface);
    ScoreRect.x = 200;
    ScoreRect.y = 100;
    ScoreRect.w = ScoreSurface->w;
    ScoreRect.h = ScoreSurface->h;
    SDL_RenderCopy(Renderer, ScoreTexture, NULL, &ScoreRect);
    SDL_RenderPresent(Renderer);
}

void QUIT() // 退出函数
{
    SDL_FreeSurface(MainBackGroundSurface);
    SDL_FreeSurface(PlayBackGroundSurface);
    SDL_FreeSurface(ScoreSurface);

    SDL_DestroyTexture(MainBackGroundTexture);
    SDL_DestroyTexture(PlayBackGroundTexture);
    SDL_DestroyTexture(ScoreTexture);

    TTF_CloseFont(ScoreFont);

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

int SDL_main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    Window = SDL_CreateWindow("PROJECT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN);
    // 参数分别是（title,x,y,w,h,flags）
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    // 参数分别是（对应的window，index，flags）
    SDL_Event MainEvent; // 主事件
    LOAD();              // 加载图片

    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, MainBackGroundTexture, NULL, &MainBackGroundRect);
    SDL_RenderPresent(Renderer);

    while (SDL_WaitEvent(&MainEvent))
    {
        switch (MainEvent.type)
        {
        case SDL_QUIT:
            QUIT();
            break;
        case SDL_KEYDOWN: // 按下按键
            switch (MainEvent.key.keysym.sym)
            {
            case SDLK_s: // S按键
            case SDLK_RETURN:
                PLAY();
                break;
            case SDLK_ESCAPE: // ESC键退出
                QUIT();
                break;
            case SDLK_e:
                PRINTSCORE();
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN: // 按下鼠标
            if (MainEvent.button.x > 205 && MainEvent.button.x < 597 && MainEvent.button.y > 651 && MainEvent.button.y < 774)
                PLAY(); // 通过坐标判断开始按钮

            printf("(%d,%d)\n", MainEvent.button.x, MainEvent.button.y); // 打印鼠标位置
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        case SDL_MOUSEMOTION:
            break;
        default:
            break;
        }
    }

    QUIT();
}