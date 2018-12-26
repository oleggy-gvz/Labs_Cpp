#pragma once

#include "draw_polygon.h"

class CombiDrawPolygon : public DrawPolygon
{
	DrawPolygon f_in; // ���������� ������������ �������������
	// ������������� ������� ��� ������� � ��������� ����� CombiDrawPolygon::f_in �����
	friend void CopyInternalDrawPolygon(DrawPolygon &in, const CombiDrawPolygon &cdp);

public:
	CombiDrawPolygon();
	// ����������� �������� ���������������� �������������� �� ���� �������� ���������������
	CombiDrawPolygon(const DrawPolygon &dp_out, const DrawPolygon &dp_in);
	// ����������� ����������� ���������������� �������������� �� �������������
	CombiDrawPolygon(const CombiDrawPolygon &cdp);
	~CombiDrawPolygon();

	// �������� ����������������  �������������� �� ���� �������� ���������������
	void SetCombiPolygon(const DrawPolygon &dp_out, const DrawPolygon &dp_in);
	// ����������� ���������������� ��������� �������� ��������������
	void CopyCombiPolygon(const CombiDrawPolygon &cdp);
	// �������� ��������������� ������������ ������������� �� ������
	bool Show();

	// ��������� ��������� ������ �� ������ CombiDrawPolygon � ����
	void Save(std::ofstream &b_out);
	// ��������� ��������� ������ �� ����� � ����� CombiDrawPolygon
	void Load(std::ifstream &b_in);
};