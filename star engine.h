//If the code comments are garbled, ignore them!
/*
作者:xsq1234
邮箱:1993346266@qq.com(常用),c6668883535357a@163.com(不常用)
版本信息
0.1 完成了引擎的基本框架
0.11 修复了部分BUG
0.12 修复了部分BUG
0.13 优化了绘制体验
*/
#pragma once
#include"star.h"
//游戏结构体
typedef struct
{
	LPCWSTR Name;
	HWND Windowhwnd;
	int Windowwidth;
	int Windowheight;
	int CMDswitch;
	DOUBLEBUFFER doublebuffer;
	TIMELOAD timeload;
}GAME;

//初始化游戏
void InitialisationGame(GAME* Game, LPCWSTR name, int width, int height, int timeload, BOOL fullscreen, BOOL cmdswitch)
{
	//初始化结构体
	Game->Windowhwnd = Window((HWND)NULL, name, width, height, (nScreenWidth - width) / 2, (nScreenheight - height) / 2);	//创建窗口
	Game->Name = name;								//窗口名字
	if (fullscreen != 0)							//如果全屏则不变
	{
		Game->Windowwidth = width;					//窗口宽度
		Game->Windowheight = height;				//窗口高度
		TitleBar(Game->Windowhwnd);
		FullScreen(Game->Windowhwnd);
	}
	else											//反之修正窗口大小误差
	{
		Game->Windowwidth = width + 15;				//窗口宽度
		Game->Windowheight = height + 39;			//窗口高度
	}
	Game->CMDswitch = cmdswitch;					//是否显示控制台窗口
	CMD(cmdswitch);
	Game->doublebuffer.hdc = DoubleBuffer(Game->Windowhwnd, Game->doublebuffer.hBitmap, Game->Windowwidth, Game->Windowheight);					//双缓冲渲染
	SetTimeLoad(&(Game->timeload), timeload);		//初始化定时器,用于帧率控制
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
