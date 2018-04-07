#ifndef __WINAPP_H__
#define __WINAPP_H__

#include<Windows.h>

class OpenGL;

class WinApp
{
public:
	WinApp(HINSTANCE hInst);
	~WinApp();

	static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

	int main(int width, int height);
	LRESULT onEvent(HWND, UINT, WPARAM, LPARAM);
private:
	//´°¿Ú¾ä±ú
	HWND _hwnd;
	HINSTANCE _hInst;

	int m_nWidth;
	int m_nHeight;
	OpenGL *m_pOpenGL;
};


#endif // !__WINAPP_H__


