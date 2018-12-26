#include <windowsx.h>
#include <iostream>
#include "draw_polygon.h"

void DrawPolygon::SetOutput(output o)
{
	// ���� ���������� ���� ��� ������ � �� ���������
	if (hwnd != NULL && o == out) return;
	out = o;

	switch (out)
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

// ������������� ��������� �������� ���� � �����
void DrawPolygon::CreatePenBrush()
{
	if (hwnd == NULL)
	{
		std::cerr << "CreatePenBrush: �� ���������� ���������� ����" << std::endl;
		return;
	}
	hdc = GetDC(hwnd); // �������� �������� �����������

	// ������������� ������� �������� ����
	PEN dp = GetPen();
	curr_PB.hPen = CreatePen(dp.style, dp.width, GetPenColorCR());
	// ������������� ������� �������� �����
	int st = GetBrushStyle();
	if (st == -1) // ��� ������� ���������� ���� �������
		curr_PB.hBrush = CreateSolidBrush(GetBrushColorCR());
	else if (st == -2) // �������� ������� ������ ����
		curr_PB.hBrush = CreateSolidBrush(GetBackColorCR());
	else // ������� - ���������
		curr_PB.hBrush = CreateHatchBrush(st, GetBrushColorCR());

	// ������������� ������� �������� ����� ����
	SetBkColor(hdc, GetBackColorCR());

	// ������� ���� ���� � ����� ��� ��������� ����
	//back_PB.hPen = CreatePen(PS_NULL, 0, s.GetBackColorCR());
	back_PB.hPen = GetStockPen(NULL_PEN);
	back_PB.hBrush = CreateSolidBrush(GetBackColorCR());

	// ��������� ���������� �������� ���� � �����
	// ���� �������� ��������� ������ ����� ��� ���� ��������� ����. ����.
	if (old_PB.hPen == NULL) old_PB.hPen = SelectPen(hdc, curr_PB.hPen);
	else SelectPen(hdc, curr_PB.hPen);

	if (old_PB.hBrush == NULL) old_PB.hBrush = SelectBrush(hdc, curr_PB.hBrush);
	else SelectBrush(hdc, curr_PB.hBrush);
}

void DrawPolygon::FreePenBrush()
{
	// ��������������� ���������� �������� ���� � �����
	SelectPen(hdc, old_PB.hPen);
	SelectBrush(hdc, old_PB.hBrush);
	// ������� ������� �������� ���� � �����
	DeletePen(curr_PB.hPen);
	DeleteBrush(curr_PB.hBrush);
	// ������� �������� ���� � ����� ��� ��������� ����
	DeletePen(back_PB.hPen);
	DeleteBrush(back_PB.hBrush);

	ReleaseDC(hwnd, hdc); // ����������� �������� �����������

	if (pi.hProcess != NULL) // ���� ��� ������ �������
	{
		// ��������� ��������� ���� �� ��� �����������
		TerminateProcess(pi.hProcess, NO_ERROR);
		CloseHandle(pi.hProcess); // ��������� ���������� ���������� ����
		CloseHandle(pi.hThread);
	}
	hwnd = NULL;
}

DrawPolygon::DrawPolygon(output o)
{
	SetOutput(o);
	CreatePenBrush();
}

DrawPolygon::DrawPolygon(const CPolygon &p, output o)
{
	SetDrawPolygon(p, o);
}

DrawPolygon::DrawPolygon(const Paint &s, const CPolygon &p, output o)
{
	SetDrawPolygon(s, p, o);
}

DrawPolygon::DrawPolygon(DrawPolygon &dp)
{
	SetDrawPolygon(dp);
}

DrawPolygon::~DrawPolygon()
{
	FreePenBrush();
}

void DrawPolygon::UpdatePenBrush()
{
	CreatePenBrush();
}

void DrawPolygon::SetDrawPolygon(const CPolygon &p, output o)
{
	SetPolygon(p); // ��������� �������������

	SetOutput(o);
	CreatePenBrush();
}

void DrawPolygon::SetDrawPolygon(const Paint &s, output o)
{
	SetPaint(s); // ��������� �����

	SetOutput(o);
	CreatePenBrush();
}

void DrawPolygon::SetDrawPolygon(const Paint &s, const CPolygon &p, output o)
{	
	SetPaint(s); // ��������� �����
	SetPolygon(p); // ��������� �������������

	SetOutput(o);
	CreatePenBrush();
}

void DrawPolygon::SetDrawPolygon(DrawPolygon &dp)
{
	SetPaint(dp.GetPaint()); // ��������� �����
	SetPolygon(dp.GetPolygon()); // ��������� �������������

	SetOutput(dp.GetOutput());
	CreatePenBrush();
}

output DrawPolygon::GetOutput() const // ��������� ������� ������ �����������
{
	return out;
}

// �������� ����� ������ ������� ����
void DrawPolygon::ClearScreen()
{
	// ������������� ���� � �����
	HPEN hCurrPen = SelectPen(hdc, back_PB.hPen);
	HBRUSH hCurrBrush = SelectBrush(hdc, back_PB.hBrush);

	GetClientRect(hwnd, &rt); // �������� ������ ����
	POINT screen[4] = { { 0, 0 },{ 0, rt.bottom },{ rt.right, rt.bottom },{ rt.right, 0 } };
	Polygon(hdc, screen, 4); // ������������ ������������� �����/������ back_PB

	SelectPen(hdc, hCurrPen);
	SelectBrush(hdc, hCurrBrush);
}

void DrawPolygon::SetUpdateScreen(bool upd)
{
	update_screen = upd;
}

void DrawPolygon::Show()
{
	if (update_screen) ClearScreen(); // ���������� ������
	try
	{
		if (!IsExist()) throw;
	}
	catch (...) // ��������� ������
	{
		std::cerr << "������������� ����� ������ 3-� ������, �� ����� ���� ���������" << std::endl;
		return;
	}

	int n = GetCountVertexes();
	POINT *v = new POINT[n];
	for (int i = 0; i < n; i++)	v[i] = GetVertex(i);

	Polygon(hdc, v, n); // ������ �������������

	delete []v;
}