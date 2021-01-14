//#include "stdafx.h"
//#include "mousePen.h"
//
//#define MAX_LOADSTRING 100			
//
// Global Variables:
//HINSTANCE hInst;                       // current instance
//TCHAR szTitle[MAX_LOADSTRING];         // The title bar text
//TCHAR szWindowClass[MAX_LOADSTRING];   // the main window class name
//
// Forward declarations of functions included in this code module:
//ATOM				MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
//LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//void AddControls(HWND);
//COLORREF GetPenColor(int);
//
//int nCount = 0;
//int startX[1000];
//int startY[1000];
//int endX[1000];
//int endY[1000];
//int nTextLen = 0;
//TCHAR text[20];
//
//RECT mapRect;
//
//bool needRefresh = true;
//bool isEraser = false;
//
//int type = PEN;
//int penWidth = PEN_NORMAL;
//
//HWND firstFillCombobox;
//HWND secondFillCombobox;
//HWND penColorCombobox;
//HWND eraser;
//
//int APIENTRY _tWinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPTSTR    lpCmdLine,
//	int       nCmdShow)
//{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
//	 TODO: Place code here.
//	MSG msg;
//	HACCEL hAccelTable;
//
//	 Initialize global strings
//	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadString(hInstance, IDC_MOUSE, szWindowClass, MAX_LOADSTRING);
//	MyRegisterClass(hInstance);
//
//	 Perform application initialization:
//	if (!InitInstance(hInstance, nCmdShow))
//	{
//		return FALSE;
//	}
//
//	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOUSE));
//
//	 Main message loop:
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//
//	return (int)msg.wParam;
//}
//
//
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
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInstance;
//	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOUSE));
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MOUSE);
//	wcex.lpszClassName = szWindowClass;
//	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//	return RegisterClassEx(&wcex);
//}
//
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
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//	HWND hWnd;
//
//	hInst = hInstance; // Store instance handle in our global variable
//
//	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
//
//	if (!hWnd)
//	{
//		return FALSE;
//	}
//
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	return TRUE;
//}
//
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
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT ps;
//	HDC hdc;
//	int wmId, wmEvent;
//	switch (message)
//	{
//	case WM_CREATE:
//		AddControls(hWnd);
//	case WM_COMMAND:
//		wmId = LOWORD(wParam);
//		wmEvent = HIWORD(wParam);
//		 Parse the menu selections:
//		switch (wmId)
//		{
//		case CLEAR_SCREEN:
//			needRefresh = true;
//			InvalidateRect(hWnd, &mapRect, FALSE);
//			break;
//		case SET_PEN_TYPE:
//			type = PEN;
//			if (isEraser)
//			{
//				SendMessage(eraser, BM_SETCHECK, BST_UNCHECKED, 0L);
//				isEraser = false;
//			}
//			break;
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//		break;
//	case WM_LBUTTONDOWN:
//	{
//		if (nCount < 1000)
//		{
//			int xPos = LOWORD(lParam);
//			int yPos = HIWORD(lParam);
//
//			startX[nCount] = xPos;
//			startY[nCount] = yPos;
//		}
//
//	}
//	break;
//	case WM_LBUTTONUP:
//	{
//		if (nCount < 1000)
//		{
//			int xPos = LOWORD(lParam);
//			int yPos = HIWORD(lParam);
//
//			endX[nCount] = xPos;
//			endY[nCount] = yPos;
//			RECT lastRect;
//			lastRect.left = min(startX[nCount], endX[nCount]) - 1;
//			lastRect.right = max(startX[nCount], endX[nCount]) + 1;
//			lastRect.top = min(startY[nCount], endY[nCount]) - 1;
//			lastRect.bottom = max(startY[nCount], endY[nCount]) + 1;
//			nCount++;
//			InvalidateRect(hWnd, &lastRect, TRUE);
//		}
//
//	}
//	break;
//	case WM_CHAR:
//	{
//		TCHAR code = (TCHAR)wParam;
//		if (nTextLen < 20)
//		{
//			text[nTextLen++] = code;
//			RECT textRect = { 200, 200, 400, 250 };
//			InvalidateRect(hWnd, &textRect, TRUE);
//		}
//	}
//	break;
//	case WM_PAINT:
//	{
//		hdc = BeginPaint(hWnd, &ps);
//
//		RECT textRect = { 200, 200, 400, 250 };
//		DrawText(hdc, text, nTextLen, &textRect, DT_CENTER);
//
//		HPEN pen = CreatePen(PS_SOLID, 5, RGB(200, 0, 0));
//		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
//		for (int i = 0; i < nCount; i++)
//		{
//			MoveToEx(hdc, startX[i], startY[i], NULL);
//			LineTo(hdc, endX[i], endY[i]);
//		}
//		SelectObject(hdc, oldPen);
//		DeleteObject(pen);
//
//		EndPaint(hWnd, &ps);
//	}
//	break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
//
// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}
//
//void AddControls(HWND hWnd)
//{
//	LOGFONT lf;
//
//	wcscpy(lf.lfFaceName, L"Arial");
//	lf.lfHeight = 25;
//	lf.lfWidth = 11;
//	lf.lfItalic = 0;
//	lf.lfStrikeOut = 0;
//	lf.lfUnderline = 0;
//	lf.lfWeight = 1000;
//	lf.lfCharSet = DEFAULT_CHARSET;
//	lf.lfPitchAndFamily = DEFAULT_PITCH;
//	lf.lfEscapement = 0;
//
//	HFONT hFont = CreateFontIndirect(&lf);
//
//	HWND hwndClearButton = CreateWindowW(L"	Button", L"Clear", WS_VISIBLE | WS_CHILD, 1185, 10, 185, 60, hWnd, (HMENU)CLEAR_SCREEN, NULL, NULL);
//
//	HWND toolLabel = CreateWindowW(L"STATIC", L"Tools:", WS_CHILD | WS_VISIBLE, 1185, 80, 185, 30, hWnd, NULL, NULL, NULL);
//
//	HWND hPen = CreateWindowW(L"Button", L"Pen", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 1185, 110, 185, 40, hWnd, (HMENU)SET_PEN_TYPE, NULL, NULL);
//
//	HWND hPen = CreateWindowW(L"Button", L"Pen", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 1185, 110, 185, 40, hWnd, (HMENU)SET_PEN_TYPE, NULL, NULL);
//
//	SendMessage(hPen, WM_SETFONT, (WPARAM)hFont, 0L);
//	SendMessage(hPen, BM_SETCHECK, BST_CHECKED, 0L);
//
//	HWND penLabel = CreateWindowW(L"STATIC", L"Pen Width:", WS_CHILD | WS_VISIBLE, 1185, 330, 185, 30, hWnd, NULL, NULL, NULL);
//
//	SendMessage(toolLabel, WM_SETFONT, (WPARAM)hFont, 0L);
//	SendMessage(penLabel, WM_SETFONT, (WPARAM)hFont, 0L);
//
//	HWND penColorLabel = CreateWindowW(L"STATIC", L"Pen Color:", WS_CHILD | WS_VISIBLE, 1185, 490, 185, 30, hWnd, NULL, NULL, NULL);
//
//	penColorCombobox = CreateWindowW(L"Combobox", L"Pen color", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 1185, 520, 185, 300, hWnd, (HMENU)SET_PEN_COLOR, NULL, NULL);
//
//	SendMessage(penColorCombobox, WM_SETFONT, (WPARAM)hFont, 0L);
//	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Black");
//	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Red");
//	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Blue");
//	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Green");
//	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Yellow");
//	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Pink");
//	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Purple");
//	SendMessage(penColorCombobox, CB_SETCURSEL, 0, 0L);
//}
//
//COLORREF GetPenColor(int color)
//{
//	switch (color)
//	{
//	case COMBO_PEN_BLACK:
//		return RGB(0, 0, 0);
//	case COMBO_PEN_RED:
//		return RGB(255, 0, 0);
//	case COMBO_PEN_BLUE:
//		return RGB(0, 0, 255);
//	case COMBO_PEN_GREEN:
//		return RGB(0, 255, 0);
//	case COMBO_PEN_YELLOW:
//		return RGB(255, 255, 0);
//	case COMBO_PEN_PINK:
//		return RGB(255, 20, 147);
//	case COMBO_PEN_PURPLE:
//		return RGB(128, 0, 128);
//	default:
//		return RGB(255, 255, 255);
//	}
//}

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

int nCount = 0;
int startX[1000];
int startY[1000];
int endX[1000];
int endY[1000];
int nTextLen = 0;
TCHAR text[20];

RECT mapRect;

bool needRefresh = true;
bool isEraser = false;

int type = PEN;
int penWidth = PEN_NORMAL;

HWND firstFillCombobox;
HWND secondFillCombobox;
HWND penColorCombobox;
HWND eraser;

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
	HDC hdc;
	int wmId, wmEvent;
	switch (message)
	{
	case WM_CREATE:
		AddControls(hWnd);
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case CLEAR_SCREEN:
			needRefresh = true;
			InvalidateRect(hWnd, &mapRect, FALSE);
			break;
		case SET_PEN_TYPE:
			type = PEN;
			if (isEraser)
			{
				SendMessage(eraser, BM_SETCHECK, BST_UNCHECKED, 0L);
				isEraser = false;
			}
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
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
	case WM_CHAR:
	{
		TCHAR code = (TCHAR)wParam;
		if (nTextLen < 20)
		{
			text[nTextLen++] = code;
			RECT textRect = { 200, 200, 400, 250 };
			InvalidateRect(hWnd, &textRect, TRUE);
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		RECT textRect = { 200, 200, 400, 250 };
		DrawText(hdc, text, nTextLen, &textRect, DT_CENTER);

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(200, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		for (int i = 0; i < nCount; i++)
		{
			MoveToEx(hdc, startX[i], startY[i], NULL);
			LineTo(hdc, endX[i], endY[i]);
		}
		SelectObject(hdc, oldPen);
		DeleteObject(pen);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
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

void AddControls(HWND hWnd)
{
	LOGFONT lf;

	wcscpy(lf.lfFaceName, L"Arial");
	lf.lfHeight = 25;
	lf.lfWidth = 11;
	lf.lfItalic = 0;
	lf.lfStrikeOut = 0;
	lf.lfUnderline = 0;
	lf.lfWeight = 1000;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfPitchAndFamily = DEFAULT_PITCH;
	lf.lfEscapement = 0;

	HFONT hFont = CreateFontIndirect(&lf);

	HWND hwndClearButton = CreateWindowW(L"	Button", L"Clear", WS_VISIBLE | WS_CHILD, 1185, 10, 185, 60, hWnd, (HMENU)CLEAR_SCREEN, NULL, NULL);

	HWND toolLabel = CreateWindowW(L"STATIC", L"Tools:", WS_CHILD | WS_VISIBLE, 1185, 80, 185, 30, hWnd, NULL, NULL, NULL);

	HWND hPen = CreateWindowW(L"Button", L"Pen", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 1185, 110, 185, 40, hWnd, (HMENU)SET_PEN_TYPE, NULL, NULL);

	//HWND hPen = CreateWindowW(L"Button", L"Pen", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 1185, 110, 185, 40, hWnd, (HMENU)SET_PEN_TYPE, NULL, NULL);

	//SendMessage(hPen, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(hPen, BM_SETCHECK, BST_CHECKED, 0L);

	HWND penLabel = CreateWindowW(L"STATIC", L"Pen Width:", WS_CHILD | WS_VISIBLE, 1185, 330, 185, 30, hWnd, NULL, NULL, NULL);

	SendMessage(toolLabel, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(penLabel, WM_SETFONT, (WPARAM)hFont, 0L);

	HWND penColorLabel = CreateWindowW(L"STATIC", L"Pen Color:", WS_CHILD | WS_VISIBLE, 1185, 490, 185, 30, hWnd, NULL, NULL, NULL);

	penColorCombobox = CreateWindowW(L"Combobox", L"Pen color", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 1185, 520, 185, 300, hWnd, (HMENU)SET_PEN_COLOR, NULL, NULL);

	SendMessage(penColorCombobox, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Black");
	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Red");
	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Blue");
	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Green");
	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Yellow");
	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Pink");
	SendMessage(penColorCombobox, CB_ADDSTRING, 0, (LPARAM)L"Purple");
	SendMessage(penColorCombobox, CB_SETCURSEL, 0, 0L);
}

COLORREF GetPenColor(int color)
{
	switch (color)
	{
	case COMBO_PEN_BLACK:
		return RGB(0, 0, 0);
	case COMBO_PEN_RED:
		return RGB(255, 0, 0);
	case COMBO_PEN_BLUE:
		return RGB(0, 0, 255);
	case COMBO_PEN_GREEN:
		return RGB(0, 255, 0);
	case COMBO_PEN_YELLOW:
		return RGB(255, 255, 0);
	case COMBO_PEN_PINK:
		return RGB(255, 20, 147);
	case COMBO_PEN_PURPLE:
		return RGB(128, 0, 128);
	default:
		return RGB(255, 255, 255);
	}
}
