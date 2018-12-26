#include <windowsx.h>
#include <iostream>
#include "draw_polygon.h"

void DrawPolygon::SetOutput(output o)
{
	// если дескриптор окна уже создан и не поменялся
	if (hwnd != NULL && o == out) return;
	out = o;

	switch (out)
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

// устанавливаем системные значения пера и кисти
void DrawPolygon::CreatePenBrush()
{
	if (hwnd == NULL)
	{
		std::cerr << "CreatePenBrush: не установлен дескриптор окна" << std::endl;
		return;
	}
	hdc = GetDC(hwnd); // получаем контекст отображения

	// устанавливаем текущие значения пера
	PEN dp = GetPen();
	curr_PB.hPen = CreatePen(dp.style, dp.width, GetPenColorCR());
	// устанавливаем текущие значения кисти
	int st = GetBrushStyle();
	if (st == -1) // без заливки однотонный цвет заливки
		curr_PB.hBrush = CreateSolidBrush(GetBrushColorCR());
	else if (st == -2) // сплошная заливка цветом фона
		curr_PB.hBrush = CreateSolidBrush(GetBackColorCR());
	else // заливка - штриховка
		curr_PB.hBrush = CreateHatchBrush(st, GetBrushColorCR());

	// устанавливаем текущие значения цвета фона
	SetBkColor(hdc, GetBackColorCR());

	// создаем цвет пера и кисти для отрисовки фона
	//back_PB.hPen = CreatePen(PS_NULL, 0, s.GetBackColorCR());
	back_PB.hPen = GetStockPen(NULL_PEN);
	back_PB.hBrush = CreateSolidBrush(GetBackColorCR());

	// сохраняем предыдущие значения пера и кисти
	// если значения ненулевые значит ранее уже были сохранены пред. знач.
	if (old_PB.hPen == NULL) old_PB.hPen = SelectPen(hdc, curr_PB.hPen);
	else SelectPen(hdc, curr_PB.hPen);

	if (old_PB.hBrush == NULL) old_PB.hBrush = SelectBrush(hdc, curr_PB.hBrush);
	else SelectBrush(hdc, curr_PB.hBrush);
}

void DrawPolygon::FreePenBrush()
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
	hwnd = NULL;
}

DrawPolygon::DrawPolygon(output o)
{
	SetOutput(o);
	CreatePenBrush();
}

DrawPolygon::DrawPolygon(const CPolygon &p, output o)
{
	SetDrawPolygon(p, o);
}

DrawPolygon::DrawPolygon(const Paint &s, const CPolygon &p, output o)
{
	SetDrawPolygon(s, p, o);
}

DrawPolygon::DrawPolygon(DrawPolygon &dp)
{
	SetDrawPolygon(dp);
}

DrawPolygon::~DrawPolygon()
{
	FreePenBrush();
}

void DrawPolygon::UpdatePenBrush()
{
	CreatePenBrush();
}

void DrawPolygon::SetDrawPolygon(const CPolygon &p, output o)
{
	SetPolygon(p); // установим многоугольник

	SetOutput(o);
	CreatePenBrush();
}

void DrawPolygon::SetDrawPolygon(const Paint &s, output o)
{
	SetPaint(s); // установим стили

	SetOutput(o);
	CreatePenBrush();
}

void DrawPolygon::SetDrawPolygon(const Paint &s, const CPolygon &p, output o)
{	
	SetPaint(s); // установим стили
	SetPolygon(p); // установим многоугольник

	SetOutput(o);
	CreatePenBrush();
}

void DrawPolygon::SetDrawPolygon(DrawPolygon &dp)
{
	SetPaint(dp.GetPaint()); // установим стили
	SetPolygon(dp.GetPolygon()); // установим многоугольник

	SetOutput(dp.GetOutput());
	CreatePenBrush();
}

output DrawPolygon::GetOutput() const // получение способа вывода изображения
{
	return out;
}

// отчищаем экран цветом заднего фона
void DrawPolygon::ClearScreen()
{
	// устанавливаем перо и кисть
	HPEN hCurrPen = SelectPen(hdc, back_PB.hPen);
	HBRUSH hCurrBrush = SelectBrush(hdc, back_PB.hBrush);

	GetClientRect(hwnd, &rt); // получаем размер окна
	POINT screen[4] = { { 0, 0 },{ 0, rt.bottom },{ rt.right, rt.bottom },{ rt.right, 0 } };
	Polygon(hdc, screen, 4); // зарисовываем многоугольник пером/кистью back_PB

	SelectPen(hdc, hCurrPen);
	SelectBrush(hdc, hCurrBrush);
}

void DrawPolygon::SetUpdateScreen(bool upd)
{
	update_screen = upd;
}

void DrawPolygon::Show()
{
	if (update_screen) ClearScreen(); // обновление экрана
	try
	{
		if (!IsExist()) throw;
	}
	catch (...) // обработка ошибок
	{
		std::cerr << "многоугольник имеет меньше 3-х вершин, не может быть нарисован" << std::endl;
		return;
	}

	int n = GetCountVertexes();
	POINT *v = new POINT[n];
	for (int i = 0; i < n; i++)	v[i] = GetVertex(i);

	Polygon(hdc, v, n); // рисуем прямоугольник

	delete []v;
}