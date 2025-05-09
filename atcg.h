注意！！该拓展包已弃用！
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"star.h"

//作者: xsq1234
//未经作者授权，禁止转载
// 
//邮箱：c6668883535357a@163.com |1993346266@qq.com 
//
//此为star.h的拓展包,对于您的游戏创作将更加方便
// star版本 2.01
// 版本信息：0.1
// 0.1 更新了Dna函数，您将方便快捷的制作地图






int Dna(char const* filename, int x, int y)
{
	FILE* fp = fopen(filename, "r");
	char arratcg[200000] = { 0 };
	fscanf(fp, "%s", arratcg);
	int a = 0;
	Gotoxy(x, y);
	while (1)
	{
		if (arratcg[a] == 'x')
		{
			break;
		}
		switch (arratcg[a])
		{
		case 's':
			Color(B_RED | B_GREEN);
			printf(" ");
			break;

		case 'l':
			Color(B_GREEN);
			printf(" ");
			break;

		case 'p':
			Color(B_RED | B_GREEN | B_BLUE);
			printf(" ");
			break;

		case 'w':
			Color(B_BLUE);
			printf(" ");
			break;

		case 'h':
			Gotoxy(x, y++);
			break;
		}
		a++;
	}
	fclose(fp);
	return a;
}
