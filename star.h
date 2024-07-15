#pragma once
#include <stdio.h>
#include<conio.h>
#include <windows.h>
#include <math.h>
#include<stdlib.h>

//消息处理函数
LRESULT CALLBACK WndPorc(HWND hwnd, UINT msgid, WPARAM  wparam, LPARAM lparam)
{

	HDC hdc = GetDC(hwnd);

	switch (msgid)
	{
		//关闭窗口时顺便结束进程
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//绘画
	case WM_PAINT:

		break;
	}


	return DefWindowProc(hwnd, msgid, wparam, lparam);

}



//创建窗口
void Window(
	HWND hwnd	/*句柄*/,
	int w		/*窗口宽度*/,
	int h		/*窗口高度*/,
	int x		/*窗口水平坐标*/,
	int y		/*窗口竖直坐标*/
)
{

	HINSTANCE hinstance = GetModuleHandle(NULL);

	//注册窗口类
	WNDCLASS wndclass = { 0 };

	wndclass.cbClsExtra = 0;

	wndclass.cbWndExtra = 0;

	//获取笔刷 填充背景
	wndclass.hbrBackground = (HBRUSH)GetStockObject(0);

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
	hwnd = CreateWindow(TEXT("main"), TEXT(" ")/*标题*/, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, x, y, w, h, NULL, NULL, hinstance, NULL);
	
	//显示窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);



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

	}

}

