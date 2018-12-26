#pragma once

#include <windows.h>
#include "style.h"
#include "polygon.h"

enum output {CONSOL, NOTEPAD};

// класс рисования
class CDraw
{
	HWND hwnd; // идентификатор окна
	HDC hdc; // контекст отображения
	RECT rt; // размеры области окна

	HPEN hPen; // текущие значение пера
	HBRUSH hBrush; // текущие значениt кисти

	HPEN hPenBack; // значения пера для отрисовки фона
	HBRUSH hBrushBack; // значения кисти для отрисовки фона
	
	HPEN hOldPen = NULL; // старое значения пера
	HBRUSH hOldBrush = NULL; // старое значения кисти

	STARTUPINFO si = { NULL }; // структура для запуска процесса
	PROCESS_INFORMATION pi = { NULL }; // информация о запущенном процессе

public:
	CDraw(const CStyle &s, output o = CONSOL);
	~CDraw();

	void SetStyle(const CStyle &s); // установить стиль
	void SetOutput(output o); // установить вывод
	void Clear(); // отчистка окна цветом фона
	void Show(const CPolygon &p, bool update = true); // показать изображение на экране
};