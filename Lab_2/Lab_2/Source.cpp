#include <iostream>
#include <locale.h>
#include <conio.h>
#include "polygon.h"
#include "style.h"
#include "draw.h"
#include "dlist.h"
#include <math.h>
#include <time.h> // для смены превдослучайных значений
#include <stdlib.h> // для заполнения псевдослучаными значениями исходного массива

using namespace std;

const unsigned char ESC = 27;

enum order { DIRECT, INVERSE }; // тип порядка обхода списка (прямой/обратный)

// перевород массива координат наоборот
void reverse(POINT *v, int n)
{
	POINT tmp;
	int k = n / 2; // середина массива округл. вниз
	for (int i = 0; i < k; i++)
	{
		tmp = v[n - 1 - i];
		v[n - 1 - i] = v[i];
		v[i] = tmp;
	}
}

// вывод фигуры на экран с ожиданием нажатия ESC
void show_polygon(CDraw &d, const CPolygon &p)
{
	do
	{
		d.Show(p);
	} while (_getch() != ESC);
}

// сохраняем параметры фигуры из класса CPolygon в файл
void save_polygon(CPolygon &p, const string &f)
{
	ofstream b_out(f.c_str(), ios::binary);
	p.Save(b_out);
	b_out.close();
}

// загружаем параметры фигуры из файла в класс CPolygon 
void load_polygon(CPolygon &p, const string &f)
{
	ifstream b_in(f.c_str(), ios::binary);
	p.Load(b_in);
	b_in.close();
}

// сохраняем список DList в файл
void save_list(DList &l, const string &f)
{
	ofstream b_out(f.c_str(), ios::binary);
	b_out << l;
	b_out.close();
}

// загружаем в список DList данные из файла
void load_list(DList &l, const string &f)
{
	ifstream b_in(f.c_str(), ios::binary);
	b_in >> l;
	b_in.close();
}

void print_info_polygon(CPolygon *p, int pos)
{
	cout << "фигура №: " << pos + 1;
	cout << ", ключ (вершины): " << p->GetCountVertexes();
	cout << ", выпуклый: " << (p->IsConvex() ? "да" : "нет");
	cout << endl;
}

// вывод списка на экран в прямом и обратном направлениях
void show_list(CDraw &d, DList &L, order type = DIRECT)
{
	int bak = L.GetCurrentPosition();
	
	void (DList::*Next)(); // указатель на метод - шаг

	switch(type)
	{
	case DIRECT:
		L.SetFront(); // начало с первого узла
		Next = &DList::Next; // направление вперед
		break;
	case INVERSE:
		L.SetRear(); // начало с последнего узла
		Next = &DList::Previous; // направление назад
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
	
	cout << "фигуры с ключем (" << k << "): " << endl;
	
	p = L.Find(k);
	if (p == NULL)
	{
		cout << "не найдены" << endl;
		return;
	}
	while (p != NULL)
	{
		print_info_polygon(p, L.GetCurrentPosition()-1);
		show_polygon(d, *p);
		p = L.Find(k, FALSE); // ищем следующий эл-т с таким ключем
	}
	L.Reset(bak);
}

// заполняем массив координат координатами многоугольника в виде курга
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

// вносим случайные отклонения координат в диапазоне по x и y (-seed/2..seed/2)
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

// получаем координаты случайного многоугольника
void get_rand_polygon(POINT *v, int *n, int seed_vert, POINT cent, int r, int seed)
{
	// задаем координаты вершин многоугольника
	*n = 3 + rand() % (seed_vert + 1); // кол-во вершин
	get_polygon_circle(v, *n, r, cent); // создаем правильный многоугольник из n вершин
	change_vertex_random(v, *n, seed); // искажаем вершины в случайные
}

void show_about_list(DList &L)
{
	cout << "список: " << (L.IsEmpty() ? "пустой" : "заполнен") << endl;
	cout << "размер списка: " << L.GetSize() << endl;
	cout << "текущ. позиция: " << L.GetCurrentPosition();
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

	int N = 3; // кол-во многоугольников
	CPolygon *poly = new CPolygon[N];

	POINT v[7] = {0};
	POINT center = { 180, 180 }; // координаты центра многоугольника
	int radius = 120; // радиус окружности по которой делается шаблон многоугольника
	int n; // кол-во вершин в многоугольнике
	int seed_n = 4; // разброс кол-во вершин в многоугольнике начиная с 3 до 3 +4
	int seed = 80; // разброс координат в каждой точке по x и y (-seed/2..seed/2)
	
	DList list1;
	// инициализируем многоуголники с нужными гранями
	for (int i = 0; i < N; i++)
	{
		// получаем координаты случайного многоугольника
		get_rand_polygon(v, &n, seed_n, center, radius, seed);
		poly[i].SetAllVertexes(n, v); // создаем фигуру
		list1.InsertAfter(poly[i]); // добавляем фигуру в контейнер list1
	}

	show_about_list(list1); // покажем информацию о списке
	show_list(draw, list1); // покажем все созданные фигуры
	save_list(list1, file); // сохраняем в файл
	delete []poly;

	DList list2;
	load_list(list2, file);
	show_about_list(list2); // покажем информацию о списке

	int key = 4;
	show_find_nodes(draw, list2, key);
}