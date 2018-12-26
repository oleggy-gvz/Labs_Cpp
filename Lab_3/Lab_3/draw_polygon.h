#pragma once

#include <windows.h>
#include "polygon.h"
#include "paint.h"

enum output {CONSOL, NOTEPAD};

// ��������� ���� � �����
struct PEN_BRUSH
{
	HPEN hPen;
	HBRUSH hBrush;
};

// ����� ������ ������ �� �����
class DrawPolygon : public Paint, public CPolygon
{
	HWND hwnd = NULL; // ������������� ����
	HDC hdc; // �������� �����������
	RECT rt; // ������� ������� ����
	output out;
	bool update_screen = true; // ���������� ������ ��� ���������

	PEN_BRUSH curr_PB; // ������� �������� ���� � �����
	PEN_BRUSH back_PB; // �������� ���� � ����� ��� ��������� ����
	PEN_BRUSH old_PB = { NULL }; // ������ �������� ���� � �����

	STARTUPINFO si = { NULL }; // ��������� ��� ������� ��������
	PROCESS_INFORMATION pi = { NULL };

	void SetOutput(output o); // ��������� ������ �����������
	void CreatePenBrush(); // ������� ���� � ����� �� �c������� Paint
	void FreePenBrush(); // ������� ���� � �����

public:

	DrawPolygon(output o = CONSOL);
	DrawPolygon(const CPolygon &p, output o = CONSOL);
	DrawPolygon(const Paint &s, const CPolygon &p, output o = CONSOL);
	DrawPolygon(DrawPolygon &dp);
	~DrawPolygon();

	void SetDrawPolygon(const CPolygon &p, output o = CONSOL);
	void SetDrawPolygon(const Paint &s, output o = CONSOL);
	void SetDrawPolygon(const Paint &s, const CPolygon &p, output o = CONSOL);
	void SetDrawPolygon(DrawPolygon &dp);
	void SetUpdateScreen(bool upd); // ���������� ����� ��� ���������
	void UpdatePenBrush();

	output GetOutput() const; // ��������� ������� ������ �����������

	void ClearScreen(); // �������� ���� ������ ����
	
	void Show(); // �������� ����������� �� ������
};