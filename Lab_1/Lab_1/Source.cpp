#include <iostream>
#include <locale.h>
#include <conio.h>
#include "polygon.h"
#include "paint.h"
#include "draw.h"
#include <math.h>
#include <time.h> // ��� ����� ��������������� ��������
#include <stdlib.h> // ��� ���������� ��������������� ���������� ��������� �������

using namespace std;

const unsigned char ESC = 27;

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

void get_rand_polygon(POINT *v, int *n, int seed_vert, POINT cent, int r,  int seed)
{
	// ������ ���������� ������ ��������������
	*n = 3 + rand() % (seed_vert + 1); // ���-�� ������
	get_polygon_circle(v, *n, r, cent); // ������� ���������� ������������� �� n ������
	change_vertex_random(v, *n, seed); // �������� ������� � ���������
}

void print_info_polygon(CPolygon *p, int pos)
{
	cout << "������ �: " << pos + 1;
	cout << ", �������: " << p->GetCountVertexes();
	cout << ", ��������: " << (p->IsConvex() ? "��" : "���");
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned int)time(NULL));

	Paint s;
	s.SetPenStyle(PS_INSIDEFRAME, 10);
	s.SetPenColor({ 0, 0, 255 });
	s.SetBrushStyle(HS_CROSS);
	s.SetBrushColor({ 255, 0, 255 });
	s.SetPenColor({ 0, 0, 255 });
	s.SetBackColor({ 255, 255, 255 });

	CDraw d(s, NOTEPAD);

	POINT v[7] = { 0 };
	POINT center = { 300, 180 }; // ���������� ������ ��������������
	int radius = 120; // ������ ���������� �� ������� �������� ������ ��������������
	int n, seed_n = 4; // + ���-�� ������ � ��������������
	int seed = 80; // ������� ��������� � ������ ����� �� x � y (-seed/2..seed/2)

	get_rand_polygon(v, &n, seed_n, center, radius, seed);

	string file = "d:\\1.bin";

	CPolygon p1(n, v);
	print_info_polygon(&p1, 0);
	show_polygon(d, p1);


	save_polygon(p1, file);
	cout << "��������� �������������" << endl;

	CPolygon p2;

	load_polygon(p2, file);
	cout << "��������� �������������" << endl;

	show_polygon(d, p2);
}