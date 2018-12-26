#pragma once

#include <windows.h>
#include "shape.h"

class CPolygon: public Shape
{
	bool convex; // признак выпуклости
	bool exist; // признак существования

	bool CheckConvex(POINT *v, int n); // проверяет многоугольник на выпуклость
	bool CheckExist(POINT *v, int n); // проверяет возможность отображения многоугольника
	void Clear(); // отчистить параметры фигуры

public:
	CPolygon();
	CPolygon(int n, POINT *v); // конструктор создания многоугольника по массиву вершин
	CPolygon(int n, POINT v, ...); // конструктор создания многоугольника с переменным кол-вом вершин
	CPolygon(const CPolygon& p); // конструктор создания многоугольника из другого
	~CPolygon();
	
	// свойства многоугольника
	bool IsConvex() const; // получаем признак выпуклости
	bool IsExist() const; // получаем признак существования (отображения)
	void ResetStatus(); // обновление признаков многоугольника
						
	void SetPolygon(int n, POINT *v); // задание многоугольника по массиву вершин
	void SetPolygon(const CPolygon& p); // создание многоугольника из другого существующего
	CPolygon& GetPolygon(); // получение многоугольника

	void Show(); // показать информацию о многоугольнике
	void Save(std::ofstream &b_out); // сохранение данных фигуры в файл
	int Load(std::ifstream &b_in); // загрузка данных фигуры из файла
};