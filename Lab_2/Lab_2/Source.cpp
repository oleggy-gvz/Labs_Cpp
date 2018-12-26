#include <iostream>
#include <locale.h>
#include <conio.h>
#include "polygon.h"
#include "style.h"
#include "draw.h"
#include "dlist.h"
#include <math.h>
#include <time.h> // ��� ����� ��������������� ��������
#include <stdlib.h> // ��� ���������� ��������������� ���������� ��������� �������

using namespace std;

const unsigned char ESC = 27;

enum order { DIRECT, INVERSE }; // ��� ������� ������ ������ (������/��������)

// ��������� ������� ��������� ��������
void reverse(POINT *v, int n)
{
	POINT tmp;
	int k = n / 2; // �������� ������� ������. ����
	for (int i = 0; i < k; i++)
	{
		tmp = v[n - 1 - i];
		v[n - 1 - i] = v[i];
		v[i] = tmp;
	}
}

// ����� ������ �� ����� � ��������� ������� ESC
void show_polygon(CDraw &d, const CPolygon &p)
{
	do
	{
		d.Show(p);
	} while (_getch() != ESC);
}

// ��������� ��������� ������ �� ������ CPolygon � ����
void save_polygon(CPolygon &p, const string &f)
{
	ofstream b_out(f.c_str(), ios::binary);
	p.Save(b_out);
	b_out.close();
}

// ��������� ��������� ������ �� ����� � ����� CPolygon 
void load_polygon(CPolygon &p, const string &f)
{
	ifstream b_in(f.c_str(), ios::binary);
	p.Load(b_in);
	b_in.close();
}

// ��������� ������ DList � ����
void save_list(DList &l, const string &f)
{
	ofstream b_out(f.c_str(), ios::binary);
	b_out << l;
	b_out.close();
}

// ��������� � ������ DList ������ �� �����
void load_list(DList &l, const string &f)
{
	ifstream b_in(f.c_str(), ios::binary);
	b_in >> l;
	b_in.close();
}

void print_info_polygon(CPolygon *p, int pos)
{
	cout << "������ �: " << pos + 1;
	cout << ", ���� (�������): " << p->GetCountVertexes();
	cout << ", ��������: " << (p->IsConvex() ? "��" : "���");
	cout << endl;
}

// ����� ������ �� ����� � ������ � �������� ������������
void show_list(CDraw &d, DList &L, order type = DIRECT)
{
	int bak = L.GetCurrentPosition();
	
	void (DList::*Next)(); // ��������� �� ����� - ���

	switch(type)
	{
	case DIRECT:
		L.SetFront(); // ������ � ������� ����
		Next = &DList::Next; // ����������� ������
		break;
	case INVERSE:
		L.SetRear(); // ������ � ���������� ����
		Next = &DList::Previous; // ����������� �����
		break;
	}

	for (; !L.EndOfList(); (L.*Next)())
	{	
		CPolygon *p = L.Data();
		print_info_polygon(p, L.GetCurrentPosition());
		show_polygon(d, *L.Data());
	}
	L.Reset(bak);
}

void show_find_nodes(CDraw &d, DList &L, int k)
{
	int bak = L.GetCurrentPosition();
	CPolygon *p;
	
	cout << "������ � ������ (" << k << "): " << endl;
	
	p = L.Find(k);
	if (p == NULL)
	{
		cout << "�� �������" << endl;
		return;
	}
	while (p != NULL)
	{
		print_info_polygon(p, L.GetCurrentPosition()-1);
		show_polygon(d, *p);
		p = L.Find(k, FALSE); // ���� ��������� ��-� � ����� ������
	}
	L.Reset(bak);
}

// ��������� ������ ��������� ������������ �������������� � ���� �����
void get_polygon_circle(POINT *v, int n, int r, POINT d)
{
	if (n < 3) return;
	float PI = acosf(-1), da = 2 * PI / n, a = 3 * PI / 2;

	for (int i = 0; i < n; i++, a += da)
	{
		v[i].x = d.x + (LONG)(r * cos(a));
		v[i].y = d.y + (LONG)(r * sin(a));
	}
}

// ������ ��������� ���������� ��������� � ��������� �� x � y (-seed/2..seed/2)
void change_vertex_random(POINT *v, int n, int seed)
{
	for (int i = 0; i < n; i++)
	{
		v[i].x += (rand() % (seed + 1) - seed / 2);
		if (v[i].x < 0) v[i].x = 0;
		v[i].y += (rand() % (seed + 1) - seed / 2);
		if (v[i].y < 0) v[i].y = 0;
	}
}

// �������� ���������� ���������� ��������������
void get_rand_polygon(POINT *v, int *n, int seed_vert, POINT cent, int r, int seed)
{
	// ������ ���������� ������ ��������������
	*n = 3 + rand() % (seed_vert + 1); // ���-�� ������
	get_polygon_circle(v, *n, r, cent); // ������� ���������� ������������� �� n ������
	change_vertex_random(v, *n, seed); // �������� ������� � ���������
}

void show_about_list(DList &L)
{
	cout << "������: " << (L.IsEmpty() ? "������" : "��������") << endl;
	cout << "������ ������: " << L.GetSize() << endl;
	cout << "�����. �������: " << L.GetCurrentPosition();
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned int)time(NULL));

	CStyle s;
	s.SetPenStyle(PS_INSIDEFRAME, 10);
	s.SetPenColor({ 0, 0, 255 });
	s.SetBrushStyle(HS_CROSS);
	s.SetBrushColor({ 255, 0, 255 });
	s.SetPenColor({ 0, 0, 255 });
	s.SetBackColor({ 255, 255, 255 });

	CDraw draw(s, NOTEPAD);
	string file = "D:\\list.bin";

	int N = 3; // ���-�� ���������������
	CPolygon *poly = new CPolygon[N];

	POINT v[7] = {0};
	POINT center = { 180, 180 }; // ���������� ������ ��������������
	int radius = 120; // ������ ���������� �� ������� �������� ������ ��������������
	int n; // ���-�� ������ � ��������������
	int seed_n = 4; // ������� ���-�� ������ � �������������� ������� � 3 �� 3 +4
	int seed = 80; // ������� ��������� � ������ ����� �� x � y (-seed/2..seed/2)
	
	DList list1;
	// �������������� ������������� � ������� �������
	for (int i = 0; i < N; i++)
	{
		// �������� ���������� ���������� ��������������
		get_rand_polygon(v, &n, seed_n, center, radius, seed);
		poly[i].SetAllVertexes(n, v); // ������� ������
		list1.InsertAfter(poly[i]); // ��������� ������ � ��������� list1
	}

	show_about_list(list1); // ������� ���������� � ������
	show_list(draw, list1); // ������� ��� ��������� ������
	save_list(list1, file); // ��������� � ����
	delete []poly;

	DList list2;
	load_list(list2, file);
	show_about_list(list2); // ������� ���������� � ������

	int key = 4;
	show_find_nodes(draw, list2, key);
}