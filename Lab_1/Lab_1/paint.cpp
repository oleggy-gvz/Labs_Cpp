#include "paint.h"

Paint::Paint()
{
	// по умолчанию линия границ - сплошная, толщиной - 1 пиксель, цвет - белый
	SetPenStyle(PS_SOLID, 1);
	SetPenColor({255, 255, 255 });
	SetBrushStyle(0); // без заливки
	SetBrushColor({ 0, 0, 0 }); // по умолчанию цвет заливки фигур черный
	SetTextColor({ 255, 255, 255 }); // по умолчанию цвет текста - белый
	SetBackColor({ 0, 0, 0 }); // по умолчанию цвет фона - черный
}

Paint::Paint(PEN p, BRUSH b)
{
	SetPen(p);
	SetBrush(b);
}

Paint::Paint(const Paint &s)
{
	SetStyle(s);
}

// установить весь стиль
void Paint::SetStyle(const Paint &s)
{
	SetPen(s.GetPen());
	SetBrush(s.GetBrush());
	SetTextColor(s.GetTextColor());
	SetBackColor(s.GetBackColor());
}

// установить перо
void Paint::SetPen(PEN p)
{
	pen = p;
}

// установить стиль пера
void Paint::SetPenStyle(int s, int w)
{
	pen.style = s;
	pen.width = w;
}

// установить цвет пера
void Paint::SetPenColor(COLOR c)
{
	pen.color = c;
}

// установить кисть
void Paint::SetBrush(BRUSH b )
{
	brush = b;
}

// установить стиль кисти
void Paint::SetBrushStyle(int s)
{
	brush.style = s;
}

// установить цвет кисти
void Paint::SetBrushColor(COLOR c)
{
	brush.color = c;
}

// установить цвет текста
void Paint::SetTextColor(COLOR c)
{
	c_txt = c;
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

// получить стиль пера
int Paint::GetPenStyle() const
{
	return pen.style;
}

// получить толщину пера
int Paint::GetPenWidth() const
{
	return pen.width;
}

// получить цвет пера
COLOR Paint::GetPenColor() const
{
	return pen.color;
}

// получить цвет пера
COLORREF Paint::GetPenColorCR() const
{
	return RGB(pen.color.r, pen.color.g, pen.color.b);
}

// получить данные кисти
BRUSH Paint::GetBrush() const
{
	return brush;
}

// получить стиль кисти
int Paint::GetBrushStyle() const
{
	return brush.style;
}

// получить цвет кисти
COLOR Paint::GetBrushColor() const
{
	return brush.color;
}

// получить цвет кисти
COLORREF Paint::GetBrushColorCR() const
{
	return RGB(brush.color.r, brush.color.g, brush.color.b);
}

// получить цвет текста
COLOR Paint::GetTextColor() const
{
	return c_txt;
}

// получить цвет текста
COLORREF Paint::GetTextColorCR() const
{
	return RGB(c_txt.r, c_txt.g, c_txt.b);
}

// получить цвет фона
COLOR Paint::GetBackColor() const
{
	return c_bak;
}

// получить цвет фона
COLORREF Paint::GetBackColorCR() const
{
	return RGB(c_bak.r, c_bak.g, c_bak.b);
}