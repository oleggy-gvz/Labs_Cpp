#pragma once

#include <windows.h>
#include "shape.h"

// замкнутая фигура - многоугольник
class CPolygon: public Shape
{
	bool exist = false; // признак существования многоугольника
	bool convex = false; // признак выпуклости многоугольника

	// проверяет возможность отображения многоугольника
	bool CheckExist(POINT *v, int n);
	// проверяет многоугольник на выпуклость
	bool CheckConvex(POINT *v, int n);

public:
	CPolygon();
	// конструктор создания многоугольника по массиву вершин
	CPolygon(int n, POINT *v); 	
	// конструктор создания многоугольника с переменным кол-вом вершин
	CPolygon(int n, POINT v, ...);
	// конструктор копирования многоугольника
	CPolygon(const CPolygon& p); 
	~CPolygon();
	
	// задание многоугольника по массиву вершин		
	void SetPolygon(int n, POINT *v); 
	// копируем многоугольник из другого
	void CopyPolygon(const CPolygon& p);
	// отчистить многоугольник
	void Clear();

	// свойства многоугольника
	// получаем признак существования (отображения)
	bool IsExist() const;
	// получаем признак выпуклости
	bool IsConvex() const;
	// обновление признаков многоугольника
	void UpdateStatus(); 

	// показать информацию о многоугольнике
	bool Show(); 
	// сохранение данных фигуры в файл
	void Save(std::ofstream &b_out);
	// загрузка данных фигуры из файла
	void Load(std::ifstream &b_in); 
};