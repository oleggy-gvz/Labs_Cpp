#include <windowsx.h>
#include <iostream>
#include "draw_polygon.h"

void CopyHwnd(DrawPolygon &dest, const DrawPolygon &scr)
{
	// ���������� ���������� ������������� ����
	dest.hwnd = scr.hwnd;
	// �� �������������� ����
	dest.change_output = false;
}

// ��������/��������� ���� ������ �����������
void DrawPolygon::CreateGDIOutput()
{
	DeleteGDIOutput(); // ������� ������ ����

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
		DWORD dwExitCode;
		if (CreateProcess(L"c:\\Windows\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			// ���� ���� ���� ������� �� ����� ����� ��� + �� ������� �������� � 100 ��
			dwExitCode = WaitForSingleObject(pi.hProcess, 100);
		}
		else
		{
			std::cerr << "CreateGDIOutput: ������ " << GetLastError() << std::endl;
		}
		hwnd = FindWindow(L"Notepad", NULL);
		break;
	}
}

// ��������/��������� ���� ������ �����������
void DrawPolygon::DeleteGDIOutput()
{
	if (hwnd == NULL) return; // ���� ���� �� ���� �������
	if (pi.hProcess == NULL) return; // ���� �� ��� ������ �������
	
	TerminateProcess(pi.hProcess, NO_ERROR); // ��������� �������
	CloseHandle(pi.hProcess); // ��������� ���������� ���������� ����
	CloseHandle(pi.hThread);

	hwnd = NULL;
}

// ������� ���� � ����� GDI �� �c������� Paint
void DrawPolygon::CreateGDIPenBrush()
{
	if (hwnd == NULL)
	{
		std::cerr << "UpdatePenBrush: �� ���������� ���������� ����" << std::endl;
		return;
	}
	hdc = GetDC(hwnd); // �������� �������� �����������

	// ������������� ������� �������� GDI ���� �� ���� Pant
	PEN pan = GetPen();
	COLORREF pan_c = RGB(pan.color.r, pan.color.g, pan.color.b);
	curr_PB.hPen = CreatePen(pan.style, pan.width, pan_c);

	// ������������� ������� �������� GDI ����� �� ����� Pant
	BRUSH brush = GetBrush();
	COLORREF bush_c = RGB(brush.color.r, brush.color.g, brush.color.b);
	
	// ������������� ������� �������� GDI ����� ���� �� ����� ���� Pant
	COLOR �ol = GetBackColor();
	COLORREF back_c = RGB(�ol.r, �ol.g, �ol.b);

	if (brush.style == -1) // ���������� ������� ������ �����
		curr_PB.hBrush = CreateSolidBrush(bush_c);
	else if (brush.style == -2) // �������� ������� ������ ����
		curr_PB.hBrush = CreateSolidBrush(back_c);
	else // ������� - ���������
		curr_PB.hBrush = CreateHatchBrush(brush.style, bush_c);

	// ������������� ������� �������� ����� ����
	SetBkColor(hdc, back_c);

	// ������� ���� ���� � ����� ��� ��������� ����
	//back_PB.hPen = CreatePen(PS_NULL, 0, s.GetBackColorCR());
	back_PB.hPen = GetStockPen(NULL_PEN);
	back_PB.hBrush = CreateSolidBrush(back_c);

	// ��������� ���������� �������� ���� � �����
	// ���� �������� ��������� ������ ����� ��� ���� ��������� ����. ����.
	if (old_PB.hPen == NULL) old_PB.hPen = SelectPen(hdc, curr_PB.hPen);
	else SelectPen(hdc, curr_PB.hPen);

	if (old_PB.hBrush == NULL) old_PB.hBrush = SelectBrush(hdc, curr_PB.hBrush);
	else SelectBrush(hdc, curr_PB.hBrush);
}

// ������� ���� � ����� GDI 
void DrawPolygon::DeleteGDIPenBrush()
{
	if (hdc == NULL) return; // ���� �������� ����������� �� ��� ������

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
}

// ����������� �� ���������
DrawPolygon::DrawPolygon()
{}

// ����������� �������� ��������� �������� ��������������
DrawPolygon::DrawPolygon(const CPolygon &p, const Paint &s, output o)
{
	SetDrawPolygon(p, s, o);
}

// ����������� ����������� ��������� �������� �������������� �� �������
DrawPolygon::DrawPolygon(const DrawPolygon &dp)
{
	CopyDrawPolygon(dp);
}

DrawPolygon::~DrawPolygon()
{
	DeleteGDIPenBrush();
	DeleteGDIOutput();
}

// �������� ��������� �������� ��������������
void DrawPolygon::SetDrawPolygon(const CPolygon &p, const Paint &s, output o)
{	
	CopyPolygon(p);
	CopyPaint(s);
	SetOutput(o);
}

// ����������� ����������� ��������� �������� �������������� �� �������
void DrawPolygon::CopyDrawPolygon(const DrawPolygon &dp)
{
	CopyPolygon(dp);
	CopyPaint(dp);
	SetOutput(dp.GetOutput());
}

// ��������� ������� ������ �����������
void DrawPolygon::SetOutput(output o)
{
	if (o != out) // ���� ��� ������ ���������
	{
		out = o;
		change_output = true; // ��� ��������� ������ ���� �� �����
	}
}

// ��������� ������� ������ �����������
output DrawPolygon::GetOutput() const
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

	// �������� ������������ ������������� �� ������
bool DrawPolygon::Show()
{
	// ���� ���� �� ����� ���������, ��������� �� ������� �� ��� ���
	// ���� �������, ���� ����� ������� ��������
	if (!change_output && GetDC(hwnd) == NULL) change_output = true;
	if (change_output)
	{
			CreateGDIOutput(); // ������� ����� ���� ��� ������ ���� ������
			change_output = false; // � ����������� ������� ��������� ���� ������ �� �����
	}
	// ������ ��������� ���� � ����� � ��� �.�. � ������������ �����
	// ��� ���� ������� ����� ������������ ��������
	CreateGDIPenBrush(); 

	if (update_screen) ClearScreen(); // ���������� ������
	try
	{
		if (!IsExist()) throw 1;
	}
	catch (int i) // ��������� ������
	{
		std::cerr << "������������� ����� ������ 3-� ������, � �� ����� ���� ���������" << std::endl;
		std::cerr << "������� ������� ������:" << std::endl;
		CPolygon::Show();

		return false;
	}

	int n = GetCountVertexes();
	POINT *v = new POINT[n];
	for (int i = 0; i < n; i++)	v[i] = GetVertex(i); // �������� �������
	Polygon(hdc, v, n); // ������ �������������
	delete []v;

	return true;
}

// ��������� ��������� ������ �� ������ DrawPolygon � ����
void DrawPolygon::Save(std::ofstream &b_out)
{
	CPolygon::Save(b_out);

	// ��������� ������ �����
	PEN pen = GetPen(); // ������ ����
	BRUSH brush = GetBrush(); // ������ ����� (�������)
	COLOR c_bak = GetBackColor(); // ���� ����

	b_out.write((char*)&pen, sizeof(pen)); // ������ ����
	b_out.write((char*)&brush, sizeof(brush)); // ������ ����� (�������)
	b_out.write((char*)&c_bak, sizeof(c_bak));  // ���� ����

	b_out.write((char*)&out, sizeof(out));  // �����
	b_out.write((char*)&update_screen, sizeof(update_screen)); // ���������� ������
}

// ��������� ��������� ������ �� ����� � ����� DrawPolygon
void DrawPolygon::Load(std::ifstream &b_in)
{
	CPolygon::Load(b_in);

	PEN pen; // ������ ����
	BRUSH brush; // ������ ����� (�������)
	COLOR c_bak; // ���� ����

	b_in.read((char*)&pen, sizeof(pen)); // ������ ����
	b_in.read((char*)&brush, sizeof(brush)); // ������ ����� (�������)
	b_in.read((char*)&c_bak, sizeof(c_bak)); // ���� ����

	SetPaint(pen, brush, c_bak); // ��������� �����

	b_in.read((char*)&out, sizeof(out)); // �����
	b_in.read((char*)&update_screen, sizeof(update_screen)); // ���������� ������
}