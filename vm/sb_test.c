#include <windows.h>

LRESULT CALLBACK WindowProc(_In_ HWND hwnd,
			    _In_ UINT uMsg,
			    _In_ WPARAM wParam,
			    _In_ LPARAM lParam
			    );
			    

int CALLBACK
WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
  WNDCLASS WindowClass = {};
  WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  WindowClass.lpfnWndProc = ;
  WindowClass.hInstance = hInstance;
  WindowClass.lpszClassName = "KILELINWINTest";

  return(0);
}


