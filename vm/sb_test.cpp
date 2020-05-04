#include <windows.h>
#include <cstdio>
LRESULT CALLBACK MainWindowCallback(HWND hwnd,
			    UINT uMsg,
			    WPARAM wParam,
			    LPARAM lParam)
{
  LRESULT result = 0;
  switch(uMsg){
    case WM_SIZE:{
      OutputDebugStringA("WM_SIZE\n");
      printf("WM_SIZE\n");
    }break;
    case WM_DESTROY:{
      OutputDebugStringA("WM_DESTROY\n");
      printf("WM_DESTROY\n");
    }break;
    case WM_CLOSE:{
       OutputDebugStringA("WM_CLOSE\n");
      printf("WM_CLOSE\n");
    }break;
    case WM_ACTIVATEAPP:{
       OutputDebugStringA("WM_ACTIVATEAPP\n");
      printf("WM_ACTIVATEAPP\n");
    }break;
    case WM_PAINT:{
      PAINTSTRUCT Paint;
      HDC DeviceContext = BeginPaint(hwnd,&Paint);
      int X = Paint.rcPaint.left;
      int Y = Paint.rcPaint.top;
      int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
      int Width = Paint.rcPaint.right - Paint.rcPaint.left;
      PatBlt(DeviceContext,X,Y,Width,Height,WHITENESS);
      EndPaint(hwnd,&Paint);
    }break;
    default:{
      result = DefWindowProc(hwnd,uMsg,wParam,lParam);
    }break;
  }
  return(result);
}
int CALLBACK
WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
  WNDCLASS WindowClass = {};
  WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  WindowClass.lpfnWndProc = MainWindowCallback;
  WindowClass.hInstance = hInstance;
  WindowClass.lpszClassName = "KILELINWINTest";

  if(RegisterClass(&WindowClass)){
    HWND WindowHandle = CreateWindowEx(
				       0,
				       WindowClass.lpszClassName,
				       "KILE Prac",
				       WS_OVERLAPPEDWINDOW|WS_VISIBLE,
				       CW_USEDEFAULT,
				       CW_USEDEFAULT,
				       CW_USEDEFAULT,
				       CW_USEDEFAULT,
				       0,
				       0,
				       hInstance,
				       0);
    if(WindowHandle){
      for(;;){
	MSG Message;
	BOOL MessageResult = GetMessage(&Message,0,0,0);
	if(MessageResult > 0){
	  TranslateMessage(&Message);
	  DispatchMessage(&Message);
	}else{
	  break;
	}
      }
    }else{
    }
  }else{ 
  }
  return(0);
}


