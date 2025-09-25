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
1.02 修复了部分BUG
1.1 添加了简单物理
1.2 cpp移植成功,现在cpp和都可以同时使用该引擎
1.3 添加了OpenCL支持
1.4 添加了对象注册表，现在可以通过GAME结构体访问全部对象
1.5 修改了动画部分
1.6 重做了按钮模块
1.7 对实体系统添加了Hash查找
1.71 修复了被遗忘的隐藏BUG
1.72 修正了多文件支持的BUG
1.73 去除了部分全局数据,可能造成兼容问题
*/
#pragma once
#pragma warning(disable:4996)
#undef STARDLC
#include<star.h>
#if STARTOpenCL || STARTGPU
#include<CL/opencl.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib,"OpenCL.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#endif

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

#define VECTORY float

#define ENTITYNUMBER 10000
#define nScreenHeight nScreenheight

#define RANDOM(a,b) Random(a,b)
#define DEGRAD(a) DegRad(a)
#define switchlogic(alpha) if(FALSE);
#define caselogic(beta) else if(beta)
#define NOTFOUND Error
#define RANGE(alpha, beta, gamma) min(max(alpha, beta), gamma)
#define SETMOUSECOORD(x, y) SetCursorPos(x, y)
#define HashFindEntityIndex(nameid) (Hash(nameid) % ENTITYNUMBER)//hash寻找实体

typedef DOUBLEPOINT VELOCITY;			//速度分量结构体

//--------------------------------------------------------------------------------------游戏结构体----------------------------------------------------------------------------------------------------------//

//对象
typedef struct
{
	char* nameid;
	int length;
	void* entityindex;
}ENTITYINDEX;

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
	BOOL escswitch;				//是否启用esc
	ENTITYINDEX entityindex[ENTITYNUMBER];//对象池注册表
	int GAMEDEAD;				//游戏结束
	int GAMEINPUT;				//游戏输入
	int MOUSEX, MOUSEY;
	int GAMEPOWER;
	TIMELOAD fps;
	int fpsmax, fpsmax2;
}GAME;

typedef struct
{
	POINT lengths;				//图片大小
	DOUBLEBUFFER image;			//图片
}IMAGE;

//动画结构体
typedef struct
{
	LPCSTR Name;
	IMAGE* sequenceframes;		//序列帧数组
	long long int number;		//当前序列帧
	int totalnumber;			//序列帧总数
	BOOL animeswitch;			//动画动画播放开关
	TIMELOAD timeload;			//定时器
}ANIME;

typedef struct
{
	RECT coord;
}BUTTON;

typedef struct
{
	DOUBLEPOINT coor;
	DOUBLEPOINT vectory;
	int R;
	double mass;
}CIRCLEPHYSICS;

typedef struct
{
	float x;
	float y;
	float z;
}POINT3D;

typedef struct
{
	float x;
	float y;
	float Z;
}POINT2D;

typedef struct
{
	int color;
	POINT3D vertex[3];
}SURFACE;

typedef struct
{
	POINT3D camerapoint;
	POINT3D cameravectorx;
	POINT3D cameravectory;
	POINT3D cameranormal;
	float cameravectorxmo;
	float cameravectorymo;
	float focalLength;
	float matrixR[3][3];
	float matrix[3][3];
}CAMERA;

#if STARTOpenCL || STARTGPU
typedef struct
{
	HDC hdc;
	HGLRC hrc;
	int width;
	int height;
}OPENGL;

#endif

//--------------------------------------------------------------------------------------绘图函数----------------------------------------------------------------------------------------------------------//

static void PIX(GAME* Game, int x, int y, COLORREF color) { Pix(Game->Windowhwnd, Game->doublebuffer.hdc, x, y, color); }
static void LINE(GAME* Game, int x1, int y1, int x2, int y2, COLORREF color) { Line(Game->Windowhwnd, Game->doublebuffer.hdc, x1, y1, x2, y2, color); }
static void APPIX(GAME* Game, int apx, int apy, int x, int y, double rad, COLORREF color) { ApPix(Game->Windowhwnd, Game->doublebuffer.hdc, apx, apy, x, y, rad, color); }
static void APLINE(GAME* Game, int apx, int apy, int x1, int y1, int x2, int y2, double rad, COLORREF color) { ApLine(Game->Windowhwnd, Game->doublebuffer.hdc, apx, apy, x1, y1, x2, y2, rad, color); }
static void BOX(GAME* Game, int x, int y, int width, int height, COLORREF color) { BoxC(Game->Windowhwnd, Game->doublebuffer.hdc, x, y, width, height, color); }
static void BOXA(GAME* Game, int x, int y, int width, int height, COLORREF color)
{
	LINE(Game, x, y, x + width, y, color);
	LINE(Game, x, y, x, y + height, color);
	LINE(Game, x, y + height, x + width, y + height, color);
	LINE(Game, x + width, y, x + width, y + height, color);
}
static void CIRCLE(GAME* Game, int R, int x, int y, COLORREF color) { Circle(Game->Windowhwnd, Game->doublebuffer.hdc, R, x, y, color); }

//显示图片
static void IMG(GAME* Game, const wchar_t* File, int x, int y) { Img(Game->Windowhwnd, Game->doublebuffer.hdc, File, x, y); }
static void IMGA(GAME* Game, const wchar_t* File, int x, int y, int widthbs, int heightbs, COLORREF color) { ImgA(Game->Windowhwnd, Game->doublebuffer.hdc, File, x, y, widthbs, heightbs, color); }

//文字
static void NewTEXT(GAME* Game, LPCWSTR text, int x, int y, COLORREF color) { Text(Game->Windowhwnd, Game->doublebuffer.hdc, x, y, text, color); }
static void NewDIGHT(GAME* Game, int number, int x, int y, COLORREF color) { Dight(Game->Windowhwnd, Game->doublebuffer.hdc, x, y, number, color); }

//--------------------------------------------------------------------------------------游戏工具----------------------------------------------------------------------------------------------------------//

//加载图片
static void ImageLoad(IMAGE* image, LPCWSTR* imagefile, int imagenumber)
{
	if (imagenumber == 1)
	{
		HDC hdcmem;
		BITMAP bitmap;
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, *imagefile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		hdcmem = CreateCompatibleDC(image->image.hdc);
		SelectObject(hdcmem, hBitmap);
		TransparentBlt(image->image.hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcmem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(1,1,1));
		image->lengths.x = bitmap.bmWidth;
		image->lengths.y = bitmap.bmHeight;
		DeleteDC(hdcmem);
		DeleteObject(hBitmap); // 释放位图资源
	}
	else if (imagenumber > 0)
		for (int i = 0; i < imagenumber; i++)
		{
			HDC hdcmem;
			BITMAP bitmap;
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, imagefile[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			GetObject(hBitmap, sizeof(BITMAP), &bitmap);
			hdcmem = CreateCompatibleDC(image[i].image.hdc);
			SelectObject(hdcmem, hBitmap);
			TransparentBlt(image[i].image.hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcmem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(1, 1, 1));
			image[i].lengths.x = bitmap.bmWidth;
			image[i].lengths.y = bitmap.bmHeight;
			DeleteDC(hdcmem);
			DeleteObject(hBitmap); // 释放位图资源
		}
}

//按键检测
static int KEYSTATEbuffer[255];
static int KeyState(int Key)
{
	int state = GetAsyncKeyState(Key);
	if (state & 0x8000)
	{
		if (KEYSTATEbuffer[Key] == 0) { KEYSTATEbuffer[Key] = 1; return 1; }
		return 0;
	}
	else { KEYSTATEbuffer[Key] = 0; return 0; }
}

//按钮控件

//初始化按钮
static void InitialisationButton(BUTTON* button,int x,int y,int width,int height)
{
	button->coord.left = x;
	button->coord.top = y;
	button->coord.right = width;
	button->coord.bottom = height;
}

static int NewButton(GAME* Game, BUTTON* button, int mode, IMAGE buttonimagealpha, IMAGE buttonimagebeta, IMAGE buttonimagegamma)
{
	int out = FALSE, type = FALSE;
	if (Game->MOUSEX > button->coord.left && Game->MOUSEX > button->coord.right + button->coord.left - 1 && Game->MOUSEY > button->coord.top && Game->MOUSEY > button->coord.bottom + button->coord.top - 1)
	{
		type = TRUE;
		out = KeyState(1);
	}
	if (mode)
	{
		if (out && type)TransparentBlt(Game->doublebuffer.hdc, button->coord.left, button->coord.top, buttonimagealpha.lengths.x, buttonimagealpha.lengths.y, buttonimagealpha.image.hdc, 0, 0, buttonimagealpha.lengths.x, buttonimagealpha.lengths.y, RGB(1, 1, 1));
		if (!out && type)TransparentBlt(Game->doublebuffer.hdc, button->coord.left, button->coord.top, buttonimagebeta.lengths.x, buttonimagebeta.lengths.y, buttonimagebeta.image.hdc, 0, 0, buttonimagebeta.lengths.x, buttonimagebeta.lengths.y, RGB(1, 1, 1));
		if (!out && !type)TransparentBlt(Game->doublebuffer.hdc, button->coord.left, button->coord.top, buttonimagegamma.lengths.x, buttonimagegamma.lengths.y, buttonimagegamma.image.hdc, 0, 0, buttonimagegamma.lengths.x, buttonimagegamma.lengths.y, RGB(1, 1, 1));
	}
	return out;
}

//动画控件

//初始化动画
static int InitialisationAnime(ANIME* anime, LPCSTR name, IMAGE* sequenceframes, int timeload, int totalnumber,int width,int height)
{
	anime->Name = name;
	Color(0x07);
	if (totalnumber <= 0) { printf("[InitialisationAnime函数错误]动画序列帧总数有问题,请检查名为[%s]的动画!\n", name); return Error; }
	if (sequenceframes == NULL) { printf("[InitialisationAnime函数错误]动画序列帧有问题,请检查名为[%s]的动画是否存在!\n", name); return Error; }
	anime->animeswitch = 0;
	anime->sequenceframes = sequenceframes;
	anime->totalnumber = totalnumber;
	anime->number = 0;
	for(int i = 0;i<anime->totalnumber;i++)
	{
		anime->sequenceframes[i].lengths.x = width;
		anime->sequenceframes[i].lengths.y = height;
	}
	SetTimeLoad(&(anime->timeload), timeload);		//设置定时器
	return YES;
}

//运行动画
static int RunAnime(GAME* Game, ANIME* anime, int animeswitch, int x, int y, int widthsize, int heightsize)
{
	if (!animeswitch)return 0;
	else 
	{
		anime->number %= anime->totalnumber;
		TransparentBlt(Game->doublebuffer.hdc, x, y, anime->sequenceframes[anime->number].lengths.x * widthsize, anime->sequenceframes[anime->number].lengths.y * heightsize, anime->sequenceframes[anime->number].image.hdc, 0, 0, anime->sequenceframes[anime->number].lengths.x, anime->sequenceframes[anime->number].lengths.y, RGB(1, 1, 1));
	}
	if (TimeLoad(&(anime->timeload), 1)) ++anime->number;	//添加下一帧	
	return anime->number;
}

//简单物理

static void CirclePhysics(CIRCLEPHYSICS* a, CIRCLEPHYSICS* b)
{
	int R = a->R + b->R;
	int L = sqrt(pow(a->coor.x - b->coor.x, 2) + pow(a->coor.y - b->coor.y, 2));
	if ((L <= R))
	{
		double mass = a->mass + b->mass;
		double vectory[4];
		double vectorybuffer[2];
		DOUBLEPOINT vector[2];
		vector[0].x = (a->coor.x - b->coor.x) * 1. / L;
		vector[0].y = (a->coor.y - b->coor.y) * 1. / L;
		vector[1].x = (b->coor.x - a->coor.x) * 1. / L;
		vector[1].y = (b->coor.y - a->coor.y) * 1. / L;
		vectory[0] = sqrt(pow(a->vectory.x, 2) + pow(a->vectory.y, 2));
		vectory[1] = sqrt(pow(b->vectory.x, 2) + pow(b->vectory.y, 2));
		vectory[2] = ((a->mass - b->mass) * vectory[0] + 2 * b->mass * vectory[1]) / mass;
		vectory[3] = ((b->mass - a->mass) * vectory[1] + 2 * a->mass * vectory[0]) / mass;
		a->coor.x += vector[0].x * (R - L) / 2.;
		a->coor.y += vector[0].y * (R - L) / 2.;
		b->coor.x += vector[1].x * (R - L) / 2.;
		b->coor.y += vector[1].y * (R - L) / 2.;
		vectorybuffer[0] = a->vectory.x * vector[1].x + a->vectory.y * vector[1].y;
		vectorybuffer[1] = b->vectory.x * vector[0].x + b->vectory.y * vector[0].y;
		a->vectory.x -= vector[1].x * vectorybuffer[0];
		a->vectory.y -= vector[1].y * vectorybuffer[0];
		b->vectory.x -= vector[0].x * vectorybuffer[1];
		b->vectory.y -= vector[0].y * vectorybuffer[1];
		a->vectory.x += vector[0].x * vectory[2];
		a->vectory.y += vector[0].y * vectory[2];
		b->vectory.x += vector[1].x * vectory[3];
		b->vectory.y += vector[1].y * vectory[3];
	}
	a->coor.x += a->vectory.x;
	a->coor.y += a->vectory.y;
	b->coor.x += b->vectory.x;
	b->coor.y += b->vectory.y;
}

static void InitialisationCircle(CIRCLEPHYSICS* circle, int x, int y, double m, double vx, double vy, int R)
{
	circle->coor.x = x;
	circle->coor.y = y;
	circle->vectory.x = vx;
	circle->vectory.y = vy;
	circle->R = R;
	circle->mass = m;
}

//-----------------------------------------------------------------------------------------3D-------------------------------------------------------------------------------------------------------------//
static void CameraMatrix(CAMERA* camera, float Rx, float Ry, float Rz)
{

	/*
	The results of the math software calculations
	>> Announcement : Welcome to math procedure
	>> Read "matrix.txt"
	>> Var matrixR  = "matrix.txt"->A
	>> Var matrixRy = "matrix.txt"->B
	>> Var matrixRz = "matrix.txt"->C
	>> Var matrixRx = "matrix.txt"->D
	>> Var matrixRc
	>> JudgmentLogic matrixR
	>> No Logic
	>> Var rx="matrix.txt"->rx
	>> Var ry="matrix.txt"->ry
	>> Var rz="matrix.txt"->rz
	>> matrixRc = matrixRy * matrixRx
	>> Print Var matrixRc Standard
	>> matrixRc :
	{
		 cos(ry), sin(ry) * sin(rx), sin(ry) * cos(rx);
			   0,			cos(rx),		  -sin(rx);
		-sin(ry), cos(ry) * sin(rx), cos(ry) * cos(rx);
	}
	>> matrixR = matrixRc * matrixRz
	>> Print Var matrixR Standard
	>> matrixR :
	{
		 cos(ry) * cos(rz)+ sin(ry) * sin(rx) * sin(rz),cos(ry) * -sin(rz)+ sin(ry) * sin(rx) * cos(rz),sin(ry) * cos(rx);
									  cos(rx) * sin(rz),							  cos(rx) * cos(rz),		 -sin(rx);
		-sin(ry) * cos(rz)+ cos(ry) * sin(rx) * sin(rz),sin(ry) * sin(rz) + cos(ry) * sin(rx) * cos(rz),cos(ry) * cos(rx);
	}
	>> Write matrixR to "matrix.txt"->A
	>> Exit
	>> Announcement : Byebye

x and y are the spatial orientation vectors of the camera
Z vectors can be calculated by fork multiplication
	From the x and y directions of the camera, you can define a two-dimensional tensor space that opens up in space, and according to the following matrix transformation,
you can get an orthogonal projection, and then you can get the perspective effect by perspective division, although it is more troublesome than a homogeneous matrix, but it is easier to understand and write code

		matrixA =
		|x.x, y.x|
		|x.y, y.y|
		|x.z, y.z|

		matrixB =
		|x.x, x.y, x.z|
		|y.x, y.y, y.z|

		matrixC =(matrixB * matrixA)^-1

		(matrixB * matrixA)^-1 =
		|y.x * y.x + y.y * y.y + y.z * y.z, -(x.x * y.x + x.y * y.y + x.z * y.z)|
		|-(x.x * y.x + x.y * y.y + x.z * y.z), x.x * x.x + x.y * x.y + x.z * x.z|
		matrix = matrixA * (matrixB * matrixA)^-1 * matrixB

		p = matrix * a

	double matrixA[2][3] =
	{
		{ x.x, x.y, x.z},
		{ y.x, y.y, y.z}
	};

	double matrixB[3][2] =
	{
		{ x.x, y.x},
		{ x.y, y.y},
		{ x.z, y.z}
	};
	*/

	double
		rx = DegRad(Rx),
		ry = DegRad(Ry),
		rz = DegRad(Rz);
	double matrixR[3][3];

	matrixR[0][0] = cos(ry) * cos(rz) + sin(ry) * sin(rx) * sin(rz);
	matrixR[0][1] = -cos(ry) * sin(rz) + sin(ry) * sin(rx) * cos(rz);
	matrixR[0][2] = sin(ry) * cos(rx);
	matrixR[1][0] = cos(rx) * sin(rz);
	matrixR[1][1] = cos(rx) * cos(rz);
	matrixR[1][2] = -sin(rx);
	matrixR[2][0] = -sin(ry) * cos(rz) + cos(ry) * sin(rx) * sin(rz);
	matrixR[2][1] = sin(ry) * sin(rz) + cos(ry) * sin(rx) * cos(rz);
	matrixR[2][2] = cos(ry) * cos(rx);

	double
		buffera = camera->cameravectorx.x * camera->cameravectorx.x + camera->cameravectorx.y * camera->cameravectorx.y + camera->cameravectorx.z * camera->cameravectorx.z,
		bufferb = camera->cameravectory.x * camera->cameravectory.x + camera->cameravectory.y * camera->cameravectory.y + camera->cameravectory.z * camera->cameravectory.z,
		bufferc = -(camera->cameravectorx.x * camera->cameravectory.x + camera->cameravectorx.y * camera->cameravectory.y + camera->cameravectorx.z * camera->cameravectory.z);
	double matrix[3][3];
	matrix[0][0] = (camera->cameravectorx.x * bufferb + camera->cameravectory.x * bufferc) * camera->cameravectorx.x + (camera->cameravectorx.x * bufferc + camera->cameravectory.x * buffera) * camera->cameravectory.x;
	matrix[1][0] = (camera->cameravectorx.y * bufferb + camera->cameravectory.y * bufferc) * camera->cameravectorx.x + (camera->cameravectorx.y * bufferc + camera->cameravectory.y * buffera) * camera->cameravectory.x;
	matrix[2][0] = (camera->cameravectorx.z * bufferb + camera->cameravectory.z * bufferc) * camera->cameravectorx.x + (camera->cameravectorx.z * bufferc + camera->cameravectory.z * buffera) * camera->cameravectory.x;
	matrix[0][1] = (camera->cameravectorx.x * bufferb + camera->cameravectory.x * bufferc) * camera->cameravectorx.y + (camera->cameravectorx.x * bufferc + camera->cameravectory.x * buffera) * camera->cameravectory.y;
	matrix[1][1] = (camera->cameravectorx.y * bufferb + camera->cameravectory.y * bufferc) * camera->cameravectorx.y + (camera->cameravectorx.y * bufferc + camera->cameravectory.y * buffera) * camera->cameravectory.y;
	matrix[2][1] = (camera->cameravectorx.z * bufferb + camera->cameravectory.z * bufferc) * camera->cameravectorx.y + (camera->cameravectorx.z * bufferc + camera->cameravectory.z * buffera) * camera->cameravectory.y;
	matrix[0][2] = (camera->cameravectorx.x * bufferb + camera->cameravectory.x * bufferc) * camera->cameravectorx.z + (camera->cameravectorx.x * bufferc + camera->cameravectory.x * buffera) * camera->cameravectory.z;
	matrix[1][2] = (camera->cameravectorx.y * bufferb + camera->cameravectory.y * bufferc) * camera->cameravectorx.z + (camera->cameravectorx.y * bufferc + camera->cameravectory.y * buffera) * camera->cameravectory.z;
	matrix[2][2] = (camera->cameravectorx.z * bufferb + camera->cameravectory.z * bufferc) * camera->cameravectorx.z + (camera->cameravectorx.z * bufferc + camera->cameravectory.z * buffera) * camera->cameravectory.z;
	for (int i = 0; i < 3; i++)
		for (int o = 0; o < 3; o++)
		{
			camera->matrixR[o][i] = matrixR[o][i];
			camera->matrix[o][i] = matrix[o][i];
		}
}

static void CameraCompute(CAMERA* camera, float Rx, float Ry, float Rz)
{
	CameraMatrix(camera, Rx, Ry, Rz);
	camera->cameravectorx.x = camera->matrixR[0][0] * camera->cameravectorxmo;
	camera->cameravectorx.y = camera->matrixR[1][0] * camera->cameravectorxmo;
	camera->cameravectorx.z = camera->matrixR[2][0] * camera->cameravectorxmo;

	camera->cameravectory.x = camera->matrixR[0][1] * camera->cameravectorymo;
	camera->cameravectory.y = camera->matrixR[1][1] * camera->cameravectorymo;
	camera->cameravectory.z = camera->matrixR[2][1] * camera->cameravectorymo;

	camera->cameranormal.x = camera->cameravectorx.y * camera->cameravectory.z - camera->cameravectorx.z * camera->cameravectory.y;
	camera->cameranormal.y = camera->cameravectorx.z * camera->cameravectory.x - camera->cameravectorx.x * camera->cameravectory.z;
	camera->cameranormal.z = camera->cameravectorx.x * camera->cameravectory.y - camera->cameravectorx.y * camera->cameravectory.x;
}

static POINT2D Point3DDrawing(POINT3D point, CAMERA camera, float L, BOOL orthogonal)
{

	POINT3D cameravectory = camera.cameranormal;
	POINT3D relativecoordinatespointbuffer =
	{
		-point.x + camera.camerapoint.x,
		-point.y + camera.camerapoint.y,
		-point.z + camera.camerapoint.z,
	};
	double direction = (relativecoordinatespointbuffer.x * cameravectory.x + relativecoordinatespointbuffer.y * cameravectory.y + relativecoordinatespointbuffer.z * cameravectory.z) / (sqrt(cameravectory.x * cameravectory.x + cameravectory.y * cameravectory.y + cameravectory.z * cameravectory.z) * sqrt(relativecoordinatespointbuffer.x * relativecoordinatespointbuffer.x + relativecoordinatespointbuffer.y * relativecoordinatespointbuffer.y + relativecoordinatespointbuffer.z * relativecoordinatespointbuffer.z));
	POINT2D EOR = { Error,Error,Error };
	if (direction >= -L)return EOR;

	POINT3D  relativecoordinatespoint = relativecoordinatespointbuffer;
	relativecoordinatespointbuffer.x = relativecoordinatespoint.x * camera.matrix[0][0] + relativecoordinatespoint.y * camera.matrix[1][0] + relativecoordinatespoint.z * camera.matrix[2][0];
	relativecoordinatespointbuffer.y = relativecoordinatespoint.x * camera.matrix[0][1] + relativecoordinatespoint.y * camera.matrix[1][1] + relativecoordinatespoint.z * camera.matrix[2][1];
	relativecoordinatespointbuffer.z = relativecoordinatespoint.x * camera.matrix[0][2] + relativecoordinatespoint.y * camera.matrix[1][2] + relativecoordinatespoint.z * camera.matrix[2][2];

	POINT2D returnpoint =
	{
		 relativecoordinatespointbuffer.x * camera.cameravectorx.x + relativecoordinatespointbuffer.y * camera.cameravectorx.y + relativecoordinatespointbuffer.z * camera.cameravectorx.z ,
		 relativecoordinatespointbuffer.x * camera.cameravectory.x + relativecoordinatespointbuffer.y * camera.cameravectory.y + relativecoordinatespointbuffer.z * camera.cameravectory.z ,
		 0
	};

	if (!orthogonal)
	{
		double pointmo[2] =
		{
			sqrt(relativecoordinatespointbuffer.x * relativecoordinatespointbuffer.x + relativecoordinatespointbuffer.y * relativecoordinatespointbuffer.y + relativecoordinatespointbuffer.z * relativecoordinatespointbuffer.z),
			sqrt(relativecoordinatespoint.x * relativecoordinatespoint.x + relativecoordinatespoint.y * relativecoordinatespoint.y + relativecoordinatespoint.z * relativecoordinatespoint.z)
		};

		returnpoint.Z = sqrt(pointmo[1] * pointmo[1] - pointmo[0] * pointmo[0]);
		returnpoint.x = returnpoint.x / returnpoint.Z * camera.focalLength;
		returnpoint.y = returnpoint.y / returnpoint.Z * camera.focalLength;
		if (returnpoint.Z > 5000)return EOR;
	}
	else returnpoint.Z = 1;
	return returnpoint;
}

#if STARTOpenCL || STARTGPU

static cl_platform_id platformid;
static cl_device_id deviceid;
static cl_context context;
static cl_command_queue commandqueue;
static cl_program program;
static cl_kernel kernel3D;

static const char* STAROpenCL3D =
/*
"__kernel void Point3DDrawing(__global float* pointx, __global float* pointy, __global float* pointz, __global float* cameravectorx, __global float* cameravectory, __global float* camerapoint, __global float* cameramatrix, __global float* returnpointx, __global float* returnpointy, __global float* returnpointz,__global float* focalLength)"
"{"
"	int number=get_global_id(0);"
"	float cameravectorZ[3];"
"	cameravectorZ[0] = cameravectorx[1] * cameravectory[2] - cameravectorx[2] * cameravectory[1];"
"	cameravectorZ[1] = cameravectorx[2] * cameravectory[0] - cameravectorx[0] * cameravectory[2];"
"	cameravectorZ[2] = cameravectorx[0] * cameravectory[1] - cameravectorx[1] * cameravectory[0];"
"	float relativecoordinatespointbuffer[3];"
"	relativecoordinatespointbuffer[0] = - pointx[number] + camerapoint[0];"
"	relativecoordinatespointbuffer[1] = - pointy[number] + camerapoint[1];"
"	relativecoordinatespointbuffer[2] = - pointz[number] + camerapoint[2];"
"	float direction = (relativecoordinatespointbuffer[0] * cameravectorZ[0] + relativecoordinatespointbuffer[1] * cameravectorZ[1] + relativecoordinatespointbuffer[2] * cameravectorZ[2]) / (sqrt(cameravectorZ[0] * cameravectorZ[0] + cameravectorZ[1] * cameravectorZ[1] + cameravectorZ[2] * cameravectorZ[2]) * sqrt(relativecoordinatespointbuffer[0] * relativecoordinatespointbuffer[0] + relativecoordinatespointbuffer[1] * relativecoordinatespointbuffer[1] + relativecoordinatespointbuffer[2] * relativecoordinatespointbuffer[2]));"
"	if(direction >= -.1f){returnpointz[number] = -1; return;}"
"	float relativecoordinatespoint[3];"
"	relativecoordinatespoint[0]= relativecoordinatespointbuffer[0];"
"	relativecoordinatespoint[1]= relativecoordinatespointbuffer[1];"
"	relativecoordinatespoint[2]= relativecoordinatespointbuffer[2];"
"	relativecoordinatespointbuffer[0] = relativecoordinatespoint[0] * cameramatrix[0] + relativecoordinatespoint[1] * cameramatrix[1] + relativecoordinatespoint[2] * cameramatrix[2];"
"	relativecoordinatespointbuffer[1] = relativecoordinatespoint[0] * cameramatrix[3] + relativecoordinatespoint[1] * cameramatrix[4] + relativecoordinatespoint[2] * cameramatrix[5];"
"	relativecoordinatespointbuffer[2] = relativecoordinatespoint[0] * cameramatrix[6] + relativecoordinatespoint[1] * cameramatrix[7] + relativecoordinatespoint[2] * cameramatrix[8];"
"	returnpointx[number] = relativecoordinatespointbuffer[0] * cameravectorx[0] + relativecoordinatespointbuffer[1] * cameravectorx[1] + relativecoordinatespointbuffer[2] * cameravectorx[2];"
"	returnpointy[number] = relativecoordinatespointbuffer[0] * cameravectory[0] + relativecoordinatespointbuffer[1] * cameravectory[1] + relativecoordinatespointbuffer[2] * cameravectory[2];"
"	returnpointz[number] = 0;"
"	float pointmo[2];"
"	pointmo[0] = sqrt(relativecoordinatespointbuffer[0] * relativecoordinatespointbuffer[0] + relativecoordinatespointbuffer[1] * relativecoordinatespointbuffer[1] + relativecoordinatespointbuffer[2] * relativecoordinatespointbuffer[2]);"
"	pointmo[1] = sqrt(relativecoordinatespoint[0] * relativecoordinatespoint[0] + relativecoordinatespoint[1] * relativecoordinatespoint[1] + relativecoordinatespoint[2] * relativecoordinatespoint[2]);"
"	returnpointz[number] = sqrt(pointmo[1] * pointmo[1] - pointmo[0] * pointmo[0]);"
"	returnpointx[number] = returnpointx[number] / returnpointz[number] * *focalLength;"
"	returnpointy[number] = returnpointy[number] / returnpointz[number] * *focalLength;"
"	if (returnpointz[number] > 5000){returnpointz[number] = -1;return;}"
"	return;"
"}"
*/
//point			[x][y][z]
//cameravector	[x.x][x.y][x.z][y.x][y.y][y.z][normal.x][normal.y][normal.z]
//returnpoint	[x][y][Z]
"__kernel void Point3DDrawing(float* point, float* cameravector, float* camerapoint, float* cameramatrix, __global float* returnpoint, float* focalLength)"
"{"
"	int number = get_global_id(0);"
"	float cameravectorZ[3];"
"	cameravectorZ[0] = cameravector[6];"
"	cameravectorZ[1] = cameravector[7];"
"	cameravectorZ[2] = cameravector[8];"
"	float relativecoordinatespointbuffer[3];"
"	relativecoordinatespointbuffer[0] = - point[number * 3] + camerapoint[0];"
"	relativecoordinatespointbuffer[1] = - point[number * 3 + 1] + camerapoint[1];"
"	relativecoordinatespointbuffer[2] = - point[number * 3 + 2] + camerapoint[2];"
"	float direction = (relativecoordinatespointbuffer[0] * cameravectorZ[0] + relativecoordinatespointbuffer[1] * cameravectorZ[1] + relativecoordinatespointbuffer[2] * cameravectorZ[2]) / (sqrt(cameravectorZ[0] * cameravectorZ[0] + cameravectorZ[1] * cameravectorZ[1] + cameravectorZ[2] * cameravectorZ[2]) * sqrt(relativecoordinatespointbuffer[0] * relativecoordinatespointbuffer[0] + relativecoordinatespointbuffer[1] * relativecoordinatespointbuffer[1] + relativecoordinatespointbuffer[2] * relativecoordinatespointbuffer[2]));"
"	if(direction >= -.1f){returnpoint[number * 3 + 2] = -1; return;}"
"	float relativecoordinatespoint[3];"
"	relativecoordinatespoint[0] = relativecoordinatespointbuffer[0];"
"	relativecoordinatespoint[1] = relativecoordinatespointbuffer[1];"
"	relativecoordinatespoint[2] = relativecoordinatespointbuffer[2];"
"	relativecoordinatespointbuffer[0] = relativecoordinatespoint[0] * cameramatrix[0] + relativecoordinatespoint[1] * cameramatrix[1] + relativecoordinatespoint[2] * cameramatrix[2];"
"	relativecoordinatespointbuffer[1] = relativecoordinatespoint[0] * cameramatrix[3] + relativecoordinatespoint[1] * cameramatrix[4] + relativecoordinatespoint[2] * cameramatrix[5];"
"	relativecoordinatespointbuffer[2] = relativecoordinatespoint[0] * cameramatrix[6] + relativecoordinatespoint[1] * cameramatrix[7] + relativecoordinatespoint[2] * cameramatrix[8];"
"	returnpoint[number * 3] = relativecoordinatespointbuffer[0] * cameravector[0] + relativecoordinatespointbuffer[1] * cameravector[1] + relativecoordinatespointbuffer[2] * cameravector[2];"
"	returnpoint[number * 3 + 1] = relativecoordinatespointbuffer[0] * cameravector[3] + relativecoordinatespointbuffer[1] * cameravector[4] + relativecoordinatespointbuffer[2] * cameravector[5];"
"	returnpoint[number * 3 + 2] = 0;"
"	float pointmo[2];"
"	pointmo[0] = sqrt(relativecoordinatespointbuffer[0] * relativecoordinatespointbuffer[0] + relativecoordinatespointbuffer[1] * relativecoordinatespointbuffer[1] + relativecoordinatespointbuffer[2] * relativecoordinatespointbuffer[2]);"
"	pointmo[1] = sqrt(relativecoordinatespoint[0] * relativecoordinatespoint[0] + relativecoordinatespoint[1] * relativecoordinatespoint[1] + relativecoordinatespoint[2] * relativecoordinatespoint[2]);"
"	returnpoint[number * 3 + 2] = sqrt(pointmo[1] * pointmo[1] - pointmo[0] * pointmo[0]);"
"	returnpoint[number * 3] = returnpoint[number * 3] / returnpoint[number * 3 + 2] * *focalLength;"
"	returnpoint[number * 3 + 1] = returnpoint[number * 3 + 1] / returnpoint[number * 3 + 2] * *focalLength;"
"	if (returnpoint[number * 3 + 2] > 5000){returnpoint[number * 3 + 2] = -1;return;}"
"	return;"
"}"
;

//---------------------------------------------------------------------------------------------以下为OpenGL内容------------------------------------------------------------------------------------------------------//

static void SetOpenGL(HWND hwnd, OPENGL* opengl, int width, int height)
{
	HDC hdc;
	HGLRC hrc;
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32, // 颜色深度
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		24, // 深度缓冲区
		8,  // 模板缓冲区
		0, 
		PFD_MAIN_PLANE, 
		0, 0, 0
	};

	hdc = GetDC(hwnd);
	int pixelformat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelformat, &pfd);
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	// 设置视口和正交投影
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	opengl->hdc = hdc;
	opengl->hrc = hrc;
	opengl->width = width;
	opengl->height = height;
}

//绘制画面
static void RunOpenGL(HDC hdc)
{
	SwapBuffers(hdc);
	glClear(GL_COLOR_BUFFER_BIT);
}

static void DeletOPENGL(OPENGL opengl)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(opengl.hrc);
}
//---------------------------------------------------------------------------------------------以下为具体渲染内容------------------------------------------------------------------------------------------------------//

static void SurfaceDrawingGPU(GAME* Game, CAMERA camera, SURFACE surface, float L)
{

}
#endif

static void SurfaceDrawing(GAME* Game, CAMERA camera, SURFACE surface, float L)
{
	POINT2D screencoord[3] = { 0 };
	for (int i = 0; i < 3; i++)screencoord[i] = Point3DDrawing(surface.vertex[i], camera, L, FALSE);
	if (screencoord[0].Z >= -L && screencoord[1].Z >= -L && screencoord[2].Z >= -L)return;
}

//--------------------------------------------------------------------------------------对象注册----------------------------------------------------------------------------------------------------------//
//对象需要是一个结构体数组,在GAME结构体里指定对象类型索引进行注册然后通过GAME结构体统一调用
static int CreateEntityIndex(GAME* Game, void* arrentity, char* nameid,int length)
{
	int index = NOTFOUND;
	int hash = Hash(nameid) % ENTITYNUMBER;
	if (Game->entityindex[hash].entityindex == NULL)
	{
		if (hash != Error)
		{
			index = hash;
			Game->entityindex[index].entityindex = arrentity;
			Game->entityindex[index].nameid = nameid;
			Game->entityindex[index].length = length;
		}
		else printf("非法的字符串[%s],无法通过这个字符串得到哈希值", nameid);
	}
	else
	{
		printf("字符串[%s]导致的哈希冲突，请换一个名字", nameid);
		index = NOTFOUND;
	}
	return index;
}

//--------------------------------------------------------------------------------------游戏流程----------------------------------------------------------------------------------------------------------//

//初始化游戏
static void InitialisationGame(GAME* Game, LPCWSTR name, int x, int y, int width, int height, int timeload, int fullscreenmode, BOOL cmdswitch, BOOL cursor)
{
	//初始化结构体
	if (y < 0) Game->Windowhwnd = Window((HWND)NULL, name, width, height, (nScreenWidth - width) / 2, (nScreenheight - height) / 2);		//创建窗口	
	else Game->Windowhwnd = Window((HWND)NULL, name, width, height, x, y);
	Game->Name = name;						//窗口名字
	switch (fullscreenmode)					//如果全屏则不变
	{
	case 0:
		Game->Windowwidth = width;		//窗口宽度
		Game->Windowheight = height;	//窗口高度
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
	SetTimeLoad(&Game->fps, 1000);						//控制帧率
	for (int i = 0; i < ENTITYNUMBER; i++)
	{
		Game->entityindex[i].entityindex = NULL;
		Game->entityindex[i].nameid = NULL;
		Game->entityindex[i].length = NULL;
	}
#if STARTOpenCL || STARTGPU
	cl_int error;
	clGetPlatformIDs(1, &platformid, NULL);
	clGetDeviceIDs(platformid, CL_DEVICE_TYPE_GPU, 1, &deviceid, NULL);
	context = clCreateContext(NULL, 1, &deviceid, NULL, NULL, NULL);
	commandqueue = clCreateCommandQueue(context, deviceid, NULL, NULL);
	program = clCreateProgramWithSource(context, 1, (const char**)&STAROpenCL3D, NULL, &error);
	clBuildProgram(program, 1, &deviceid, NULL, NULL, NULL);
	kernel3D = clCreateKernel(program, "Point3DDrawing", NULL);
#endif
	Game->fpsmax = 0;
	Game->fpsmax2 = 0;
}

//游戏画面绘制
extern void GameDrawing(GAME* Game);

//游戏逻辑绘制
extern void GameLogic(GAME* Game);

//逻辑线程
static CREATTHREAD GAMELOGIC;
static GAME* GAMETHEARDLOGIC;

//游戏逻辑线程
static THREAD GameThreadLogic(LPARAM lparam)
{
	printf("[star engine logic进入成功!]\n");
	while (!GAMETHEARDLOGIC->GAMEDEAD)
	{
		GameLogic(GAMETHEARDLOGIC);												//游戏逻辑计算
		GAMETHEARDLOGIC->GAMEINPUT = HardwareDetection();										//按键检测
		GAMETHEARDLOGIC->MOUSEX = MouseX(GAMETHEARDLOGIC->Windowhwnd);
		GAMETHEARDLOGIC->MOUSEY = MouseY(GAMETHEARDLOGIC->Windowhwnd);
		if (GAMETHEARDLOGIC->escswitch && GetAsyncKeyState(VK_ESCAPE))GAMETHEARDLOGIC->GAMEDEAD = 1;	//是否启用esc退出游戏
		if (!IsWindow(GAMETHEARDLOGIC->Windowhwnd))GAMETHEARDLOGIC->GAMEDEAD = 1;//检查窗口是否存活
	}
	return 0;
}
//游戏循环
static void GameLoop(GAME* Game, BOOL esc, void(*GameSetting)(GAME* Game))
{
	
	GAMETHEARDLOGIC = Game;
	Game->escswitch = esc;
	srand((unsigned)time(NULL));
	GetAsyncKeyState(VK_ESCAPE);
	RunThread((THREAD*)GameThreadLogic, GAMELOGIC.ID);
	HDC hdc = GetDC(Game->Windowhwnd);
	GameSetting(Game);
	while (!Game->GAMEDEAD)
	{
		if (!TimeLoad(&Game->fps, 1))Game->fpsmax++;
		else { Game->fpsmax2 = Game->fpsmax; Game->fpsmax = 0; }
		if (!Game->GAMEPOWER)if (!TimeLoad(&(Game->timeload), 1))Sleep(Game->timeload.timeload);
		BoxB(0, Game->doublebuffer.hdc, 0, 0, Game->Windowwidth, Game->Windowheight, RGB(0, 0, 0));		 //清除双缓冲屏幕画面
		GameDrawing(Game);
		Text(0, Game->doublebuffer.hdc, 0, 0, L"FPS:", RGB(0, 150, 0));
		NewDIGHT(Game, Game->fpsmax2, 30, 0, RGB(0, 150, 0));
		BitBlt(hdc, 0, 0, Game->Windowwidth, Game->Windowheight, Game->doublebuffer.hdc, 0, 0, SRCCOPY); //通过双缓冲绘制到屏幕上
		ClearWindow();								 //消息循环
	}
	printf("[star Game Loop 结束!]\n");
}

//游戏结束
static void GameOver(GAME* Game, BOOL cmdswitch)
{
	printf("[star Game Over进入成功!]\n");
	DeletThread(GAMELOGIC.ThreadHwnd);									//清理逻辑线程
	DeletBuffer(Game->doublebuffer.hBitmap, Game->doublebuffer.hdc);	//销毁双缓冲资源
	DeletWindow(Game->Windowhwnd);										//删除游戏窗口
	if (cmdswitch)CMD(ON);												//是否在游戏结束时恢复控制台窗口
#if STARTOpenCL || STARTGPU
	clReleaseProgram(program);
	clReleaseDevice(deviceid);
	clReleaseContext(context);
#endif
	printf("游戏资源清理完成!");
}
