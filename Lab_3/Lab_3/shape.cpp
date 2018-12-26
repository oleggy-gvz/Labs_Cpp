#include "shape.h"
#include <iostream>

// ��������� ������ ���-�� ������ � ��������� ������ �� ���� ��������
void Shape::CreateVertexes(int n)
{
	if (n == count) return; // ���� ���-�� ������� �� ����������

	FreeVertexes(); // ������� �������	
	vert = new POINT[n]; // �������� ������ ��� ����� ���-�� ������
	if (vert == NULL)
	{
		std::cerr << "CreateVertexes: �� ���������� ������" << std::endl;
		exit(1);
	}
	count = n; // ���������� ����� ���-�� ������
}

// ������������ ������ ��������������
void Shape::FreeVertexes()
{
	if (vert != NULL) delete[] vert;
}

// ��������� ���� ������ ��������������
void Shape::Clear()
{
	FreeVertexes();

	vert = NULL;
	count = 0;
}

Shape::Shape()
{}

// ����������� �������� ������ � �� ������� ������
Shape::Shape(int n, POINT *v)
{
	SetFigure(n, v);
}

// ����������� �������� ������ � ���������� ���-��� ������
Shape::Shape(int n, POINT v, ...)
{
	SetFigure(n, &v);
}

Shape::~Shape()
{
	FreeVertexes();
}

// ��������� ��������� ��� n-�� ������� ������
void Shape::SetVertex(int n, POINT v)
{
	if (n > count || n < 0) 
		std::cerr << "SetVertex: ������� ������� � ������� �� ��������� ������������" << std::endl;
	vert[n] = v;
}

// ���������� ���������� n-�� ������� ������
POINT Shape::GetVertex(int n) const
{
	if (n > count || n < 0)
		std::cerr << "SetVertex: ������� ������� � ������� �� ��������� ������������" << std::endl;

	return vert[n];
}

// ���������� ���-�� ������ ������
int Shape::GetCountVertexes() const
{
	return count;
}

// ������� ������ �� ������� ������
void Shape::SetFigure(int n, POINT *v)
{
	CreateVertexes(n); // ������������� ����� ���-�� ������
	for (int i = 0; i < count; i++)	vert[i] = v[i]; // �������� �������
}