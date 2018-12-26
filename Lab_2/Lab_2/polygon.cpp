#include "polygon.h"
#include <iostream>

// ��������� ������ ���-�� ������ � ��������� ������ �� ���� ��������
int CPolygon::CreateVertexes(int n)
{
	if (n == count) return 0; // ���� ���-�� ������� �� ����������

	if (vert != NULL) delete[] vert; // ������� �������	
	vert = new POINT[n]; // �������� ������ ��� ����� ���-�� ������
	if (vert == NULL)
	{
		std::cerr << "CreateVertexes: �� ���������� ������" << std::endl;
		exit(1);
	}
	count = n; // ���������� ����� ���-�� ������

	return 0;
}

// ������������ ������ ��������������
void CPolygon::FreeVertexes()
{
	delete[] vert;
}

CPolygon::CPolygon()
{}

CPolygon::CPolygon(int n, POINT *v)
{
	SetAllVertexes(n, v);
}

// ����������� �������� � ���������� ���-��� ������
CPolygon::CPolygon(int n, POINT v, ...)
{
	POINT *ver = &v;
	SetAllVertexes(n, ver);
}

// ����������� �������� ������ �� �������
CPolygon::CPolygon(const CPolygon& p)
{
	int n = p.GetCountVertexes();
	CreateVertexes(n);
	for (int i = 0; i < count; i++) vert[i] = p.GetVertex(i); // �������� �������	
}

CPolygon::~CPolygon()
{
	FreeVertexes();
}

// ��������� ����������� ����������� ��������������
// ������ ����� ���� �� 3 ������� � ���������� ������������
bool CPolygon::CheckExist(int n, POINT *v)
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
bool CPolygon::CheckConvex(int n, POINT *v)
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
		// ���� � ����� ����� �� 1 �.�. 11 (dec: 3) �� ���� ��������� ��� ������ ������
		if (flag == 3) return false; 	
	}
	if (flag != 0) return true;
	return false;
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

// ���������� ���������� n-�� ������� ��������������
POINT CPolygon::GetVertex(int n) const
{
	try
	{
		if (n > count || n < 0) throw "GetVertex: ������� ������� � ������� �� ��������� ������������";
	}
	catch (char *str) // ��������� ������
	{
		std::cerr << str << std::endl;
		exit(1);
	}

	return vert[n];
}

// ���������� ���-�� ������ ��������������
int CPolygon::GetCountVertexes() const
{
	return count;
}

// �������� ������� 
void CPolygon::ResetStatus()
{
	exist = CheckExist(count, vert); // �������� ����������� �� �������������
	convex = CheckConvex(count, vert); // �������� ����������� �� ����������
}

// ������� ���� ��������� ������
void CPolygon::SetAllVertexes(int n, POINT *v)
{
	CreateVertexes(n); // ������������� ����� ���-�� ������
	for (int i = 0; i < count; i++) vert[i] = v[i]; // �������� �������
	ResetStatus();
}

// ��������� ��������� POINT ��� n-�� �������
void CPolygon::SetVertex(int n, POINT v)
{
	try
	{
		if (n > count || n < 0) throw "SetVertex: ������� ������� � ������� �� ��������� ������������";
	}
	catch (char *str) // ��������� ������
	{
		std::cerr << str << std::endl;
	}
	vert[n] = v;
}

// ��������� ���� ������ ��������������
void CPolygon::Clear()
{
	FreeVertexes();

	vert = NULL;
	count = 0;
	convex = false;
	exist = false;
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