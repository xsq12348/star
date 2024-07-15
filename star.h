#pragma once
#include <stdio.h>
#include<conio.h>
#include <windows.h>
#include <math.h>
#include<stdlib.h>

//��Ϣ������
LRESULT CALLBACK WndPorc(HWND hwnd, UINT msgid, WPARAM  wparam, LPARAM lparam)
{

	HDC hdc = GetDC(hwnd);

	switch (msgid)
	{
		//�رմ���ʱ˳���������
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//�滭
	case WM_PAINT:

		break;
	}


	return DefWindowProc(hwnd, msgid, wparam, lparam);

}



//��������
void Window(
	HWND hwnd	/*���*/,
	int w		/*���ڿ��*/,
	int h		/*���ڸ߶�*/,
	int x		/*����ˮƽ����*/,
	int y		/*������ֱ����*/
)
{

	HINSTANCE hinstance = GetModuleHandle(NULL);

	//ע�ᴰ����
	WNDCLASS wndclass = { 0 };

	wndclass.cbClsExtra = 0;

	wndclass.cbWndExtra = 0;

	//��ȡ��ˢ ��䱳��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(0);

	//���ָ��
	wndclass.hCursor = NULL;

	//ϵͳĬ��ͼ��
	wndclass.hIcon = NULL;

	//������
	wndclass.hInstance = hinstance;

	wndclass.lpfnWndProc = WndPorc;

	//����
	wndclass.lpszClassName = TEXT("main");

	//�˵�
	wndclass.lpszMenuName = NULL;

	//������ʽ
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);

	//��������
	hwnd = CreateWindow(TEXT("main"), TEXT(" ")/*����*/, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, x, y, w, h, NULL, NULL, hinstance, NULL);
	
	//��ʾ����
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);



}

//��Ϣѭ��
void RunWindow()
{
	//��Ϣѭ��
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

}

