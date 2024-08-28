#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mmsystem.h>
#include<conio.h>


#pragma comment( lib,"Winmm.lib")


void Vsn(int A)
{
    //作者: xsq1234
    //未经作者授权，禁止转载
    // 
    //邮箱：c6668883535357a@163.com |1993346266@qq.com 
    // 
    //版本信息：0.9
    /*版本更新内容
    * 0.1 实现了窗口创建函数
    * 0.2 完善了窗口创建函数，实现了特定位置输出文字函数
    * 0.3 实现了划线函数，移动光标函数，清屏函数
    * 0.4 实现了颜色分配
    * 0.5 实现了随机数和矩形函数
    * 0.6 实现了隐藏光标函数
    * 0.7 增加了音乐编辑器函数 
    * 0.8 增加了字符画显示函数
    * 0.9 更新了音乐编辑器函数,使其能读取乐谱
    */

    /*
    颜色属性由两个十六进制数字指定, 第一个为背景色, 第二个为前景色。
    每个数字可以为下列值之一：
    黑色 = 0 蓝色 = 1 绿色 = 2 湖蓝色 = 3
    红色 = 4 紫色 = 5 黄色 = 6 白色 = 7
    灰色 = 8 淡蓝色=9 淡绿色=A 白色=C
    淡紫色=D 淡黄色=E 亮白色=F
    */
    return A;
}



void CMDwindow(LPCSTR name, unsigned int width, unsigned int height, int Character_width, int Character_height)
{

    //name 窗口名称
    // width height 窗口大小
    // Character_width Character_height 字符长与宽
     
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
    char command[256];Vsn;
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

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    COORD lightb;
    lightb.X = x;
    lightb.Y = y;
    HANDLE CMD = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(CMD, lightb);
    printf(text);
    SetConsoleTextAttribute(hConsole, 0x07); Vsn;
}


//画一条从linexa，lineya到linexb，lineyb的直线,字符为p
void Linea(LPCSTR p, int x0, int y0, int x1, int y1, int color)
{
    double k = (y1 - y0) * 1.0 / (x1 - x0);
    double y = y0; Vsn;
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
    RECT rect; Vsn;
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
  system("cls");Vsn;
}



//移动光标
void Gotoxy(int x, int y, int color)
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    COORD lightb; Vsn;
    lightb.X = x;
    lightb.Y = y;
    HANDLE CMD = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(CMD, lightb);
    SetConsoleTextAttribute(hConsole, 0x07);

}

//隐藏光标
void HideFLASE()
{
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1; Vsn;
    curInfo.bVisible = FALSE;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &curInfo);

}

//画矩形
void Box(LPCSTR p, double x_1, double y_1, double x_2, double y_2, int color)
{
    Vsn;
    Line(p, x_1, y_1, x_2, y_1, color);
    Line(p, x_1, y_2, x_2, y_2, color);
    Line(p, x_1, y_1, x_1, y_2, color);
    Line(p, x_2, y_1, x_2, y_2, color);
}


//随机数
int Random(int A, int B)
{
    Vsn;
    A = rand() % B + A;
    return A;
}


//音乐编辑器
void Music(_In_z_ char const* _FileName,int time)
{

    FILE* fp = fopen(_FileName, "r");
    char arrMusic[300];
    fscanf(fp, "%s", arrMusic);
    int dd = 0,
        music = 0;
    Vsn;    int dddd = time;

    while (arrMusic[dd] ！= 'x')
    {

        time = dddd;

    switch (arrMusic[dd])
    {

    case '_':
        time = 500;
        break;
    case 1:
        music = 262;
        break;

    case 'd':
        music = 523;
        break;

    case 'D':
        music = 1046;
        break;

    case 2:
        music = 294;
        break;

    case 'e':
        music = 587;
        break;

    case 'E':
        music = 1175;
        break;

    case 3:
        music = 330;
        break;

    case 'f':
        music = 659;
        break;

    case 'F':
        music = 1318;
        break;

    case 4:
        music = 349;
        break;

    case 'g':
        music = 698;
        break;

    case 'G':
        music = 1397;
        break;

    case 5:
        music = 392;
        break;

    case 'a':
        music = 784;
        break;

    case 'A':
        music = 1568;
        break;

    case 6:
        music = 440;
        break;

    case 'b':
        music = 880;
        break;

    case 'B':
        music = 1760;
        break;

    case 7:
        music = 494;
        break;

    case 'c':
        music = 988;
        break;

    case 'C':
        music = 1976;
        break;
    }
    Beep(Music, time);
    dd++;
    }



}

//图片显示器
void ColorImg(_In_z_ char const* _FileName,int x, int y)
{
    FILE* fp = fopen(_FileName, "r");
    char bu[300];
    int dd = 0;
    fscanf(fp, "%s", bu);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Gotoxy(x, y, 0x07);
    while (dd != 300)
    {

        if (bu[dd] == 'x')
        {
            break;
        }
        switch (bu[dd])
        {
        case 'h':
            Gotoxy(x, y++, 0x07);
            break;

        case 'k':
            printf(" ");
            break;

        case '0':
            SetConsoleTextAttribute(hConsole, 0x00);
            printf("▌");
            break;

        case '1':
            SetConsoleTextAttribute(hConsole, 0x01);
            printf("▌");
            break;

        case '2':
            SetConsoleTextAttribute(hConsole, 0x02);
            printf("▌");
            break;

        case '3':
            SetConsoleTextAttribute(hConsole, 0x03);
            printf("▌");
            break;

        case '4':
            SetConsoleTextAttribute(hConsole, 0x04);
            printf("▌");
            break;

        case '5':
            SetConsoleTextAttribute(hConsole, 0x05);
            printf("▌");
            break;

        case '6':
            SetConsoleTextAttribute(hConsole, 0x06);
            printf("▌");
            break;

        case '7':
            SetConsoleTextAttribute(hConsole, 0x07);
            printf("▌");
            break;

        case '8':
            SetConsoleTextAttribute(hConsole, 0x08);
            printf("▌");
            break;

        case '9':
            SetConsoleTextAttribute(hConsole, 0x09);
            printf("▌");
            break;

        case 'a':
            SetConsoleTextAttribute(hConsole, 0x0A);
            printf("▌");
            break;

        case 'c':
            SetConsoleTextAttribute(hConsole, 0x0C);
            printf("▌");
            break;

        case 'd':
            SetConsoleTextAttribute(hConsole, 0x0D);
            printf("▌");
            break;

        case 'e':
            SetConsoleTextAttribute(hConsole, 0x0E);
            printf("▌");
            break;

        case 'f':
            SetConsoleTextAttribute(hConsole, 0x0F);
            printf("▌");
            break;

        }


        dd++;
        
    }

    fclose(fp);

}

int Add(int a,int b)
{
    int c = a + b;
    return c;
}

