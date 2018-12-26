#include "style.h"

CStyle::CStyle()
{
	// �� ��������� ����� ������ - ��������, �������� - 1 �������, ���� - �����
	SetPenStyle(PS_SOLID, 1);
	SetPenColor({255, 255, 255 });
	SetBrushStyle(0); // ��� �������
	SetBrushColor({ 0, 0, 0 }); // �� ��������� ���� ������� ����� ������
	SetTextColor({ 255, 255, 255 }); // �� ��������� ���� ������ - �����
	SetBackColor({ 0, 0, 0 }); // �� ��������� ���� ���� - ������
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

// ���������� ���� �����
void CStyle::SetStyle(const CStyle &s)
{
	SetPen(s.GetPen());
	SetBrush(s.GetBrush());
	SetTextColor(s.GetTextColor());
	SetBackColor(s.GetBackColor());
}

// ���������� ����
void CStyle::SetPen(PEN p)
{
	pen = p;
}

// ���������� ����� ����
void CStyle::SetPenStyle(int s, int w)
{
	pen.style = s;
	pen.width = w;
}

// ���������� ���� ����
void CStyle::SetPenColor(COLOR c)
{
	pen.color = c;
}

// ���������� �����
void CStyle::SetBrush(BRUSH b)
{
	brush = b;
}

// ���������� ����� �����
void CStyle::SetBrushStyle(int s)
{
	brush.style = s;
}

// ���������� ���� �����
void CStyle::SetBrushColor(COLOR c)
{
	brush.color = c;
}

// ���������� ���� ������
void CStyle::SetTextColor(COLOR c)
{
	c_txt = c;
}

// ���������� ���� ����
void CStyle::SetBackColor(COLOR c)
{
	c_bak = c;
}

// �������� ����
PEN CStyle::GetPen() const
{
	return pen;
}

// �������� ����� ����
int CStyle::GetPenStyle() const
{
	return pen.style;
}

// �������� ������� ����
int CStyle::GetPenWidth() const
{
	return pen.width;
}

// �������� ���� ����
COLOR CStyle::GetPenColor() const
{
	return pen.color;
}

// �������� ���� ����
COLORREF CStyle::GetPenColorCR() const
{
	return RGB(pen.color.r, pen.color.g, pen.color.b);
}

// �������� ������ �����
BRUSH CStyle::GetBrush() const
{
	return brush;
}

// �������� ����� �����
int CStyle::GetBrushStyle() const
{
	return brush.style;
}

// �������� ���� �����
COLOR CStyle::GetBrushColor() const
{
	return brush.color;
}

// �������� ���� �����
COLORREF CStyle::GetBrushColorCR() const
{
	return RGB(brush.color.r, brush.color.g, brush.color.b);
}

// �������� ���� ������
COLOR CStyle::GetTextColor() const
{
	return c_txt;
}

// �������� ���� ������
COLORREF CStyle::GetTextColorCR() const
{
	return RGB(c_txt.r, c_txt.g, c_txt.b);
}

// �������� ���� ����
COLOR CStyle::GetBackColor() const
{
	return c_bak;
}

// �������� ���� ����
COLORREF CStyle::GetBackColorCR() const
{
	return RGB(c_bak.r, c_bak.g, c_bak.b);
}