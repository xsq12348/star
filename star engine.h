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
*/
#pragma once
#include"star.h"
#define MOUSEX(a) MouseX(a)
#define MOUSEY(a) MouseY(a)
int GAMEINPUT;					//游戏输入

//游戏结构体
typedef struct
{
	LPCWSTR Name;				//窗口名字
	HWND Windowhwnd;			//窗口句柄
	int Windowwidth;			//窗口宽度
	int Windowheight;			//窗口高度
	BOOL CMDswitch;				//CMD开关
	DOUBLEBUFFER doublebuffer;	//双缓冲渲染
	TIMELOAD timeload;			//帧率控制
	BOOL cuesor;				//鼠标光标
}GAME;

//NPC
typedef struct
{
	POINT coor;	//位置
	int health; //血量
	int mode;	//状态
	int sid;	//阵营
}NPC;

//--------------------------------------------------------------------------------------游戏工具----------------------------------------------------------------------------------------------------------//
//按钮控件,用于展示不同状态的按钮,悬停时显示图片2,按下时显示图片3
int ButtonStart(GAME* Game, int x, int y, int width, int height, int YESORNO, const wchar_t* File1, const wchar_t* File2, const wchar_t* File3)
{
	int button = ButtonA(0, Game->doublebuffer.hdc, x, y, width, height, YESORNO);
	switch (button)
	{
	case 0:Img(0, Game->doublebuffer.hdc, File1, x, y); break;
	case 1:Img(0, Game->doublebuffer.hdc, File3, x, y); break;
	case 2:Img(0, Game->doublebuffer.hdc, File2, x, y); break;
	}
	return button;
}

//动画控件

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

//初始化动画
int InitialisationAnime(ANIME* anime,LPCSTR name, LPCWSTR* sequenceframes[], int load, int totalnumber)
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
	Img(0, Game->doublebuffer.hdc, anime->sequenceframes[anime->number % anime->totalnumber], x, y);
	if (TimeLoad(&(anime->timeload), 1)) ++anime->number;	//添加下一帧	
	return anime->number;
}

//--------------------------------------------------------------------------------------游戏流程----------------------------------------------------------------------------------------------------------//

//初始化游戏
void InitialisationGame(GAME* Game, LPCWSTR name, int width, int height, int timeload, int fullscreenmode, BOOL cmdswitch,BOOL cursor)
{
	//初始化结构体
	Game->Windowhwnd = Window((HWND)NULL, name, width, height, (nScreenWidth - width) / 2, (nScreenheight - height) / 2);		//创建窗口
	Game->Name = name;								//窗口名字
	switch (fullscreenmode)					//如果全屏则不变
	{
	case 0:
		Game->Windowwidth = width + 15;				//窗口宽度
		Game->Windowheight = height + 39;			//窗口高度
		break;
	case 1:
		Game->Windowwidth = nScreenWidth;					//窗口宽度
		Game->Windowheight = nScreenheight;				//窗口高度
		TitleBar(Game->Windowhwnd);
		FullScreen(Game->Windowhwnd);
		break;
	case 2:
		Game->Windowwidth = nScreenWidth;				//窗口宽度
		Game->Windowheight = nScreenheight;			//窗口高度
		FullScreen(Game->Windowhwnd);
		break;
	}
	Game->CMDswitch = cmdswitch;					//是否显示控制台窗口
	CMD(cmdswitch);
	Game->doublebuffer.hdc = DoubleBuffer(Game->Windowhwnd, Game->doublebuffer.hBitmap, Game->Windowwidth, Game->Windowheight);	//双缓冲渲染
	SetTimeLoad(&(Game->timeload), timeload);		//初始化定时器,用于帧率控制
	Mouse(cursor);									//鼠标光标显示
}

//游戏画面绘制
void GameDrawing(GAME* Game);

//游戏逻辑绘制
void GameLogic(GAME* Game);

//游戏循环
void GameLoop(GAME* Game, BOOL esc)
{
	GetAsyncKeyState(VK_ESCAPE);
	while (1)
	{
		ClearWindow();																						//消息循环
		GameLogic(Game);																					//游戏逻辑计算
		GAMEINPUT = HardwareDetection();																//按键检测
		if (TimeLoad(&(Game->timeload), 1))
		{
			BoxB(0, Game->doublebuffer.hdc, 0, 0, Game->Windowwidth, Game->Windowheight, RGB(0, 0, 0));		//清除双缓冲屏幕画面
			GameDrawing(Game);																				//游戏画面绘制
		}
		RUNDoubleBuffer(Game->Windowhwnd, Game->doublebuffer.hdc, Game->Windowwidth, Game->Windowheight);	//通过双缓冲绘制到屏幕上
		if (esc && GetAsyncKeyState(VK_ESCAPE))return;														//是否启用esc退出游戏
	}
}

void GameOver(GAME* Game,BOOL cmdswitch)
{
	DeletBuffer(Game->doublebuffer.hBitmap, Game->doublebuffer.hdc);										//销毁双缓冲资源
	DeletWindow(Game->Windowhwnd);																			//删除游戏窗口
	if (cmdswitch)CMD(ON);																					//是否在游戏结束时恢复控制台窗口
}
