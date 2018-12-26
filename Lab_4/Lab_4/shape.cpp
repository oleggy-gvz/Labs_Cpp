#include "shape.h"
#include <iostream>

// �������� ������ ���-�� ������
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

// �������� (������������) ������
void Shape::FreeVertexes()
{
	if (vert != NULL) delete[] vert;
}

// �������� ������
void Shape::Clear()
{
	FreeVertexes();

	vert = NULL;
	count = 0;
}

// ����������� �� ���������
Shape::Shape()
{}

// ����������� �������� ������ � �� ������� ������
Shape::Shape(int n, POINT *v)
{
	SetShape(n, v);
}

// ����������� �������� ������ � ���������� ���-��� ������
Shape::Shape(int n, POINT v, ...)
{
	SetShape(n, &v);
}

// ����������� ����������� ������ �� ������
Shape::Shape(const Shape& p)
{
	CopyShape(p);
}

Shape::~Shape()
{
	FreeVertexes();
}

// �������� ������ �� ������� ������
void Shape::SetShape(int n, POINT *v)
{
	CreateVertexes(n); // ������������� ����� ���-�� ������
	for (int i = 0; i < count; i++)	vert[i] = v[i]; // �������� �������
}

// ����������� ������ �� ������
void Shape::CopyShape(const Shape& p)
{
	int n = p.GetCountVertexes();
	CreateVertexes(n);
	for (int i = 0; i < count; i++) vert[i] = p.GetVertex(i); // �������� �������
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

// ���������� ���������� � ������
bool Shape::Show()
{
	if (count == 0)
	{
		std::cout << "������ ������, ��� ������" << std::endl;
		return false;
	}
	
	for (int i = 0; i < count; i++)
	{
		std::cout << "����� " << i << ": ";
		std::cout << "x = " << vert[i].x << ", y = " << vert[i].y << std::endl;
	}
	return true;
}

// ��������� ��������� ������ �� ������ Shape � ����
void Shape::Save(std::ofstream &b_out)
{
	POINT v;
	int n = GetCountVertexes();
	b_out.write((char*)&n, sizeof(n)); // ����� ���-�� ������

	for (int i = 0; i < n; i++)	// ���������� ������ ������
	{
		v = GetVertex(i);
		b_out.write((char*)&v, sizeof(v));
	}
}

// ��������� ��������� ������ �� ����� � ����� Shape
void Shape::Load(std::ifstream &b_in)
{
	POINT v;
	int n;

	b_in.read((char*)&n, sizeof(n)); // ������ ���-�� ������
	CreateVertexes(n); // ������� ������ ������

	for (int i = 0; i < n; i++) // ��������� ������ ������
	{
		b_in.read((char*)&v, sizeof(v));
		SetVertex(i, v);
	}
}