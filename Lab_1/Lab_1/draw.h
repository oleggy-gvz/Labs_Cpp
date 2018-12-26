#pragma once

#include <windows.h>
#include "paint.h"
#include "polygon.h"

enum output {CONSOL, NOTEPAD};

struct PEN_BRUSH
{
	HPEN hPen;
	HBRUSH hBrush;
};

// класс рисования
class CDraw
{
	HWND hwnd; // идентификатор окна
	HDC hdc; // контекст отображения
	RECT rt; // размеры области окна

	PEN_BRUSH curr_PB; // текущие значение пера и кисти
	PEN_BRUSH back_PB; // значения пера и кисти для отрисовки фона
	PEN_BRUSH old_PB = {NULL, NULL}; // старое значения пера и кисти

	STARTUPINFO si = { NULL }; // структура для запуска процесса
	PROCESS_INFORMATION pi = { NULL };

public:
	CDraw(const Paint &s, output o = CONSOL);
	~CDraw();

	void SetStyle(const Paint &s); // установить стиль
	void SetOutput(output o);
	void Clear(); // отчистка окна цветом фона
	void Show(const CPolygon &p, bool update = true); // показать изображение на экране
};