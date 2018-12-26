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

	bool CheckConvex(int n, POINT *v); // ��������� ������������� �� ����������
	bool CheckExist(int n, POINT *v); // ��������� ����������� ����������� ��������������

public:
	CPolygon();
	CPolygon(int n, POINT *v);
	CPolygon(int n, POINT v, ...); 
	CPolygon(const CPolygon& p); // ����������� �������� ������ �� �������
	~CPolygon();

	// �������� ��������������
	bool IsConvex() const; // �������� ������� ����������
	bool IsExist() const; // �������� ������� ������������� (�����������)
	void ResetStatus(); // ���������� ��������� ��������������

	// ��������� ������
	POINT GetVertex(int n) const; // ���������� ���������� n-�� ������� ��������������
	int GetCountVertexes() const; // ���������� ���-�� ������ ��������������

	// ��������� ������
	void SetAllVertexes(int n, POINT *v); // ������� ���� ��������� ������
	void SetVertex(int n, POINT v); // ��������� ��������� POINT ��� n-�� �������
	void Clear(); // ��������� ���� ������ ��������������


	void Save(std::ofstream &b_out); // ���������� ������ ����������� � ����
	int Load(std::ifstream &b_in); // �������� ������ ����������� � ����
};