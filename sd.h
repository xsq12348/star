#pragma once
#include"star.h" 

//这是star的拓展包“时代”
//用于兵棋游戏的快速创建
// 版本 0.1

void MassifSix(HWND hwnd, int x, int y, COLORREF color)
{
	WinLine(hwnd, x - 10, y - 17, x + 10, y - 17, color);
	WinLine(hwnd, x - 10, y + 17, x + 10, y + 17, color);
	WinLine(hwnd, x - 17, y, x - 10, y - 17, color);
	WinLine(hwnd, x + 10, y - 17, x + 17, y, color);
	WinLine(hwnd, x - 17, y, x - 10, y + 17, color);
	WinLine(hwnd, x + 17, y, x + 10, y + 17, color);
}


void MassifSixMap(HWND hwnd, int X, int Y, int Width, int Height, COLORREF color)
{
    int Y1 = Y;
    int Y2 = Y - 17; // 上方六边形的Y坐标

    for (int i = 0; i < Width; i++)
    {
        for (int o = 0; o < Height; o++)
        {
            int x = X + i * 27;
            int y = (i % 2 == 0) ? Y1 + o * 35 : Y2 + o * 35;
            MassifSix(hwnd, x, y, color);
        }
    }
}









