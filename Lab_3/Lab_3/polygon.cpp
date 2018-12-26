#include "polygon.h"
#include <iostream>

// ��������� ���� ������ ��������������
void CPolygon::Clear()
{
	Shape::Clear();
	convex = false;
	exist = false;
}

// ��������� ����������� ����������� ��������������
// ������ ����� ���� �� 3 ������� � ���������� ������������
bool CPolygon::CheckExist(POINT *v, int n)
{
	if (n < 3) return false;
	// ���� ���������� ���� ����� ����������, ������ ����� �����������
	for (int i = 1, c = 0; i <= n; i++)
	{
		if (v[i - 1].x != v[i % n].x || v[i - 1].y != v[i % n].y)
		{
			c++;
			if (c == 3) return true;
		}	
	}
	return false;
}

/*
��� ��������� �������������� ��� ��������� ������������ �������� ������ ��� 
������ ������� ����� ����������� �����, ���� ��� �� ��� �� �������� �������������
������|AB| = ������|B| - ������|A|, �.�. AB_x = Bx-Ax, AB_y= By-Ay
|a|*|b| = ax*by - ay*bx
��������� ������������ ������ ����, ���� ������ ������ ��������� ����� ��
�������, � ������ ����, ���� ������.
*/
bool CPolygon::CheckConvex(POINT *v, int n)
{
	if (n == 3) return true; // ����������� ������ ��������

	int i, j, k;
	int flag = 0;
	long long z;

	for (i = 0; i < n; i++)
	{
		// i - ���������� �������
		j = (i + 1) % n; // j - ��������������� �������
		k = (i + 2) % n; // k - ��������� �������
		// ������������ �������� |ij| � |jk|
		z = (v[j].x - v[i].x) * (v[k].y - v[j].y) - (v[j].y - v[i].y) * (v[k].x - v[j].x);
		if (z < 0) flag |= 1; // ���������� � ������ ��� - 1
		else if (z > 0)	flag |= 2; // ���������� �� ������ ��� - 1
		// ���� � ����� ����� �� 1 �.�. 11 (dec) -> 3, �� ���� ��������� ��� ������ ������
		if (flag == 3) return false; 	
	}
	if (flag != 0) return true;
	return false;
}

CPolygon::CPolygon() : convex(false), exist(false)
{}

// ����������� �������� �������������� �� ������� ������
CPolygon::CPolygon(int n, POINT *v)
{
	SetPolygon(n, v);
}

// ����������� �������� �������������� � ���������� ���-��� ������
CPolygon::CPolygon(int n, POINT v, ...)
{
	SetPolygon(n, &v);
}

// ����������� �������� �������������� �� �������
CPolygon::CPolygon(const CPolygon& p)
{
	SetPolygon(p);
}

CPolygon::~CPolygon()
{
	FreeVertexes();
}

// ���������� ������� ����������
bool CPolygon::IsConvex() const
{
	return convex;
}

// ���������� ������� �������������
bool CPolygon::IsExist() const
{
	return exist;
}

// ���������� ������� ��������������
void CPolygon::ResetStatus()
{
	exist = CheckExist(vert, count); // �������� ������������� �� �������������
	convex = CheckConvex(vert, count); // �������� ������������� �� ����������
}

// ������� ���� ��������� ��������������
void CPolygon::SetPolygon(int n, POINT *v)
{
	SetFigure(n, v);
	ResetStatus();
}

// �������� �������������� �� ������� �������������
void CPolygon::SetPolygon(const CPolygon& p)
{
	int n = p.GetCountVertexes();
	CreateVertexes(n);
	for (int i = 0; i < count; i++) vert[i] = p.GetVertex(i); // �������� �������
	// �������� ������� �� ������� �������������
	convex = p.IsConvex();
	exist = p.IsExist();
}

// ��������� �������������� �� ������� �������������
CPolygon& CPolygon::GetPolygon()
{
	return *this;
}

// ���������� ���������� � ��������������
void CPolygon::Show()
{
	if (count == 0)
	{
		std::cout << "������������� �� �����" << std::endl;
		return;
	}	
	std::cout << "������������� ������� �� " << count << " ������(�)" << std::endl;
	
	for (int i = 0; i < count; i++)
	{
		std::cout << "������� " << i << ": ";
		std::cout << "x = " << vert[i].x << ", y = " << vert[i].y << std::endl;
	}
	if (!exist)
	{
		std::cout << "������������� ����� ������ 3-� ������, �� ����� ���� ���������" << std::endl;
		return;
	}
	std::cout << "������������� ��������: " << (convex ? "��" : "���") << std::endl;
}

// ��������� ��������� ������ �� ������ CPolygon � ����
void CPolygon::Save(std::ofstream &b_out)
{
	POINT v;
	int n = GetCountVertexes();
	b_out.write((char*)&n, sizeof(n));

	// ���������� ������ ������ � ����
	for (int i = 0; i < n; i++)
	{
		v = GetVertex(i);
		b_out.write((char*)&v, sizeof(POINT));
	}
}

// ��������� ��������� ������ �� ����� � ����� CPolygon
int CPolygon::Load(std::ifstream &b_in)
{
	POINT v;
	int n;

	try
	{
		b_in.read((char*)&n, sizeof(n));
		if (b_in.eof()) throw 1; // ���� ���� ������� ��������� �� ������� �����

		CreateVertexes(n);
		for (int i = 0; i < n; i++)
		{
			b_in.read((char*)&v, sizeof(POINT));
			if (b_in.eof()) throw 2; // ���� ���� ������� ��������� �� ������� �����
			SetVertex(i, v);
		}
	}
	catch (int i) // ��������� ������
	{
		switch (i)
		{
		case 1:
			return 1;
		case 2:
			Clear(); // ������ ������ �� �����, ��������
			std::cerr << "Load: ����������� ����� �����" << std::endl;
			return 1;
		}
	}
	ResetStatus();

	return 0;
}
