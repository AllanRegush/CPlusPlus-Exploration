#include <windows.h>


LRESULT CALLBACK
Win32MainWindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;
    switch (Message)
    {
        case WM_SIZE:
        {
        } break;
        case WM_DESTROY:
        {
	        PostQuitMessage(0);
        } break;
        case WM_PAINT:
        {
	        RECT Rect;
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
	        GetClientRect(Window, &Rect);
	        DrawTextA(DeviceContext, "Hello, World", -1, &Rect,
		              DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(Window, &Paint);
        } break;
        default:
        {
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }
    return Result;
}

int CALLBACK
WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowCode)
{
	WNDCLASS WindowClass = {};
	WindowClass.style         = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc   = Win32MainWindowCallback;
	WindowClass.hInstance     = Instance;
	WindowClass.lpszClassName = "HelloWorldClass";

	if (RegisterClass(&WindowClass))
	{
		HWND Window = CreateWindowEx(0,
					     WindowClass.lpszClassName,
					     "HelloApp",
				 	     WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	         			 CW_USEDEFAULT,
					     CW_USEDEFAULT,
				      	 CW_USEDEFAULT,
					     CW_USEDEFAULT,
					     0,
					     0,
					     Instance,
					     0);

		if (Window)
		{

			MSG Message;
			while (GetMessage(&Message, 0, 0, 0))
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else
		{
		}
	}
	else
	{
		MessageBoxA(0, "Could not get window", "HelloApp", MB_ICONERROR);
	}

	return 0;
}
