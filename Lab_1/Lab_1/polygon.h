#pragma once

#include <windows.h>
#include <fstream>

class CPolygon
{
	POINT *vert = NULL; // ������ ������
	int count = 0; // ���-�� ������

	bool convex = false; // ������� ����������
	bool exist = false; // ������� �������������

	int CreateVertexes(int n); // �������� n ������ ��������������
	void FreeVertexes(); // ������������ ������ ��������������

	bool CheckConvex(POINT *v, int n); // ��������� ������������� �� ����������
	bool CheckExist(POINT *v, int n); // ��������� ����������� ����������� ��������������

public:
	CPolygon();
	CPolygon(int n, POINT *v);
	CPolygon(int n, POINT ver, ...); 
	CPolygon(const CPolygon& p); // ����������� �������� ������ �� �������
	~CPolygon();

	// �������� ��������������
	bool IsConvex() const; // �������� ������� ����������
	bool IsExist() const; // �������� ������� ������������� (�����������)
	void ResetStatus(); // ���������� ��������� ��������������

	void SetVertex(int n, POINT v); // ��������� ��������� n-�� ������� ��������������
	POINT GetVertex(int n) const; // ���������� ���������� n-�� ������� ��������������
	int GetCountVertexes() const; // ���������� ���-�� ������ ��������������

	void SetAllVertexes(int n, POINT *v); // ������� ���� ��������� ������
	void Clear(); // ��������� ���� ������ ��������������

	void Save(std::ofstream &b_out); // ���������� ������ ����������� � ����
	int Load(std::ifstream &b_in); // �������� ������ ����������� � ����
};