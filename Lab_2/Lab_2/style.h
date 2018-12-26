#pragma once

#include <windows.h>

typedef unsigned char uchar;

struct COLOR
{
	uchar r; // �������
	uchar g; // �������
	uchar b; // �����
};

// �������������� ����
struct PEN
{
	int style; // ����� ����
	int width; // ������ ����
	COLOR color; // ���� ����
};

// �������������� ����
struct BRUSH
{
	int style; // ����� ��������� �����, 0 - ��������
	COLOR color; // ���� �����
};

// ����� ��������� ������ � ������
class CStyle
{
		PEN pen; // ������ ����
		BRUSH brush; // ������ ����� (�������)
		COLOR c_txt; // ���� ������
		COLOR c_bak; // ���� ���� ������

public:
	CStyle();
	CStyle(PEN p, BRUSH b);
	CStyle(const CStyle &s);

	void SetStyle(const CStyle &s); // ���������� ���� �����

	void SetPen(PEN p); // ���������� ����
	void SetPenStyle(int s, int w); // ���������� ����� ����
	void SetPenColor(COLOR c); // ���������� ���� ����

	void SetBrush(BRUSH b); // ���������� �����
	void SetBrushStyle(int s); // ���������� ����� �����
	void SetBrushColor(COLOR c); // ���������� ���� �����

	void SetTextColor(COLOR c); // ���������� ���� ������
	void SetBackColor(COLOR c); // ���������� ���� ����

	PEN GetPen() const; // �������� ����
	int GetPenStyle() const; // �������� ����� ����
	int GetPenWidth() const; // �������� ������� ����
	COLOR GetPenColor() const; // �������� ���� ����
	COLORREF GetPenColorCR() const; // �������� ���� ���� COLORREF

	BRUSH GetBrush() const; // �������� ������ �����
	int GetBrushStyle() const; // �������� ����� �����
	COLOR GetBrushColor() const; // �������� ���� �����
	COLORREF GetBrushColorCR() const; // �������� ���� ����� COLORREF

	COLOR GetTextColor() const; // �������� ���� ������
	COLORREF GetTextColorCR() const; // �������� ���� ������ COLORREF
	COLOR GetBackColor() const; // �������� ���� ����
	COLORREF GetBackColorCR() const; // �������� ���� ���� COLORREF
};