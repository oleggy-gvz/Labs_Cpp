#include <iostream>
#include <locale.h>
#include <conio.h>
#include "combi_d_polygon.h"
#include <math.h>
#include <time.h> // для смены превдослучайных значений
#include <stdlib.h> // для заполнения псевдослучаными значениями исходного массива

using namespace std;

const unsigned char ESC = 27;

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
void show_polygon(DrawPolygon &d)
{
	do
	{
		d.Show();
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

void get_rand_polygon(POINT *v, int *n, int seed_vert, POINT cent, int r,  int seed)
{
	// задаем координаты вершин многоугольника
	*n = 3 + rand() % (seed_vert + 1); // кол-во вершин
	get_polygon_circle(v, *n, r, cent); // создаем правильный многоугольник из n вершин
	change_vertex_random(v, *n, seed); // искажаем вершины в случайные
}

void print_info_polygon(CPolygon *p, int pos)
{
	cout << "фигура №: " << pos + 1;
	cout << ", вершины: " << p->GetCountVertexes();
	cout << ", выпуклый: " << (p->IsConvex() ? "да" : "нет");
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "Russian");

	// задаем стиль отображения
	Paint s;
	s.SetPenStyle(PS_INSIDEFRAME, 2);
	s.SetPenColor({ 0, 0, 255 });
	s.SetBrushStyle(HS_CROSS);
	s.SetBrushColor({ 255, 0, 255 }); // цвет заливки фигуры
	s.SetBackColor({ 255, 255, 255 });

	// создаем случайный многоугольник
	srand((unsigned int)time(NULL));
	POINT vert[7] = { 0 };
	POINT center = { 300, 180 }; // координаты центра многоугольника
	int radius = 120; // радиус окружности по которой делается шаблон многоугольника
	int n, seed_n = 4; // + кол-во вершин в многоугольнике
	int seed = 80; // разброс координат в каждой точке по x и y (-seed/2..seed/2)

	/*CPolygon p1(n, vert);
	//CPolygon p1(3, vert[0], vert[1], vert[2]);
	
	string file = "d:\\1.bin";
	Draw d(s, NOTEPAD);
	print_info_polygon(&p1, 0);
	show_polygon(d, p1);
	save_polygon(p1, file);
	cout << "сохраняем многоугольник" << endl;
	CPolygon p2;
	load_polygon(p2, file);
	cout << "загружаем многоугольник" << endl;
	show_polygon(d, p2);
	*/
	
	Shape *pS; // базовый класс фигура
	CPolygon p; // наследуемый класс многоугольник

	// задаем многоугольник
	get_rand_polygon(vert, &n, seed_n, center, radius, seed);
	p.SetPolygon(n, vert);

	pS = &p; // класс многоугольник
	pS->Show(); // пишем информацию о многоугольнике
	_getch();

	// раскрашенный многоугольник, наследуемый класс многоугольник + класс цвета
	DrawPolygon dp; 
	dp.SetDrawPolygon(s, p, NOTEPAD);

	pS = &dp;
	do
	{
		pS->Show(); // рисуем
	} while (_getch() != ESC);

	CPolygon p1, p2;
	// задаем многоугольник 1
	get_rand_polygon(vert, &n, seed_n, center, radius, seed);
	p1.SetPolygon(n, vert);
	// задаем многоугольник 2
	get_rand_polygon(vert, &n, seed_n, center, radius / 3, seed);
	p2.SetPolygon(n, vert);

	DrawPolygon dp1(s, p1), dp2(s, p2);
	// класс раскрашенный комбинированный многоугольник
	CombiDrawPolygon cdp(dp1, dp2);

	pS = &cdp; 
	do
	{
		pS->Show(); // рисуем
	} while (_getch() != ESC);
}