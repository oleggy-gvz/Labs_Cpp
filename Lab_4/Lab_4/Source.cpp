#include <iostream>
#include <locale.h>
#include <conio.h>
#include "combi_d_polygon.h"
#include "dlist.h"
#include <math.h>
#include <time.h> // ��� ����� ��������������� ��������
#include <stdlib.h> // ��� ���������� ��������������� ���������� ��������� �������
#include <string>

#define DEBUG

using namespace std;

const unsigned char ESC = 27;
enum order { DIRECT, INVERSE }; // ��� ������� ������ ������ (������/��������)

// ��������� ������ ��������� ������������ �������������� � ���� �����
void get_polygon_circle(int n, POINT *v, int r, POINT d)
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
void change_vertex_random(int n, POINT *v, int seed)
{
	for (int i = 0; i < n; i++)
	{
		v[i].x += (rand() % (seed + 1) - seed / 2);
		if (v[i].x < 0) v[i].x = 0;
		v[i].y += (rand() % (seed + 1) - seed / 2);
		if (v[i].y < 0) v[i].y = 0;
	}
}

void get_rand_polygon(int &n, POINT *v, int n_seed1, int n_seed2, POINT cent, int r,  int seed)
{
	// ������ ����. ���-�� ������ �������������� �� n_seed1..n_seed2
	n = n_seed1 + rand() % ((n_seed2 - n_seed1) + 1); // ���-�� ������
	// ������ ���������� ������ ��������������
	get_polygon_circle(n, v, r, cent); // ������� ���������� ������������� �� n ������
	change_vertex_random(n, v, seed); // �������� ������� � ���������
}

// ����� ������ �� ����� � ��������� ������� ESC
void show_wait(Shape &s, string msg = "")
{
	if (msg != "") cout << msg.c_str() << endl;
	do
	{
		s.Show(); // ������� ����������, �������� ��������������� ����� ������ ����������� � ���������
	} while (_getch() != ESC);
}

// ��������� ��������� ������ �� ������ ������ � ����
void save_shape(Shape &s, const string &f, string msg = "")
{
	ofstream b_out(f.c_str(), ios::binary);
	s.Save(b_out);
	b_out.close();
	if (!msg.empty()) cout << msg.c_str() << endl;
}

// ��������� ��������� ������ �� ����� � ����� ������
void load_shape(Shape &s, const string &f, string msg = "")
{
	ifstream b_in(f.c_str(), ios::binary);
	s.Load(b_in);
	b_in.close();
	if (!msg.empty()) cout << msg.c_str() << endl;
}

// ������� ���������� �� ������
template <class T>
void show_about_list(DList<T> &l, string msg = "")
{
	if (!msg.empty()) cout << msg << ", ";
	cout << (l.IsEmpty() ? "������" : "��������");
	if (!l.IsEmpty())
		cout << ", ������ " << l.GetSize();
	cout << endl;
}

// ����� ������ �� ����� � ������ � �������� ������������
template <class T>
void show_list(DList<T> &l, string msg, order type = DIRECT)
{
	if (!msg.empty()) cout << msg.c_str() << endl;

	int bak = l.GetCurrentPosition();

	void (DList<T>::*Next)(); // ������ ��������� Next �� ����� ������ - ���

	switch (type)
	{
	case DIRECT:
		l.SetFront(); // ������ � ������� ����
		Next = &DList<T>::Next; // ����������� ������
		break;
	case INVERSE:
		l.SetRear(); // ������ � ���������� ����
		Next = &DList<T>::Previous; // ����������� �����
		break;
	}

	for (; !l.EndOfList(); (l.*Next)())
		show_wait(l.Data(), "������ " + to_string(l.GetCurrentPosition() + 1) + ":");
	l.Reset(bak);
}

// ��������� ������ DList � ����
template <class T>
void save_list(DList<T> &l, const string &f, string msg = "")
{
	if (!msg.empty()) cout << msg << endl;

	ofstream b_out(f.c_str(), ios::binary);
	//b_out << l;
	l.Save(b_out);
	b_out.close();
}

// ��������� � ������ DList ������ �� �����
template <class T>
void load_list(DList<T> &l, const string &f, string msg = "")
{
	if (!msg.empty()) cout << msg << endl;

	ifstream b_in(f.c_str(), ios::binary);
	//b_in >> l;
	l.Load(b_in);
	b_in.close();
}

template <class T>
void show_find_nodes(DList<T> &l, int k)
{
	int bak = l.GetCurrentPosition(); // ��������� ������� �������
	T *p = NULL;

	cout << "������ � ������ (" << k << "): " << endl;

	for (l.Reset(); !l.EndOfList(); l.Next())
	{
		p = &l.Find(k); // ���� ��-� � ����� ������
		if (p == NULL)
		{
			cout << "�� �������" << endl;
			break;
		}			
		else
		{
			show_wait(*p, "������ " + to_string(l.GetCurrentPosition() + 1) + ":");
		}	
	} 
	l.Reset(bak); // ��������������� ������� �������
}

void main()
{
	setlocale(LC_ALL, "Russian");

	// ������ ����� ����������� �������� ����
	Paint s;
	s.SetPen({ PS_INSIDEFRAME, 10, { 0, 0, 255 } });
	s.SetBrush({ HS_CROSS, { 255, 0, 255 } });
	s.SetBackColor({ 255, 255, 255 });

	int N = 3; // ���-�� ���������������

	// ���������� ��������� ������� ��� ��������������
	srand((unsigned int)time(NULL));
	POINT v[7] = {0};
	POINT center = { 180, 180 }; // ���������� ������ ��������������
	int radius = 120; // ������ ���������� �� ������� �������� ������ ��������������
	int n; // ���-�� ������ � ��������������
	int n_seed1 = 3, n_seed2 = 7; // ������� ���-�� ������ � �������������� ������...�����
	int xy_seed = 80; // ������� ��������� � ������ ����� �� x � y (-seed/2..seed/2)

#ifdef DEBUG
	CPolygon poly1, poly2, poly3;
	string file_poly = "D:\\poly.bin";

	get_rand_polygon(n, v, n_seed1, n_seed2, center, radius, xy_seed);
	poly1.SetPolygon(n, v); // ������� ������ 1
	get_rand_polygon(n, v, n_seed1, n_seed2, center, radius / 3, xy_seed);
	poly2.SetPolygon(n, v); // ������� ������ 2
	save_shape(poly1, file_poly, "��������� poly1 � ���� " + file_poly);
	load_shape(poly3, file_poly, "��������� � poly3 �� ����� " + file_poly);
	show_wait(poly3, "������� ������������� poly3");

	DrawPolygon draw_poly1, draw_poly2, draw_poly3;
	string file_draw_poly = "D:\\draw_poly.bin";

	draw_poly1.SetDrawPolygon(poly1, s, NOTEPAD);
	draw_poly2.SetDrawPolygon(poly2, s, NOTEPAD);
	save_shape(draw_poly1, file_draw_poly, "��������� draw_poly1 � ���� " + file_draw_poly);
	load_shape(draw_poly3, file_draw_poly, "��������� � draw_poly3 �� ����� " + file_draw_poly);
	show_wait(draw_poly3, "������� ������������� draw_poly3");

	/*
	CombiDrawPolygon combi_poly1, combi_poly2;
	string file_combi_poly = "D:\\combi_poly.bin";

	combi_poly1.SetCombiPolygon(draw_poly1, draw_poly2);
	save_shape(combi_poly1, file_combi_poly, "��������� combi_poly1 � ���� " + file_combi_poly);
	load_shape(combi_poly2, file_combi_poly, "��������� � combi_poly2 �� ����� " + file_combi_poly);
	show_wait(combi_poly2, "������� ������������� combi_poly2");
	*/
#else
	/************************************************************************/
	DList<CPolygon> list_poly1;
	DList<CPolygon> list_poly2;

	CPolygon *poly1 = new CPolygon[N];
	string file_list_poly = "D:\\list_poly.bin";

	// �������������� ������������� � ������� �������
	for (int i = 0; i < N; i++)
	{
		// �������� ���������� ���������� ��������������
		get_rand_polygon(n, v, 5, 5, center, radius, xy_seed);
		poly1[i].SetPolygon(n, v); // ������� ������
		list_poly1.InsertAfter(poly1[i], n); // ��������� ������ � ���������
	}
	int key = 5;

	save_list(list_poly1, file_list_poly, "��������� list_poly1 � ���� " + file_list_poly); // ��������� � ����
	load_list(list_poly2, file_list_poly, "��������� � list_poly2 �� ����� " + file_list_poly); // ��������� ������ �� �����
	show_about_list(list_poly2, "���������� � list_poly2"); // ������� ���������� � ������
	show_list(list_poly2, "������� ������ list_poly2"); // ������� ��� ��������� ������
	show_find_nodes(list_poly2, key); // ������� ��� �������������� � ������ key

	/************************************************************************/
	DList<DrawPolygon> list_draw1;
	DList<DrawPolygon> list_draw2;
	string file_list_draw = "D:\\list_draw.bin";

	DrawPolygon *draw_poly1 = new DrawPolygon[N];

	// �������������� ������������ ������������� �� ������ ����������
	for (int i = 0; i < N; i++)
	{	
		draw_poly1[i].SetDrawPolygon(poly1[i], s, NOTEPAD); // ������� ������ ������������� ��������������
		list_draw1.InsertAfter(draw_poly1[i], n); // ��������� ������ � ���������
	}	
	key = 5;

	save_list(list_draw1, file_list_draw, "��������� list_draw1 � ���� " + file_list_draw); // ��������� � ����
	load_list(list_draw2, file_list_draw, "��������� � list_draw2 �� ����� " + file_list_draw); // ��������� ������ �� �����
	show_about_list(list_draw2, "���������� � list_draw2"); // ������� ���������� � ������
	show_list(list_draw2, "������� ������ list_draw2"); // ������� ��� ��������� ������
	show_find_nodes(list_draw2, key); // ������� ��� �������������� � ������ key

	/************************************************************************/
	DList<CombiDrawPolygon> list_combi1;
	DList<CombiDrawPolygon> list_combi2;
	string file_list_combi = "D:\\list_combi.bin";

	CPolygon *poly2 = new CPolygon[N];
	DrawPolygon *draw_poly2 = new DrawPolygon[N];
	CombiDrawPolygon *combi_poly = new CombiDrawPolygon[N];

	list_draw1.Reset();
	// �������������� ���������������  ������������� �� ������ ����������
	for (int i = 0; i < N; i++)
	{
		// �������� ���������� ���������� ��������������
		get_rand_polygon(n, v, n_seed1, n_seed2, center, radius / 3, xy_seed);
		poly2[i].SetPolygon(n, v); // ������� �������������
		draw_poly2[i].SetDrawPolygon(poly2[i], s); // ������� �������� ���������� �������������
		
		combi_poly[i].SetCombiPolygon(draw_poly1[i], draw_poly2[i]); // ����������� �� � ����
		// ��������� ������ � ��������� ��� ����, ���-�� ������ ������� ������
		list_combi1.InsertAfter(combi_poly[i], list_draw1.Key());
		list_draw1.Next();
	}
	key = 5;

	save_list(list_combi1, file_list_combi, "��������� list_combi1 � ���� " + file_list_combi); // ��������� � ����
	load_list(list_combi2, file_list_combi, "��������� � list_combi2 �� ����� " + file_list_combi); // ��������� ������ �� �����
	show_about_list(list_combi2, "���������� � list_combi2"); // ������� ���������� � ������
	show_list(list_combi2, "������� ������ list_combi2"); // ������� ��� ��������� ������
	show_find_nodes(list_combi2, key); // ������� ��� �������������� � ������ key

	/************************************************************************/
	delete []combi_poly;
	delete []draw_poly2;
	delete []poly2;
	delete []draw_poly1;
	delete []poly1;
#endif
}