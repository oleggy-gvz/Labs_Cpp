#include <windowsx.h>
#include <iostream>
#include "draw.h"
#include "paint.h"
#include "polygon.h"

CDraw::CDraw(const Paint &s, output o)
{
	SetOutput(o);
	hdc = GetDC(hwnd); // получаем контекст отображения

	SetStyle(s); // устанавливаем стиль рисования
}

CDraw::~CDraw()
{
	// восстанавливаем предыдущие значения пера и кисти
	SelectPen(hdc, old_PB.hPen);
	SelectBrush(hdc, old_PB.hBrush);
	// удаляем текущие значения пера и кисти
	DeletePen(curr_PB.hPen);
	DeleteBrush(curr_PB.hBrush);
	// удаляем значения пера и кисти для отрисовки фона
	DeletePen(back_PB.hPen);
	DeleteBrush(back_PB.hBrush);

	ReleaseDC(hwnd, hdc); // освобождаем контекст отображения

	if (pi.hProcess != NULL) // если был открыт процесс
	{
		// закрываем созданное окно по его дескриптору
		TerminateProcess(pi.hProcess, NO_ERROR);
		CloseHandle(pi.hProcess); // закрываем дескриптор созданного окна
		CloseHandle(pi.hThread);
	}
}

// устанавливаем стиль рисования
void CDraw::SetStyle(const Paint &s)
{
	// устанавливаем текущие значения пера
	PEN dp = s.GetPen();
	curr_PB.hPen = CreatePen(dp.style, dp.width, s.GetPenColorCR());
	// устанавливаем текущие значения кисти
	int st = s.GetBrushStyle();
	if (st == 0) // однотонный цвет заливки
		curr_PB.hBrush = CreateSolidBrush(s.GetBrushColorCR());
	else // заливка - штриховка
		curr_PB.hBrush = CreateHatchBrush(st, s.GetBrushColorCR());

	// устанавливаем текущие значения цветов текста и его фона
	SetTextColor(hdc, s.GetTextColorCR());
	SetBkColor(hdc, s.GetBackColorCR());

	// создаем цвет пера и кисти для отрисовки фона
	//back_PB.hPen = CreatePen(PS_NULL, 0, s.GetBackColorCR());
	back_PB.hPen = GetStockPen(NULL_PEN);
	back_PB.hBrush = CreateSolidBrush(s.GetBackColorCR());

	// сохраняем предыдущие значения пера и кисти
	// если значения ненулевые значит ранее уже были сохранены пред. знач.
	if (old_PB.hPen == NULL) old_PB.hPen = SelectPen(hdc, curr_PB.hPen);
	if (old_PB.hBrush == NULL) old_PB.hBrush = SelectBrush(hdc, curr_PB.hBrush);
}

void CDraw::SetOutput(output o)
{
	switch (o)
	{
	case CONSOL:
		hwnd = GetConsoleWindow(); // получаем идентификатор окна
		break;
	case NOTEPAD:
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
		si.dwX = 100;
		si.dwY = 100;
		si.dwXSize = 100;
		si.dwYSize = 100;
		
		/*
		// 2-ой параметр lpCommandLine должен передаватся только переменной, иначе - исключение
		// TCHAR -> tchar.h
		TCHAR szCmdLine[] = _T("c:\\Windows\\notepad.exe");
		CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		*/
		CreateProcess(L"c:\\Windows\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		//WaitForSingleObject(pi.hProcess, INFINITE);
		Sleep(100);
		hwnd = FindWindow(L"Notepad", NULL);
		break;
	}
}

// отчищаем экран цветом заднего фона
void CDraw::Clear()
{
	// устанавливаем перо и кисть
	HPEN hCurrPen = SelectPen(hdc, back_PB.hPen);
	HBRUSH hCurrBrush = SelectBrush(hdc, back_PB.hBrush);

	GetClientRect(hwnd, &rt); // получаем размер окна
	POINT screen[4] = { { 0, 0 }, { 0, rt.bottom }, { rt.right, rt.bottom }, { rt.right, 0 } };
	Polygon(hdc, screen, 4); // зарисовываем многоугольник
	
	SelectPen(hdc, hCurrPen);
	SelectBrush(hdc, hCurrBrush);
}

void CDraw::Show(const CPolygon &p, bool update)
{
	if (update) Clear();

	try
	{
		if (!p.IsExist()) throw 1;
		//if (!p.IsConvex()) throw 2;
	}
	catch (int i) // обработка ошибок
	{
		switch (i)
		{
		case 1:
			std::cerr << "Многоугольник имеет меньше 3-х вершин, не может быть нарисован" << std::endl;
			return;
		/*case 2:
			std::cerr << "Многоугольник не является выпуклым" << std::endl;*/
		}
	}

	int n = p.GetCountVertexes();
	POINT *v = new POINT[n];
	for (int i = 0; i < n; i++)	v[i] = p.GetVertex(i);

	Polygon(hdc, v, n); // рисуем прямоугольник

	delete []v;
}