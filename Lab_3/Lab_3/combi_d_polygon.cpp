#include "combi_d_polygon.h"
#include <conio.h>

CombiDrawPolygon::CombiDrawPolygon(DrawPolygon &dp_in, DrawPolygon &dp_out)
{
	SetCombiPolygon(dp_in, dp_out);
}

CombiDrawPolygon::~CombiDrawPolygon()
{
	delete f_in;
	delete f_out;
}

void CombiDrawPolygon::SetCombiPolygon(DrawPolygon &dp_out, DrawPolygon &dp_in)
{
		f_in = new DrawPolygon(dp_in);
		f_out = new DrawPolygon(dp_out);
}

void CombiDrawPolygon::Show()
{
	f_out->Show(); // ������ ������� ������

	f_in->SetBrushColor(f_out->GetBackColor()); // ��������� ������� ���������� ������ ������ ���� ������ �������
	f_in->SetBrushStyle(-1); // ������ ��� ������� - ���������� ����
	f_in->UpdatePenBrush(); // ��������� ��������� ���� � �����
	f_in->SetUpdateScreen(false); // �� �������������� ����� ��� ��������� ���������� ������

	f_in->Show(); // ���������� ������
}