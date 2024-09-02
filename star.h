#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mmsystem.h>
#include<conio.h>
#include<string.h>

#define NO 1
#define OFF 0

#pragma comment( lib,"Winmm.lib")


int Vsn(int A)
{
    //作者: xsq1234
    //未经作者授权，禁止转载
    // 
    //邮箱：c6668883535357a@163.com |1993346266@qq.com 
    // 
    //版本信息：1.05
    /*
    *     版本更新内容
    * 0.1 实现了窗口创建函数
    * 0.2 完善了窗口创建函数，实现了特定位置输出文字函数
    * 0.3 实现了划线函数，移动光标函数，清屏函数
    * 0.4 实现了颜色分配
    * 0.5 实现了随机数和矩形函数
    * 0.6 实现了隐藏光标函数
    * 0.7 增加了音乐编辑器函数
    * 0.8 增加了字符画显示函数
    * 0.9 更新了音乐编辑器函数,使其能读取乐谱
    * 1.0 更改音乐编辑器函数为音乐播放函数,增加了加法函数。
    * 1.01 将颜色选项从Gotoxy函数中分离，使之成为独立的函数。Music函数维修中
    * 1.02 修复了部分错误
    * 1.03 更新了Line函数
    * 1.04 更新了部分内容,对部分函数进行了整改
    * 1.05 解决了Line函数的bug
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



void CMDwindow(LPCWSTR name, unsigned int width, unsigned int height, int Character_width, int Character_height)
{

    //name 窗口名称
    // width height 窗口大小
    // Character_width Character_height 字符长与宽
    /*
        //得知显示器像素数,以后维护时可能有用
    int nScreenWidth, nScreenHeight;
    nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    */

    //获取当前控制台的句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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
    char command[256]; Vsn;
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
    double a = x1 - x0;
    double b = y1 - y0;
    double c = sqrt(pow(a, 2) + pow(b, 2));
    double x = (a * 1.0) / c;
    double y = (b * 1.0) / c; Vsn;
    int x2, y2,
        x3 = x1,
        y3 = y1;
    do
    {
        x2 = x0;
        y2 = y0;
        Text(p, x0, y0, color);
        x0 = x0 + x;
        y0 = y0 + y;

    } while (x2 != x3 && y2 != y3);
}


//清屏
void Clear()
{
    system("cls"); Vsn;
}



//移动光标
void Gotoxy(int x, int y)
{
    COORD lightb; Vsn;
    lightb.X = x;
    lightb.Y = y;
    HANDLE CMD = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(CMD, lightb);

}



//隐藏/显示光标
void HideFLASE(BOOL A)
{
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1; Vsn;
    curInfo.bVisible = A;
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
    A = rand() % B + A;
    Vsn; return A;
}

/*
维修中

//音乐编辑器
void Music(const char* _FileName)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char d[100] = { 0 };
    //snprintf(d, sizeof(d), "open %s alias bgm", _FileName);



    mciSendString("close bgm", NULL, 0, NULL);
    snprintf(d, sizeof(d), "open \"%s\" alias bgm", _FileName);




    printf("d: %s\n", d);
    int rct = mciSendString(d, NULL, 0, NULL);

    if (rct != 0)
    {
        SetConsoleTextAttribute(hConsole, 0x04);
        switch (rct)
        {
        case MCIERR_BAD_CONSTANT:
            printf("\n[Music函数错误]为参数指定的值未知[Enter]退出\n");
            break;

        case MCIERR_BAD_INTEGER:
            printf("\n[Music函数错误]命令中的整数无效或缺失[Enter]退出\n");
            break;

        case MCIERR_DUPLICATE_FLAGS:
            printf("\n[Music函数错误]已指定标志或值两次[Enter]退出\n");
            break;

        case MCIERR_MISSING_COMMAND_STRING:
            printf("\n[Music函数错误]未指定任何命令[Enter]退出\n");
            break;

        case MCIERR_MISSING_DEVICE_NAME:
            printf("\n[Music函数错误]未指定设备名称[Enter]退出\n");
            break;

        case MCIERR_MISSING_STRING_ARGUMENT:
            printf("\n[Music函数错误]命令中缺少字符串值[Enter]退出\n");
            break;

        case MCIERR_NEW_REQUIRES_ALIAS:
            printf("\n[Music函数错误]别名必须与“新”设备名称一起使用[Enter]退出\n");
            break;

        case MCIERR_NO_CLOSING_QUOTE:
            printf("\n[Music函数错误]缺少右引号[Enter]退出\n");
            break;

        case MCIERR_NOTIFY_ON_AUTO_OPEN:
            printf("\n[Music函数错误]自动打开“通知”标志是非法的[Enter]退出\n");
            break;

        case MCIERR_PARAM_OVERFLOW:
            printf("\n[Music函数错误]输出字符串不够长[Enter]退出\n");
            break;

        case MCIERR_PARSER_INTERNAL:
            printf("\n[Music函数错误]发生内部分析程序错误[Enter]退出\n");
            break;

        case MCIERR_UNRECOGNIZED_KEYWORD:
            printf("\n[Music函数错误]指定了未知的命令参数[Enter]退出\n");
            break;
        }
        SetConsoleTextAttribute(hConsole, 0x07);
        getchar();
        return 0;
    }

    mciSendString("play bgm", NULL, 0, NULL);

}

*/


//图片显示器
void ColorImg(_In_z_ char const* _FileName, int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE* fp = fopen(_FileName, "r");
    if (fp == NULL)
    {
        SetConsoleTextAttribute(hConsole, 0x04);
        printf("\n[ColorImg函数错误][%s]文件打开失败，请检查文件是否在目录中.[Enter]退出\n", _FileName);
        SetConsoleTextAttribute(hConsole, 0x07);
        getchar();
        return 0;
    }
    char bu[300];
    int dd = 0; Vsn;
    fscanf(fp, "%s", bu);
    Gotoxy(x, y);
    Color(0x07);
    while (dd != 300)
    {

        if (bu[dd] == 'x')
        {
            break;
        }
        switch (bu[dd])
        {
        case 'h':
            Gotoxy(x, y++);
            Color(0x07);
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
    SetConsoleTextAttribute(hConsole, 0x07);
}

//加法函数
int Add(int a, int b)
{
    int c = a + b;
    Vsn; return c;
}

//颜色函数
int Color(int color)
{   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color); Vsn;
}

