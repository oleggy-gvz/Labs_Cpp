#include "polygon.h"
#include <iostream>

// установка нового кол-ва вершин и стрирание данных по всем вершинам
int CPolygon::CreateVertexes(int n)
{
	if (n == count) return 0; // если кол-во вершине не поменялось

	if (vert != NULL) delete[] vert; // удаляем вершины	
	vert = new POINT[n]; // выделить память под новое кол-во вершин
	if (vert == NULL)
	{
		std::cerr << "CreateVertexes: не достаточно памяти" << std::endl;
		exit(1);
	}
	count = n; // установить новое кол-во вершин

	return 0;
}

// освобождение вершин многоугольника
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

// конструктор создания с переменным кол-вом вершин
CPolygon::CPolygon(int n, POINT v, ...)
{
	POINT *ver = &v;
	SetAllVertexes(n, ver);
}

// конструктор создания класса из другого
CPolygon::CPolygon(const CPolygon& p)
{
	int n = p.GetCountVertexes();
	CreateVertexes(n);
	for (int i = 0; i < count; i++) vert[i] = p.GetVertex(i); // копируем вершины	
}

CPolygon::~CPolygon()
{
	FreeVertexes();
}

// проверяем возможность отображения многоугольника
// должен иметь хотя бы 3 вершины с различными координатами
bool CPolygon::CheckExist(int n, POINT *v)
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
bool CPolygon::CheckConvex(int n, POINT *v)
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
		// если в обоих битах по 1 т.е. 11 (dec: 3) то знак поменялся при обходе вершин
		if (flag == 3) return false; 	
	}
	if (flag != 0) return true;
	return false;
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

// возвращаем координаты n-ой вершины многоугольника
POINT CPolygon::GetVertex(int n) const
{
	try
	{
		if (n > count || n < 0) throw "GetVertex: попытка доступа к вершине за границами существующих";
	}
	catch (char *str) // обработка ошибок
	{
		std::cerr << str << std::endl;
		exit(1);
	}

	return vert[n];
}

// возвращаем кол-во вершин многоугольника
int CPolygon::GetCountVertexes() const
{
	return count;
}

// обновить статусы 
void CPolygon::ResetStatus()
{
	exist = CheckExist(count, vert); // провеяем треугольник на существование
	convex = CheckConvex(count, vert); // провеяем треугольник на выпуклость
}

// задание всех координат фигуры
void CPolygon::SetAllVertexes(int n, POINT *v)
{
	CreateVertexes(n); // устанавливаем новое кол-во вершин
	for (int i = 0; i < count; i++) vert[i] = v[i]; // копируем вершины
	ResetStatus();
}

// установка координат POINT для n-ой вершины
void CPolygon::SetVertex(int n, POINT v)
{
	try
	{
		if (n > count || n < 0) throw "SetVertex: попытка доступа к вершине за границами существующих";
	}
	catch (char *str) // обработка ошибок
	{
		std::cerr << str << std::endl;
	}
	vert[n] = v;
}

// обнуление всех данных многоугольника
void CPolygon::Clear()
{
	FreeVertexes();

	vert = NULL;
	count = 0;
	convex = false;
	exist = false;
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