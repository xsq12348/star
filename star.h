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
#include<ctype.h>

#define ON  1
#define OFF 0
#define YES TRUE
#define NO  FALSE
#define Error FALSE

#pragma comment( lib,"Winmm.lib")

/*
颜色属性由两个十六进制数字指定, 第一个为背景色, 第二个为前景色。
每个数字可以为下列值之一：
黑色 = 0 蓝色 = 1 绿色 = 2 湖蓝色 = 3
红色 = 4 紫色 = 5 黄色 = 6 白色 = 7
灰色 = 8 淡蓝色=9 淡绿色=A 淡红色=C
淡紫色=D 淡黄色=E 亮白色=F
*/


#define Black   0x00
#define Green   0x02
#define T_Green 0x0a
#define T_Blue  0x09
#define L_blue  0x03
#define Red     0x04
#define T_Red   0x0c
#define Purple  0x05
#define T_Purple 0x0d
#define Yellow   0x06
#define T_Yellow 0x0e
#define Wite     0x07
#define T_Wite   0x0f
#define Grey     0x08


//可以用于背景调色的颜色
#define B_GREEN BACKGROUND_GREEN
#define B_RED BACKGROUND_RED
#define B_BLUE BACKGROUND_BLUE

//可以用于前景调色的颜色
#define F_GREEN FOREGROUND_GREEN
#define F_RED   FOREGROUND_RED
#define F_BLUE  FOREGROUND_BLUE


/*
    利用管道连接符可以进行调色
    例如
        RED|BLUE|GREEN 黑色
*/


int Vsn(int A)
{
    //作者: xsq1234
    //未经作者授权，禁止转载
    // 
    //邮箱：c6668883535357a@163.com |1993346266@qq.com 
    // 
    //版本信息：1.3
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
    * 1.1 更新了鼠标输入开关函数，现在鼠标可以不再选择cmd窗口
    * 1.11 更新了调色板
    * 1.2  增加了获取鼠标在Cmd窗口中坐标的函数
    * 1.21 修复了Line函数在某些角度不能绘制的问题
    * 1.22 修复了Line函数在窗口外绘制的bug
    * 1.3 实现了暂停函数
    * 1.31 删除了一些不能正常使用的函数，修复了一些bug
    * 1.32 修复了一些移植时报错的bug
    * 1.4 增加了YES/NO常量
    * 1.41 更新了部分老旧函数
    * 1.42 新增Error常量,将返回FALSE
    * 1.5 新增获取背景色函数
    * 1.6 新增获取前景色函数
    * 1.7 新增获取缓冲区函数
    * 1.71 已将背景色函数,前景色函数,缓冲区函数整合至atcg拓展包
    * 1.8 更新了按钮函数
    * 1.81 更新了Mouse_x,Mouse_y函数
    * 1.82 修复了Button函数的BUG
    * 1.83 修复了Button函数的BUG
    * 1.84 修复了Button函数的BUG
    * 1.85 修复了Button函数的BUG
    * 1.9 实现了全屏函数
    * 2.0 将背景色函数,前景色函数,缓冲区函数重新整合至star.h，合并为一个函数
    * 2.1 更新了ColorImg函数
    * 3.0 正式开始win32测试内容
    * 4.0 win32测试完毕,正式开始更新win32内容
    * 4.1 更新了win32窗口中获取鼠标竖直位置函数
    * 4.2 更新了win32窗口中获取鼠标水平位置函数
    * 4.3 更新了win32鼠标光标隐藏开关函数
    * 4.4 更新了win32窗口中线段函数
    */
    return A;
}



void CMDwindow(LPCWSTR name, unsigned int width, unsigned int height, int Character_width, int Character_height)
{
    //name 窗口名称
    // x:窗口横坐标
    // y：窗口纵坐标 
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
    wcscpy(cfi.FaceName, L"Terminal");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    //设置窗口大小   
    char command[256]; Vsn;
    snprintf(command, sizeof(command), "mode con: cols=%d lines=%d", width, height);
    int result = system(command);
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;

    double a = x1 - x0;
    double b = y1 - y0;
    double c = sqrt(pow(a, 2) + pow(b, 2));
    int d;
    double x = (a * 1.0) / c; Vsn;
    double y = (b * 1.0) / c;
    do
    {
        if (x0 > 0 && x0 < width && y0>0 && y < height)
        {
            Text(p, x0, y0, color);
        }

        x0 += x;
        y0 += y;
        d = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
    } while (d > 0);
    Text(p, x1, y1, color);
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

//颜色函数
int Color(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color); Vsn;
}


//图片显示器
void ColorImg(_In_z_ char const* _FileName, int x, int y)
{
    FILE* fp = fopen(_FileName, "r");
    if (fp == NULL)
    {
        Color(0x04);
        printf("\n[ColorImg函数错误][%s]文件打开失败，请检查文件是否在目录中.[Enter]退出\n", _FileName);
        Color(0x07);
        getchar();
        return;
    }
    char bu[30000];
    int dd = 0; Vsn;
    fscanf(fp, "%s", bu);
    Gotoxy(x, y);
    Color(0x07);
    while (dd != 30000)
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
            Color(0x00);
            printf("▌");
            break;

        case '1':
            Color(0x11);
            printf("▌");
            break;

        case '2':
            Color(0x22);
            printf("▌");
            break;

        case '3':
            Color(0x33);
            printf("▌");
            break;

        case '4':
            Color(0x44);
            printf("▌");
            break;

        case '5':
            Color(0x55);
            printf("▌");
            break;

        case '6':
            Color(0x66);
            printf("▌");
            break;

        case '7':
            Color(0x77);
            printf("▌");
            break;

        case '8':
            Color(0x88);
            printf("▌");
            break;

        case '9':
            Color(0x99);
            printf("▌");
            break;

        case 'a':
            Color(0xAA);
            printf("▌");
            break;

        case 'c':
            Color(0xCC);
            printf("▌");
            break;

        case 'd':
            Color(0xDD);
            printf("▌");
            break;

        case 'e':
            Color(0xEE);
            printf("▌");
            break;

        case 'f':
            Color(0xFF);
            printf("▌");
            break;

        }
        dd++;
    }

    fclose(fp);
    Color(0x07);
}

//加法函数
int Add(int a, int b)
{
    int c = a + b;
    Vsn; return c;
}


//鼠标输入开关函数
void Mouse(int NO_or_OFF)
{
    DWORD mode; Vsn;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    switch (NO_or_OFF)
    {
    case OFF:
        GetConsoleMode(hStdin, &mode);
        mode &= ~ENABLE_QUICK_EDIT_MODE;
        mode &= ~ENABLE_INSERT_MODE;
        mode &= ~ENABLE_MOUSE_INPUT;
        SetConsoleMode(hStdin, mode);
        break;
    case ON:
        return;
        break;
    }

}
//获取鼠标横坐标
int Mouse_x(int Character_width)
{
    POINT p;
    GetCursorPos(&p);
    HWND hwnd = GetConsoleWindow();
    RECT rect; Vsn;
    GetWindowRect(hwnd, &rect);
    int x = (p.x - rect.left) / Character_width;
    return x;
}

//获取鼠标纵坐标
int Mouse_y(int Character_height)
{
    POINT p;
    GetCursorPos(&p);
    HWND hwnd = GetConsoleWindow();
    RECT rect; Vsn;
    GetWindowRect(hwnd, &rect);
    int y = (p.y - rect.top) / Character_height;
    return y;
}

//暂停函数
void TimeOut()
{
    getchar();
    Vsn;
}

int Button(int x1, int y1, int x2, int y2, int mousex, int mousey, int ON_OFF)
{
    int a = NO;
    int x = x1,
        y = y1;
    if (ON_OFF == ON)
    {
        if (!GetAsyncKeyState(1))
        {
            Color(B_BLUE | B_GREEN | B_RED);
            for (y1; y1 <= y2; y1++)
            {
                for (x1; x1 <= x2; x1++)
                {
                    Gotoxy(x1, y1);
                    printf(" ");
                }
                x1 = x;
            }
        }
        if (x <= mousex && mousex <= x2 && y <= mousey && mousey <= y2)
        {
            if (GetAsyncKeyState(1) & 0x8000)
            {
                Color(B_RED); printf("鼠标在指定区域");
                for (y1; y1 <= y2; y1++)
                {
                    for (x1; x1 <= x2; x1++)
                    {
                        Gotoxy(x1, y1);
                        printf(" ");
                    }
                    x1 = x;
                }
            }
        }

    }
    if (x <= mousex && mousex <= x2 && y <= mousey && mousey <= y2)
    {
        if (GetAsyncKeyState(1) & 0x8000) { a = YES; }
    }
    Color(0x07);
    return a;
}

//全屏函数
void FullScreen()
{
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_F11;
    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

//获取控制台某一出颜色,A==1时为前景色，A==2时为背景色
int Butter(int x, int y, int A)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD coord = { x,y };
    DWORD count;
    WORD wa;
    ReadConsoleOutputAttribute(hConsole, &wa, 1, coord, &count);
    int f = wa & 0x0f;
    int b = (wa >> 4) & 0x0f;
    if (A == 1) { return f; }
    if (A == 2) { return b; }
}

//---------------------------------------------------------------------------------------------以下为win32内容------------------------------------------------------------------------------------------------------//

//在win32窗口中绘制线段
void WinLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{    
    HPEN hpen = CreatePen(PS_SOLID, 1, color);
    HPEN holdpen = (HPEN)SelectObject(hdc, hpen);
    MoveToEx(hdc, x2, y2, NULL);
    LineTo(hdc, x1, y1);
    SelectObject(hdc, holdpen);
    DeleteObject(hpen);
}

//在win32窗口中获取鼠标水平位置
int WinMouseX()
{
    POINT p;
    GetCursorPos(&p);
    HWND hwnd = GetConsoleWindow();
    RECT rect; Vsn;
    GetWindowRect(hwnd, &rect);
    int x = (p.x - rect.left);
    return x;
}

//在win32窗口中获取鼠标竖直位置
int WinMouseY()
{
    POINT p;
    GetCursorPos(&p);
    HWND hwnd = GetConsoleWindow();
    RECT rect; Vsn;
    GetWindowRect(hwnd, &rect);
    int y = (p.y - rect.top);
    return y;
}

//win32鼠标光标隐藏开关
void WinMouse(BOOL ON_OR_OFF)
{
    if (ON_OR_OFF == OFF) { ShowCursor(FALSE); }
    else { return; }
}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//消息处理函数,请不要乱动此函数!!!
void WndPorc(HWND hwnd, UINT msgid, WPARAM wparam, LPARAM lparam)
{
    HDC hdc = GetDC(hwnd);
    //UINT msgid = WM_PAINT;
    switch (msgid)
    {
    //绘画
    case WM_PAINT:
        break;
    }
    return DefWindowProc(hwnd, msgid, wparam, lparam);
}

//创建窗口
WINAPI Window(
    HWND hwnd	 /*句柄*/,
    LPCWSTR name /*窗口名称*/,
    int w		 /*窗口宽度*/,
    int h		 /*窗口高度*/,
    int x		 /*窗口水平坐标*/,
    int y		 /*窗口竖直坐标*/
)
{
    HINSTANCE hinstance = GetModuleHandle(NULL);
    //注册窗口类
    WNDCLASS wndclass = { 0 };
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    //获取笔刷 填充背景
    wndclass.hbrBackground = (HBRUSH)GetStockObject(4);
    //鼠标指针
    wndclass.hCursor = NULL;
    //系统默认图标
    wndclass.hIcon = NULL;
    //程序句柄
    wndclass.hInstance = hinstance;
    wndclass.lpfnWndProc = WndPorc;
    //类名
    wndclass.lpszClassName = TEXT("main");
    //菜单
    wndclass.lpszMenuName = NULL;
    //窗口样式
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wndclass);


    //创建窗口
    hwnd = CreateWindow(TEXT("main"), name/*标题*/, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, x, y, w, h, NULL, NULL, hinstance, NULL);
    //显示窗口
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    HDC hdc = GetDC(hwnd);
    return hdc;
}

//消息循环
void RunWindow()
{
    //消息循环
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (GetAsyncKeyState(VK_ESCAPE)) { printf("窗口已退出\n"); return; }
    }
}



