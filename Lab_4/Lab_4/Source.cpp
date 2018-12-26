#include <iostream>
#include <locale.h>
#include <conio.h>
#include "combi_d_polygon.h"
#include "dlist.h"
#include <math.h>
#include <time.h> // для смены превдослучайных значений
#include <stdlib.h> // для заполнения псевдослучаными значениями исходного массива
#include <string>

#define DEBUG

using namespace std;

const unsigned char ESC = 27;
enum order { DIRECT, INVERSE }; // тип порядка обхода списка (прямой/обратный)

// заполняем массив координат координатами многоугольника в виде курга
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

// вносим случайные отклонения координат в диапазоне по x и y (-seed/2..seed/2)
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
	// задаем случ. кол-во вершин многоугольника от n_seed1..n_seed2
	n = n_seed1 + rand() % ((n_seed2 - n_seed1) + 1); // кол-во вершин
	// задаем координаты вершин многоугольника
	get_polygon_circle(n, v, r, cent); // создаем правильный многоугольник из n вершин
	change_vertex_random(n, v, seed); // искажаем вершины в случайные
}

// вывод фигуры на экран с ожиданием нажатия ESC
void show_wait(Shape &s, string msg = "")
{
	if (msg != "") cout << msg.c_str() << endl;
	do
	{
		s.Show(); // позднее связывание, вызываем соответствующий метод класса хрянящегося в указателе
	} while (_getch() != ESC);
}

// сохраняем параметры фигуры из класса фигуры в файл
void save_shape(Shape &s, const string &f, string msg = "")
{
	ofstream b_out(f.c_str(), ios::binary);
	s.Save(b_out);
	b_out.close();
	if (!msg.empty()) cout << msg.c_str() << endl;
}

// загружаем параметры фигуры из файла в класс фигуры
void load_shape(Shape &s, const string &f, string msg = "")
{
	ifstream b_in(f.c_str(), ios::binary);
	s.Load(b_in);
	b_in.close();
	if (!msg.empty()) cout << msg.c_str() << endl;
}

// покажем информацию по списку
template <class T>
void show_about_list(DList<T> &l, string msg = "")
{
	if (!msg.empty()) cout << msg << ", ";
	cout << (l.IsEmpty() ? "пустой" : "заполнен");
	if (!l.IsEmpty())
		cout << ", размер " << l.GetSize();
	cout << endl;
}

// вывод списка на экран в прямом и обратном направлениях
template <class T>
void show_list(DList<T> &l, string msg, order type = DIRECT)
{
	if (!msg.empty()) cout << msg.c_str() << endl;

	int bak = l.GetCurrentPosition();

	void (DList<T>::*Next)(); // пустой указатель Next на метод класса - шаг

	switch (type)
	{
	case DIRECT:
		l.SetFront(); // начало с первого узла
		Next = &DList<T>::Next; // направление вперед
		break;
	case INVERSE:
		l.SetRear(); // начало с последнего узла
		Next = &DList<T>::Previous; // направление назад
		break;
	}

	for (; !l.EndOfList(); (l.*Next)())
		show_wait(l.Data(), "фигура " + to_string(l.GetCurrentPosition() + 1) + ":");
	l.Reset(bak);
}

// сохраняем список DList в файл
template <class T>
void save_list(DList<T> &l, const string &f, string msg = "")
{
	if (!msg.empty()) cout << msg << endl;

	ofstream b_out(f.c_str(), ios::binary);
	//b_out << l;
	l.Save(b_out);
	b_out.close();
}

// загружаем в список DList данные из файла
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
	int bak = l.GetCurrentPosition(); // сохраняем текущую позицию
	T *p = NULL;

	cout << "фигуры с ключем (" << k << "): " << endl;

	for (l.Reset(); !l.EndOfList(); l.Next())
	{
		p = &l.Find(k); // ищем эл-т с таким ключем
		if (p == NULL)
		{
			cout << "не найдены" << endl;
			break;
		}			
		else
		{
			show_wait(*p, "фигура " + to_string(l.GetCurrentPosition() + 1) + ":");
		}	
	} 
	l.Reset(bak); // восстанавливаем текущую позицию
}

void main()
{
	setlocale(LC_ALL, "Russian");

	// задаем стиль отображения общийдля всех
	Paint s;
	s.SetPen({ PS_INSIDEFRAME, 10, { 0, 0, 255 } });
	s.SetBrush({ HS_CROSS, { 255, 0, 255 } });
	s.SetBackColor({ 255, 255, 255 });

	int N = 3; // кол-во многоугольников

	// генерируем случайные вершины для многоугольника
	srand((unsigned int)time(NULL));
	POINT v[7] = {0};
	POINT center = { 180, 180 }; // координаты центра многоугольника
	int radius = 120; // радиус окружности по которой делается шаблон многоугольника
	int n; // кол-во вершин в многоугольнике
	int n_seed1 = 3, n_seed2 = 7; // разброс кол-во вершин в многоугольнике начало...конец
	int xy_seed = 80; // разброс координат в каждой точке по x и y (-seed/2..seed/2)

#ifdef DEBUG
	CPolygon poly1, poly2, poly3;
	string file_poly = "D:\\poly.bin";

	get_rand_polygon(n, v, n_seed1, n_seed2, center, radius, xy_seed);
	poly1.SetPolygon(n, v); // создаем фигуру 1
	get_rand_polygon(n, v, n_seed1, n_seed2, center, radius / 3, xy_seed);
	poly2.SetPolygon(n, v); // создаем фигуру 2
	save_shape(poly1, file_poly, "сохраняем poly1 в файл " + file_poly);
	load_shape(poly3, file_poly, "загружаем в poly3 из файла " + file_poly);
	show_wait(poly3, "покажем многоугольник poly3");

	DrawPolygon draw_poly1, draw_poly2, draw_poly3;
	string file_draw_poly = "D:\\draw_poly.bin";

	draw_poly1.SetDrawPolygon(poly1, s, NOTEPAD);
	draw_poly2.SetDrawPolygon(poly2, s, NOTEPAD);
	save_shape(draw_poly1, file_draw_poly, "сохраняем draw_poly1 в файл " + file_draw_poly);
	load_shape(draw_poly3, file_draw_poly, "загружаем в draw_poly3 из файла " + file_draw_poly);
	show_wait(draw_poly3, "покажем многоугольник draw_poly3");

	/*
	CombiDrawPolygon combi_poly1, combi_poly2;
	string file_combi_poly = "D:\\combi_poly.bin";

	combi_poly1.SetCombiPolygon(draw_poly1, draw_poly2);
	save_shape(combi_poly1, file_combi_poly, "сохраняем combi_poly1 в файл " + file_combi_poly);
	load_shape(combi_poly2, file_combi_poly, "загружаем в combi_poly2 из файла " + file_combi_poly);
	show_wait(combi_poly2, "покажем многоугольник combi_poly2");
	*/
#else
	/************************************************************************/
	DList<CPolygon> list_poly1;
	DList<CPolygon> list_poly2;

	CPolygon *poly1 = new CPolygon[N];
	string file_list_poly = "D:\\list_poly.bin";

	// инициализируем многоуголники с нужными гранями
	for (int i = 0; i < N; i++)
	{
		// получаем координаты случайного многоугольника
		get_rand_polygon(n, v, 5, 5, center, radius, xy_seed);
		poly1[i].SetPolygon(n, v); // создаем фигуру
		list_poly1.InsertAfter(poly1[i], n); // добавляем фигуру в контейнер
	}
	int key = 5;

	save_list(list_poly1, file_list_poly, "сохраняем list_poly1 в файл " + file_list_poly); // сохраняем в файл
	load_list(list_poly2, file_list_poly, "загружаем в list_poly2 из файла " + file_list_poly); // загружаем список из файла
	show_about_list(list_poly2, "информация о list_poly2"); // покажем информацию о списке
	show_list(list_poly2, "покажем список list_poly2"); // покажем все созданные фигуры
	show_find_nodes(list_poly2, key); // покажем все многоугольники с ключом key

	/************************************************************************/
	DList<DrawPolygon> list_draw1;
	DList<DrawPolygon> list_draw2;
	string file_list_draw = "D:\\list_draw.bin";

	DrawPolygon *draw_poly1 = new DrawPolygon[N];

	// инициализируем раскрашенные многоуголники на основе созданного
	for (int i = 0; i < N; i++)
	{	
		draw_poly1[i].SetDrawPolygon(poly1[i], s, NOTEPAD); // создаем фигуру раскрашенного многоугольника
		list_draw1.InsertAfter(draw_poly1[i], n); // добавляем фигуру в контейнер
	}	
	key = 5;

	save_list(list_draw1, file_list_draw, "сохраняем list_draw1 в файл " + file_list_draw); // сохраняем в файл
	load_list(list_draw2, file_list_draw, "загружаем в list_draw2 из файла " + file_list_draw); // загружаем список из файла
	show_about_list(list_draw2, "информация о list_draw2"); // покажем информацию о списке
	show_list(list_draw2, "покажем список list_draw2"); // покажем все созданные фигуры
	show_find_nodes(list_draw2, key); // покажем все многоугольники с ключом key

	/************************************************************************/
	DList<CombiDrawPolygon> list_combi1;
	DList<CombiDrawPolygon> list_combi2;
	string file_list_combi = "D:\\list_combi.bin";

	CPolygon *poly2 = new CPolygon[N];
	DrawPolygon *draw_poly2 = new DrawPolygon[N];
	CombiDrawPolygon *combi_poly = new CombiDrawPolygon[N];

	list_draw1.Reset();
	// инициализируем комбинированный  многоуголники на основе созданного
	for (int i = 0; i < N; i++)
	{
		// получаем координаты случайного многоугольника
		get_rand_polygon(n, v, n_seed1, n_seed2, center, radius / 3, xy_seed);
		poly2[i].SetPolygon(n, v); // создаем многоугольник
		draw_poly2[i].SetDrawPolygon(poly2[i], s); // создаем рисуемый внутренний многоугольник
		
		combi_poly[i].SetCombiPolygon(draw_poly1[i], draw_poly2[i]); // комбинируем их в одну
		// добавляем фигуру в контейнер где ключ, кол-во вершин внешней фигуры
		list_combi1.InsertAfter(combi_poly[i], list_draw1.Key());
		list_draw1.Next();
	}
	key = 5;

	save_list(list_combi1, file_list_combi, "сохраняем list_combi1 в файл " + file_list_combi); // сохраняем в файл
	load_list(list_combi2, file_list_combi, "загружаем в list_combi2 из файла " + file_list_combi); // загружаем список из файла
	show_about_list(list_combi2, "информация о list_combi2"); // покажем информацию о списке
	show_list(list_combi2, "покажем список list_combi2"); // покажем все созданные фигуры
	show_find_nodes(list_combi2, key); // покажем все многоугольники с ключом key

	/************************************************************************/
	delete []combi_poly;
	delete []draw_poly2;
	delete []poly2;
	delete []draw_poly1;
	delete []poly1;
#endif
}