#pragma once
#include <stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<math.h>



void CMDwindow(LPCSTR name, unsigned int width, unsigned int height, int Character_width, int Character_height)
{
    //获取当前控制台的句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    //得知显示器像素数,以后维护时可能有用
    int nScreenWidth, nScreenHeight;
    nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    nScreenHeight = GetSystemMetrics(SM_CYSCREEN);


    //字符大小
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = Character_width;
    cfi.dwFontSize.Y = Character_height;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


    //设置窗口大小
    char command[256];
    snprintf(command, sizeof(command), "mode con: cols=%d lines=%d", width, height);
    int result = system(command);





    /*
    以后维护时可能有用
    //屏幕缓冲区
    COORD Size;
    Size.X = 1;
    Size.Y = 1;
    SetConsoleScreenBufferSize(hConsole, Size);

    //设置控制台窗口的大小
    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = width - 1;  // 窗口的右边界
    windowSize.Bottom = height - 1; // 窗口的下边界
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    */



    //更改窗口标题
    SetConsoleTitle(name);

    // 禁止改变窗口大小
    LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);

    // 移除可调整大小的样式
    style &= ~WS_SIZEBOX;
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, style);

    //隐藏滚动条
    ShowScrollBar(GetConsoleWindow(), SB_VERT, FALSE);
    ShowScrollBar(GetConsoleWindow(), SB_HORZ, FALSE);



}


//设置文字出现的坐标
void Text(LPCSTR text, int x, int y, int color)
{
    /*
    颜色属性由两个十六进制数字指定, 第一个为背景色, 第二个为前景色。
    每个数字可以为下列值之一：
    黑色 = 0 蓝色 = 1 绿色 = 2 湖蓝色 = 3
    红色 = 4 紫色 = 5 黄色 = 6 白色 = 7
    灰色 = 8 淡蓝色=9 淡绿色=A 白色=C
    淡紫色=D 淡黄色=E 亮白色=F
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    COORD lightb;
    lightb.X = x;
    lightb.Y = y;
    HANDLE CMD = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(CMD, lightb);
    printf(text);
    SetConsoleTextAttribute(hConsole, 0x07);
}


//画一条从linexa，lineya到linexb，lineyb的直线,字符为p
void Linea(LPCSTR p, int x0, int y0, int x1, int y1, int color)
{
    double k = (y1 - y0) * 1.0 / (x1 - x0);
    double y = y0;
    auto x = x0;
    while (x <= x1)
    {
        Text(p, x, y, color);
        y += k;
        x++;
    }
}



//画一条从linexa，lineya到linexb，lineyb的直线,字符为p
void Line(LPCSTR p, double x0, double y0, double x1, double y1, int color)
{
    //获取当前控制台的句柄
    HWND hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    double a = x1 - x0;
    double b = y1 - y0;
    double c = sqrt(pow(a, 2) + pow(b, 2));
    double x = (a * 1.0) / c;
    double y = (b * 1.0) / c;
    RECT rect;
    do
    {
        GetWindowRect(hconsole, &rect);
        Text(p, x0, y0, color);
        x0 = x0 + x;
        y0 = y0 + y;

    } while (x0 <= x1 && y0 <= y1 || y0 <= y1 && x0 <= x1);

}



void Clear()
{
    system("cls");
}


typedef struct
{
    // 获取窗口的宽度和高度
    int x_;
    int y_;
    char m_buffe[];

}VIEP;

//移动光标
void Gotoxy(int x, int y)
{


    COORD lightb;
    lightb.X = x;
    lightb.Y = y;
    HANDLE CMD = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(CMD, lightb);
}

/*

}
*/

