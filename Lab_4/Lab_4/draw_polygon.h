#pragma once

#include <windows.h>
#include "polygon.h"
#include "paint.h"

enum output {CONSOL, NOTEPAD}; // ��� ���� ������ �����������

// ��������� ���� � �����
struct PEN_BRUSH
{
	HPEN hPen;
	HBRUSH hBrush;
};

// ����� ��������� ��������������
class DrawPolygon : public Paint, public CPolygon
{
	output out = CONSOL; // ��� ���� ������ �����������
	bool change_output = true; // ���� ��������� ���� ������ 
	// ���������� ������ ��� ���������, �� ��������� ������ ���������
	bool update_screen = true;

	// ��������� �������� ���� � �����

	HWND hwnd = NULL; // ������������� ����
	// ������������� ������� ��� ������� � ��������� ����� DrawPolygon::hwnd �����
	friend void CopyHwnd(DrawPolygon &dest, const DrawPolygon &scr);

	HDC hdc = NULL; // �������� �����������
	RECT rt;  // ������� ������� ����
	
	PEN_BRUSH curr_PB; // ������� �������� ���� � �����
	PEN_BRUSH back_PB; // �������� ���� � ����� ��� ��������� ����
	PEN_BRUSH old_PB = { NULL }; // ������ �������� ���� � �����
	STARTUPINFO si = { NULL }; // ��������� ��� ������� ��������
	PROCESS_INFORMATION pi = { NULL }; // ��������� � ����������� � ���������� ��������

	void CreateGDIOutput(); // ��������/��������� ���� ������ �����������
	void DeleteGDIOutput(); // ��������/��������� ���� ������ �����������	
	void CreateGDIPenBrush(); // ������� ���� � ����� GDI �� �c������� Paint	
	void DeleteGDIPenBrush(); // ������� ���� � ����� GDI 

public:

	DrawPolygon();
	// ��������� ��������� ��������������
	DrawPolygon(const CPolygon &p, const Paint &s, output o = CONSOL);
	// ����������� ����������� ��������� �������������� �� �������
	DrawPolygon(const DrawPolygon &dp);
	~DrawPolygon();

	// ��������� ��������� �������� ��������������
	void SetDrawPolygon(const CPolygon &p, const Paint &s, output o = CONSOL);
	// ����������� ��������� �������� ��������������
	void CopyDrawPolygon(const DrawPolygon &dp);

	void SetUpdateScreen(bool upd); // ���������� ����� ��� ���������
	void SetOutput(output o); // ��������� ������� ������ �����������
	output GetOutput() const; // ��������� ������� ������ �����������
	void ClearScreen(); // �������� ���� ������ ����	
	bool Show(); // �������� ������������ ������������� �� ������

	// ���������� ��������� �������������� � ����
	void Save(std::ofstream &b_out);
	// �������� ��������� �������������� �� �����
	void Load(std::ifstream &b_in);
};