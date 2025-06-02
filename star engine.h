//If the code comments are garbled, ignore them!
/*
作者:xsq1234
邮箱:1993346266@qq.com(常用),c6668883535357a@163.com(不常用)
版本信息
0.1 完成了引擎的基本框架
0.11 修复了部分BUG
0.12 修复了部分BUG
0.13 优化了绘制体验
0.2 添加了动画模块
0.21 修复了初始化游戏的窗口bug
0.22 更新了NPC结构体
0.23 更新了动画资源关键字
0.23 重新开始写npc模块
0.24 npc结构体已被改成ENTITY结构体
0.3 增加了多线程
0.4 绘图函数移植成功
0.5 重写了按钮控件
0.51 修改了MOUSE宏
0.6 修改了渲染逻辑
0.61 新增了修改窗口坐标
0.7 解决了隐性的线程无法关闭的BUG
0.71 优化提升了部分性能
0.72 增加了性能开关
0.73 优化了绘制逻辑
0.8 增加了按键检测
0.9 优化了帧数限制问题
0.91 正在解决原本游戏点击关闭窗口后游戏仍然在运行的BUG(消息循环)
1.0 解决了原本游戏点击关闭窗口后游戏仍然在运行的BUG
1.01 调整了部分代码
*/
#pragma once
#include"star.h"

#define VK_0 48
#define VK_1 49
#define VK_2 50
#define VK_3 51
#define VK_4 52
#define VK_5 53
#define VK_6 54
#define VK_7 55
#define VK_8 56
#define VK_9 57

#define VK_A 65
#define VK_B 66
#define VK_C 67
#define VK_D 68
#define VK_E 69
#define VK_F 70
#define VK_G 71
#define VK_H 72
#define VK_I 73
#define VK_J 74
#define VK_K 75
#define VK_L 76
#define VK_M 77
#define VK_N 78
#define VK_O 79
#define VK_P 80
#define VK_Q 81
#define VK_R 82
#define VK_S 83
#define VK_T 84
#define VK_U 85
#define VK_V 86
#define VK_W 87
#define VK_X 88
#define VK_Y 89
#define VK_Z 90

TIMELOAD fps;
int fpsmax = 0,
fpsmax2 = 0;

#define RANDOM(a,b) Random(a,b)
#define DEGRAD(a) DegRad(a)

int GAMEDEAD = 0;				//游戏结束
int GAMEINPUT;					//游戏输入
int MOUSEX = 0, MOUSEY = 0;
int GAMEPOWER = 0;
typedef LPCWSTR ANIMEIMG;		//动画资源关键字
typedef POINT VELOCITY;			//速度分量结构体

//--------------------------------------------------------------------------------------游戏结构体----------------------------------------------------------------------------------------------------------//

//游戏结构体
typedef struct
{
	LPCWSTR Name;				//窗口名字
	HWND Windowhwnd;			//窗口句柄
	HWND Windowchildhwnd;		//子窗口句柄
	int Windowwidth;			//窗口宽度
	int Windowheight;			//窗口高度
	BOOL CMDswitch;				//CMD开关
	DOUBLEBUFFER doublebuffer;	//双缓冲渲染
	TIMELOAD timeload;			//帧率控制
	BOOL cuesor;				//鼠标光标
	BOOL escswitch;				//是否启用esc
}GAME;

//动画结构体
typedef struct
{
	LPCSTR Name;
	LPCWSTR* sequenceframes;	//序列帧数组
	int number;					//当前序列帧
	int totalnumber;			//序列帧总数
	BOOL animeswitch;			//动画动画播放开关
	TIMELOAD timeload;			//定时器
}ANIME;

//实体结构体
typedef struct
{
	LPCSTR Name;				//名称
	POINT coor;					//位置
	VELOCITY velocity;			//速度
	int hp;						//血量
	int sid;					//阵营
	int mode;					//行为模式
	BOOL crashboxswitch;		//碰撞箱开关
	struct ENTITY* parent;		//父实体
	struct ENTITY* children;	//子实体
}ENTITY;

typedef struct
{
	POINT coor;
	POINT lengths;
	BOOL buttonswitch;
	BOOL button;
	BOOL triggered;
}BUTTON;

//--------------------------------------------------------------------------------------绘图函数----------------------------------------------------------------------------------------------------------//

void PIX(GAME* Game, int x, int y, COLORREF color) { Pix(0, Game->doublebuffer.hdc, x, y, color); }
void LINE(GAME* Game, int x1, int y1, int x2, int y2, COLORREF color) { Line(0, Game->doublebuffer.hdc, x1, y1, x2, y2, color); }
void APPIX(GAME* Game, int apx, int apy, int x, int y, double rad, COLORREF color) { ApPix(0, Game->doublebuffer.hdc, apx, apy, x, y, rad, color); }
void APLINE(GAME* Game, int apx, int apy, int x1, int y1, int x2, int y2, double rad, COLORREF color) { ApLine(0, Game->doublebuffer.hdc, apx, apy, x1, y1, x2, y2, rad, color); }
void BOX(GAME* Game, int x, int y, int width, int height, COLORREF color) { BoxC(0, Game->doublebuffer.hdc, x, y, width, height, color); }
void BOXA(GAME* Game, int x, int y, int width, int height, COLORREF color)
{
	LINE(Game, x, y, x + width, y, color);
	LINE(Game, x, y, x, y + height, color);
	LINE(Game, x, y + height, x + width, y + height, color);
	LINE(Game, x + width, y, x + width, y + height, color);
}
void CIRCLE(GAME* Game, int R, int x, int y, COLORREF color) { Circle(0, Game->doublebuffer.hdc, R, x, y, color); }

//显示图片
void IMG(GAME* Game, const wchar_t File, int x, int y) { Img(0, Game->doublebuffer.hdc, File, x, y); }
void IMGA(GAME* Game, const wchar_t File, int x, int y, int widthbs, int heightbs, COLORREF color) { ImgA(0, Game->doublebuffer.hdc, File, x, y, widthbs, heightbs, color); }

//文字
void NewTEXT(GAME* Game, LPCWSTR text, int x, int y, COLORREF color) { Text(0, Game->doublebuffer.hdc, x, y, text, color); }
void NewDIGHT(GAME* Game, int number, int x, int y, COLORREF color) { Dight(0, Game->doublebuffer.hdc, x, y, number, color); }

//--------------------------------------------------------------------------------------游戏工具----------------------------------------------------------------------------------------------------------//

//按钮控件

int InitialisationButton(BUTTON* button, int x, int y, int width, int height, int YESORNO)
{
	button->coor.x = x;
	button->coor.y = y;
	button->lengths.x = width;
	button->lengths.y = height;
	button->buttonswitch = YESORNO;
	button->button = 0;
	button->triggered = 0;
}

//用于展示不同状态的按钮,悬停时显示图片2,按下时显示图片3
int ButtonStart(GAME* Game, BUTTON* button, const wchar_t* File1, const wchar_t* File2, const wchar_t* File3)
{
	button->button = ButtonA(0, Game->doublebuffer.hdc, button->coor.x, button->coor.y, button->lengths.x, button->lengths.y, button->buttonswitch);
	switch (button->button)
	{
	case 0:Img(0, Game->doublebuffer.hdc, File1, button->coor.x, button->coor.y); break;
	case 1:Img(0, Game->doublebuffer.hdc, File3, button->coor.x, button->coor.y); break;
	case 2:Img(0, Game->doublebuffer.hdc, File2, button->coor.x, button->coor.y); break;
	}
	return button->button;
}

//新按钮
int NewButton(GAME* Game, BUTTON* button)
{
	if (button->triggered)
	{
		button->button = 0;
		button->triggered = 1;
	}
	else if (GetAsyncKeyState(1))
	{
		if (MOUSEX > button->coor.x && MOUSEX  < button->coor.x + button->lengths.x && MOUSEY  > button->coor.y && MOUSEY < button->coor.y + button->lengths.y)
		{
			button->button = 1;
			button->triggered = 1;
		}
	}
	if (!GetAsyncKeyState(1))button->triggered = 0;
	//if (!(MOUSEX(Game->Windowhwnd) > button->coor.x && MOUSEX(Game->Windowhwnd) < button->coor.x + button->lengths.x && MOUSEY(Game->Windowhwnd) > button->coor.y && MOUSEY(Game->Windowhwnd) < button->coor.y + button->lengths.y))button->button = 0;
	if (button->buttonswitch)if (button->button)BOXA(Game, button->coor.x, button->coor.y, button->lengths.x, button->lengths.y, RGB(255, 0, 0));
	else BOXA(Game, button->coor.x, button->coor.y, button->lengths.x, button->lengths.y, RGB(255, 255, 255));
	return button->button;
}

//按键检测
int KEYSTATEbuffer[255];
int KeyState(int Key)
{
	int state = GetAsyncKeyState(Key);
	if (state & 0x8000)
	{
		if (KEYSTATEbuffer[Key] == 0)
		{
			KEYSTATEbuffer[Key] = 1;
			return 1;
		}
		return 0;
	}
	else
	{
		KEYSTATEbuffer[Key] = 0;
		return 0;
	}
}

//动画控件

//初始化动画
int InitialisationAnime(ANIME* anime, LPCSTR name, ANIMEIMG* sequenceframes[], int load, int totalnumber)
{
	anime->Name = name;
	if (totalnumber <= 0)
	{
		Color(0x07);
		printf("[InitialisationAnime函数错误]动画序列帧总数有问题,请检查名为[%s]的动画!\n", name);
		return Error;
	}
	if (sequenceframes == NULL)
	{
		Color(0x07);
		printf("[InitialisationAnime函数错误]动画序列帧有问题,请检查名为[%s]的动画是否存在!\n", name);
		return Error;
	}
	anime->animeswitch = 0;
	anime->sequenceframes = sequenceframes;
	anime->totalnumber = totalnumber;
	anime->number = 0;
	SetTimeLoad(&(anime->timeload), load);		//设置定时器
	return YES;
}

//运行动画
int RunAnime(GAME* Game, ANIME* anime, int animeswitch, int x, int y)
{
	if (!animeswitch)return 0;
	else ImgA(0, Game->doublebuffer.hdc, anime->sequenceframes[anime->number % anime->totalnumber], x, y, 1, 1, RGB(1, 1, 1));
	if (TimeLoad(&(anime->timeload), 1)) ++anime->number;	//添加下一帧	
	return anime->number;
}

//--------------------------------------------------------------------------------------游戏流程----------------------------------------------------------------------------------------------------------//

//初始化游戏
void InitialisationGame(GAME* Game, LPCWSTR name, int x, int y, int width, int height, int timeload, int fullscreenmode, BOOL cmdswitch, BOOL cursor)
{
	//初始化结构体
	if (y < 0) Game->Windowhwnd = Window((HWND)NULL, name, width, height, (nScreenWidth - width) / 2, (nScreenheight - height) / 2);		//创建窗口	
	else Game->Windowhwnd = Window((HWND)NULL, name, width, height, x, y);
	Game->Name = name;						//窗口名字
	switch (fullscreenmode)					//如果全屏则不变
	{
	case 0:
		Game->Windowwidth = width + 15;		//窗口宽度
		Game->Windowheight = height + 39;	//窗口高度
		break;
	case 1:
		Game->Windowwidth = nScreenWidth;	//窗口宽度
		Game->Windowheight = nScreenheight;	//窗口高度
		TitleBar(Game->Windowhwnd);
		FullScreen(Game->Windowhwnd);
		break;
	case 2:
		Game->Windowwidth = nScreenWidth;	//窗口宽度
		Game->Windowheight = nScreenheight;	//窗口高度
		FullScreen(Game->Windowhwnd);
		break;
	}
	for (int i = 0; i < 255; i++) KEYSTATEbuffer[i] = 0;	
	Game->CMDswitch = cmdswitch;			//是否显示控制台窗口
	CMD(cmdswitch);
	Game->doublebuffer.hdc = DoubleBuffer(Game->Windowhwnd, Game->doublebuffer.hBitmap, Game->Windowwidth, Game->Windowheight);	//双缓冲渲染
	SetTimeLoad(&(Game->timeload), 1000 / timeload);	//初始化定时器,用于帧率控制
	Mouse(cursor);										//鼠标光标显示
	Game->escswitch = 0;								//是否启用esc退出游戏
	SetTimeLoad(&fps, 1000);
}

//游戏画面绘制
void GameDrawing(GAME* Game);

//游戏逻辑绘制
void GameLogic(GAME* Game);

//逻辑线程
CREATTHREAD GAMELOGIC;
GAME* GAMETHEARDLOGIC;

//游戏逻辑线程
THREAD GameThreadLogic(LPARAM lparam)
{
	printf("[star engine logic进入成功!]\n");
	while (!GAMEDEAD)
	{
		GameLogic(GAMETHEARDLOGIC);												//游戏逻辑计算
		GAMEINPUT = HardwareDetection();										//按键检测
		MOUSEX = MouseX(GAMETHEARDLOGIC->Windowhwnd);
		MOUSEY = MouseY(GAMETHEARDLOGIC->Windowhwnd);
		if (GAMETHEARDLOGIC->escswitch && GetAsyncKeyState(VK_ESCAPE))GAMEDEAD = 1;	//是否启用esc退出游戏
		if (!IsWindow(GAMETHEARDLOGIC->Windowhwnd))GAMEDEAD = 1;//检查窗口是否存活
	}
}
//游戏循环
void GameLoop(GAME* Game, BOOL esc)
{
	GAMEDEAD = 0;
	GAMETHEARDLOGIC = Game;
	Game->escswitch = esc;
	srand((unsigned)time(NULL));
	GetAsyncKeyState(VK_ESCAPE);
	RunThread(&GameThreadLogic, &GAMELOGIC.ID);
	//RunThread(&WINDOWMESSAGE, &MESSAGE.ID);
	HDC hdc = GetDC(Game->Windowhwnd);
	HDC hdcchild = GetDC(Game->Windowchildhwnd);
	while (!GAMEDEAD)
	{
		if (!TimeLoad(&fps, 1))fpsmax++;
		else
		{
			fpsmax2 = fpsmax;
			fpsmax = 0;
		}
		//if (!GAMEPOWER)Sleep(1);
		if (!GAMEPOWER)Sleep(Game->timeload.timeload);
		BoxB(0, Game->doublebuffer.hdc, 0, 0, Game->Windowwidth, Game->Windowheight, RGB(0, 0, 0));		 //清除双缓冲屏幕画面
		GameDrawing(Game);
		Text(0, Game->doublebuffer.hdc, 0, 0, L"FPS:", RGB(0, 150, 0));
		NewDIGHT(Game, fpsmax2, 30, 0, RGB(0, 150, 0));
		BitBlt(hdc, 0, 0, Game->Windowwidth, Game->Windowheight, Game->doublebuffer.hdc, 0, 0, SRCCOPY); //通过双缓冲绘制到屏幕上
		ClearWindow();								 //消息循环
	}
	printf("[star Game Loop 结束!]\n");
}

//游戏结束
void GameOver(GAME* Game, BOOL cmdswitch)
{
	printf("[star Game Over进入成功!]\n");
	DeletThread(GAMELOGIC.ThreadHwnd);									//清理逻辑线程
	DeletBuffer(Game->doublebuffer.hBitmap, Game->doublebuffer.hdc);	//销毁双缓冲资源
	DeletWindow(Game->Windowhwnd);										//删除游戏窗口
	if (cmdswitch)CMD(ON);												//是否在游戏结束时恢复控制台窗口
	//PostQuitMessage(0);
	printf("游戏资源清理完成!");
}
