#include "paint.h"

// конструктор по умолчанию
Paint::Paint()
{	
	/*SetPen({ PS_SOLID, 1, { 255, 255, 255 } }); // линия границ сплошная, толщиной 1 пиксель, цвет линий белый
	SetBrush({ -1, { 0, 0, 0 } }); // однотонная заливка определенным цветом (черным)
	SetBackColor({ 0, 0, 0 }); // по умолчанию цвет фона - черный*/
}

// конструктор с установкой стиля
Paint::Paint(PEN p, BRUSH b, COLOR c)
{
	SetPaint(p, b, c);
}

// конструктор копирования стиля из другого
Paint::Paint(const Paint &s)
{
	CopyPaint(s);
}

// установка стиля из другого существующего
void Paint::SetPaint(PEN p, BRUSH b, COLOR c)
{
	pen = p;
	brush = b;
	c_bak = c;
}

// установка стиля из другого существующего
void Paint::CopyPaint(const Paint &s)
{
	pen = s.GetPen();
	brush = s.GetBrush();
	c_bak = s.GetBackColor();
}

// установить перо
void Paint::SetPen(PEN p)
{
	pen = p;
}

// установить кисть
void Paint::SetBrush(BRUSH b )
{
	brush = b;
}

// установить цвет фона
void Paint::SetBackColor(COLOR c)
{
	c_bak = c;
}

// получить перо
PEN Paint::GetPen() const
{
	return pen;
}

// получить данные кисти
BRUSH Paint::GetBrush() const
{
	return brush;
}

// получить цвет фона
COLOR Paint::GetBackColor() const
{
	return c_bak;
}