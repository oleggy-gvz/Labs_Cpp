#include "paint.h"

Paint::Paint()
{
	// �� ��������� ����� ������ - ��������, �������� - 1 �������, ���� - �����
	SetPenStyle(PS_SOLID, 1);
	SetPenColor({255, 255, 255 });
	SetBrushStyle(-1); // ����� ������� ����� - ��� �������
	SetBrushColor({ 0, 0, 0 }); // �� ��������� ���� ������� ����� ������
	SetBackColor({ 0, 0, 0 }); // �� ��������� ���� ���� - ������
}

Paint::Paint(PEN p, BRUSH b)
{
	SetPen(p);
	SetBrush(b);

	SetBackColor({ 0, 0, 0 }); // �� ��������� ���� ���� - ������
}

Paint::Paint(const Paint &s)
{
	SetPaint(s);
}

// ��������� ����� �� ������� �������������
void Paint::SetPaint(const Paint &s)
{
	SetPen(s.GetPen());
	SetBrush(s.GetBrush());
	SetBackColor(s.GetBackColor());
}

// ���������� ����
void Paint::SetPen(PEN p)
{
	pen = p;
}

// ���������� ����� ����
void Paint::SetPenStyle(int s, int w)
{
	pen.style = s;
	pen.width = w;
}

// ���������� ���� ����
void Paint::SetPenColor(COLOR c)
{
	pen.color = c;
}

// ���������� �����
void Paint::SetBrush(BRUSH b )
{
	brush = b;
}

// ���������� ����� �����
void Paint::SetBrushStyle(int s)
{
	brush.style = s;
}

// ���������� ���� �����
void Paint::SetBrushColor(COLOR c)
{
	brush.color = c;
}

// ���������� ���� ����
void Paint::SetBackColor(COLOR c)
{
	c_bak = c;
}

// ��������� �����
Paint &Paint::GetPaint()
{
	return *this;
}

// �������� ����
PEN Paint::GetPen() const
{
	return pen;
}

// �������� ����� ����
int Paint::GetPenStyle() const
{
	return pen.style;
}

// �������� ������� ����
int Paint::GetPenWidth() const
{
	return pen.width;
}

// �������� ���� ����
COLOR Paint::GetPenColor() const
{
	return pen.color;
}

// �������� ���� ����
COLORREF Paint::GetPenColorCR() const
{
	return RGB(pen.color.r, pen.color.g, pen.color.b);
}

// �������� ������ �����
BRUSH Paint::GetBrush() const
{
	return brush;
}

// �������� ����� �����
int Paint::GetBrushStyle() const
{
	return brush.style;
}

// �������� ���� �����
COLOR Paint::GetBrushColor() const
{
	return brush.color;
}

// �������� ���� �����
COLORREF Paint::GetBrushColorCR() const
{
	return RGB(brush.color.r, brush.color.g, brush.color.b);
}

// �������� ���� ����
COLOR Paint::GetBackColor() const
{
	return c_bak;
}

// �������� ���� ����
COLORREF Paint::GetBackColorCR() const
{
	return RGB(c_bak.r, c_bak.g, c_bak.b);
}