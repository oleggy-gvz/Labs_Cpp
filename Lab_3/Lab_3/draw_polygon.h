#pragma once

#include <windows.h>
#include "polygon.h"
#include "paint.h"

enum output {CONSOL, NOTEPAD};

// структура пера и кисти
struct PEN_BRUSH
{
	HPEN hPen;
	HBRUSH hBrush;
};

// класс вывода фигуры на экран
class DrawPolygon : public Paint, public CPolygon
{
	HWND hwnd = NULL; // идентификатор окна
	HDC hdc; // контекст отображения
	RECT rt; // размеры области окна
	output out;
	bool update_screen = true; // обновление экрана при рисовании

	PEN_BRUSH curr_PB; // текущие значение пера и кисти
	PEN_BRUSH back_PB; // значения пера и кисти для отрисовки фона
	PEN_BRUSH old_PB = { NULL }; // старое значения пера и кисти

	STARTUPINFO si = { NULL }; // структура для запуска процесса
	PROCESS_INFORMATION pi = { NULL };

	void SetOutput(output o); // установка вывода изображения
	void CreatePenBrush(); // создаем перо и кисть на оcновании Paint
	void FreePenBrush(); // удаляем перо и кисть

public:

	DrawPolygon(output o = CONSOL);
	DrawPolygon(const CPolygon &p, output o = CONSOL);
	DrawPolygon(const Paint &s, const CPolygon &p, output o = CONSOL);
	DrawPolygon(DrawPolygon &dp);
	~DrawPolygon();

	void SetDrawPolygon(const CPolygon &p, output o = CONSOL);
	void SetDrawPolygon(const Paint &s, output o = CONSOL);
	void SetDrawPolygon(const Paint &s, const CPolygon &p, output o = CONSOL);
	void SetDrawPolygon(DrawPolygon &dp);
	void SetUpdateScreen(bool upd); // обновления эрана при рисовании
	void UpdatePenBrush();

	output GetOutput() const; // получение способа вывода изображения

	void ClearScreen(); // отчистка окна цветом фона
	
	void Show(); // показать изображение на экране
};