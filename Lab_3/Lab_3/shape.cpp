#include "shape.h"
#include <iostream>

// установка нового кол-ва вершин и стрирание данных по всем вершинам
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

// освобождение вершин многоугольника
void Shape::FreeVertexes()
{
	if (vert != NULL) delete[] vert;
}

// обнуление всех данных многоугольника
void Shape::Clear()
{
	FreeVertexes();

	vert = NULL;
	count = 0;
}

Shape::Shape()
{}

// конструктор создания фигуры с по массиву вершин
Shape::Shape(int n, POINT *v)
{
	SetFigure(n, v);
}

// конструктор создания фигуры с переменным кол-вом вершин
Shape::Shape(int n, POINT v, ...)
{
	SetFigure(n, &v);
}

Shape::~Shape()
{
	FreeVertexes();
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

// задание фигуры по массиву вершин
void Shape::SetFigure(int n, POINT *v)
{
	CreateVertexes(n); // устанавливаем новое кол-во вершин
	for (int i = 0; i < count; i++)	vert[i] = v[i]; // копируем вершины
}