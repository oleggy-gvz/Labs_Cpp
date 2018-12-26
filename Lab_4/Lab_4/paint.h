#pragma once

#include <windows.h>

typedef unsigned char uchar;

// ��������� ����
struct COLOR
{
	uchar r; // �������
	uchar g; // �������
	uchar b; // �����
};

// ��������� �������������� ����
struct PEN
{
	int style; // ����� ����
	int width; // ������ ����
	COLOR color; // ���� ����
};

// ��������� �������������� �����
struct BRUSH
{
	int style; // ����� ��������� �����, 0 - ��������
	COLOR color; // ���� �����
};

// ����� ��������� ������
class Paint
{
	PEN pen = { PS_SOLID, 1, { 255, 255, 255 } }; // ������ ����	
	BRUSH brush = { -1, { 0, 0, 0 } }; // ������ ����� (�������)
	COLOR c_bak = { 0, 0, 0 }; // ���� ����

public:
	// ����������� �� ���������
	Paint(); 
	// ����������� � ���������� �����
	Paint(PEN p, BRUSH b, COLOR c = { 0, 0, 0 });
	// ����������� ����������� ����� �� �������
	Paint(const Paint &s); 

	// ��������� �����
	void SetPaint(PEN p, BRUSH b, COLOR c = { 0, 0, 0 });
	// �������� ����� �� �������
	void CopyPaint(const Paint &s); 

	// ���������� ����
	void SetPen(PEN p);
	// ���������� �����
	void SetBrush(BRUSH);
	// ���������� ���� ����
	void SetBackColor(COLOR c); 

	// �������� ����
	PEN GetPen() const;
	// �������� ������ �����
	BRUSH GetBrush() const;
	// �������� ���� ����
	COLOR GetBackColor() const;
};