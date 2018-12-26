#pragma once

#include <windows.h>
#include "style.h"
#include "polygon.h"

enum output {CONSOL, NOTEPAD};

// ����� ���������
class CDraw
{
	HWND hwnd; // ������������� ����
	HDC hdc; // �������� �����������
	RECT rt; // ������� ������� ����

	HPEN hPen; // ������� �������� ����
	HBRUSH hBrush; // ������� �������t �����

	HPEN hPenBack; // �������� ���� ��� ��������� ����
	HBRUSH hBrushBack; // �������� ����� ��� ��������� ����
	
	HPEN hOldPen = NULL; // ������ �������� ����
	HBRUSH hOldBrush = NULL; // ������ �������� �����

	STARTUPINFO si = { NULL }; // ��������� ��� ������� ��������
	PROCESS_INFORMATION pi = { NULL }; // ���������� � ���������� ��������

public:
	CDraw(const CStyle &s, output o = CONSOL);
	~CDraw();

	void SetStyle(const CStyle &s); // ���������� �����
	void SetOutput(output o); // ���������� �����
	void Clear(); // �������� ���� ������ ����
	void Show(const CPolygon &p, bool update = true); // �������� ����������� �� ������
};