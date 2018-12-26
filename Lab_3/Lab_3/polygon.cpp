#include "polygon.h"
#include <iostream>

// обнуление всех данных многоугольника
void CPolygon::Clear()
{
	Shape::Clear();
	convex = false;
	exist = false;
}

// проверяем возможность отображения многоугольника
// должен иметь хотя бы 3 вершины с различными координатами
bool CPolygon::CheckExist(POINT *v, int n)
{
	if (n < 3) return false;
	// если координаты трех точек отличаются, значит будет треугольник
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
для выпуклого многоугольника все векторные произведения соседних сторон для 
каждой вершины будут одинакового знака, если нет то это не выпуклый многоугольник
вектор|AB| = вектор|B| - вектор|A|, т.е. AB_x = Bx-Ax, AB_y= By-Ay
|a|*|b| = ax*by - ay*bx
векторное произведение больше нуля, если второй вектор направлен влево от
первого, и меньше нуля, если вправо.
*/
bool CPolygon::CheckConvex(POINT *v, int n)
{
	if (n == 3) return true; // треугольник всегда выпуклый

	int i, j, k;
	int flag = 0;
	long long z;

	for (i = 0; i < n; i++)
	{
		// i - предыдущая вершина
		j = (i + 1) % n; // j - просматриваемая вершина
		k = (i + 2) % n; // k - следующая вершина
		// произведение векторов |ij| и |jk|
		z = (v[j].x - v[i].x) * (v[k].y - v[j].y) - (v[j].y - v[i].y) * (v[k].x - v[j].x);
		if (z < 0) flag |= 1; // записываем в первый бит - 1
		else if (z > 0)	flag |= 2; // записываем во второй бит - 1
		// если в обоих битах по 1 т.е. 11 (dec) -> 3, то знак поменялся при обходе вершин
		if (flag == 3) return false; 	
	}
	if (flag != 0) return true;
	return false;
}

CPolygon::CPolygon() : convex(false), exist(false)
{}

// конструктор создания многоугольника по массиву вершин
CPolygon::CPolygon(int n, POINT *v)
{
	SetPolygon(n, v);
}

// конструктор создания многоугольника с переменным кол-вом вершин
CPolygon::CPolygon(int n, POINT v, ...)
{
	SetPolygon(n, &v);
}

// конструктор создания многоугольника из другого
CPolygon::CPolygon(const CPolygon& p)
{
	SetPolygon(p);
}

CPolygon::~CPolygon()
{
	FreeVertexes();
}

// возвращает признак выпуклости
bool CPolygon::IsConvex() const
{
	return convex;
}

// возвращает признак существования
bool CPolygon::IsExist() const
{
	return exist;
}

// обновление свойств многоугольника
void CPolygon::ResetStatus()
{
	exist = CheckExist(vert, count); // провеяем многоугольник на существование
	convex = CheckConvex(vert, count); // провеяем многоугольник на выпуклость
}

// задание всех координат многоугольника
void CPolygon::SetPolygon(int n, POINT *v)
{
	SetFigure(n, v);
	ResetStatus();
}

// создание многоугольника из другого существующего
void CPolygon::SetPolygon(const CPolygon& p)
{
	int n = p.GetCountVertexes();
	CreateVertexes(n);
	for (int i = 0; i < count; i++) vert[i] = p.GetVertex(i); // копируем вершины
	// копируем статусы из другого существующего
	convex = p.IsConvex();
	exist = p.IsExist();
}

// получение многоугольника из другого существующего
CPolygon& CPolygon::GetPolygon()
{
	return *this;
}

// отобразить информацию о многоугольнике
void CPolygon::Show()
{
	if (count == 0)
	{
		std::cout << "многоугольник не задан" << std::endl;
		return;
	}	
	std::cout << "многоугольник состоит из " << count << " вершин(ы)" << std::endl;
	
	for (int i = 0; i < count; i++)
	{
		std::cout << "вершина " << i << ": ";
		std::cout << "x = " << vert[i].x << ", y = " << vert[i].y << std::endl;
	}
	if (!exist)
	{
		std::cout << "многоугольник имеет меньше 3-х вершин, не может быть нарисован" << std::endl;
		return;
	}
	std::cout << "многоугольник выпуклый: " << (convex ? "да" : "нет") << std::endl;
}

// сохраняем параметры фигуры из класса CPolygon в файл
void CPolygon::Save(std::ofstream &b_out)
{
	POINT v;
	int n = GetCountVertexes();
	b_out.write((char*)&n, sizeof(n));

	// записываем массив вершин в файл
	for (int i = 0; i < n; i++)
	{
		v = GetVertex(i);
		b_out.write((char*)&v, sizeof(POINT));
	}
}

// загружаем параметры фигуры из файла в класс CPolygon
int CPolygon::Load(std::ifstream &b_in)
{
	POINT v;
	int n;

	try
	{
		b_in.read((char*)&n, sizeof(n));
		if (b_in.eof()) throw 1; // если была попытка прочитать за границы файла

		CreateVertexes(n);
		for (int i = 0; i < n; i++)
		{
			b_in.read((char*)&v, sizeof(POINT));
			if (b_in.eof()) throw 2; // если была попытка прочитать за границы файла
			SetVertex(i, v);
		}
	}
	catch (int i) // обработка ошибок
	{
		switch (i)
		{
		case 1:
			return 1;
		case 2:
			Clear(); // значит данные не полны, отчищаем
			std::cerr << "Load: неожиданный конец файла" << std::endl;
			return 1;
		}
	}
	ResetStatus();

	return 0;
}
