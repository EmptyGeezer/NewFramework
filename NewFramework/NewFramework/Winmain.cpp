#include<Windows.h>

bool GenerateWindows(HINSTANCE hInstance, int nCmdShow, LPCSTR ClassName, LPCSTR WindowsTitle, int width, int height);				//Generate Windows without locating it on the monitor
bool GenerateWindows(HINSTANCE hInstance, int nCmdShow, LPCSTR ClassName, LPCSTR WindowsTitle,int x, int y, int width, int height);  //Generate Windows and locate it on the monitor

//Manage Messages
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//WinMain function set up a windows instance and enter a message loop
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (GenerateWindows(hInstance, nCmdShow, "Win32Windows", "Don't_Give_Up", 1280, 720))
	{
		MSG msg;
		while (true)
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // Lấy message, dịch và gửi nó 
			{
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT) // nếu message là quit thì break vòng while
			{
				break;
			}
			else
			{
				//Update(), Draw your game
			}
			
		}
		return msg.wParam;
	}
	return 0;
}

bool GenerateWindows(HINSTANCE hInstance, int nCmdShow, LPCSTR ClassName, LPCSTR WindowsTitle, int width, int height)
{
	return GenerateWindows(
		hInstance,
		nCmdShow,
		ClassName,
		WindowsTitle,
		(GetSystemMetrics(SM_CXSCREEN)) - width,
		(GetSystemMetrics(SM_CYSCREEN)) - height,
			width,
			height);
}

bool GenerateWindows(HINSTANCE hInstance, int nCmdShow, LPCSTR ClassName, LPCSTR WindowsTitle, int x, int y, int width, int height)
{
	HWND hWnd;
	
	WNDCLASSEX wcex;

	// Set up data for Windows
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WinProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = ClassName;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	//If set up fail, return false
	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	//set up successful -> CreateWindows -> return true
	hWnd = CreateWindowEx(NULL, ClassName, WindowsTitle, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	return true;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
