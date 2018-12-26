#pragma once

#include <windows.h>

typedef unsigned char uchar;

struct COLOR
{
	uchar r; // красный
	uchar g; // зеленый
	uchar b; // синий
};

// характеристики пера
struct PEN
{
	int style; // стиль пера
	int width; // ширина пера
	COLOR color; // цвет пера
};

// характеристики пера
struct BRUSH
{
	int style; // стиль штриховки кисти, 0 - сплошная
	COLOR color; // цвет кисти
};

// стиль рисования фигуры и текста
class Paint
{
	PEN pen; // данные пера
	BRUSH brush; // данные кисти (заливки)
	COLOR c_txt; // цвет текста
	COLOR c_bak; // цвет фона текста

public:
	Paint();
	Paint(PEN p, BRUSH b);
	Paint(const Paint &s);

	void SetStyle(const Paint &s); // установить весь стиль

	void SetPen(PEN p); // установить перо
	void SetPenStyle(int s, int w); // установить стиль пера
	void SetPenColor(COLOR c); // установить цвет пера

	void SetBrush(BRUSH); // установить кисть
	void SetBrushStyle(int); // установить стиль кисти
	void SetBrushColor(COLOR c); // установить цвет кисти

	void SetTextColor(COLOR c); // установить цвет текста
	void SetBackColor(COLOR c); // установить цвет фона

	PEN GetPen() const; // получить перо
	int GetPenStyle() const; // получить стиль пера
	int GetPenWidth() const; // получить толщину пера
	COLOR GetPenColor() const; // получить цвет пера
	COLORREF GetPenColorCR() const; // получить цвет пера COLORREF

	BRUSH GetBrush() const; // получить данные кисти
	int GetBrushStyle() const; // получить стиль кисти
	COLOR GetBrushColor() const; // получить цвет кисти
	COLORREF GetBrushColorCR() const; // получить цвет кисти COLORREF

	COLOR GetTextColor() const; // получить цвет текста
	COLORREF GetTextColorCR() const; // получить цвет текста COLORREF
	COLOR GetBackColor() const; // получить цвет фона
	COLORREF GetBackColorCR() const; // получить цвет фона COLORREF
};