#include"include.h"

int CALLBACK _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevinst, LPTSTR lpCmdLine, int nShowCmd)
{
	WinApp app(hInstance);
	app.main(800, 600);

	return 0;
}
