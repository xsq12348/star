//This Star's DLC
//Creat Time:2025/6/16
#if STARDLC
#include"star.h"
#else
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
#endif
//In order to expand the CPP functionality in the future, DLC is now availables
// In order to prevent the Star function from being redefined, you can freely choose whether to add the Star library by defining the STARDLC macro
// If you decide to use StarEngine, do not define STARDLC macros
// Don't worry about the error
//Version number:0.1

#define CREATWNDPROC static LRESULT WINAPI
#define WNDPROCEND (HWND hwnd, UINT msgid, WPARAM wparam, LPARAM lparam){return DefWindowProc(hwnd, msgid, wparam, lparam);}
//��������
static HWND NewWindow(
    WNDPROC WndPorc,
    HWND hwnd	 /*���*/,
    LPCWSTR name /*��������*/,
    int w		 /*���ڿ��*/,
    int h		 /*���ڸ߶�*/,
    int x		 /*����ˮƽ����*/,
    int y		 /*������ֱ����*/
)
{
    HINSTANCE hinstance = GetModuleHandle(NULL);
    //ע�ᴰ����
    WNDCLASS wndclass = { 0 };
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(4);    //��ȡ��ˢ ��䱳��
    wndclass.hCursor = NULL;                               //���ָ��
    wndclass.hIcon = NULL;                                 //ϵͳĬ��ͼ��
    //������
    wndclass.hInstance = hinstance;
    wndclass.lpfnWndProc = WndPorc;
    wndclass.lpszClassName = TEXT("main");                 //����
    wndclass.lpszMenuName = NULL;                          //�˵�
    //������ʽ
    wndclass.style = CS_HREDRAW | CS_CLASSDC;
    RegisterClass(&wndclass);
    hwnd = CreateWindow(TEXT("main"), name/*����*/, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, x, y, w, h, NULL, NULL, hinstance, NULL);    //��������
    //��ʾ����
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}