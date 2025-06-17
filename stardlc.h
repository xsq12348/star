//This Star's DLC
//Creat Time:2025/6/16
#if STARDLC
#include"star.h"
int KEYSTATEbuffer[255];
int KeyState(int Key)
{
    int state = GetAsyncKeyState(Key);
    if (state & 0x8000)
    {
        if (KEYSTATEbuffer[Key] == 0) { KEYSTATEbuffer[Key] = 1; return 1; }
        return 0;
    }
    else { KEYSTATEbuffer[Key] = 0; return 0; }
}
#else
#endif
//In order to expand the CPP functionality in the future, DLC is now availables
// In order to prevent the Star function from being redefined, you can freely choose whether to add the Star library by defining the STARDLC macro
// If you decide to use StarEngine, do not define STARDLC macros
// Don't worry about the error
//Version number:0.1

#define CREATWNDPROC static LRESULT WINAPI
#define WNDPROCEND (HWND hwnd, UINT msgid, WPARAM wparam, LPARAM lparam){return DefWindowProc(hwnd, msgid, wparam, lparam);}
//创建窗口
static HWND NewWindow(
    WNDPROC WndPorc,
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
    wndclass.hbrBackground = (HBRUSH)GetStockObject(4);    //获取笔刷 填充背景
    wndclass.hCursor = NULL;                               //鼠标指针
    wndclass.hIcon = NULL;                                 //系统默认图标
    //程序句柄
    wndclass.hInstance = hinstance;
    wndclass.lpfnWndProc = WndPorc;
    wndclass.lpszClassName = TEXT("main");                 //类名
    wndclass.lpszMenuName = NULL;                          //菜单
    //窗口样式
    wndclass.style = CS_HREDRAW | CS_CLASSDC;
    RegisterClass(&wndclass);
    hwnd = CreateWindow(TEXT("main"), name/*标题*/, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, x, y, w, h, NULL, NULL, hinstance, NULL);    //创建窗口
    //显示窗口
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}
