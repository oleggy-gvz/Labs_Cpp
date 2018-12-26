#pragma once

#include <windows.h>
#include <fstream>

// ����� ����� ������ � ������� ������������ ���������
class Shape
{
protected:
	POINT *vert = NULL; // ������ ��������� ������
	int count = 0; // ���-�� �����
	
	void CreateVertexes(int n); // �������� n ����� ������
	void FreeVertexes(); // ������������ ����� ������
	virtual void Clear(); // ��������� ��������� ������

public:
	Shape();
	Shape(int n, POINT *v); // ����������� �������� ������ � �� ������� ������
	Shape(int n, POINT v, ...); // ����������� �������� ������ � ���������� ���-��� ������
	~Shape();

	void SetFigure(int n, POINT *v); // ������� ������ �� ������� ������
	void SetVertex(int n, POINT v); // ��������� ��������� ��� n-�� ������� ������

	POINT GetVertex(int n) const; // ���������� ���������� n-�� ������� ������
	int GetCountVertexes() const; // ���������� ���-�� ������ ������

	virtual void Show() = 0; // ���������� ������
	virtual void Save(std::ofstream &b_out) = 0; // ���������� ������ ������ � ����
	virtual int Load(std::ifstream &b_in) = 0; // �������� ������ ������ �� �����
};