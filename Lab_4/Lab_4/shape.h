#pragma once

#include <windows.h>
#include <fstream>

// ����� ������ (�������� �� �����)
class Shape
{	
	POINT *vert = NULL; // ������ ��������� ������
	int count = 0; // ���-�� ����� ������

	// �������� ������ ���-�� ������
	void CreateVertexes(int n);
	// �������� (������������) ������
	void FreeVertexes(); 

public:
	Shape();
	// ����������� �������� ������ �� ������� ������
	Shape(int n, POINT *v);
	// ����������� �������� ������ � ���������� ���-��� ������
	Shape(int n, POINT v, ...);
	// ����������� ����������� ������
	Shape(const Shape& p);
	~Shape();

	// �������� ������ �� ������� ������
	void SetShape(int n, POINT *v);
	// ����������� ������ �� ������
	void CopyShape(const Shape& p);
	// ��������� ��������� ��� n-�� ������� ������
	void SetVertex(int n, POINT v);
	// ���������� ���������� n-�� ������� ������
	POINT GetVertex(int n) const;
	// ���������� ���-�� ������ ������
	int GetCountVertexes() const;
	// ��������� ��������� ������
	virtual void Clear();
	// ���������� ������
	virtual bool Show();
	// ���������� ������ ������ � ����
	virtual void Save(std::ofstream &b_out);
	// �������� ������ ������ �� �����
	virtual void Load(std::ifstream &b_in);
};