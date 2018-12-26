#include "style.h"

CStyle::CStyle()
{
	// по умолчанию линия границ - сплошная, толщиной - 1 пиксель, цвет - белый
	SetPenStyle(PS_SOLID, 1);
	SetPenColor({255, 255, 255 });
	SetBrushStyle(0); // без заливки
	SetBrushColor({ 0, 0, 0 }); // по умолчанию цвет заливки фигур черный
	SetTextColor({ 255, 255, 255 }); // по умолчанию цвет текста - белый
	SetBackColor({ 0, 0, 0 }); // по умолчанию цвет фона - черный
}

CStyle::CStyle(PEN p, BRUSH b)
{
	SetPen(p);
	SetBrush(b);
}

CStyle::CStyle(const CStyle &s)
{
	SetStyle(s);
}

// установить весь стиль
void CStyle::SetStyle(const CStyle &s)
{
	SetPen(s.GetPen());
	SetBrush(s.GetBrush());
	SetTextColor(s.GetTextColor());
	SetBackColor(s.GetBackColor());
}

// установить перо
void CStyle::SetPen(PEN p)
{
	pen = p;
}

// установить стиль пера
void CStyle::SetPenStyle(int s, int w)
{
	pen.style = s;
	pen.width = w;
}

// установить цвет пера
void CStyle::SetPenColor(COLOR c)
{
	pen.color = c;
}

// установить кисть
void CStyle::SetBrush(BRUSH b)
{
	brush = b;
}

// установить стиль кисти
void CStyle::SetBrushStyle(int s)
{
	brush.style = s;
}

// установить цвет кисти
void CStyle::SetBrushColor(COLOR c)
{
	brush.color = c;
}

// установить цвет текста
void CStyle::SetTextColor(COLOR c)
{
	c_txt = c;
}

// установить цвет фона
void CStyle::SetBackColor(COLOR c)
{
	c_bak = c;
}

// получить перо
PEN CStyle::GetPen() const
{
	return pen;
}

// получить стиль пера
int CStyle::GetPenStyle() const
{
	return pen.style;
}

// получить толщину пера
int CStyle::GetPenWidth() const
{
	return pen.width;
}

// получить цвет пера
COLOR CStyle::GetPenColor() const
{
	return pen.color;
}

// получить цвет пера
COLORREF CStyle::GetPenColorCR() const
{
	return RGB(pen.color.r, pen.color.g, pen.color.b);
}

// получить данные кисти
BRUSH CStyle::GetBrush() const
{
	return brush;
}

// получить стиль кисти
int CStyle::GetBrushStyle() const
{
	return brush.style;
}

// получить цвет кисти
COLOR CStyle::GetBrushColor() const
{
	return brush.color;
}

// получить цвет кисти
COLORREF CStyle::GetBrushColorCR() const
{
	return RGB(brush.color.r, brush.color.g, brush.color.b);
}

// получить цвет текста
COLOR CStyle::GetTextColor() const
{
	return c_txt;
}

// получить цвет текста
COLORREF CStyle::GetTextColorCR() const
{
	return RGB(c_txt.r, c_txt.g, c_txt.b);
}

// получить цвет фона
COLOR CStyle::GetBackColor() const
{
	return c_bak;
}

// получить цвет фона
COLORREF CStyle::GetBackColorCR() const
{
	return RGB(c_bak.r, c_bak.g, c_bak.b);
}