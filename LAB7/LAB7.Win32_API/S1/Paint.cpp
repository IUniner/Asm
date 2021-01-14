#define _CRT_SECURE_NO_WARNINGS
//#include "framework.h"
//#include "Paint.h"
#include "math.h"
#include "Windows.h"
#include <iostream>
#include "Resource.h"

using namespace std;

#define MAX_LOADSTRING 100

#define CLEAR_SCREEN 10001
#define SET_PEN_TYPE 10002
#define SET_LINE_TYPE 10003
#define SET_RECT_TYPE 10004
#define SET_ELLIPSE_TYPE 10005
#define SET_SNOWFLAKE_TYPE 10006

#define SET_SLIM_TYPE 10007
#define SET_NORMAL_TYPE 10008
#define SET_BOLD_TYPE 10009

#define SET_ERASER 10010

#define SET_HLINEAR_GRAD 10011
#define SET_VLINEAR_GRAD 10012

#define SET_PEN_COLOR 10013

#define PEN 0
#define LINE 1
#define RECTANGLE 2
#define ELLIPSE 3
#define SNOWFLAKE 4

#define PEN_SLIM 1
#define PEN_NORMAL 5
#define PEN_BOLD 10

#define COMBO_BRUSH_NONE 0
#define COMBO_BRUSH_RED 1
#define COMBO_BRUSH_BLUE 2
#define COMBO_BRUSH_BLACK 3
#define COMBO_BRUSH_WHITE 4
#define COMBO_BRUSH_YELLOW 5
#define COMBO_BRUSH_PURPLE 6
#define COMBO_BRUSH_GREEN 7
#define COMBO_BRUSH_PINK 8

#define COMBO_PEN_BLACK 0
#define COMBO_PEN_RED 1
#define COMBO_PEN_BLUE 2
#define COMBO_PEN_GREEN 3
#define COMBO_PEN_YELLOW 4
#define COMBO_PEN_PINK 5
#define COMBO_PEN_PURPLE 6

#define HLINEAR_GRAD 0
#define VLINEAR_GRAD 1

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
BOOL Line(HDC, int, int, int, int);
bool CheckBorders(int, int);
void Snowflake(HDC, int, int, int, int);
HBRUSH CreateGradientBrush(HDC, COLORREF, COLORREF, RECT);
HBRUSH GetBrushColor(HDC, int, int, RECT);
COLORREF GetBrushColor(int);
COLORREF GetPenColor(int);

int startX = -1;
int startY = -1;
int endX = -1;
int endY = -1;

int map_x1 = 10;
int map_y1 = 10;
int map_x2 = 1150;
int map_y2 = 630;

RECT mapRect;

bool isPressed = false;
bool needRefresh = true;
bool isEraser = false;

int type = PEN;

int penWidth = PEN_NORMAL;

int grad = HLINEAR_GRAD;

HWND firstFillCombobox;
HWND secondFillCombobox;
HWND penColorCombobox;
HWND eraser;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	SetProcessDPIAware();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	mapRect.left = map_x1;
	mapRect.right = map_x2;
	mapRect.top = map_y1;
	mapRect.bottom = map_y2;

	// Initialize global strings
	 LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	/*wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
*/
	return RegisterClassExW(&wcex);
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
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		100, 100, 1420, 825, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		AddControls(hWnd);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		
		
		case SET_LINE_TYPE:
			type = LINE;
			if (isEraser)
			{
				SendMessage(eraser, BM_SETCHECK, BST_UNCHECKED, 0L);
				isEraser = false;
			}
			break;
		case SET_RECT_TYPE:
			type = RECTANGLE;
			if (isEraser)
			{
				SendMessage(eraser, BM_SETCHECK, BST_UNCHECKED, 0L);
				isEraser = false;
			}
			break;
		case SET_ELLIPSE_TYPE:
			type = ELLIPSE;
			if (isEraser)
			{
				SendMessage(eraser, BM_SETCHECK, BST_UNCHECKED, 0L);
				isEraser = false;
			}
			break;
		case SET_SNOWFLAKE_TYPE:
			type = SNOWFLAKE;
			if (isEraser)
			{
				SendMessage(eraser, BM_SETCHECK, BST_UNCHECKED, 0L);
				isEraser = false;
			}
			break;
		case SET_SLIM_TYPE:
			penWidth = PEN_SLIM;
			break;
		case SET_NORMAL_TYPE:
			penWidth = PEN_NORMAL;
			break;
		case SET_BOLD_TYPE:
			penWidth = PEN_BOLD;
			break;
		case SET_ERASER:
			isEraser = !isEraser;
			break;
		case SET_PEN_COLOR:
			if (isEraser)
			{
				isEraser = false;
				SendMessage(eraser, BM_SETCHECK, BST_UNCHECKED, 0L);
			}
			break;
		case SET_HLINEAR_GRAD:
			grad = HLINEAR_GRAD;
			break;
		case SET_VLINEAR_GRAD:
			grad = VLINEAR_GRAD;
			break;
		/*case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;*/
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		HPEN solidPen;
		HBRUSH solidBrush;

		HGDIOBJ oldPen;
		HGDIOBJ oldBrush;

		if (needRefresh)
		{
			needRefresh = false;

			solidPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
			solidBrush = CreateSolidBrush(RGB(255, 255, 255));

			oldPen = SelectObject(hdc, solidPen);
			oldBrush = SelectObject(hdc, solidBrush);

			Rectangle(hdc, map_x1 - 5, map_y1 - 5, map_x2 + 5, map_y2 + 5);

			SelectObject(hdc, oldPen);
			SelectObject(hdc, oldBrush);

			DeleteObject(solidPen);
			DeleteObject(solidBrush);

			EndPaint(hWnd, &ps);

			break;
		}

		if (startX < 0 && startY < 0) break;

		if (CheckBorders(startX, startY) && CheckBorders(endX, endY))
		{
			if (isEraser)
			{
				solidPen = CreatePen(PS_SOLID, penWidth, RGB(255, 255, 255));

				oldPen = SelectObject(hdc, solidPen);

				Line(hdc, startX, startY, endX, endY);

				startX = endX;
				startY = endY;

				SelectObject(hdc, oldPen);

				DeleteObject(solidPen);
			}
			else if (type == PEN || type == LINE)
			{
				int penColor = SendMessage(penColorCombobox, CB_GETCURSEL, 0, 0L);

				solidPen = CreatePen(PS_SOLID, penWidth, GetPenColor(penColor));
				oldPen = SelectObject(hdc, solidPen);

				Line(hdc, startX, startY, endX, endY);

				if (type == PEN)
				{
					startX = endX;
					startY = endY;
				}

				SelectObject(hdc, oldPen);
				DeleteObject(solidPen);
			}
			else
			{
				int color1 = SendMessage(firstFillCombobox, CB_GETCURSEL, 0, 0L);
				int color2 = SendMessage(secondFillCombobox, CB_GETCURSEL, 0, 0L);

				int penColor = SendMessage(penColorCombobox, CB_GETCURSEL, 0, 0L);

				RECT rect\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
					
					\;

				rect.left = min(startX, endX);
				rect.right = max(startX, endX);
				rect.top = min(startY, endY);
				rect.bottom = max(startY, endY);

				solidBrush = GetBrushColor(hdc, color1, color2, rect);
				solidPen = CreatePen(PS_SOLID, penWidth, GetPenColor(penColor));

				oldPen = SelectObject(hdc, solidPen);
				oldBrush = SelectObject(hdc, solidBrush);

				switch (type)
				{
				case RECTANGLE:
					Rectangle(hdc, startX, startY, endX, endY);
					break;
				case ELLIPSE:
					Ellipse(hdc, startX, startY, endX, endY);
					break;
				case SNOWFLAKE:
					Snowflake(hdc, startX, startY, endX, endY);
					break;
				default:
					Line(hdc, startX, startY, endX, endY);
					break;
				}

				SelectObject(hdc, oldPen);
				SelectObject(hdc, oldBrush);

				DeleteObject(solidPen);
				DeleteObject(solidBrush);
			}
		}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		isPressed = true;

		startX = LOWORD(lParam);
		startY = HIWORD(lParam);

		endX = startX;
		endY = startY;
	}
	break;
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		if (!CheckBorders(x, y))
		{
			isPressed = false;

			break;
		}
		x -= map_x1;
		y -= map_y1;

		WCHAR text[100] = L"Paint (";

		WCHAR xStr[100];
		WCHAR yStr[100];

		_itow(x, xStr, 10);
		_itow(y, yStr, 10);

		wcscat(text, xStr);
		wcscat(text, L", ");
		wcscat(text, yStr);
		wcscat(text, L")");

		SetWindowText(hWnd, text);

		if (isPressed && (type == PEN || isEraser))
		{
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);

			if (CheckBorders(endX, endY))
			{
				InvalidateRect(hWnd, &mapRect, FALSE);
			}
			else
			{
				isPressed = false;
			}
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (type == PEN && !isPressed) break;

		endX = LOWORD(lParam);
		endY = HIWORD(lParam);

		isPressed = false;

		InvalidateRect(hWnd, &mapRect, FALSE);
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

	HWND hwndClearButton = CreateWindowW(L"Button", L"Clear", WS_VISIBLE | WS_CHILD, 1185, 10, 185, 60, hWnd, (HMENU)CLEAR_SCREEN, NULL, NULL);

	HWND toolLabel = CreateWindowW(L"STATIC", L"Tools:", WS_CHILD | WS_VISIBLE, 1185, 80, 185, 30, hWnd, NULL, NULL, NULL);

	HWND hPen = CreateWindowW(L"Button", L"Pen", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 1185, 110, 185, 40, hWnd, (HMENU)SET_PEN_TYPE, NULL, NULL);
	HWND hLine = CreateWindowW(L"Button", L"Line", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 1185, 150, 185, 40, hWnd, (HMENU)SET_LINE_TYPE, NULL, NULL);
	HWND hRect = CreateWindowW(L"Button", L"Rectangle", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 1185, 190, 185, 40, hWnd, (HMENU)SET_RECT_TYPE, NULL, NULL);
	HWND hEllipse = CreateWindowW(L"Button", L"Ellipse", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 1185, 230, 185, 40, hWnd, (HMENU)SET_ELLIPSE_TYPE, NULL, NULL);
	HWND hTree = CreateWindowW(L"Button", L"Snowflake", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 1185, 270, 185, 40, hWnd, (HMENU)SET_SNOWFLAKE_TYPE, NULL, NULL);

	SendMessage(hwndClearButton, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(hPen, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(hLine, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(hRect, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(hEllipse, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(hTree, WM_SETFONT, (WPARAM)hFont, 0L);

	SendMessage(hPen, BM_SETCHECK, BST_CHECKED, 0L);

	HWND penLabel = CreateWindowW(L"STATIC", L"Pen Width:", WS_CHILD | WS_VISIBLE, 1185, 330, 185, 30, hWnd, NULL, NULL, NULL);

	HWND slimPen = CreateWindowW(L"Button", L"Slim", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 1185, 360, 185, 40, hWnd, (HMENU)SET_SLIM_TYPE, NULL, NULL);
	HWND normalPen = CreateWindowW(L"Button", L"Normal", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 1185, 400, 185, 40, hWnd, (HMENU)SET_NORMAL_TYPE, NULL, NULL);
	HWND boldPen = CreateWindowW(L"Button", L"Bold", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 1185, 440, 185, 40, hWnd, (HMENU)SET_BOLD_TYPE, NULL, NULL);

	SendMessage(normalPen, BM_SETCHECK, BST_CHECKED, 0L);

	SendMessage(slimPen, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(normalPen, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(boldPen, WM_SETFONT, (WPARAM)hFont, 0L);

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

	SendMessage(penColorLabel, WM_SETFONT, (WPARAM)hFont, 0L);

	eraser = CreateWindowW(L"Button", L"Eraser", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 1185, 560, 185, 40, hWnd, (HMENU)SET_ERASER, NULL, NULL);
	SendMessage(eraser, WM_SETFONT, (WPARAM)hFont, 0L);

	HWND fillLabel = CreateWindowW(L"STATIC", L"Fill Colors:", WS_CHILD | WS_VISIBLE, 25, 650, 185, 30, hWnd, NULL, NULL, NULL);
	SendMessage(fillLabel, WM_SETFONT, (WPARAM)hFont, 0L);

	firstFillCombobox = CreateWindowW(L"Combobox", L"First Color:", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 210, 650, 100, 300, hWnd, NULL, NULL, NULL);

	SendMessage(firstFillCombobox, WM_SETFONT, (WPARAM) hFont, 0L);
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"None");
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Red");
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Blue");
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Black");
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"White");
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Yellow");
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Purple");
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Green");
	SendMessage(firstFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Pink");
	SendMessage(firstFillCombobox, CB_SETCURSEL, 0, 0L);

	HWND plusLabel = CreateWindowW(L"STATIC", L" + ", WS_CHILD | WS_VISIBLE, 320, 652, 25, 25, hWnd, NULL, NULL, NULL);
	SendMessage(plusLabel, WM_SETFONT, (WPARAM)hFont, 0L);

	secondFillCombobox = CreateWindowW(L"Combobox", L"Second Color:", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 355, 650, 100, 300, hWnd, NULL, NULL, NULL);

	SendMessage(secondFillCombobox, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"None");
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Red");
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Blue");
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Black");
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"White");
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Yellow");
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Purple");
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Green");
	SendMessage(secondFillCombobox, CB_ADDSTRING, 0, (LPARAM)L"Pink");
	SendMessage(secondFillCombobox, CB_SETCURSEL, 0, 0L);

	HWND gradientLabel = CreateWindowW(L"STATIC", L"Gradient:", WS_CHILD | WS_VISIBLE, 25, 700, 110, 30, hWnd, NULL, NULL, NULL);
	SendMessage(gradientLabel, WM_SETFONT, (WPARAM)hFont, 0L);

	HWND hlinearGrad = CreateWindowW(L"Button", L"Horizontal Linear", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 135, 700, 215, 30, hWnd, (HMENU)SET_HLINEAR_GRAD, NULL, NULL);
	HWND vlinearGrad = CreateWindowW(L"Button", L"Vertical Linear", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 350, 700, 190, 30, hWnd, (HMENU)SET_VLINEAR_GRAD, NULL, NULL);

	SendMessage(hlinearGrad, BM_SETCHECK, BST_CHECKED, 0L);

	SendMessage(hlinearGrad, WM_SETFONT, (WPARAM)hFont, 0L);
	SendMessage(vlinearGrad, WM_SETFONT, (WPARAM)hFont, 0L);
}

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}

void Snowflake(HDC hdc, int x1, int y1, int x2, int y2)
{
	if (!CheckBorders(x1, y1) || !CheckBorders(x2, y2)) return;

	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);

	HBRUSH solidBrush = CreateSolidBrush(RGB(255, 255, 255));
	HGDIOBJ oldBrush = SelectObject(hdc, solidBrush);

	Ellipse(hdc, x1 + (x2 - x1) / 4, y1 + (y2 - y1) / 4, x2 - (x2 - x1) / 4, y2 - (y2 - y1) / 4);

	Line(hdc, (x1 + x2) / 2, y1, (x1 + x2) / 2, y2); // |
	Line(hdc, x1, (y1 + y2) / 2, x2, (y1 + y2) / 2); // --

	Line(hdc, x1 + (x2 - x1) / 4, y1 + (y2 - y1) / 4, x2 - (x2 - x1) / 4, y2 - (y2 - y1) / 4); // '\'
	Line(hdc, x2 - (x2 - x1) / 4, y1 + (y2 - y1) / 4, x1 + (x2 - x1) / 4, y2 - (y2 - y1) / 4); // '/'

	SelectObject(hdc, oldBrush);
	DeleteObject(solidBrush);
}

bool CheckBorders(int x, int y)
{
	return x >= map_x1 && x <= map_x2 && y >= map_y1 && y <= map_y2;
}

HBRUSH CreateGradientBrush(HDC hdc, COLORREF top, COLORREF bottom, RECT rect)
{
	HBRUSH currentBrush = NULL;
	HDC hdcmem = CreateCompatibleDC(hdc);
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	SelectObject(hdcmem, hbitmap);

	int r1 = GetRValue(top), r2 = GetRValue(bottom), g1 = GetGValue(top), g2 = GetGValue(bottom), b1 = GetBValue(top), b2 = GetBValue(bottom);

	float currentR = r1, currentG = g1, currentB = b1;

	if (grad == HLINEAR_GRAD)
	{
		int n = rect.bottom - rect.top;

		float hR = (float)(r2 - r1) / (float)n;
		float hG = (float)(g2 - g1) / (float)n;
		float hB = (float)(b2 - b1) / (float)n;

		for (int i = rect.top; i <= rect.bottom; i++)
		{
			RECT temp;
			temp.left = rect.left;
			temp.top = i;
			temp.right = rect.right;
			temp.bottom = i + 1;

			currentR = currentR + hR;
			currentG = currentG + hG;
			currentB = currentB + hB;

			int r = (int)currentR;
			int g = (int)currentG;
			int b = (int)currentB;

			currentBrush = CreateSolidBrush(RGB(r, g, b));

			FillRect(hdcmem, &temp, currentBrush);
			DeleteObject(currentBrush);
		}
	}
	else
	{
		int n = rect.right - rect.left;

		float hR = (float)(r2 - r1) / (float)n;
		float hG = (float)(g2 - g1) / (float)n;
		float hB = (float)(b2 - b1) / (float)n;

		for (int i = rect.left; i <= rect.right; i++)
		{
			RECT temp;
			temp.left = i;
			temp.top = rect.top;
			temp.right = i + 1;
			temp.bottom = rect.bottom;

			currentR = currentR + hR;
			currentG = currentG + hG;
			currentB = currentB + hB;

			int r = (int)currentR;
			int g = (int)currentG;
			int b = (int)currentB;

			currentBrush = CreateSolidBrush(RGB(r, g, b));

			FillRect(hdcmem, &temp, currentBrush);
			DeleteObject(currentBrush);
		}
	}
	HBRUSH pattern = CreatePatternBrush(hbitmap);

	DeleteDC(hdcmem);
	DeleteObject(hbitmap);

	return pattern;
}

HBRUSH GetBrushColor(HDC hdc, int color1, int color2, RECT rect)
{
	if (color1 != COMBO_BRUSH_NONE && color2 == COMBO_BRUSH_NONE)
	{
		return CreateSolidBrush(GetBrushColor(color1));
	}

	if (color1 == COMBO_BRUSH_NONE && color2 != COMBO_BRUSH_NONE)
	{
		return CreateSolidBrush(GetBrushColor(color2));
	}

	if (color1 == COMBO_BRUSH_NONE && color2 == COMBO_BRUSH_NONE)
	{
		return CreateSolidBrush(RGB(255, 255, 255));
	}

	return CreateGradientBrush(hdc, GetBrushColor(color1), GetBrushColor(color2), rect);
}

COLORREF GetBrushColor(int color)
{
	switch (color)
	{
	case COMBO_BRUSH_NONE:
		return RGB(255, 255, 255);
	case COMBO_BRUSH_RED:
		return RGB(255, 0, 0);
	case COMBO_BRUSH_BLUE:
		return RGB(0, 0, 255);
	case COMBO_BRUSH_BLACK:
		return RGB(0, 0, 0);
	case COMBO_BRUSH_WHITE:
		return RGB(255, 255, 255);
	case COMBO_BRUSH_YELLOW:
		return RGB(255, 255, 0);
	case COMBO_BRUSH_PURPLE:
		return RGB(128, 0, 128);
	case COMBO_BRUSH_GREEN:
		return RGB(0, 255, 0);
	case COMBO_BRUSH_PINK:
		return RGB(255, 20, 147);
	default:
		return RGB(255, 255, 255);
	}
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
