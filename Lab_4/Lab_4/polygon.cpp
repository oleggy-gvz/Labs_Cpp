#include "polygon.h"
#include <iostream>

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

// конструктор по умолчанию
CPolygon::CPolygon()
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
	CopyPolygon(p);
}

CPolygon::~CPolygon()
{
	Clear();
}

// задание всех координат многоугольника
void CPolygon::SetPolygon(int n, POINT *v)
{
	SetShape(n, v);
	UpdateStatus();
}

// копирование многоугольника из другого существующего
void CPolygon::CopyPolygon(const CPolygon& p)
{
	CopyShape(p);
	// копируем статусы из другого существующего
	convex = p.IsConvex();
	exist = p.IsExist();
}

// обнуление всех данных многоугольника
void CPolygon::Clear()
{
	Shape::Clear();
	convex = false;
	exist = false;
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
void CPolygon::UpdateStatus()
{
	int n = GetCountVertexes();
	POINT *v = new POINT[n];
	for (int i = 0; i < n; i++)	v[i] = GetVertex(i);

	exist = CheckExist(v, n); // провеяем многоугольник на существование
	convex = CheckConvex(v, n); // провеяем многоугольник на выпуклость

	delete []v;
	
	/*
	// установить модификатор protected для vert, count в родительском классе 
	exist = CheckExist(vert, count); // провеяем многоугольник на существование
	convex = CheckConvex(vert, count); // провеяем многоугольник на выпуклость
	*/
	}

// отобразить информацию о многоугольнике
bool CPolygon::Show()
{
	Shape::Show();
	if (IsExist())
	{
		std::cout << "многоугольник выпуклый: " << (convex ? "да" : "нет") << std::endl;
		return false;
	}
	return true;
}

// сохраняем параметры фигуры из класса CPolygon в файл
void CPolygon::Save(std::ofstream &b_out)
{
	Shape::Save(b_out);

	b_out.write((char*)&exist, sizeof(exist));
	b_out.write((char*)&convex, sizeof(convex));
}

// загружаем параметры фигуры из файла в класс CPolygon
void CPolygon::Load(std::ifstream &b_in)
{
	Shape::Load(b_in);

	b_in.read((char*)&exist, sizeof(exist));
	b_in.read((char*)&convex, sizeof(convex));
}