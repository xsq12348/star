注意！！该拓展包已弃用,现在有更加成熟的方案！
#pragma once
#include"star.h" 

//这是star的拓展包“时代”
//用于兵棋游戏的快速创建
// 版本 1.1

double DegRad(int deg)
{
    double a = deg * Pi * 1.0 / 180;
    return a;
}

//六角格
void MassifSix(HWND hwnd, int x, int y, COLORREF color)
{
    WinLine(hwnd, x - 10, y - 17, x + 10, y - 17, color);
    WinLine(hwnd, x - 10, y + 17, x + 10, y + 17, color);
    WinLine(hwnd, x - 17, y, x - 10, y - 17, color);
    WinLine(hwnd, x + 10, y - 17, x + 17, y, color);
    WinLine(hwnd, x - 17, y, x - 10, y + 17, color);
    WinLine(hwnd, x + 17, y, x + 10, y + 17, color);
}

void MassifSixB(HWND hwnd, int x, int y, COLORREF color)
{
    WinLine(hwnd, x - 8, y - 15, x + 8, y - 15, color);
    WinLine(hwnd, x - 8, y + 15, x + 8, y + 15, color);
    WinLine(hwnd, x - 15, y, x - 8, y - 15, color);
    WinLine(hwnd, x + 8, y - 15, x + 15, y, color);
    WinLine(hwnd, x - 15, y, x - 8, y + 15, color);
    WinLine(hwnd, x + 15, y, x + 8, y + 15, color);
}


//六角格地图
void MassifSixMap(HWND hwnd, int MX, int MY, int Width, int Height, COLORREF color)
{
    int Y1 = MY;
    int Y2 = MY - 17;
    int x, y;
    for (int i = 0; i < Width; i++)
    {
        for (int o = 0; o < Height; o++)
        {
            x = MX + i * 27;
            y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
            MassifSix(hwnd, x, y, color);
        }
    }
}

//图标树
void Wood(HWND hwnd, int MX, int MY, int X, int Y)
{
    int Y1 = MY;
    int Y2 = MY - 17;
    int x, y;
    for (int i = 0; i < X; i++)
    {
        for (int o = 0; o < Y; o++)
        {
            x = MX + i * 27;
            y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
        }
    }
    WinLine(hwnd, x - 5, y, x + 5, y, RGB(0, 255, 0));
    WinLine(hwnd, x, y, x, y + 5, RGB(0, 255, 0));
    WinLine(hwnd, x + 5, y, x, y - 5, RGB(0, 255, 0));
    WinLine(hwnd, x - 5, y, x, y - 5, RGB(0, 255, 0));
}

//状态框A
void PointWireframeA(HWND hwnd, int x, int y, COLORREF color)
{
    WinLine(hwnd, x, y, x + 30, y, color);
    WinLine(hwnd, x, y, x, y + 20, color);
    WinLine(hwnd, x, y + 20, x + 30, y + 20, color);
    WinLine(hwnd, x + 30, y, x + 30, y + 20, color);
}

//状态框B
void PointWireframeB(HWND hwnd, int x, int y, COLORREF color)
{
    WinLine(hwnd, x, y, x + 60, y, color);
    WinLine(hwnd, x, y, x, y + 40, color);
    WinLine(hwnd, x, y + 40, x + 60, y + 40, color);
    WinLine(hwnd, x + 60, y, x + 60, y + 40, color);
}

//步兵图标
void Infantry(HWND hwnd, int MX, int MY, int X, int Y, COLORREF color)
{

    int Y1 = MY;
    int Y2 = MY - 17;
    int x, y;
    for (int i = 0; i < X; i++)
    {
        for (int o = 0; o < Y; o++)
        {
            x = MX + i * 27;
            y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
        }
    }
    x -= 7;
    y -= 5;
    WinLine(hwnd, x, y, x + 15, y, color);
    WinLine(hwnd, x, y, x, y + 10, color);
    WinLine(hwnd, x, y + 10, x + 15, y + 10, color);
    WinLine(hwnd, x + 15, y, x + 15, y + 10, color);
    WinLine(hwnd, x, y, x + 15, y + 10, color);
    WinLine(hwnd, x, y + 10, x + 15, y, color);
}
    
//机械化图标
void MechanizedTroops(HWND hwnd, int MX, int MY, int X, int Y, COLORREF color)
{

    int Y1 = MY;
    int Y2 = MY - 17;
    int x, y;
    for (int i = 0; i < X; i++)
    {
        for (int o = 0; o < Y; o++)
        {
            x = MX + i * 27;
            y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
        }
    }
    x -= 7;
    y -= 5;

    WinLine(hwnd, x, y, x + 15, y, color);
    WinLine(hwnd, x, y, x, y + 10, color);
    WinLine(hwnd, x, y + 10, x + 15, y + 10, color);
    WinLine(hwnd, x + 15, y, x + 15, y + 10, color);

    WinLine(hwnd, x + 4, y + 3, x + 4, y + 6, color);
    WinLine(hwnd, x + 11, y + 3, x + 11, y + 6, color);
    WinLine(hwnd, x + 4, y + 3, x + 10, y + 3, color);
    WinLine(hwnd, x + 4, y + 7, x + 10, y + 7, color);
}

//机械化步兵图标
void MechanizedInfantry(HWND hwnd, int MX, int MY, int X, int Y, COLORREF color)
{

    int Y1 = MY;
    int Y2 = MY - 17;
    int x, y;
    for (int i = 0; i < X; i++)
    {
        for (int o = 0; o < Y; o++)
        {
            x = MX + i * 27;
            y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
        }
    }
    x -= 7;
    y -= 5;

    WinLine(hwnd, x, y, x + 15, y, color);
    WinLine(hwnd, x, y, x, y + 10, color);
    WinLine(hwnd, x, y + 10, x + 15, y + 10, color);
    WinLine(hwnd, x + 15, y, x + 15, y + 10, color);

    WinLine(hwnd, x + 4, y + 3, x + 4, y + 6, color);
    WinLine(hwnd, x + 11, y + 3, x + 11, y + 6, color);
    WinLine(hwnd, x + 4, y + 3, x + 10, y + 3, color);
    WinLine(hwnd, x + 4, y + 7, x + 10, y + 7, color);

    WinLine(hwnd, x, y, x + 15, y + 10, color);
    WinLine(hwnd, x, y + 10, x + 15, y, color);
}

//骑兵
void Cavalry(HWND hwnd, int MX, int MY, int X, int Y, COLORREF color)
{
    int Y1 = MY;
    int Y2 = MY - 17;
    int x, y;
    for (int i = 0; i < X; i++)
    {
        for (int o = 0; o < Y; o++)
        {
            x = MX + i * 27;
            y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
        }
    }
    x -= 7;
    y -= 5;

    WinLine(hwnd, x, y, x + 15, y, color);
    WinLine(hwnd, x, y, x, y + 10, color);
    WinLine(hwnd, x, y + 10, x + 15, y + 10, color);
    WinLine(hwnd, x + 15, y, x + 15, y + 10, color);

    WinLine(hwnd, x, y, x + 15, y + 10, color);
}






//城市图标
void City(HWND hwnd, int MX, int MY, int X, int Y, COLORREF color)
{
    int Y1 = MY;
    int Y2 = MY - 17;
    int x, y;
    for (int i = 0; i < X; i++)
    {
        for (int o = 0; o < Y; o++)
        {
            x = MX + i * 27;
            y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
        }
    }
    x -= 7;
    y -= 5;
    WinText(hwnd, x-3, y-3, TEXT("city"), color);
}

void Corsur(HWND hwnd, int MX, int MY, int X, int Y, COLORREF color)
{
    int Y1 = MY;
    int Y2 = MY - 17;
    int x = 0, y = 0;
    for (int i = 0; i < X; i++)
    {
        for (int o = 0; o < Y; o++)
        {
            x = MX + i * 27;
            y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
        }
    }
    WinLine(hwnd, x - 8, y - 15, x + 8, y - 15, color);
    WinLine(hwnd, x - 8, y + 15, x + 8, y + 15, color);
    WinLine(hwnd, x - 15, y, x - 8, y - 15, color);
    WinLine(hwnd, x + 8, y - 15, x + 15, y, color);
    WinLine(hwnd, x - 15, y, x - 8, y + 15, color);
    WinLine(hwnd, x + 15, y, x + 8, y + 15, color);
}
