//If the code comments are garbled, ignore them!
/*
����:xsq1234
����:1993346266@qq.com(����),c6668883535357a@163.com(������)
�汾��Ϣ
0.1 ���������Ļ������
*/
#pragma once
#include"star.h"
//��Ϸ�ṹ��
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

//��ʼ����Ϸ
void InitialisationGame(GAME* Game, LPCWSTR name, int width, int height, int timeload, BOOL fullscreen, BOOL cmdswitch)
{
	//��ʼ���ṹ��
	Game->Windowhwnd = Window(NULL, Game->Name, Game->Windowwidth, Game->Windowheight, (nScreenWidth - Game->Windowwidth) / 2, (nScreenheight - Game->Windowheight) / 2);	//��������
	Game->Name = name;								//��������
	if (fullscreen != 0)							//���ȫ���򲻱�
	{
		Game->Windowwidth = width;					//���ڿ��
		Game->Windowheight = height;				//���ڸ߶�
		TitleBar(Game->Windowhwnd);
		FullScreen(Game->Windowhwnd);
	}
	else											//��֮�������ڴ�С���
	{
		Game->Windowwidth = width + 15;				//���ڿ��
		Game->Windowheight = height + 39;			//���ڸ߶�
	}
	Game->CMDswitch = cmdswitch;					//�Ƿ���ʾ����̨����
	Game->doublebuffer.hdc = DoubleBuffer(Game->Windowhwnd, Game->doublebuffer.hBitmap, Game->Windowwidth, Game->Windowheight);					//˫������Ⱦ
	SetTimeLoad(&(Game->timeload), timeload);		//��ʼ����ʱ��,����֡�ʿ���
}

//��Ϸ�������
void GameDrawing(GAME* Game) {};

//��Ϸ�߼�����
void GameLogic(GAME* Game) {};

//��Ϸѭ��
void GameLoop(GAME* Game,BOOL esc)
{
	while (1)
	{
		ClearWindow();								//��Ϣѭ��
		GameLogic(Game);							//��Ϸ�߼�����
		GameDrawing(Game);							//��Ϸ�������
		if (TimeLoad(&(Game->timeload), 1)) RUNDoubleBuffer(Game->Windowhwnd, Game->doublebuffer.hdc, Game->Windowwidth, Game->Windowheight);	//ͨ��˫������Ƶ���Ļ��		
		BoxB(0, Game->doublebuffer.hdc, 0, 0, Game->Windowwidth, Game->Windowheight, RGB(0, 0, 0));												//���˫������Ļ����
		if (esc && !GetAsyncKeyState(VK_ESCAPE))return;																							//�Ƿ�����esc�˳���Ϸ
	}
}

void GameOver(GAME* Game,BOOL cmdswitch)
{
	DeletBuffer(Game->doublebuffer.hBitmap, Game->doublebuffer.hdc);																			//����˫������Դ
	DeletWindow(Game->Windowhwnd);					//ɾ����Ϸ����
	if (cmdswitch)CMD(ON);							//�Ƿ�����Ϸ����ʱ�ָ�����̨����
}