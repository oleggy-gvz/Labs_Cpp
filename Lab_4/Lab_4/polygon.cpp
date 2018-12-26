#include "polygon.h"
#include <iostream>

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

// ����������� �� ���������
CPolygon::CPolygon()
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
	CopyPolygon(p);
}

CPolygon::~CPolygon()
{
	Clear();
}

// ������� ���� ��������� ��������������
void CPolygon::SetPolygon(int n, POINT *v)
{
	SetShape(n, v);
	UpdateStatus();
}

// ����������� �������������� �� ������� �������������
void CPolygon::CopyPolygon(const CPolygon& p)
{
	CopyShape(p);
	// �������� ������� �� ������� �������������
	convex = p.IsConvex();
	exist = p.IsExist();
}

// ��������� ���� ������ ��������������
void CPolygon::Clear()
{
	Shape::Clear();
	convex = false;
	exist = false;
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
void CPolygon::UpdateStatus()
{
	int n = GetCountVertexes();
	POINT *v = new POINT[n];
	for (int i = 0; i < n; i++)	v[i] = GetVertex(i);

	exist = CheckExist(v, n); // �������� ������������� �� �������������
	convex = CheckConvex(v, n); // �������� ������������� �� ����������

	delete []v;
	
	/*
	// ���������� ����������� protected ��� vert, count � ������������ ������ 
	exist = CheckExist(vert, count); // �������� ������������� �� �������������
	convex = CheckConvex(vert, count); // �������� ������������� �� ����������
	*/
	}

// ���������� ���������� � ��������������
bool CPolygon::Show()
{
	Shape::Show();
	if (IsExist())
	{
		std::cout << "������������� ��������: " << (convex ? "��" : "���") << std::endl;
		return false;
	}
	return true;
}

// ��������� ��������� ������ �� ������ CPolygon � ����
void CPolygon::Save(std::ofstream &b_out)
{
	Shape::Save(b_out);

	b_out.write((char*)&exist, sizeof(exist));
	b_out.write((char*)&convex, sizeof(convex));
}

// ��������� ��������� ������ �� ����� � ����� CPolygon
void CPolygon::Load(std::ifstream &b_in)
{
	Shape::Load(b_in);

	b_in.read((char*)&exist, sizeof(exist));
	b_in.read((char*)&convex, sizeof(convex));
}