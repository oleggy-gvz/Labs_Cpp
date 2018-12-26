#include "paint.h"

// ����������� �� ���������
Paint::Paint()
{	
	/*SetPen({ PS_SOLID, 1, { 255, 255, 255 } }); // ����� ������ ��������, �������� 1 �������, ���� ����� �����
	SetBrush({ -1, { 0, 0, 0 } }); // ���������� ������� ������������ ������ (������)
	SetBackColor({ 0, 0, 0 }); // �� ��������� ���� ���� - ������*/
}

// ����������� � ���������� �����
Paint::Paint(PEN p, BRUSH b, COLOR c)
{
	SetPaint(p, b, c);
}

// ����������� ����������� ����� �� �������
Paint::Paint(const Paint &s)
{
	CopyPaint(s);
}

// ��������� ����� �� ������� �������������
void Paint::SetPaint(PEN p, BRUSH b, COLOR c)
{
	pen = p;
	brush = b;
	c_bak = c;
}

// ��������� ����� �� ������� �������������
void Paint::CopyPaint(const Paint &s)
{
	pen = s.GetPen();
	brush = s.GetBrush();
	c_bak = s.GetBackColor();
}

// ���������� ����
void Paint::SetPen(PEN p)
{
	pen = p;
}

// ���������� �����
void Paint::SetBrush(BRUSH b )
{
	brush = b;
}

// ���������� ���� ����
void Paint::SetBackColor(COLOR c)
{
	c_bak = c;
}

// �������� ����
PEN Paint::GetPen() const
{
	return pen;
}

// �������� ������ �����
BRUSH Paint::GetBrush() const
{
	return brush;
}

// �������� ���� ����
COLOR Paint::GetBackColor() const
{
	return c_bak;
}