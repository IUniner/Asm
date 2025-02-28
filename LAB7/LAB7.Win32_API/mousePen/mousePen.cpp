﻿









#include "stdafx.h"
#include "mousePen.h"

#define MAX_LOADSTRING 100	

// Global Variables:
HINSTANCE hInst;                       // current instance
TCHAR szTitle[MAX_LOADSTRING];         // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];   // the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
COLORREF GetPenColor(int);
void ClearScreen(HWND, HDC);

int nCount = 0;
int startX[1000];
int startY[1000];
int endX[1000];
int endY[1000];
COLORREF PenColors[1000];
COLORREF PenColor = RGB(255,0,0);

RECT mapRect;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MOUSE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOUSE));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOUSE));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MOUSE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HPEN oldPen;
	HPEN pen;
	HDC hdc;// = GetDC(hWnd);
	int wmId, wmEvent;
	switch (message)
	{
	case WM_CREATE:
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{	
		case CLEAR_SCREEN:
			ClearScreen(hWnd,hdc);
			break;
		case COLOR_PEN_BLACK:
			PenColor = RGB(0, 0, 0);
			break;
		case COLOR_PEN_RED:
			PenColor = RGB(255, 0, 0);
			break;
		case COLOR_PEN_BLUE:
			PenColor = RGB(0, 0, 255);
			break;
		case COLOR_PEN_GREEN:
			PenColor = RGB(0, 255, 0);
			break;
		case COLOR_PEN_YELLOW:
			PenColor = RGB(255, 255, 0);
			break;
		case COLOR_PEN_PINK:
			PenColor = RGB(255, 20, 147);
			break;
		case COLOR_PEN_PURPLE:
			PenColor = RGB(128, 0, 128);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			ReleaseDC(hWnd, hdc); // освобождаем контекст
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
	{
		if (nCount < 1000)
		{
			int xPos = LOWORD(lParam);
			int yPos = HIWORD(lParam);

			startX[nCount] = xPos;
			startY[nCount] = yPos;
			PenColors[nCount] = PenColor;
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (nCount < 1000)
		{
			int xPos = LOWORD(lParam);
			int yPos = HIWORD(lParam);

			endX[nCount] = xPos;
			endY[nCount] = yPos;
			PenColors[nCount] = PenColor;
			RECT lastRect;
			lastRect.left = min(startX[nCount], endX[nCount]) - 1;
			lastRect.right = max(startX[nCount], endX[nCount]) + 1;
			lastRect.top = min(startY[nCount], endY[nCount]) - 1;
			lastRect.bottom = max(startY[nCount], endY[nCount]) + 1;
			nCount++;
			InvalidateRect(hWnd, &lastRect, TRUE);
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = GetDC(hWnd);
		if (hdc)
		{
			for (int i = 0,br = 1; i < nCount; i++)
			{
				pen = CreatePen(PS_SOLID, 1, PenColors[i]);
				oldPen = (HPEN)SelectObject(hdc, pen);
				MoveToEx(hdc, startX[i], startY[i], NULL);
				LineTo(hdc, endX[i], endY[i]);	
				SelectObject(hdc, oldPen);
				DeleteObject(pen);
			}		
			
		}
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_DESTROY:
		ReleaseDC(hWnd, hdc); // освобождаем контекст
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void ClearScreen(HWND hWnd,HDC hdc) 
{
	hdc = GetDC(hWnd);
	HPEN pen = CreatePen(PS_SOLID, 50, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	//Rectangle(hdc, 0, 0, 5000, 5000);		
	//FloodFill(hdc, 1, 1, RGB(255, 255, 255));
	for(;nCount>=0;--nCount)
	{		
		MoveToEx(hdc, startX[nCount], startY[nCount], NULL);
		LineTo(hdc, endX[nCount], endY[nCount]);
	}
	SelectObject(hdc, oldPen);
	DeleteObject(pen);
	ReleaseDC(hWnd, hdc);
}