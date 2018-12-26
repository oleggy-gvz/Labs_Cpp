#pragma once

#include <windows.h>
#include "shape.h"

class CPolygon: public Shape
{
	bool convex; // ������� ����������
	bool exist; // ������� �������������

	bool CheckConvex(POINT *v, int n); // ��������� ������������� �� ����������
	bool CheckExist(POINT *v, int n); // ��������� ����������� ����������� ��������������
	void Clear(); // ��������� ��������� ������

public:
	CPolygon();
	CPolygon(int n, POINT *v); // ����������� �������� �������������� �� ������� ������
	CPolygon(int n, POINT v, ...); // ����������� �������� �������������� � ���������� ���-��� ������
	CPolygon(const CPolygon& p); // ����������� �������� �������������� �� �������
	~CPolygon();
	
	// �������� ��������������
	bool IsConvex() const; // �������� ������� ����������
	bool IsExist() const; // �������� ������� ������������� (�����������)
	void ResetStatus(); // ���������� ��������� ��������������
						
	void SetPolygon(int n, POINT *v); // ������� �������������� �� ������� ������
	void SetPolygon(const CPolygon& p); // �������� �������������� �� ������� �������������
	CPolygon& GetPolygon(); // ��������� ��������������

	void Show(); // �������� ���������� � ��������������
	void Save(std::ofstream &b_out); // ���������� ������ ������ � ����
	int Load(std::ifstream &b_in); // �������� ������ ������ �� �����
};