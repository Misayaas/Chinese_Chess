#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// 定义红子
#define R_SHUAI 1
#define R_SHI 2
#define R_XIANG 3
#define R_MA 4
#define R_CHE 5
#define R_PAO 6
#define R_BING 7
// 定义小黑子（你最好是
#define B_JIANG -1
#define B_SHI -2
#define B_XIANG -3
#define B_MA -4
#define B_CHE -5
#define B_PAO -6
#define B_ZU -7

SDL_Window *Window = NULL;     // 定义一个窗口
SDL_Renderer *Renderer = NULL; // 定义一个画笔
SDL_Event MainEvent;           // 定义一个主事件

// 定义开始界面（主界面）
SDL_Surface *MainBackGroundSurface = NULL; // 定义一个图形
SDL_Texture *MainBackGroundTexture = NULL; // 让画笔画出来
SDL_Rect MainBackGroundRect;               // Texture的信息

// 定义游戏界面（对局界面）
SDL_Surface *PlayBackGroundSurface = NULL;
SDL_Texture *PlayBackGroundTexture = NULL;
SDL_Rect PlayBackGroundRect;

// 定义字体(暂时没用到)
TTF_Font *Font = NULL;
SDL_Rect ScoreRect;
SDL_Color FontColor = {255, 255, 255, 255};

// 定义棋子
SDL_Surface *red_shuai = NULL;
SDL_Surface *red_shi = NULL;
SDL_Surface *red_xiang = NULL;
SDL_Surface *red_ma = NULL;
SDL_Surface *red_che = NULL;
SDL_Surface *red_pao = NULL;
SDL_Surface *red_bing = NULL;
SDL_Surface *black_jiang = NULL;
SDL_Surface *black_shi = NULL;
SDL_Surface *black_xiang = NULL;
SDL_Surface *black_ma = NULL;
SDL_Surface *black_che = NULL;
SDL_Surface *black_pao = NULL;
SDL_Surface *black_zu = NULL;
SDL_Surface *Select = NULL;
SDL_Surface *screen = NULL;

// 定义文字
SDL_Surface *red_win = NULL;
SDL_Surface *black_win = NULL;
SDL_Surface *red_choose = NULL;
SDL_Surface *black_choose = NULL;
SDL_Surface *whose_turn = NULL;

// 定义偏移量，用于计算位置
SDL_Rect offset_chess;
SDL_Rect offset_finish;
SDL_Rect offset_choose;
SDL_Rect offset_arrive;
SDL_Rect offset_red_turn;
SDL_Rect offset_black_turn;
SDL_Rect offset_turn;

void LOAD()
{
    MainBackGroundSurface = IMG_Load("Main.png"); // 想要的图片，输入文件名
    MainBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, MainBackGroundSurface);
    MainBackGroundRect.x = 0;
    MainBackGroundRect.y = 0;
    MainBackGroundRect.w = MainBackGroundSurface->w;
    MainBackGroundRect.h = MainBackGroundSurface->h;

    PlayBackGroundSurface = IMG_Load("board.png");
    PlayBackGroundTexture = SDL_CreateTextureFromSurface(Renderer, PlayBackGroundSurface);

    red_shuai = IMG_Load("red_shuai.png");
    red_shi = IMG_Load("red_shi.png");
    red_xiang = IMG_Load("red_xiang.png");
    red_ma = IMG_Load("red_ma.png");
    red_che = IMG_Load("red_che.png");
    red_pao = IMG_Load("red_pao.png");
    red_bing = IMG_Load("red_bing.png");
    black_jiang = IMG_Load("black_jiang.png");
    black_shi = IMG_Load("black_shi.png");
    black_xiang = IMG_Load("black_xiang.png");
    black_ma = IMG_Load("black_ma.png");
    black_che = IMG_Load("black_che.png");
    black_pao = IMG_Load("black_pao.png");
    black_zu = IMG_Load("black_zu.png");
    Select = IMG_Load("chessselect.png");

    red_win = IMG_Load("red_win.png");
    black_win = IMG_Load("black_win.png");
    red_choose = IMG_Load("red_choose.png");
    black_choose = IMG_Load("black_choose.png");
    whose_turn = IMG_Load("whose_turn.png");

    offset_finish.x = 130;
    offset_finish.y = 200;

    offset_red_turn.x = 320;
    offset_red_turn.y = 350;

    offset_black_turn.x = 300;
    offset_black_turn.y = 320;

    offset_turn.x = 260;
    offset_turn.y = 230;
}

void PLAY()
{
    printf("You are in the Play UI!\n");
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, PlayBackGroundTexture, NULL, NULL);
    SDL_RenderPresent(Renderer);
}

void QUIT()
{
    SDL_FreeSurface(MainBackGroundSurface);
    SDL_FreeSurface(PlayBackGroundSurface);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(red_shuai);
    SDL_FreeSurface(red_shi);
    SDL_FreeSurface(red_xiang);
    SDL_FreeSurface(red_ma);
    SDL_FreeSurface(red_che);
    SDL_FreeSurface(red_pao);
    SDL_FreeSurface(red_bing);
    SDL_FreeSurface(black_jiang);
    SDL_FreeSurface(black_shi);
    SDL_FreeSurface(black_xiang);
    SDL_FreeSurface(black_ma);
    SDL_FreeSurface(black_che);
    SDL_FreeSurface(black_pao);
    SDL_FreeSurface(black_zu);
    SDL_FreeSurface(Select);
    SDL_FreeSurface(red_win);
    SDL_FreeSurface(black_win);
    SDL_FreeSurface(red_choose);
    SDL_FreeSurface(black_choose);

    SDL_DestroyTexture(MainBackGroundTexture);
    SDL_DestroyTexture(PlayBackGroundTexture);

    TTF_CloseFont(Font);

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

int SDL_main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    Window = SDL_CreateWindow("PROJECT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    screen = SDL_GetWindowSurface(Window);
    LOAD();

    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, MainBackGroundTexture, NULL, &MainBackGroundRect);
    SDL_RenderPresent(Renderer);
    // 用数组表示棋盘，用数字代替棋子
    int board[10][9] = {{-5, -4, -3, -2, -1, -2, -3, -4, -5},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, -6, 0, 0, 0, 0, 0, -6, 0},
                        {-7, 0, -7, 0, -7, 0, -7, 0, -7},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {7, 0, 7, 0, 7, 0, 7, 0, 7},
                        {0, 6, 0, 0, 0, 0, 0, 6, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {5, 4, 3, 2, 1, 2, 3, 4, 5}};

    // 定义布尔变量判断游戏进程
    bool begin = false;
    bool red_turn = true;
    int win = 0; // 0则比赛继续，1则红方胜利，-1则黑方胜利

    while (SDL_WaitEvent(&MainEvent))
    {
        SDL_RenderPresent(Renderer);
        switch (MainEvent.type)
        {
        case SDL_QUIT:
            QUIT();
            break;
        case SDL_KEYDOWN:
            switch (MainEvent.key.keysym.sym)
            {
            case SDLK_RETURN:
                PLAY();
                break;
            case SDLK_ESCAPE:
                QUIT();
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (MainEvent.button.x > 295 && MainEvent.button.x < 502 && MainEvent.button.y > 118 && MainEvent.button.y < 251)
            {
                PLAY();
                begin = true;
            }

            printf("(%d,%d)\n", MainEvent.button.x, MainEvent.button.y);
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        default:
            break;
        }

        if (begin == true)
            break;
    }

    int select_hang = 0;   // 光标在哪行
    int select_lie = 0;    // 光标在哪列
    int arrive_hang = 0;   // 棋子目标在哪行
    int arrive_lie = 0;    // 棋子目标在哪列
    bool IsChoose = false; // 判断是否选择棋子
    while (SDL_WaitEvent(&MainEvent))
    {
        // if (MainEvent.type == SDL_MOUSEBUTTONDOWN)
        // printf("(%d,%d)\n", MainEvent.button.x, MainEvent.button.y);

        // SDL_RenderClear(Renderer);
        // SDL_RenderCopy(Renderer, PlayBackGroundTexture, NULL, NULL);
        // SDL_RenderPresent(Renderer);
        SDL_BlitSurface(PlayBackGroundSurface, NULL, screen, NULL);
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                offset_chess.x = 56 + 78 * j;
                offset_chess.y = 20 + 77 * i;

                if (board[i][j] != 0)
                {
                    switch (board[i][j])
                    {
                    // 摆放红子
                    case 1:
                        SDL_BlitSurface(red_shuai, NULL, screen, &offset_chess);
                        break;
                    case 2:
                        SDL_BlitSurface(red_shi, NULL, screen, &offset_chess);
                        break;
                    case 3:
                        SDL_BlitSurface(red_xiang, NULL, screen, &offset_chess);
                        break;
                    case 4:
                        SDL_BlitSurface(red_ma, NULL, screen, &offset_chess);
                        break;
                    case 5:
                        SDL_BlitSurface(red_che, NULL, screen, &offset_chess);
                        break;
                    case 6:
                        SDL_BlitSurface(red_pao, NULL, screen, &offset_chess);
                        break;
                    case 7:
                        SDL_BlitSurface(red_bing, NULL, screen, &offset_chess);
                        break;
                    // 摆放小黑子（真ikun）
                    case -1:
                        SDL_BlitSurface(black_jiang, NULL, screen, &offset_chess);
                        break;
                    case -2:
                        SDL_BlitSurface(black_shi, NULL, screen, &offset_chess);
                        break;
                    case -3:
                        SDL_BlitSurface(black_xiang, NULL, screen, &offset_chess);
                        break;
                    case -4:
                        SDL_BlitSurface(black_ma, NULL, screen, &offset_chess);
                        break;
                    case -5:
                        SDL_BlitSurface(black_che, NULL, screen, &offset_chess);
                        break;
                    case -6:
                        SDL_BlitSurface(black_pao, NULL, screen, &offset_chess);
                        break;
                    case -7:
                        SDL_BlitSurface(black_zu, NULL, screen, &offset_chess);
                        break;
                    }
                }
            }
        }
        // SDL_UpdateWindowSurface(Window);

        // 判断胜负
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == 1)
                    win++;
                else if (board[i][j] == -1)
                    win--;
            }
        }

        if (win == 1)
        {
            SDL_BlitSurface(red_win, NULL, screen, &offset_finish);
            SDL_UpdateWindowSurface(Window);
            for (;;)
            {
                while (SDL_PollEvent(&MainEvent))
                {
                    if (MainEvent.type == SDL_QUIT)
                    {
                        QUIT();
                        return 0;
                    }
                }
            }
        }
        else if (win == -1)
        {
            SDL_BlitSurface(black_win, NULL, screen, &offset_finish);
            SDL_UpdateWindowSurface(Window);
            for (;;)
            {
                while (SDL_PollEvent(&MainEvent))
                {
                    if (MainEvent.type == SDL_QUIT)
                    {
                        QUIT();
                        return 0;
                    }
                }
            }
        }
        SDL_BlitSurface(whose_turn, NULL, screen, &offset_turn);

        // 本回合归属的提示信息
        if (red_turn == true)
        {
            SDL_BlitSurface(red_choose, NULL, screen, &offset_red_turn);
        }
        else
        {
            SDL_BlitSurface(black_choose, NULL, screen, &offset_black_turn);
        }
        SDL_UpdateWindowSurface(Window);

        switch (MainEvent.type)
        {
        case SDL_QUIT:
            QUIT();
            break;
        case SDL_KEYDOWN:
        {
            switch (MainEvent.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                QUIT();
                break;
            default:
                break;
            }
        }
        }

        // 选择棋子
        bool ESC_for = false;

        if (MainEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            if (IsChoose == false) // 还没选择
            {
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 9; j++)
                    {
                        offset_choose.x = 56 + 78 * j;
                        offset_choose.y = 20 + 77 * i;
                        if (MainEvent.button.x > 56 + 78 * j && MainEvent.button.x < 131 + 78 * j && MainEvent.button.y > 20 + 77 * i && MainEvent.button.y < 92 + 77 * i)
                        {
                            if (board[i][j] != 0)
                            {
                                if (red_turn == true && board[i][j] > 0)
                                {
                                    select_hang = i;
                                    select_lie = j;
                                    IsChoose = true;
                                    ESC_for = true;

                                    SDL_BlitSurface(Select, NULL, screen, &offset_choose);
                                    SDL_UpdateWindowSurface(Window);

                                    break;
                                }
                                else if (red_turn == false && board[i][j] < 0)
                                {
                                    select_hang = i;
                                    select_lie = j;
                                    IsChoose = true;
                                    ESC_for = true;

                                    SDL_BlitSurface(Select, NULL, screen, &offset_choose);
                                    SDL_UpdateWindowSurface(Window);

                                    break;
                                }
                            }
                        }
                    }

                    if (ESC_for == true)
                        break;
                }
            }

            else if (IsChoose == true) // 已经选择了一个合法的棋子
            {
                // 开始考虑棋子走法
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 9; j++)
                    {
                        offset_arrive.x = 56 + 78 * j;
                        offset_arrive.y = 20 + 77 * i;
                        if (MainEvent.button.x > 56 + 78 * j && MainEvent.button.x < 131 + 78 * j && MainEvent.button.y > 20 + 77 * i && MainEvent.button.y < 92 + 77 * i)
                        {
                            arrive_hang = i;
                            arrive_lie = j;
                            if (select_hang == arrive_hang && select_lie == arrive_lie) // 选择自身==取消选择
                            {
                                IsChoose = false;
                                ESC_for = true;
                                break;
                            }
                            if (board[arrive_hang][arrive_lie] * board[select_hang][select_lie] > 0)
                            {
                                IsChoose = false;
                                ESC_for = true;
                                break;
                            }
                            // 棋子的走法
                            bool ESC_for_inner = false;
                            switch (abs(board[select_hang][select_lie]))
                            {
                            case 1: // 帅和将的走法
                                if (board[select_hang][select_lie] * board[arrive_hang][arrive_lie] == -1 && select_lie == arrive_lie)
                                {
                                    if (board[select_hang][select_lie] == 1)
                                    {
                                        for (int k = select_hang - 1; k > arrive_hang; k--) // 面帅先判定
                                        {
                                            if (board[k][select_lie] != 0)
                                            {
                                                ESC_for = true;
                                                ESC_for_inner = true;
                                                break;
                                            }
                                        }
                                        board[i][j] = board[select_hang][select_lie];
                                        board[select_hang][select_lie] = 0;
                                        red_turn = !red_turn;
                                        break;
                                    }
                                    else if (board[select_hang][select_lie] == -1)
                                    {
                                        for (int k = select_hang + 1; k < arrive_hang; k++)
                                        {
                                            if (board[k][select_lie] != 0)
                                            {
                                                ESC_for = true;
                                                ESC_for_inner = true;
                                                break;
                                            }
                                        }
                                        board[i][j] = board[select_hang][select_lie];
                                        board[select_hang][select_lie] = 0;
                                        red_turn = !red_turn;
                                        break;
                                    }
                                }

                                if (arrive_hang > 2 && arrive_lie < 3 && arrive_lie > 5) // 超出帅的范围
                                {
                                    ESC_for = true;
                                    ESC_for_inner = true;
                                    break;
                                }

                                if (!((abs(arrive_hang - select_hang) == 0 && abs(arrive_lie - select_lie) == 1) || (abs(arrive_lie - select_lie) == 0 && abs(arrive_hang - select_hang) == 1))) // 只能走一格
                                {
                                    ESC_for = true;
                                    ESC_for_inner = true;
                                    break;
                                }

                                board[i][j] = board[select_hang][select_lie];
                                board[select_hang][select_lie] = 0;
                                red_turn = !red_turn;
                                break;
                            case 2:                                                      // 士的走法
                                if (arrive_hang > 2 && arrive_lie < 3 && arrive_lie > 5) // 超出士的范围
                                {
                                    ESC_for = true;
                                    ESC_for_inner = true;
                                    break;
                                }
                                // 走斜线
                                if (abs(arrive_hang - select_hang) != 1 || abs(arrive_lie - select_lie) != 1)
                                {
                                    ESC_for = true;
                                    ESC_for_inner = true;
                                    break;
                                }

                                board[i][j] = board[select_hang][select_lie];
                                board[select_hang][select_lie] = 0;
                                red_turn = !red_turn;
                                break;
                            case 3:                                                                                 // 象的走法
                                if ((select_hang <= 4 && arrive_hang > 4) || (select_hang >= 5 && arrive_hang < 5)) // 不能过河
                                {
                                    ESC_for = true;
                                    ESC_for_inner = true;
                                    break;
                                }
                                // 走田字
                                if (abs(arrive_hang - select_hang) != 2 || abs(arrive_lie - select_lie) != 2)
                                {
                                    ESC_for_inner = true;
                                    ESC_for = true;
                                    break;
                                }
                                // 卡象脚
                                if (board[(arrive_hang + select_lie) / 2][(arrive_lie + select_lie) / 2] != 0) // 卡象脚
                                {
                                    ESC_for_inner = true;
                                    ESC_for = true;
                                    break;
                                }

                                board[i][j] = board[select_hang][select_lie];
                                board[select_hang][select_lie] = 0;
                                red_turn = !red_turn;
                                break;
                            case 4: // 马的走法
                                if (!((abs(arrive_hang - select_hang) == 2 && abs(arrive_lie - select_lie) == 1) || (abs(arrive_hang - select_hang) == 1 && abs(arrive_lie - select_lie) == 2)))
                                {
                                    ESC_for_inner = true; // 走日字
                                    ESC_for = true;
                                    break;
                                }
                                // 卡马脚
                                if (((arrive_lie < select_lie) && board[select_hang][select_lie - 1] != 0 && abs(arrive_hang - select_hang) == 1) || ((arrive_lie > select_lie) && board[select_hang][select_lie + 1] != 0 && abs(arrive_hang - select_hang) == 1) || ((arrive_hang < select_hang) && board[select_hang - 1][select_lie] != 0 && abs(arrive_hang - select_hang) == 2) || ((arrive_hang > select_hang) && board[select_hang + 1][select_lie] != 0 && abs(arrive_hang - select_hang) == 2))
                                {
                                    ESC_for_inner = true;
                                    ESC_for = true;
                                    break;
                                }

                                board[i][j] = board[select_hang][select_lie];
                                board[select_hang][select_lie] = 0;
                                red_turn = !red_turn;
                                break;
                            case 5:                                                         // 车的走法
                                if (select_hang != arrive_hang && select_lie != arrive_lie) // 走直线
                                {
                                    ESC_for_inner = true;
                                    ESC_for = true;
                                    break;
                                }

                                bool ESC_FOR_5 = false;
                                if (select_hang == arrive_hang)
                                {
                                    if (abs(arrive_lie - select_lie) == 1) // 相差一格直接走
                                    {
                                        board[i][j] = board[select_hang][select_lie];
                                        board[select_hang][select_lie] = 0;
                                        red_turn = !red_turn;
                                        break;
                                    }

                                    if (select_lie > arrive_lie)
                                    {
                                        for (int i = select_lie - 1; i > arrive_lie; i--)
                                        {
                                            if (board[select_hang][i] != 0)
                                            {
                                                ESC_for_inner = true;
                                                ESC_for = true;
                                                ESC_FOR_5 = true;
                                                break;
                                            }
                                        }
                                        if (ESC_FOR_5 == true)
                                            break;
                                    }
                                    else if (select_lie < arrive_lie)
                                    {
                                        for (int i = select_lie + 1; i < arrive_lie; i++)
                                        {
                                            if (board[select_hang][i] != 0)
                                            {
                                                ESC_for_inner = true;
                                                ESC_for = true;
                                                ESC_FOR_5 = true;
                                                break;
                                            }
                                        }
                                        if (ESC_FOR_5 == true)
                                            break;
                                    }
                                }
                                else if (select_lie == arrive_lie)
                                {
                                    if (abs(select_hang - arrive_hang) == 1)
                                    {
                                        board[i][j] = board[select_hang][select_lie];
                                        board[select_hang][select_lie] = 0;
                                        red_turn = !red_turn;
                                        break;
                                    }

                                    if (select_hang > arrive_hang)
                                    {
                                        for (int i = select_hang - 1; i > arrive_hang; i--)
                                        {
                                            if (board[i][select_lie] != 0)
                                            {
                                                ESC_for_inner = true;
                                                ESC_for = true;
                                                ESC_FOR_5 = true;
                                                break;
                                            }
                                        }
                                        if (ESC_FOR_5 == true)
                                            break;
                                    }
                                    else if (select_hang < arrive_hang)
                                    {
                                        for (int i = select_hang + 1; i < arrive_hang; i++)
                                        {
                                            if (board[i][select_lie] != 0)
                                            {
                                                ESC_for_inner = true;
                                                ESC_for = true;
                                                ESC_FOR_5 = true;
                                                break;
                                            }
                                        }
                                        if (ESC_FOR_5 == true)
                                            break;
                                    }
                                }
                                board[i][j] = board[select_hang][select_lie];
                                board[select_hang][select_lie] = 0;
                                red_turn = !red_turn;
                                break;
                            case 6:                                                         // 炮的走法
                                if (select_hang != arrive_hang && select_lie != arrive_lie) // 走直线
                                {
                                    ESC_for_inner = true;
                                    ESC_for = true;
                                    break;
                                }

                                int chess_number = 0;
                                bool ESC_for_6 = false;
                                if (arrive_hang == select_hang)
                                {
                                    if (board[arrive_hang][arrive_lie] == 0)
                                    {
                                        if (select_lie > arrive_lie)
                                        {
                                            for (int i = select_lie - 1; i >= arrive_lie; i--)
                                            {
                                                if (board[select_hang][i] != 0)
                                                {
                                                    ESC_for_inner = true;
                                                    ESC_for = true;
                                                    ESC_for_6 = true;
                                                    break;
                                                }
                                            }
                                            if (ESC_for_6 == true)
                                                break;
                                        }
                                        else if (select_lie < arrive_lie)
                                        {
                                            for (int i = select_lie + 1; i <= arrive_lie; i++)
                                            {
                                                if (board[select_hang][i] != 0)
                                                {
                                                    ESC_for_inner = true;
                                                    ESC_for = true;
                                                    ESC_for_6 = true;
                                                    break;
                                                }
                                            }
                                            if (ESC_for_6 == true)
                                                break;
                                        }
                                    }
                                    // 架炮
                                    else if (board[arrive_hang][arrive_lie] != 0)
                                    {
                                        if (select_lie > arrive_lie)
                                        {
                                            for (int i = select_lie - 1; i >= arrive_lie; i--)
                                            {
                                                if (board[select_hang][i] != 0)
                                                    chess_number++;
                                            }
                                            if (chess_number != 2)
                                            {
                                                ESC_for_inner = true;
                                                ESC_for = true;
                                                break;
                                            }
                                        }
                                        else if (select_lie < arrive_lie)
                                        {
                                            for (int i = select_lie + 1; i <= arrive_lie; i++)
                                            {
                                                if (board[select_hang][i] != 0)
                                                    chess_number++;
                                            }
                                            if (chess_number != 2)
                                            {
                                                ESC_for_inner = true;
                                                ESC_for = true;
                                                break;
                                            }
                                        }
                                    }
                                }

                                if (arrive_lie == select_lie)
                                {
                                    if (board[arrive_hang][arrive_lie] == 0)
                                    {
                                        if (select_hang > arrive_hang)
                                        {
                                            for (int i = select_hang - 1; i >= arrive_hang; i--)
                                            {
                                                if (board[i][select_lie] != 0)
                                                {
                                                    ESC_for_inner = true;
                                                    ESC_for = true;
                                                    ESC_for_6 = true;
                                                    break;
                                                }
                                            }
                                            if (ESC_for_6 == true)
                                                break;
                                        }
                                        else if (select_hang < arrive_hang)
                                        {
                                            for (int i = select_hang + 1; i <= arrive_hang; i++)
                                            {
                                                if (board[i][select_lie] != 0)
                                                {
                                                    ESC_for_inner = true;
                                                    ESC_for = true;
                                                    ESC_for_6 = true;
                                                    break;
                                                }
                                            }
                                            if (ESC_for_6 == true)
                                                break;
                                        }
                                    }
                                    else if (board[arrive_hang][arrive_lie] != 0)
                                    {
                                        if (select_hang > arrive_hang)
                                        {
                                            for (int i = select_hang - 1; i >= arrive_hang; i--)
                                            {
                                                if (board[i][select_lie] != 0)
                                                    chess_number++;
                                            }
                                            if (chess_number != 2)
                                            {
                                                ESC_for_inner = true;
                                                ESC_for = true;
                                                break;
                                            }
                                        }
                                        else if (select_hang < arrive_hang)
                                        {
                                            for (int i = select_hang + 1; i <= arrive_hang; i++)
                                            {
                                                if (board[i][select_lie] != 0)
                                                    chess_number++;
                                            }
                                            if (chess_number != 2)
                                            {
                                                ESC_for_inner = true;
                                                ESC_for = true;
                                                break;
                                            }
                                        }
                                    }
                                }
                                board[i][j] = board[select_hang][select_lie];
                                board[select_hang][select_lie] = 0;
                                red_turn = !red_turn;
                                break;

                            case 7:                                      // 兵的走法
                                if (board[select_hang][select_lie] == 7) // 红方
                                {
                                    if (select_hang >= 5)
                                    {
                                        if (select_hang - arrive_hang != 1)
                                        {
                                            ESC_for_inner = true;
                                            ESC_for = true;
                                            break;
                                        }
                                        board[i][j] = board[select_hang][select_lie];
                                        board[select_hang][select_lie] = 0;
                                        red_turn = !red_turn;
                                        break;
                                    }
                                    else if (select_hang < 5) // 过河
                                    {
                                        if (!(((abs(select_lie - arrive_lie) == 1) && (arrive_hang == select_hang)) || ((select_lie == arrive_lie) && (select_hang - arrive_hang == 1))))
                                        {
                                            ESC_for_inner = true;
                                            ESC_for = true;
                                            break;
                                        }
                                        board[i][j] = board[select_hang][select_lie];
                                        board[select_hang][select_lie] = 0;
                                        red_turn = !red_turn;
                                        break;
                                    }
                                }

                                else if (board[select_hang][select_lie] == -7) // 黑方
                                {
                                    if (select_hang <= 4)
                                    {
                                        if (select_hang - arrive_hang != -1)
                                        {
                                            ESC_for_inner = true;
                                            ESC_for = true;
                                            break;
                                        }
                                        board[i][j] = board[select_hang][select_lie];
                                        board[select_hang][select_lie] = 0;
                                        red_turn = !red_turn;
                                        break;
                                    }
                                    else if (select_hang > 4)
                                    {
                                        if (!(((abs(select_lie - arrive_lie) == 1) && (arrive_hang == select_hang)) || ((select_lie == arrive_lie) && (select_hang - arrive_hang == -1))))
                                        {
                                            ESC_for_inner = true;
                                            ESC_for = true;
                                            break;
                                        }
                                        board[i][j] = board[select_hang][select_lie];
                                        board[select_hang][select_lie] = 0;
                                        red_turn = !red_turn;
                                        break;
                                    }
                                }
                            }

                            IsChoose = false;
                            if (ESC_for_inner == true)
                                break;

                            ESC_for = true;
                        }
                    }
                    if (ESC_for == true)
                        break;
                }
            }
        }
    }

    QUIT();
}