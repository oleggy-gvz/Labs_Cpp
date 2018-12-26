#pragma once

#include <windows.h>

typedef unsigned char uchar;

// структура цвет
struct COLOR
{
	uchar r; // красный
	uchar g; // зеленый
	uchar b; // синий
};

// структура характеристики пера
struct PEN
{
	int style; // стиль пера
	int width; // ширина пера
	COLOR color; // цвет пера
};

// структура характеристики кисти
struct BRUSH
{
	int style; // стиль штриховки кисти, 0 - сплошная
	COLOR color; // цвет кисти
};

// стиль рисования фигуры
class Paint
{
	PEN pen = { PS_SOLID, 1, { 255, 255, 255 } }; // данные пера	
	BRUSH brush = { -1, { 0, 0, 0 } }; // данные кисти (заливки)
	COLOR c_bak = { 0, 0, 0 }; // цвет фона

public:
	// конструктор по умолчанию
	Paint(); 
	// конструктор с установкой стиля
	Paint(PEN p, BRUSH b, COLOR c = { 0, 0, 0 });
	// конструктор копирования стиля из другого
	Paint(const Paint &s); 

	// установка стиля
	void SetPaint(PEN p, BRUSH b, COLOR c = { 0, 0, 0 });
	// копируем стиль из другого
	void CopyPaint(const Paint &s); 

	// установить перо
	void SetPen(PEN p);
	// установить кисть
	void SetBrush(BRUSH);
	// установить цвет фона
	void SetBackColor(COLOR c); 

	// получить перо
	PEN GetPen() const;
	// получить данные кисти
	BRUSH GetBrush() const;
	// получить цвет фона
	COLOR GetBackColor() const;
};