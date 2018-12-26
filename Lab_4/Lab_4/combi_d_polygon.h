#pragma once

#include "draw_polygon.h"

class CombiDrawPolygon : public DrawPolygon
{
	DrawPolygon f_in; // внутренний раскрашенный многоугольник
	// дружественная функция для доступа к приватной части CombiDrawPolygon::f_in извне
	friend void CopyInternalDrawPolygon(DrawPolygon &in, const CombiDrawPolygon &cdp);

public:
	CombiDrawPolygon();
	// конструктор создания комбинированного многоугольника из двух рисуемых многоугольников
	CombiDrawPolygon(const DrawPolygon &dp_out, const DrawPolygon &dp_in);
	// конструктор копирования комбинированного многоугольника из существующего
	CombiDrawPolygon(const CombiDrawPolygon &cdp);
	~CombiDrawPolygon();

	// создание комбинированного  многоугольника из двух рисуемых многоугольников
	void SetCombiPolygon(const DrawPolygon &dp_out, const DrawPolygon &dp_in);
	// копирования комбинированного рисуемого цветного многоугольника
	void CopyCombiPolygon(const CombiDrawPolygon &cdp);
	// показать комбинированный раскрашенный многоугольник на экране
	bool Show();

	// сохраняем параметры фигуры из класса CombiDrawPolygon в файл
	void Save(std::ofstream &b_out);
	// загружаем параметры фигуры из файла в класс CombiDrawPolygon
	void Load(std::ifstream &b_in);
};