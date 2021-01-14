//// mouse.cpp
//
//
//#include "stdafx.h"
//#include "mouse.h"
//
//#include "Windows.h"
//#include "WinDef.h"
//#include "WinNT.h"
//#include "BaseTsd.h"
//#include "WinUser.h"
//
////typedef wchar_t WCHAR;
////typedef void *PVOID;
////typedef PVOID HANDLE;
////typedef HANDLE HINSTANCE;
////typedef unsigned short WORD;
////typedef WORD ATOM;
////#if defined(_WIN64)
//// typedef __int64 LONG_PTR; 
////#else
//// typedef long LONG_PTR;
////#endif
////typedef LONG_PTR LRESULT;
////#ifdef UNICODE
////typedef WCHAR TCHAR;
////#else
////typedef char TCHAR;
////#endif
////typedef int BOOL;
////#if defined(_WIN64) 
////typedef __int64 INT_PTR;
////#else 
////typedef int INT_PTR;
////#endif
////typedef HANDLE HWND;
////typedef unsigned int UINT;
////#if defined(_WIN64)
////typedef unsigned __int64 UINT_PTR;
////#else
////typedef unsigned int UINT_PTR;
////#endif
////typedef UINT_PTR WPARAM;
////typedef LONG_PTR LPARAM;
////#ifdef UNICODE
////typedef LPWSTR LPTSTR;
////#else
////typedef LPSTR LPTSTR;
////#endif
////typedef WCHAR *LPWSTR;
////typedef HANDLE HDC;
////typedef unsigned char BYTE;
////typedef BYTE BOOLEAN;
////typedef long LONG;
////typedef HANDLE HACCEL;
////typedef unsigned long DWORD;
////typedef char CCHAR;
////typedef char CHAR;
////typedef DWORD COLORREF;
////typedef unsigned __int64 DWORDLONG;
////typedef ULONG_PTR DWORD_PTR;
////typedef unsigned int DWORD32;
////typedef unsigned __int64 DWORD64;
////typedef float FLOAT;
////#ifdef _WIN64
////typedef int HALF_PTR;
////#else
////typedef short HALF_PTR;
////#endif
////typedef HANDLE HBITMAP;
////typedef HANDLE HBRUSH;
////typedef HANDLE HCOLORSPACE;
////typedef HANDLE HCONV;
////typedef HANDLE HCONVLIST;
////typedef HICON HCURSOR;
////typedef HANDLE HDDEDATA;
////typedef HANDLE HDESK;
////typedef HANDLE HDROP;
////typedef HANDLE HDWP;
////typedef HANDLE HENHMETAFILE;
////typedef int HFILE;
////typedef HANDLE HGDIOBJ;
////typedef HANDLE HGLOBAL;
////typedef HANDLE HHOOK;
////typedef HANDLE HICON;
////typedef HANDLE HKEY;
////typedef HANDLE HKL;
////typedef HANDLE HMENU;
////typedef HANDLE HMETAFILE;
////typedef HINSTANCE HMODULE;
/////*if (WINVER >= 0x0500)*/ typedef HANDLE HMONITOR;
////typedef HANDLE HPALETTE;
////typedef HANDLE HPEN;
////typedef LONG HRESULT;
////typedef HANDLE HRGN;
////typedef HANDLE HRSRC;
////typedef HANDLE HSZ;
////typedef HANDLE WINSTA;
////typedef int INT;
////typedef signed char INT8;
////typedef signed short INT16;
////typedef signed int INT32;
////typedef signed __int64 INT64;
////typedef WORD LANGID;
////typedef DWORD LCID;
////typedef DWORD LCTYPE;
////typedef DWORD LGRPID;
////typedef long LONG;
////#if !defined(_M_IX86)
////typedef __int64 LONGLONG;
////#else
////typedef double LONGLONG;
////#endif
////#if defined(_WIN64)
////typedef __int64 LONG_PTR;
////#else
////typedef long LONG_PTR;
////#endif
////typedef signed int LONG32;
////typedef __int64 LONG64;
////typedef DWORD *LPCOLORREF;
//////typedef __nullterminated CONST CHAR *LPCSTR;
////typedef DWORD *LPDWORD;
////typedef HANDLE *LPHANDLE;
////typedef int *LPINT;
////typedef long *LPLONG;
////typedef CHAR *LPSTR;
////#ifdef UNICODE
////typedef LPWSTR LPTSTR;
////#else
////typedef LPSTR LPTSTR;
////#endif
////typedef void *LPVOID;
////typedef WORD *LPWORD;
////typedef WCHAR *LPWSTR;
////typedef LONG_PTR LRESULT;
////typedef BOOL *PBOOL;
////typedef BOOLEAN *PBOOLEAN;
////typedef BYTE *PBYTE;
////typedef CHAR *PCHAR;
////typedef DWORD *PDWORD;
////typedef DWORDLONG *PDWORDLONG;
////typedef DWORD_PTR *PDWORD_PTR;
////typedef DWORD32 *PDWORD32;
////typedef DWORD64 *PDWORD64;
////typedef FLOAT *PFLOAT;
////#ifdef _WIN64
////typedef HALF_PTR *PHALF_PTR;
////#else
////typedef HALF_PTR *PHALF_PTR;
////#endif
////typedef HANDLE *PHANDLE;
////typedef int *PINT;
////typedef HKEY *PHKEY;
////typedef INT_PTR *PINT_PTR;
////typedef INT8 *PINT8;
////typedef INT16 *PINT16;
////typedef INT32 *PINT32;
////typedef INT64 *PINT64;
////typedef PDWORD PLCID;
////typedef LONG *PLONG;
////typedef LONGLONG *PLONGLONG;
////typedef LONG_PTR *PLONG_PTR;
////typedef LONG32 *PLONG32;
////typedef LONG64 *PLONG64;
////#if defined(_WIN64)
////#define POINTER_32 __ptr32
////#else
////#define POINTER_32
////#endif
////#if (_MSC_VER >= 1300)
////#define POINTER_64 __ptr64
////#else
////#define POINTER_64
////#endif
////#define POINTER_SIGNED __sptr
////#define POINTER_UNSIGNED __uptr
////typedef SHORT *PSHORT;
////typedef SIZE_T *PSIZE_T;
////typedef SSIZE_T *PSSIZE_T;
////typedef CHAR *PSTR;
////typedef TBYTE *PTBYTE;
////typedef TCHAR *PTCHAR;
////#ifdef UNICODE
//// typedef LPWSTR PTSTR;
////#else typedef LPSTR PTSTR;
////#endif
////typedef UCHAR *PUCHAR;
////#ifdef _WIN64
//// typedef UHALF_PTR *PUHALF_PTR;
////#else
//// typedef UHALF_PTR *PUHALF_PTR;
////#endif
////typedef UINT *PUINT;
////typedef UINT8 *PUINT8;
////typedef UINT_PTR *PUINT_PTR;
////typedef UINT16 *PUINT16;
////typedef UINT32 *PUINT32;
////typedef ULONG *PULONG;
////typedef ULONGLONG *PULONGLONG;
////typedef ULONG_PTR *PULONG_PTR;
////typedef ULONG32 *PULONG32;
////typedef ULONG64 *PULONG64;
////typedef USHORT *PUSHORT;
////typedef void *PVOID;
////typedef WCHAR *PWCHAR;
////typedef WORD *PWORD;
////typedef WCHAR *PWSTR;
////typedef unsigned __int64 QWORD;
////typedef short SHORT;
////typedef HANDLE SC_HANDLE;
////typedef LPVOID SC_LOCK;
////typedef HANDLE SERVICE_STATUS_HANDLE;
////typedef short SHORT;
////typedef ULONG_PTR SIZE_T;
////typedef LONG_PTR SSIZE_T;
////#ifdef UNICODE
//// typedef WCHAR TBYTE;
////#else
//// typedef unsigned char TBYTE;
////#endif
////#ifdef UNICODE
//// typedef WCHAR TCHAR;
////#else
//// typedef char TCHAR;
////#endif
////typedef unsigned char UCHAR;
////#ifdef _WIN64
//// typedef unsigned int UHALF_PTR;
////#else
//// typedef unsigned short UHALF_PTR;
////#endif
////typedef unsigned int UINT;
////#if defined(_WIN64)
//// typedef unsigned __int64 UINT_PTR;
////#else
//// typedef unsigned int UINT_PTR;
////#endif
////typedef unsigned char UINT8;
////typedef unsigned short UINT16;
////typedef unsigned int UINT32;
////typedef unsigned __int64 UINT64;
////typedef unsigned long ULONG;
////#if !defined(_M_IX86)
//// typedef unsigned __int64 ULONGLONG;
////#else
//// typedef double ULONGLONG;
////#endif
////#if defined(_WIN64)
//// typedef unsigned __int64 ULONG_PTR;
////#else
//// typedef unsigned long ULONG_PTR;
////#endif
////typedef unsigned int ULONG32;
////typedef unsigned __int64 ULONG64;
////typedef unsigned short USHORT;
////typedef LONGLONG USN;
////#define VOID void
////typedef wchar_t WCHAR;
////typedef UINT_PTR WPARAM;
////typedef __nullterminated CONST CHAR *LPCSTR;
////#ifdef UNICODE
////typedef LPCWSTR LPCTSTR;
////#else
////typedef LPCSTR LPCTSTR;
////#endif
////typedef CONST WCHAR *LPCWSTR;
////typedef DWORD *LPDWORD;
////typedef HANDLE *LPHANDLE;
////typedef int *LPINT;
////typedef long *LPLONG;
////typedef CHAR *LPSTR;
////#ifdef UNICODE
////typedef LPWSTR LPTSTR;
////#else
////typedef LPSTR LPTSTR;
////#endif
////typedef void *LPVOID;
////typedef WORD *LPWORD;
////typedef WCHAR *LPWSTR;
////typedef char CHAR;
////
////
////
////
////
////
////
////
////
////#define CONST const
////#define WM_LBUTTONDOWN                  0x0201
////#define WM_LBUTTONUP                    0x0202
////#define WM_COMMAND                      0x0111
////#define WM_CHAR                         0x0102
////#define WM_DESTROY                      0x0002
////#define UNREFERENCED_PARAMETER(P) (P)
////#define CALLBACK __stdcall
////#define APIENTRY WINAPI
//#define MAX_LOADSTRING 100
////
////typedef struct tagRECT {
////	LONG left;
////	LONG top;
////	LONG right;
////	LONG bottom;
////} RECT, *PRECT, *NPRECT, *LPRECT;
////typedef struct tagPAINTSTRUCT {
////	HDC  hdc;
////	BOOL fErase;
////	RECT rcPaint;
////	BOOL fRestore;
////	BOOL fIncUpdate;
////	BYTE rgbReserved[32];
////} PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;
////typedef struct tagPOINT {
////	LONG x;
////	LONG y;
////} POINT, *PPOINT, *NPPOINT, *LPPOINT;
////typedef struct tagMSG {
////	HWND   hwnd;
////	UINT   message;
////	WPARAM wParam;
////	LPARAM lParam;
////	DWORD  time;
////	POINT  pt;
////	DWORD  lPrivate;
////} MSG, *PMSG, *NPMSG, *LPMSG;
//////void MAKEINTRESOURCEA(
//////	i
//////);
//////void IS_INTRESOURCE(
//////	_r
//////);
////typedef struct tagWNDCLASSEXA {
////	UINT      cbSize;
////	UINT      style;
////	WNDPROC   lpfnWndProc;
////	int       cbClsExtra;
////	int       cbWndExtra;
////	HINSTANCE hInstance;
////	HICON     hIcon;
////	HCURSOR   hCursor;
////	HBRUSH    hbrBackground;
////	LPCSTR    lpszMenuName;
////	LPCSTR    lpszClassName;
////	HICON     hIconSm;
////} WNDCLASSEXA, *PWNDCLASSEXA, *NPWNDCLASSEXA, *LPWNDCLASSEXA;
////typedef struct _UNICODE_STRING {
////  USHORT  Length;
////  USHORT  MaximumLength;
////  PWSTR  Buffer;
////} UNICODE_STRING;
////typedef UNICODE_STRING *PUNICODE_STRING;
////typedef const UNICODE_STRING *PCUNICODE_STRING;
//
//// Global Variables:
//HINSTANCE hInst;								// current instance
//TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
//TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
//
//// Forward declarations of functions included in this code module:
//ATOM				MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
//LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//
//int nCount = 0;
//int startX[1000];
//int startY[1000];
//int endX[1000];
//int endY[1000];
//int nTextLen = 0;
//TCHAR text[20];
//
//int APIENTRY _tWinMain(HINSTANCE hInstance,
//                     HINSTANCE hPrevInstance,
//                     LPTSTR    lpCmdLine,
//                     int       nCmdShow)
//{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
// 	// TODO: Place code here.
//	LPMSG msg{};
//	HACCEL hAccelTable;
//
//	// Initialize global strings
//
//	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadString(hInstance, IDC_MOUSE, szWindowClass, MAX_LOADSTRING);
//	MyRegisterClass(hInstance);
//
//	// Perform application initialization:
//	if (!InitInstance (hInstance, nCmdShow))
//	{
//		return FALSE;
//	}
//
//	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOUSE));
//
//	if (msg != nullptr)
//	{
//		// Main message loop:
//		while (GetMessage(msg, NULL, 0, 0))
//		{
//			if (!TranslateAccelerator(msg->hwnd, hAccelTable, msg))
//			{
//				TranslateMessage(msg);
//				DispatchMessage(msg);
//			}
//		}
//
//		return (int)msg->wParam;
//	}
//}
//
////
////  FUNCTION: MyRegisterClass()
////
////  PURPOSE: Registers the window class.
////
////  COMMENTS:
////
////    This function and its usage are only necessary if you want this code
////    to be compatible with Win32 systems prior to the 'RegisterClassEx'
////    function that was added to Windows 95. It is important to call this function
////    so that the application will get 'well formed' small icons associated
////    with it.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wcex{};
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style			= CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc	= WndProc;
//	wcex.cbClsExtra		= 0;
//	wcex.cbWndExtra		= 0;
//	wcex.hInstance		= hInstance;
//	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOUSE));
//	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
//	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MOUSE);
//	wcex.lpszClassName	= szWindowClass;
//	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//	return RegisterClassEx(&wcex);
//}
//
////
////   FUNCTION: InitInstance(HINSTANCE, int)
////
////   PURPOSE: Saves instance handle and creates main window
////
////   COMMENTS:
////
////        In this function, we save the instance handle in a global variable and
////        create and display the main program window.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   HWND hWnd;
//
//   hInst = hInstance; // Store instance handle in our global variable
//
//   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}
//
////
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  PURPOSE:  Processes messages for the main window.
////
////  WM_COMMAND	- process the application menu
////  WM_PAINT	- Paint the main window
////  WM_DESTROY	- post a quit message and return
////
////
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	switch (message)
//	{
//	case WM_COMMAND:
//		wmId    = LOWORD(wParam);
//		wmEvent = HIWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
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
//		{
//			if (nCount < 1000)
//			{
//				int xPos = LOWORD(lParam); 
//				int yPos = HIWORD(lParam); 
//
//				startX[nCount] = xPos;
//				startY[nCount] = yPos;
//			}
//
//		}
//		break;
//	case WM_LBUTTONUP:
//		{
//			if (nCount < 1000)
//			{
//				int xPos = LOWORD(lParam); 
//				int yPos = HIWORD(lParam); 
//
//				endX[nCount] = xPos;
//				endY[nCount] = yPos;
//				RECT lastRect{};
//				lastRect.left = min(startX[nCount], endX[nCount]) - 1;
//				lastRect.right = max(startX[nCount], endX[nCount]) + 1;
//				lastRect.top = min(startY[nCount], endY[nCount]) - 1;
//				lastRect.bottom = max(startY[nCount], endY[nCount]) + 1;
//				nCount++;
//				InvalidateRect(hWnd, &lastRect, TRUE);
//			}
//
//		}
//		break;
//	case WM_CHAR:
//		{
//			TCHAR code = (TCHAR) wParam;
//			if (nTextLen < 20)
//			{
//				text[nTextLen++] = code;
//				RECT textRect = {200, 200, 400, 250};
//				InvalidateRect(hWnd, &textRect, TRUE);
//			}
//		}
//		break;
//	case WM_PAINT:
//		{
//			hdc = BeginPaint(hWnd, &ps);
//
//			RECT textRect = {200, 200, 400, 250};
//			DrawText(hdc, text, nTextLen, &textRect, DT_CENTER);
//
//			HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 200, 0));
//			HPEN oldPen = (HPEN) SelectObject(hdc, pen);
//			for (int i = 0; i < nCount; i++)
//			{
//					MoveToEx(hdc, startX[i], startY[i], NULL);
//					LineTo(hdc, endX[i], endY[i]);
//			}
//			SelectObject(hdc, oldPen);
//			DeleteObject(pen);
//
//			EndPaint(hWnd, &ps);
//		}
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
//
//// Message handler for about box.
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

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(200,0, 0));
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

	SendMessage(toolLabel, WM_SETFONT, (WPARAM) hFont, 0L);
	SendMessage(penLabel, WM_SETFONT, (WPARAM) hFont, 0L);

	HWND penColorLabel = CreateWindowW(L"STATIC", L"Pen Color:", WS_CHILD | WS_VISIBLE, 1185, 490, 185, 30, hWnd, NULL, NULL, NULL);

	penColorCombobox = CreateWindowW(L"Combobox", L"Pen color", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 1185, 520, 185, 300, hWnd, (HMENU)SET_PEN_COLOR, NULL, NULL);

	SendMessage(penColorCombobox, WM_SETFONT, (WPARAM) hFont, 0L);
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
