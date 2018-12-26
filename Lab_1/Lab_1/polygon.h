#pragma once

#include <windows.h>
#include <fstream>

class CPolygon
{
	POINT *vert = NULL; // массив вершин
	int count = 0; // кол-во вершин

	bool convex = false; // признак выпуклости
	bool exist = false; // признак существования

	int CreateVertexes(int n); // создание n вершин многоугольника
	void FreeVertexes(); // освобождение вершин многоугольника

	bool CheckConvex(POINT *v, int n); // проверяет многоугольник на выпуклость
	bool CheckExist(POINT *v, int n); // проверяет возможность отображения многоугольника

public:
	CPolygon();
	CPolygon(int n, POINT *v);
	CPolygon(int n, POINT ver, ...); 
	CPolygon(const CPolygon& p); // конструктор создания класса из другого
	~CPolygon();

	// свойства многоугольника
	bool IsConvex() const; // получаем признак выпуклости
	bool IsExist() const; // получаем признак существования (отображения)
	void ResetStatus(); // обновление признаков многоугольника

	void SetVertex(int n, POINT v); // установка координат n-ой вершины многоугольника
	POINT GetVertex(int n) const; // возвращаем координаты n-ой вершины многоугольника
	int GetCountVertexes() const; // возвращаем кол-во вершин многоугольника

	void SetAllVertexes(int n, POINT *v); // задание всех координат фигуры
	void Clear(); // обнуление всех данных многоугольника

	void Save(std::ofstream &b_out); // сохранение данных изображения в файл
	int Load(std::ifstream &b_in); // загрузка данных изображения в файл
};