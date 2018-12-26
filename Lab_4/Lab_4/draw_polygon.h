#pragma once

#include <windows.h>
#include "polygon.h"
#include "paint.h"

enum output {CONSOL, NOTEPAD}; // тип окна вывода изображений

// структура пера и кисти
struct PEN_BRUSH
{
	HPEN hPen;
	HBRUSH hBrush;
};

// класс рисуемого многоугольника
class DrawPolygon : public Paint, public CPolygon
{
	output out = CONSOL; // тип окна вывода изображения
	bool change_output = true; // факт изменения типа вывода 
	// обновление экрана при рисовании, по умолчанию всегда обновляем
	bool update_screen = true;

	// системные значения пера и кисти

	HWND hwnd = NULL; // идентификатор окна
	// дружественная функция для доступа к приватной части DrawPolygon::hwnd извне
	friend void CopyHwnd(DrawPolygon &dest, const DrawPolygon &scr);

	HDC hdc = NULL; // контекст отображения
	RECT rt;  // размеры области окна
	
	PEN_BRUSH curr_PB; // текущие значение пера и кисти
	PEN_BRUSH back_PB; // значения пера и кисти для отрисовки фона
	PEN_BRUSH old_PB = { NULL }; // старое значения пера и кисти
	STARTUPINFO si = { NULL }; // структура для запуска процесса
	PROCESS_INFORMATION pi = { NULL }; // структура с информацией о запущенном процессе

	void CreateGDIOutput(); // выбираем/открываем окно вывода изображения
	void DeleteGDIOutput(); // забываем/закрываем окно вывода изображения	
	void CreateGDIPenBrush(); // создаем перо и кисть GDI на оcновании Paint	
	void DeleteGDIPenBrush(); // удаляем перо и кисть GDI 

public:

	DrawPolygon();
	// установка рисуемого многоугольника
	DrawPolygon(const CPolygon &p, const Paint &s, output o = CONSOL);
	// конструктор копирования рисуемого многоугольника из другого
	DrawPolygon(const DrawPolygon &dp);
	~DrawPolygon();

	// установка рисуемого цветного многоугольника
	void SetDrawPolygon(const CPolygon &p, const Paint &s, output o = CONSOL);
	// копирование рисуемого цветного многоугольника
	void CopyDrawPolygon(const DrawPolygon &dp);

	void SetUpdateScreen(bool upd); // обновления эрана при рисовании
	void SetOutput(output o); // установка способа вывода изображения
	output GetOutput() const; // получение способа вывода изображения
	void ClearScreen(); // отчистка окна цветом фона	
	bool Show(); // показать раскрашенный многоугольник на экране

	// сохранение рисуемого многоугольника в файл
	void Save(std::ofstream &b_out);
	// загрузка рисуемого многоугольника из файла
	void Load(std::ifstream &b_in);
};