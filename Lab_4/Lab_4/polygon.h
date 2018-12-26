#pragma once

#include <windows.h>
#include "shape.h"

// ��������� ������ - �������������
class CPolygon: public Shape
{
	bool exist = false; // ������� ������������� ��������������
	bool convex = false; // ������� ���������� ��������������

	// ��������� ����������� ����������� ��������������
	bool CheckExist(POINT *v, int n);
	// ��������� ������������� �� ����������
	bool CheckConvex(POINT *v, int n);

public:
	CPolygon();
	// ����������� �������� �������������� �� ������� ������
	CPolygon(int n, POINT *v); 	
	// ����������� �������� �������������� � ���������� ���-��� ������
	CPolygon(int n, POINT v, ...);
	// ����������� ����������� ��������������
	CPolygon(const CPolygon& p); 
	~CPolygon();
	
	// ������� �������������� �� ������� ������		
	void SetPolygon(int n, POINT *v); 
	// �������� ������������� �� �������
	void CopyPolygon(const CPolygon& p);
	// ��������� �������������
	void Clear();

	// �������� ��������������
	// �������� ������� ������������� (�����������)
	bool IsExist() const;
	// �������� ������� ����������
	bool IsConvex() const;
	// ���������� ��������� ��������������
	void UpdateStatus(); 

	// �������� ���������� � ��������������
	bool Show(); 
	// ���������� ������ ������ � ����
	void Save(std::ofstream &b_out);
	// �������� ������ ������ �� �����
	void Load(std::ifstream &b_in); 
};