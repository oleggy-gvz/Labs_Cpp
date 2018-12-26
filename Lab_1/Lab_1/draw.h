#pragma once

#include <windows.h>
#include "paint.h"
#include "polygon.h"

enum output {CONSOL, NOTEPAD};

struct PEN_BRUSH
{
	HPEN hPen;
	HBRUSH hBrush;
};

// ����� ���������
class CDraw
{
	HWND hwnd; // ������������� ����
	HDC hdc; // �������� �����������
	RECT rt; // ������� ������� ����

	PEN_BRUSH curr_PB; // ������� �������� ���� � �����
	PEN_BRUSH back_PB; // �������� ���� � ����� ��� ��������� ����
	PEN_BRUSH old_PB = {NULL, NULL}; // ������ �������� ���� � �����

	STARTUPINFO si = { NULL }; // ��������� ��� ������� ��������
	PROCESS_INFORMATION pi = { NULL };

public:
	CDraw(const Paint &s, output o = CONSOL);
	~CDraw();

	void SetStyle(const Paint &s); // ���������� �����
	void SetOutput(output o);
	void Clear(); // �������� ���� ������ ����
	void Show(const CPolygon &p, bool update = true); // �������� ����������� �� ������
};