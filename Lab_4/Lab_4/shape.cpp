#include "shape.h"
#include <iostream>

// создание нового кол-ва вершин
void Shape::CreateVertexes(int n)
{
	if (n == count) return; // если кол-во вершине не поменялось
	FreeVertexes(); // удаляем вершины

	vert = new POINT[n]; // выделить память под новое кол-во вершин
	if (vert == NULL)
	{
		std::cerr << "CreateVertexes: не достаточно памяти" << std::endl;
		exit(1);
	}
	count = n; // установить новое кол-во вершин
}

// удаление (освобождение) вершин
void Shape::FreeVertexes()
{
	if (vert != NULL) delete[] vert;
}

// отчистка фигуры
void Shape::Clear()
{
	FreeVertexes();

	vert = NULL;
	count = 0;
}

// конструктор по умолчанию
Shape::Shape()
{}

// конструктор создания фигуры с по массиву вершин
Shape::Shape(int n, POINT *v)
{
	SetShape(n, v);
}

// конструктор создания фигуры с переменным кол-вом вершин
Shape::Shape(int n, POINT v, ...)
{
	SetShape(n, &v);
}

// конструктор копирования фигуры из другой
Shape::Shape(const Shape& p)
{
	CopyShape(p);
}

Shape::~Shape()
{
	FreeVertexes();
}

// создание фигуры по массиву вершин
void Shape::SetShape(int n, POINT *v)
{
	CreateVertexes(n); // устанавливаем новое кол-во вершин
	for (int i = 0; i < count; i++)	vert[i] = v[i]; // копируем вершины
}

// копирование фигуры из другой
void Shape::CopyShape(const Shape& p)
{
	int n = p.GetCountVertexes();
	CreateVertexes(n);
	for (int i = 0; i < count; i++) vert[i] = p.GetVertex(i); // копируем вершины
}

// установка координат для n-ой вершины фигуры
void Shape::SetVertex(int n, POINT v)
{
	if (n > count || n < 0) 
		std::cerr << "SetVertex: попытка доступа к вершине за границами существующих" << std::endl;
	vert[n] = v;
}

// возвращаем координаты n-ой вершины фигуры
POINT Shape::GetVertex(int n) const
{
	if (n > count || n < 0)
		std::cerr << "SetVertex: попытка доступа к вершине за границами существующих" << std::endl;

	return vert[n];
}

// возвращаем кол-во вершин фигуры
int Shape::GetCountVertexes() const
{
	return count;
}

// отобразить информацию о фигуре
bool Shape::Show()
{
	if (count == 0)
	{
		std::cout << "фигура пустая, без вершин" << std::endl;
		return false;
	}
	
	for (int i = 0; i < count; i++)
	{
		std::cout << "точка " << i << ": ";
		std::cout << "x = " << vert[i].x << ", y = " << vert[i].y << std::endl;
	}
	return true;
}

// сохраняем параметры фигуры из класса Shape в файл
void Shape::Save(std::ofstream &b_out)
{
	POINT v;
	int n = GetCountVertexes();
	b_out.write((char*)&n, sizeof(n)); // пишем кол-во вершин

	for (int i = 0; i < n; i++)	// записываем массив вершин
	{
		v = GetVertex(i);
		b_out.write((char*)&v, sizeof(v));
	}
}

// загружаем параметры фигуры из файла в класс Shape
void Shape::Load(std::ifstream &b_in)
{
	POINT v;
	int n;

	b_in.read((char*)&n, sizeof(n)); // читаем кол-во вершин
	CreateVertexes(n); // создаем массив вершин

	for (int i = 0; i < n; i++) // считываем массив вершин
	{
		b_in.read((char*)&v, sizeof(v));
		SetVertex(i, v);
	}
}