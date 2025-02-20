#include <windows.h>
#include <cstdio>
const int SCREEN_WIDTH = 250;
const int SCREEN_HEIGHT = 200;
HWND textfield, num1Box, num2Box, plusButton, minusButton, timesButton, dividedButton;
char num1Saved[20], num2Saved[20], result[20];
double num1, num2, resultNum;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		case WM_CREATE: 
			textfield = CreateWindow("STATIC",
									"    Please input two numbers",
									WS_VISIBLE|WS_CHILD,
									20,10,200,20,
									hwnd,NULL,NULL,NULL);
			plusButton = CreateWindow("BUTTON",
									"+",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									20,80,200,20,
									hwnd,(HMENU) 1,NULL,NULL);
			minusButton = CreateWindow("BUTTON",
									"-",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									20,100,200,20,
									hwnd,(HMENU) 2,NULL,NULL);
			timesButton = CreateWindow("BUTTON",
									"*",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									20,120,200,20,
									hwnd,(HMENU) 3,NULL,NULL);
			dividedButton = CreateWindow("BUTTON",
									"/",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									20,140,200,20,
									hwnd,(HMENU) 4,NULL,NULL);
			num1Box = CreateWindow("EDIT",
									"",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									20,40,90,30,
									hwnd,NULL,NULL,NULL);
			num2Box = CreateWindow("EDIT",
									"",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									130,40,90,30,
									hwnd,NULL,NULL,NULL);
			break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1: 
                    GetWindowText(num1Box, num1Saved, 20);
                    GetWindowText(num2Box, num2Saved, 20);
                    
                    num1 = atof(num1Saved); 
                    num2 = atof(num2Saved); 
                    resultNum = num1 + num2;
                    sprintf(result, "%lf", resultNum); 
                    
                    MessageBox(hwnd, result, "Result", MB_OK);
                    break;

                case 2: 
                    GetWindowText(num1Box, num1Saved, 20);
                    GetWindowText(num2Box, num2Saved, 20);
                    
                    num1 = atof(num1Saved); 
                    num2 = atof(num2Saved); 
                    resultNum = num1 - num2;
                    sprintf(result, "%lf", resultNum); 
                    
                    MessageBox(hwnd, result, "Result", MB_OK);
                    break;

                case 3:
                    GetWindowText(num1Box, num1Saved, 20);
                    GetWindowText(num2Box, num2Saved, 20);
                    
                    num1 = atof(num1Saved); 
                    num2 = atof(num2Saved); 
                    resultNum = num1 * num2; 
                    sprintf(result, "%lf", resultNum); 
                    
                    MessageBox(hwnd, result, "Result", MB_OK);
                    break;

                case 4: 
                    GetWindowText(num1Box, num1Saved, 20);
                    GetWindowText(num2Box, num2Saved, 20);
                    
                    num1 = atof(num1Saved); 
                    num2 = atof(num2Saved); 
                    
                    if (num2 == 0) { 
                        MessageBox(hwnd, "Error", "Error", MB_OK | MB_ICONERROR);
                    } else {
                        resultNum = num1 / num2; 
                        sprintf(result, "%lf", resultNum);
                        MessageBox(hwnd, result, "Result", MB_OK);
                    }
                    break;
            }
            break;

		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+25);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU, //irresizeable
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		SCREEN_WIDTH, /* width */
		SCREEN_HEIGHT, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
