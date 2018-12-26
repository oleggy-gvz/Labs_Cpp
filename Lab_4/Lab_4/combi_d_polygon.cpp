#include "combi_d_polygon.h"
#include <conio.h>

// ����������� �� ���������
CombiDrawPolygon::CombiDrawPolygon()
{}

// ����������� �������� ���������������� �������������� �� ���� �������� ���������������
CombiDrawPolygon::CombiDrawPolygon(const DrawPolygon &dp_out, const DrawPolygon &dp_in)
{
	SetCombiPolygon(dp_out, dp_in);
}

// ����������� ����������� ���������������� �������������� �� �������������
CombiDrawPolygon::CombiDrawPolygon(const CombiDrawPolygon &cdp)
{
	CopyCombiPolygon(cdp);
}

CombiDrawPolygon::~CombiDrawPolygon()
{}

// �������� ����������������  �������������� �� ���� �������� ���������������
void CombiDrawPolygon::SetCombiPolygon(const DrawPolygon &dp_out, const DrawPolygon &dp_in)
{
	CopyDrawPolygon(dp_out); // �������� ������� ������
	f_in.CopyDrawPolygon(dp_in); // �������� ���������� �������� �������������  
}

// ����������� ���������������� ��������� �������� ��������������
void CombiDrawPolygon::CopyCombiPolygon(const CombiDrawPolygon &cdp)
{
	CopyDrawPolygon(cdp); // �������� ������� ������
	// ������������� ������� ��� ������� � ��������� ����� cdp.f_in
	// �������� ������������� �� cdp.f_in � f_in
	CopyInternalDrawPolygon(f_in, cdp);
}

// ������������� ������� ��� ������� � ��������� ����� CombiDrawPolygon::f_in �����
void CopyInternalDrawPolygon(DrawPolygon &dp, const CombiDrawPolygon &cdp)
{
	// �������� ������������ ������������� � dp �� ��������� ����� ������ cdp.f_in (DrawPolygon)
	dp.CopyDrawPolygon(cdp.f_in);
}

// �������� ��������������� ������������ ������������� �� ������
bool CombiDrawPolygon::Show()
{
	bool res;
	//SetOutput(CONSOL);
	res = DrawPolygon::Show(); // ������ ������� ������

	// ���� ������� (�������) ������ �� ���������� �� �� ������ ������
	if (res == false) return false; 
	// ��������� ������� ���������� ������ ������ ���� ������ �������
	// ����� ������� - ���������� ����	
	f_in.SetBrush({ -1, GetBackColor() });
	f_in.SetOutput(GetOutput()); // ����� � �� �� ���� ���� ������� ������� �������������
	f_in.SetUpdateScreen(false); // �� �������������� ����� ��� ��������� ���������� ������

	// �������� �� ��������� ����� �������� ������ hwnd � ��������� ����� f_in.hwnd
	if (GetOutput() != CONSOL) // ���� ���� ������ �� ����������
		CopyHwnd(f_in, *this); // �������� hwnd � ������� ������ �� ����������

	f_in.Show(); // ������ ���������� ������

	return true;
}

// ��������� ��������� ������ �� ������ DrawPolygon � ����
void CombiDrawPolygon::Save(std::ofstream &b_out)
{
	DrawPolygon::Save(b_out);
	f_in.Save(b_out);
}

// ��������� ��������� ������ �� ����� � ����� DrawPolygon
void CombiDrawPolygon::Load(std::ifstream &b_in)
{
	DrawPolygon::Load(b_in);
	f_in.Load(b_in);
}