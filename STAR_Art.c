#include"star.h"
/*
颜色说明：
F1	0x01
F2	0x02
F3	0x03
F4	0x04
F5	0x05
F6	0x06
F7	0x07
F8	0x08
F9	0x09
F10	0x0a
数字1	0x0c
数字2	0x0d
数字3	0x0e
数字4	0x0f

黑色 = 0 蓝色 = 1 绿色 = 2 湖蓝色 = 3
红色 = 4 紫色 = 5 黄色 = 6 白色 = 7
灰色 = 8 淡蓝色=9 淡绿色=A 淡红色=C
淡紫色=D 淡黄色=E 亮白色=F

绘图结束后按ESC即可保存

注意!此软件在最新版本已失效，请移步最后能使用的版本9.11
*/

int main()
{
	int mousex,
		mousey;
	CMDwindow(TEXT("star_art"), 50, 20, 16, 16);
	HideFLASE(OFF);
	Mouse(OFF);
	int mode = 0;
	printf("欢迎使用star画板，本画板专为star游戏引擎设计，可以快速开发大型地图\n\n");
	while (1)
	{
		mousex = Mouse_x(16);
		mousey = Mouse_y(16) - 2;
		Text("画新的", 23, 4, 0x06);
		Text("导入画", 23, 8, 0x06);
		if (Button(16, 4, 34, 4, mousex, mousey, OFF))
		{
			mode = 1;
			break;
		}
		if(Button(16, 8, 34, 8, mousex, mousey, OFF))
		{
			mode = 2;
			break;
		}
		Sleep(1);
	}
	Clear();
	HideFLASE(ON);
	int width = 5,
		height = 5;
	printf("\n\n\n地图宽度:\n\n");
	printf("地图长度:");
	Gotoxy(10, 3);
	scanf("%d", &width);
	Gotoxy(10, 5);
	scanf("%d", &height);
	system("mode con: cols=2 lines=2");
	CMDwindow(TEXT("star_art"), width, height, 8, 8);
	Mouse(OFF);	
	int color = Yellow;
	FullScreen();
	if (mode == 1)
	{
		for (int i = 0; i <= height; i++)
		{
			for (int o = 0; o < width; o++)
			{
				Text("▌", o, i, 0x00);
			}
		}
		printf("\n初始化完成!");
	}
	char Name[255] = { 0 };
	if (mode == 2)
	{
		printf("导入画的名字:");
		scanf("%s", &Name);
		char cmd[255] = { 0 };
		snprintf(cmd, sizeof(cmd), "%s.txt", Name);
		ColorImg(cmd, 0, 0);
	}
	HideFLASE(OFF);
	Line("-", 0, height, width, height, Wite);
	Line("|", width, 0, width, height, Wite);
	Text("+", width, height, Wite);

	while (GetAsyncKeyState(VK_ESCAPE) != -32767)
	{
		HideFLASE(OFF);
		mousex = Mouse_x(8);
		mousey = Mouse_y(8);
		Gotoxy(100, height);
		if (mousex < width && mousey < height)
		{
			if (GetAsyncKeyState(1)) { Text("▌", mousex, mousey, color); }
		}
		if (GetAsyncKeyState(69)) { color = 0x00; }
		if (GetAsyncKeyState(112)) { color = 0x01; }
		if (GetAsyncKeyState(113)) { color = 0x02; }
		if (GetAsyncKeyState(114)) { color = 0x03; }
		if (GetAsyncKeyState(115)) { color = 0x04; }
		if (GetAsyncKeyState(116)) { color = 0x05; }
		if (GetAsyncKeyState(117)) { color = 0x06; }
		if (GetAsyncKeyState(118)) { color = 0x07; }
		if (GetAsyncKeyState(119)) { color = 0x08; }
		if (GetAsyncKeyState(120)) { color = 0x09; }
		if (GetAsyncKeyState(121)) { color = 0x0a; }
		if (GetAsyncKeyState(49)) { color = 0x0c; }
		if (GetAsyncKeyState(50)) { color = 0x0d; }
		if (GetAsyncKeyState(51)) { color = 0x0e; }
		if (GetAsyncKeyState(52)) { color = 0x0f; }
		Text("当前颜色:", 0, height + 3, 0x07);
		Text("▌", 10, height + 3, color);
		Sleep(1);
	}
	HideFLASE(ON);
	char name[255] = { 0 };
	printf("\n\n名字:");
	scanf("%s", &name);
	char command[256];
	snprintf(command, sizeof(command), "%s.txt", name);
	FILE* fp = fopen(command, "w+");
	FILE* Fp = fopen(command, "a");
	printf("\n正在生成");
	fprintf(Fp, "h");
	for (int i = 0; i < height; i++)
	{
		for (int o = 0; o <= width; o++)
		{
			if (o == width) { fprintf(Fp, "h"); }
			else
			{
				switch (Butter(o, i, 1))
				{
				case 0:fprintf(Fp, "0"); break;
				case 1:fprintf(Fp, "1"); break;
				case 2:fprintf(Fp, "2"); break;
				case 3:fprintf(Fp, "3"); break;
				case 4:fprintf(Fp, "4"); break;
				case 5:fprintf(Fp, "5"); break;
				case 6:fprintf(Fp, "6"); break;
				case 7:fprintf(Fp, "7"); break;
				case 8:fprintf(Fp, "8"); break;
				case 9:fprintf(Fp, "9"); break;
				case 10:fprintf(Fp, "a"); break;
				case 12:fprintf(Fp, "c"); break;
				case 13:fprintf(Fp, "d"); break;
				case 14:fprintf(Fp, "e"); break;
				case 15:fprintf(Fp, "f"); break;
				}
			}
		}
	}
	printf(" \n完成!");
	fprintf(Fp, "x");
	fclose(fp);
	fclose(Fp);
	system("pause");
	TimeOut();
}
