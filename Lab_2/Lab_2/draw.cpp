#include <windowsx.h>
#include <iostream>
#include "draw.h"
#include "style.h"
#include "polygon.h"

CDraw::CDraw(const CStyle &s, output o)
{
	SetOutput(o);
	hdc = GetDC(hwnd); // �������� �������� �����������

	SetStyle(s); // ������������� ����� ���������
}

CDraw::~CDraw()
{
	// ��������������� ���������� �������� ���� � �����
	SelectPen(hdc, hOldPen);
	SelectBrush(hdc, hOldBrush);
	// ������� ������� �������� ���� � �����
	DeletePen(hPen);
	DeleteBrush(hBrush);
	// ������� �������� ���� � ����� ��� ��������� ����
	DeletePen(hPenBack);
	DeleteBrush(hBrushBack);

	ReleaseDC(hwnd, hdc); // ����������� �������� �����������

	if (pi.hProcess != NULL) // ���� ��� ������ �������
	{
		// ��������� ��������� ���� �� ��� �����������
		TerminateProcess(pi.hProcess, NO_ERROR);
		CloseHandle(pi.hProcess); // ��������� ���������� ���������� ����
		CloseHandle(pi.hThread);
	}
}

// ������������� ����� ���������
void CDraw::SetStyle(const CStyle &s)
{
	// ������������� ������� �������� ����
	PEN dp = s.GetPen();
	hPen = CreatePen(dp.style, dp.width, s.GetPenColorCR());
	// ������������� ������� �������� �����
	int st = s.GetBrushStyle();
	if (st == 0) // ���������� ���� �������
		hBrush = CreateSolidBrush(s.GetBrushColorCR());
	else // ������� - ���������
		hBrush = CreateHatchBrush(st, s.GetBrushColorCR());

	// ������������� ������� �������� ������ ������ � ��� ����
	SetTextColor(hdc, s.GetTextColorCR());
	SetBkColor(hdc, s.GetBackColorCR());

	// ������� ���� ���� � ����� ��� ��������� ����
	//hPenBack = CreatePen(PS_NULL, 0, s.GetBackColorCR());
	hPenBack = GetStockPen(NULL_PEN);
	hBrushBack = CreateSolidBrush(s.GetBackColorCR());

	// ��������� ���������� �������� ���� � �����
	// ���� �������� ��������� ������ ����� ��� ���� ��������� ����. ����.
	if (hOldPen == NULL) hOldPen = SelectPen(hdc, hPen);
	if (hOldBrush == NULL) hOldBrush = SelectBrush(hdc, hBrush);
}

void CDraw::SetOutput(output o)
{
	switch (o)
	{
	case CONSOL:
		hwnd = GetConsoleWindow(); // �������� ������������� ����
		break;
	case NOTEPAD:
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
		si.dwX = 100;
		si.dwY = 100;
		si.dwXSize = 100;
		si.dwYSize = 100;
		
		/*
		// 2-�� �������� lpCommandLine ������ ����������� ������ ����������, ����� - ����������
		// TCHAR -> tchar.h
		TCHAR szCmdLine[] = _T("c:\\Windows\\notepad.exe");
		CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		*/
		CreateProcess(L"c:\\Windows\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		//WaitForSingleObject(pi.hProcess, INFINITE);
		Sleep(100);
		hwnd = FindWindow(L"Notepad", NULL);
		break;
	}
}

// �������� ����� ������ ������� ����
void CDraw::Clear()
{
	// ������������� ���� � �����
	HPEN hCurrPen = SelectPen(hdc, hPenBack);
	HBRUSH hCurrBrush = SelectBrush(hdc, hBrushBack);

	GetClientRect(hwnd, &rt); // �������� ������ ����
	POINT screen[4] = { { 0, 0 }, { 0, rt.bottom }, { rt.right, rt.bottom }, { rt.right, 0 } };
	Polygon(hdc, screen, 4); // ������������ �������������
	
	SelectPen(hdc, hCurrPen);
	SelectBrush(hdc, hCurrBrush);
}

void CDraw::Show(const CPolygon &p, bool update)
{
	if (update) Clear();

	try
	{
		if (!p.IsExist()) throw 1;
		//if (!p.IsConvex()) throw 2;
	}
	catch (int i) // ��������� ������
	{
		switch (i)
		{
		case 1:
			std::cerr << "������������� ����� ������ 3-� ������, �� ����� ���� ���������" << std::endl;
			return;
		/*case 2:
			std::cerr << "������������� �� �������� ��������" << std::endl;*/
		}
	}

	int n = p.GetCountVertexes();
	POINT *v = new POINT[n];
	for (int i = 0; i < n; i++)	v[i] = p.GetVertex(i);

	Polygon(hdc, v, n); // ������ �������������

	delete []v;
}