#pragma once

#include <windows.h>
#include <fstream>

// класс фигуры (контрура из точек)
class Shape
{	
	POINT *vert = NULL; // массив координат фигуры
	int count = 0; // кол-во точек фигуры

	// создание нового кол-ва вершин
	void CreateVertexes(int n);
	// удаление (освобождение) вершин
	void FreeVertexes(); 

public:
	Shape();
	// конструктор создание фигуры по массиву вершин
	Shape(int n, POINT *v);
	// конструктор создания фигуры с переменным кол-вом вершин
	Shape(int n, POINT v, ...);
	// конструктор копирования фигуры
	Shape(const Shape& p);
	~Shape();

	// создание фигуры по массиву вершин
	void SetShape(int n, POINT *v);
	// копирования фигуры из другой
	void CopyShape(const Shape& p);
	// установка координат для n-ой вершины фигуры
	void SetVertex(int n, POINT v);
	// возвращаем координаты n-ой вершины фигуры
	POINT GetVertex(int n) const;
	// возвращаем кол-во вершин фигуры
	int GetCountVertexes() const;
	// отчистить параметры фигуры
	virtual void Clear();
	// отобразить фигуру
	virtual bool Show();
	// сохранение данных фигуры в файл
	virtual void Save(std::ofstream &b_out);
	// загрузка данных фигуры из файла
	virtual void Load(std::ifstream &b_in);
};