/*Операторы препроцессора*/
/*
#define UNICODE
#ifdef UNICODE
#define _UNICODE
#endif
*/
#include "stdafx.h"
#define STRICT
#include <windows.h>
#include <windowsx.h>
/*
Файл tchar.h состоит из макросов, которые ссылаются на UNICODE
данные и функции, если определен макрос UNICODE, или на ANSI
данные и функции, если этот макрос не определен, кроме того он
полностью заменяет файл string.h
*/
#include <tchar.h>
/*Прототип оконной функции*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
/*
Прототип функции получения текущего времени
и преобразование его в символы
*/
void OutTimeDate(HWND);
/*
Массив для формирования строки - текущие дата и время
*/
TCHAR szCurrentTime[40];
int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	/*Произвольный заголовок окна*/
	TCHAR szTitle[] = _TEXT("ИТМО");
	/*Произвольное имя класса*/
	TCHAR szWindowClass[] = _TEXT("QWERTY");
	/*
	Структурная переменная msg типа MSG для получения сообщений
	*/
	MSG msg;
	/*
   Структурная переменная wcex типа WNDCLASSEX для задания
   характеристик окна
	*/
	WNDCLASSEX wcex;
	HWND hWnd; //Дескриптор главного окна
	/*Проверяем, было ли это проложение запущено ранее*/
	if (hWnd = FindWindow(szWindowClass, NULL))
	{
		/*Проверяем, было ли это окно свернуто в пиктограмму*/
		if (IsIconic(hWnd))
			ShowWindow(hWnd, SW_RESTORE);
		/*Выдвигаем окно приложения на передний план*/
		SetForegroundWindow(hWnd);
		return FALSE;
	}
	/*Обнуление всех членов структуры wcex*/
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	/*Регистрируем класс главного окна*/
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	/*Определяем оконную процедуру для главного окна*/
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;//Дескриптор приложения
   /*
   Стандартная пиктограмма, которую можно загрузить функцией
   LoadIcon(hInstance, MAKEINTRESOURCE(IDI_?_?))
   */
	wcex.hIcon = (HICON)LoadImage(hInstance,
		IDI_APPLICATION,
		IMAGE_ICON, 32, 32, 0);
	/*Стандартный курсор мыши*/
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*
   Кисть фона и ее цвет можно определить выражениями:
   wcex.hbrBackground=(HBRUSH)(COLOR_APPWORKSPACE+1);
   wcex.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
   или с помощью макроса GetStockBrush(), в этом случае
   необходимо подключить файл windowsx.h
   */
	wcex.hbrBackground = GetStockBrush(LTGRAY_BRUSH);
	/*wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MSG_1);*/
	/*
   Имя класса главного окна
   */
	wcex.lpszClassName = szWindowClass;
	/*
	Маленькая пиктограмма, wcex.hIconSm, которую
	можно загрузить функцией LoadImage()
	*/
	wcex.hIconSm = NULL;
	if (!RegisterClassEx(&wcex))
		return FALSE;
	/*Создаем главное окно*/
	hWnd = CreateWindowEx(WS_EX_WINDOWEDGE, szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return FALSE;
	/*
	Исследуем адресное пространство приложения. Выведем со- держимое сегментных регистров команд, данных и стека, а
	также смещение главной функции и строки с именем класса
	*/
	/*TCHAR szAsm[80];
	USHORT regCS, regDS, regES, regSS;
	__asm {
		mov regCS, CS
		mov regDS, DS
		mov regES, ES
		mov regSS, SS
	}
	wsprintf((LPTSTR)szAsm, _T("CS= %X,DS= %X\n ES= %X,SS= %X\n WinMain = %X \n szWindowClass = %X"),regCS, regDS, regES, regSS);
	MessageBox(NULL, (LPCTSTR)szAsm, _T("Регистры"),
		MB_ICONINFORMATION);*/
	/*Делаем окно видимым на экране*/
	ShowWindow(hWnd, SW_SHOWNORMAL);
	/*
	Функция UpdateWindow() вызывает передачу сообщения
	WM_PAINT непосредственно оконной процедуре, а
	функция InvalidateRect()вызывает постановку сообщения WM_PAINT в очередь приложения, а там оно обра- батывается с самым низким приоритетом
	 */
	UpdateWindow(hWnd);
	/*Цикл обработки сообщений*/
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	/*Код возврата*/
	return (int)msg.wParam;
}
/*Оконная функция главного окна*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	/*Горизонтальный размер главного окна*/
	int xSize = 500;
	/*Верикальный размер главного окна*/
	int ySize = 300;
	/*Структура PAINTSTRUCT с характеристиками рабочей
	области,заполняется функцией BeginPaint
	*/
	PAINTSTRUCT ps;
	/*
   TEXTMETRIC - структура для получения характеристик шрифта */
	TEXTMETRIC tm;
	/*
	LOGFONT - структура для для создания
	логических шрифтов
	*/
	LOGFONT lf;
	static HFONT hFont, hOldFont;
	/*
	RECT - структура описывает прямоугольник
	*/
	RECT rect;
	LPMINMAXINFO lpmmi;
	/*Дескриптор контекста устройства*/
	HDC hDc;
	UINT width, height;
	/*Имя шрифта*/
	LPTSTR lpszFace = _TEXT("Times New Roman Cyr");
	switch (message)
	{
		/*Переход по значению кода сообщения(msg)*/
	case WM_CREATE:
		/*
		Только здесь можно произвести модификацию класса
		окна. Например, SetClassLong(hWnd, GCL_HBRBACKGROUND,
		(LONG)CreateSolidBrush(RGB(200,160,255));
		Значение дескриптор экземпляра приложения (hInstance)
		определяется, вызовом одной из следующих функций:
		hInst = GetModuleHandle(NULL);
		hInst = (HINSTANCE)GetClassLong(hWnd,GCL_HMODULE);
		*/
		/*Обнуление всех членов структуры lf*/
		memset(&lf, 0, sizeof(lf));
		/*Устанавливаем размер шрифта*/
			lf.lfHeight = 30;
		/*Копируем в структуру имя шрифта*/
		lstrcpy(lf.lfFaceName, lpszFace);
		/*Создаем шрифт*/
		hFont = CreateFontIndirect(&lf);
		/*Первый немедленный вывод текущего времени*/
		OutTimeDate(hWnd);
		/*
		Функция SetTimer создает системный таймер с периодом 1с
		*/
		SetTimer(hWnd, 1, 1000, (TIMERPROC)NULL);
		return TRUE;
	case WM_TIMER:
		/*
		Функция OutTimeDate запрашивает у системы текущие значения даты и времени, а затем организует их обработку в
		главном окне приложения. */
		OutTimeDate(hWnd);
		break;
	case WM_KEYDOWN:
		/*Обрабатываем сообщение-нажатие клавиши.*/
		switch (wParam)
		{
		case VK_ESCAPE:
			/*
			Посылаем сообщение WM_CLOSE окну (hWnd), а после
			того, как оконная процедура обработает это сообщение, система передаст управление инструкции
			следующей за SendMessage.
			*/
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_COMMAND:
		//switch (LOWORD(wParam)) //switch(wParam)
		//{
		//case ID_FILE_TEST:
		//	//…
		//	break;
		//}
		break;
	case WM_PAINT:
		/*Получаем контекст устройства*/
		hDc = BeginPaint(hWnd, &ps);
		/*Определяем размеры клиентской области окна*/
		GetClientRect(hWnd, &rect);
		/*Выбираем в контест созданный шрифт*/
		hOldFont = SelectFont(hDc, hFont);
		/*Получим метрики текста*/
		GetTextMetrics(hDc, &tm);
		/*
		Функция SetBkMode устанавливает текущий режим фона. TRANSPARENT - в этом режиме вывода текста цвет фона
		графического элемента игнорируется, т.е. символ
		выводится на существующем фоне. */
			SetBkMode(hDc, TRANSPARENT);
		/*
		Функция SetTextColor устанавливает цвет текста для
		контекста устройства, по умолчанию применяется черный
		цвет. Цвет текста синий!
		*/
		SetTextColor(hDc, RGB(0, 0, 128));
		DrawText(hDc, szCurrentTime, -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		/*Освобождаем контекст устройства*/
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		/*
		Сообщение WM_CLOSE появляется при щелчке на кнопке
		закрытия окна - здесь предназначено для вывода предупреждающего сообщения
		*/
		if (MessageBox(hWnd, _T("Вы уверены?"),
			_T("Bad boys"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			/*
			Функция DestroyWindow разрушает указанное в ее па- раметре окно, т.е. она посылает окну сообщение
			WM_DESTROY. Затем вызывается функция
			PostQuitMessage, которя посылает сообщение WM_QUIT
			*/
			DestroyWindow(hWnd);
		}
		break;
	case WM_SIZE:
		/*
		Ширина width и высота height клиентской области окна
		в пикселях
		*/
		width = LOWORD(lParam);
		height = HIWORD(lParam);
		//...
		break;
	case WM_LBUTTONDOWN:
		/*Нажата клавиша Shift ?*/
		if (wParam & MK_SHIFT)
		{
			MessageBox(hWnd, _T("Нажата клавиша\nShift"),
				_T("Сообщение!"),
				MB_OK | MB_ICONEXCLAMATION);
		}
		break;
	case WM_GETMINMAXINFO:
		lpmmi = (LPMINMAXINFO)lParam;
		lpmmi->ptMinTrackSize.x = xSize;
		lpmmi->ptMinTrackSize.y = ySize;
		lpmmi->ptMaxTrackSize.x = xSize;
		lpmmi->ptMaxTrackSize.y = ySize;
		break;
	case WM_DESTROY:
		/*
		Функция DeleteObject удаляет логический объект.
		 39
		К удаляемым объектам относятся перья, растровые
		изображения, кисти, области, палитры и шрифты.
		*/
		/*Удаляем созданный шрифт*/
		DeleteObject(hFont);
		/*Функция KillTimer удаляет таймер*/
		KillTimer(hWnd, 1);
		/*PostQuitMessage() выполняет только одно действие - ставит в очередь сообщение WM_QUIT. Параметр у этой
		функции - код возврата, который помещается в wParam
		*/
		PostQuitMessage(0);
		break;
	default:
		/*Обработка прочих сообщений по умолчанию*/
		return DefWindowProc(hWnd, message, wParam,
			lParam);
	}
	return 0L;
}
/*
Фунуция получения текущего времени и преобразование
его в символы
*/
void OutTimeDate(HWND hWnd)
{
	LPTSTR szDay[] = { _T("Вск."),_T("Пнд."),_T("Втр."),
	_T("Ср."),_T("Чтв."),
	_T("Птн."),_T("Суб.")
	};
	LPTSTR szMonth[] = { _T(""),_T("Янв."),_T("Февр."),
	_T("Март"),_T("Апр."),
	_T("Май"),_T("Июнь"),
	_T("Июль"),_T("Авг."),
	_T("Сент."),_T("Окт."),
	_T("Нояб."),_T("Дек.")
	};
	TCHAR szT[20];
	SYSTEMTIME SystemTime;
	/*
	Функция GetLocalTime осуществляет выборку местного времени, на которое настроен компьютер, т.е. функция
	заполняет структуру типа SYSTEMTIME в числовом виде.
	*/
	GetLocalTime(&SystemTime);
	/*День недели*/
	lstrcpy(szCurrentTime,
		szDay[SystemTime.wDayOfWeek]);
	/*Разделяющий пробел*/
	lstrcat((LPTSTR)szCurrentTime, _T(" "));
	/*Месяц*/
	lstrcat((LPTSTR)szCurrentTime,
		szMonth[SystemTime.wMonth]);
	/*Разделяющий пробел*/
	lstrcat((LPTSTR)szCurrentTime, _T(" "));
	/*Дату переводим в символы*/
		wsprintf((LPTSTR)szT, _T("%d"),
			SystemTime.wDay);
	lstrcat((LPTSTR)szCurrentTime, (LPTSTR)szT);
	/*Разделяющий пробел*/
	lstrcat((LPTSTR)szCurrentTime, _T(" "));
	/*Год переводим в символы*/
	wsprintf((LPTSTR)szT, _T("%d"),
		SystemTime.wYear);
	lstrcat((LPTSTR)szCurrentTime, (LPTSTR)szT);
	lstrcat((LPTSTR)szCurrentTime, _T("---"));
	/**Часы переводим в символы*/
	wsprintf((LPTSTR)szT, _T("%d"),
		SystemTime.wHour);
	lstrcat((LPTSTR)szCurrentTime, (LPTSTR)szT);
	/*Разделяющее двоеточие*/
	lstrcat((LPTSTR)szCurrentTime, _T(":"));
	/*Минуты переводим в символы*/
	wsprintf((LPTSTR)szT, _T("%d"),
		SystemTime.wMinute);
	lstrcat((LPTSTR)szCurrentTime, (LPTSTR)szT);
	/*Разделяющее двоеточие*/
	lstrcat((LPTSTR)szCurrentTime, _T(":"));
	/*Сеуцнды переводим в символы*/
	wsprintf((LPTSTR)szT, _T("%d"),
		SystemTime.wSecond);
	lstrcat((LPTSTR)szCurrentTime, (LPTSTR)szT);
	/*Перерисовка окна*/
	InvalidateRect(hWnd, NULL, TRUE);
}