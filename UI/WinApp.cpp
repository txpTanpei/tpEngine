#include"include.h"



WinApp::WinApp(HINSTANCE hInst) : _hInst(hInst), m_nWidth(800),
       m_nHeight(600),_hwnd(0)
{
	//create win32 window
	//1.register window

	WNDCLASSEX wndClass;
	memset(&wndClass, 0, sizeof(wndClass));
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wndClass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(_hInst,IDC_ARROW);

	wndClass.lpszClassName = _T("WinApp");
	wndClass.lpfnWndProc = wndProc;
	wndClass.hIcon = 0;
	wndClass.lpszMenuName = 0;

	RegisterClassEx(&wndClass);
	m_pOpenGL = NULL;
}

WinApp::~WinApp()
{
	if (m_pOpenGL)
	{
		m_pOpenGL->destory();
		delete m_pOpenGL;
		m_pOpenGL = NULL;
	}
	//cancel register
	UnregisterClass(_T("WinApp"), _hInst);
}


LRESULT CALLBACK WinApp::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WinApp* pThis = (WinApp*)(GetWindowLong(hWnd, GWL_USERDATA));
	if (pThis)
	{
		pThis->onEvent(hWnd,msg,wParam,lParam);
	}
	if (WM_CREATE == msg)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		SetWindowLong(hWnd, GWL_USERDATA, (DWORD_PTR)pCreate->lpCreateParams);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);

}
LRESULT WinApp::onEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:

		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_LBUTTONUP:

		break;
	case WM_RBUTTONDOWN:

		break;
	case WM_RBUTTONUP:

		break;
	case WM_KEYDOWN:
	{
		//键盘具体按下了那个键
		switch (wParam)
		{
		case VK_LEFT:

			break;
		default:
			break;
		}
		break;
	}
	case WM_KEYUP:
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return S_OK;
}

int WinApp::main(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;

	//create window
	_hwnd = CreateWindow(_T("WinApp"), _T("WinApp"), WS_OVERLAPPEDWINDOW, 0, 0, width, height, 0, 0, _hInst, this);
	
	if (_hwnd == 0)
	{
		return -1;
	}
	//update window
	UpdateWindow(_hwnd);
	m_pOpenGL = new OpenGL(_hwnd);
	if (!m_pOpenGL->initOpenGL(m_nWidth, m_nHeight))
	{
		return false;
	}
	

	ShowWindow(_hwnd, SW_NORMAL);

	MSG msg = {0};
	while (msg.message != WM_QUIT)
	{
		if (msg.message == WM_DESTROY || msg.message == WM_CLOSE)
		{
			break;
		}

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Sleep(1);
		m_pOpenGL->render();
	}

	return 0;
}
