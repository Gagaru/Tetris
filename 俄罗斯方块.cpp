#include<iostream>
#include <time.h>
#include <conio.h>
#include<windows.h>
using namespace std;
void color(const unsigned short COLorl);
void gotoXY(int goRow, int goCol);
void HideCursor(bool isVisible);


#define MAXROW 24//最大行
#define MAXCOL 16//最大列
#define EMPTY 0//空
#define BLOCK 1//块
#define WALL 2//墙
#define FALLBLOCH 3//下落的块

string wall = "🧱";//墙艢
string box = "⬜";//块口旝擓
string eempty = "  ";//空
int thfig[4][4] = {};//这个图q
int x, y;
int gameMap[MAXROW][MAXCOL] = {};

int fig[][4][4] = {
    //l型
    {0,1,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,0,0},
    //反l型
    {0,0,0,0,
    0,1,1,0,
    0,1,0,0,
    0,1,0,0},
    //s型
    {0,1,0,0,
    0,1,1,0,
    0,0,1,0,
    0,0,0,0},
    //反s型
    {0,0,1,0,
    0,1,1,0,
    0,1,0,0,
    0,0,0,0},
    //t型
    {0,1,0,0,
    0,1,1,0,
    0,1,0,0,
    0,0,0,0},
    //i型
    {0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0},
    //方型
    {0,0,0,0,
    0,1,1,0,
    0,1,1,0,
    0,0,0,0}
};

//初始化地图
void initMap()
{
    for (int i = 0; i < MAXROW; i++)
    {
        for (int j = 0; j < MAXCOL; j++)
        {
            if (i == 0 || j == 0 || i == MAXROW - 1 || j == MAXCOL - 1)
            {
                gameMap[i][j] = WALL;
            }
            else
            {
                gameMap[i][j] = EMPTY;
            }
        }
    }
}

//打印地图
void coutMap()
{
    for (int i = 0; i < MAXROW; i++)
    {
        for (int j = 0; j < MAXCOL; j++)
        {
            switch (gameMap[i][j])
            {
            case WALL:cout << wall; break;
            case EMPTY:cout << eempty; break;
            }
        }
        cout << endl;
    }
}

//打印
void couts(string e,int thfig[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (thfig[i][j] == BLOCK)
            {
                gotoXY(y + i, x + j);
                cout << e;
            }
        }
    }
}

//图旋转
void revfig()
{
    int tempArr[4][4] = {};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (thfig[i][j] == BLOCK)
            {
                tempArr[j][3 - i] = BLOCK;
            }
            else
            {
                tempArr[j][3 - i] = EMPTY;
            }
        }
    }
    couts(eempty, thfig);
    int r = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tempArr[i][j] == BLOCK && gameMap[y + i][x + j] != EMPTY)
            {
                r++;
                break;
            }
        }
    }
    if (r == 0)
    {
        memcpy(thfig, tempArr, sizeof tempArr);
    }
}

//打印随机图
void coutthfig()
{
    int a = rand() % (7);
    int b = rand() % (4);
    memcpy(thfig, fig[a], sizeof fig[a]);
    y = 1;
    x = MAXCOL / 2 - 2;
    for (int i = 0; i < b; i++)
    {
        revfig();
    }
    couts(box,thfig);
}

//图移动
int moveThfig(int movey,int movex)
{
    int r = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (thfig[i][j] == BLOCK && gameMap[y + i+movey][x + j+movex] != EMPTY)
            {
                r++;
                break;
            }
        }
    }
    if (r == 0)
    {
        couts(eempty, thfig);
        y += movey;
        x += movex;
        couts(box, thfig);
        return 0;
    }
    else
        return 1;
}

//判断消去
void eliminate()
{
    for (int i = 6; i < MAXROW-1; i++)
    {
        int x = 0;
        for (int j = 1; j < MAXCOL-1; j++)
        {
            if (gameMap[i][j] == FALLBLOCH)
                x++;
        }
        if (x == MAXCOL - 2)
        {
            for (int ii = i-1; ii > 6; ii--)
            {
                for (int jj = MAXCOL - 2; jj > 0; jj--)
                {
                    gotoXY(ii + 1, jj);
                    if (gameMap[ii][jj] == FALLBLOCH)
                    {
                        gameMap[ii + 1][jj] = FALLBLOCH;
                        cout << box;
                    }
                    else
                    {
                        gameMap[ii + 1][jj] = EMPTY;
                        cout << eempty;
                    }
                }
            }
        }
    }
}

//图下落
int figfall()
{
    if (moveThfig(1, 0) == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (thfig[i][j] == BLOCK)
                {
                    gameMap[y + i][x + j] = FALLBLOCH;

                }
            }
        }
        eliminate();
        return 1;
    }
}

int main()
{
    //cout << "欢迎光临🤡🤡🤡⬜🌳🌳🧱🌾◻️🚫❌○–§®℃"<<"\n";
    int times = 0;
    srand(time(0));
	initMap();
    coutMap(); 
    while (true)
    {
        coutthfig();
        while (true)
        {
            Sleep(3);
            times++;
            int s = 0;

            if (_kbhit())
            {
                int key = _getch();
                switch (key)
                {
                case 'W':
                case 'w': {revfig(); couts(box, thfig); }break;
                case 'A':
                case 'a':moveThfig(0, -1); break;
                case 'S':
                case 's':s=figfall(); break;
                case 'D':
                case 'd':moveThfig(0, 1); break;
                default:
                    break;
                }
            }
            if (times >= 30)
            {
                s=figfall();
                times = 0;
            }
            if (s == 1)
                break;
           
        }
        
    }

}