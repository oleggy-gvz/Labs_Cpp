#pragma once

#include <windows.h>
#include <fstream>

// общий класс Фигура с чистыми виртуальными функциями
class Shape
{
protected:
	POINT *vert = NULL; // массив координат фигуры
	int count = 0; // кол-во точек
	
	void CreateVertexes(int n); // создание n точек фигуры
	void FreeVertexes(); // освобождение точек фигуры
	virtual void Clear(); // отчистить параметры фигуры

public:
	Shape();
	Shape(int n, POINT *v); // конструктор создания фигуры с по массиву вершин
	Shape(int n, POINT v, ...); // конструктор создания фигуры с переменным кол-вом вершин
	~Shape();

	void SetFigure(int n, POINT *v); // задание фигуры по массиву вершин
	void SetVertex(int n, POINT v); // установка координат для n-ой вершины фигуры

	POINT GetVertex(int n) const; // возвращаем координаты n-ой вершины фигуры
	int GetCountVertexes() const; // возвращаем кол-во вершин фигуры

	virtual void Show() = 0; // отобразить фигуру
	virtual void Save(std::ofstream &b_out) = 0; // сохранение данных фигуры в файл
	virtual int Load(std::ifstream &b_in) = 0; // загрузка данных фигуры из файла
};