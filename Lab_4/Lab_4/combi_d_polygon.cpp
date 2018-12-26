#include "combi_d_polygon.h"
#include <conio.h>

// конструктор по умолчанию
CombiDrawPolygon::CombiDrawPolygon()
{}

// конструктор создани€ комбинированного многоугольника из двух рисуемых многоугольников
CombiDrawPolygon::CombiDrawPolygon(const DrawPolygon &dp_out, const DrawPolygon &dp_in)
{
	SetCombiPolygon(dp_out, dp_in);
}

// конструктор копировани€ комбинированного многоугольника из существующего
CombiDrawPolygon::CombiDrawPolygon(const CombiDrawPolygon &cdp)
{
	CopyCombiPolygon(cdp);
}

CombiDrawPolygon::~CombiDrawPolygon()
{}

// создание комбинированного  многоугольника из двух рисуемых многоугольников
void CombiDrawPolygon::SetCombiPolygon(const DrawPolygon &dp_out, const DrawPolygon &dp_in)
{
	CopyDrawPolygon(dp_out); // копируем внешнюю фигуру
	f_in.CopyDrawPolygon(dp_in); // копируем внутренний рисуемый многоугольник  
}

// копировани€ комбинированного рисуемого цветного многоугольника
void CombiDrawPolygon::CopyCombiPolygon(const CombiDrawPolygon &cdp)
{
	CopyDrawPolygon(cdp); // копируем внешнюю фигуру
	// дружественна€ функци€ дл€ доступа к приватной части cdp.f_in
	// копируем многоугольник из cdp.f_in в f_in
	CopyInternalDrawPolygon(f_in, cdp);
}

// дружественна€ функци€ дл€ доступа к приватной части CombiDrawPolygon::f_in извне
void CopyInternalDrawPolygon(DrawPolygon &dp, const CombiDrawPolygon &cdp)
{
	// копируем раскрашенный многоугольник в dp из приватной части класса cdp.f_in (DrawPolygon)
	dp.CopyDrawPolygon(cdp.f_in);
}

// показать комбинированный раскрашенный многоугольник на экране
bool CombiDrawPolygon::Show()
{
	bool res;
	//SetOutput(CONSOL);
	res = DrawPolygon::Show(); // рисуем внешнюю фигуру

	// если главна€ (внешн€€) фигура не нарисована то не рисуем больше
	if (res == false) return false; 
	// установка заливки внутренней фигуры цветом фона фигуры внешней
	// стиль заливки - однотонный цвет	
	f_in.SetBrush({ -1, GetBackColor() });
	f_in.SetOutput(GetOutput()); // вывод в то же окно куда выведен внешний многоугольник
	f_in.SetUpdateScreen(false); // не перерисовываем экран при рисовании внутренней фигуры

	// копируем из приватной части текущего класса hwnd в приватную часть f_in.hwnd
	if (GetOutput() != CONSOL) // если окно вывода не консольное
		CopyHwnd(f_in, *this); // копируем hwnd у внешней фигуры во внутреннюю

	f_in.Show(); // рисуем внутреннюю фигуру

	return true;
}

// сохран€ем параметры фигуры из класса DrawPolygon в файл
void CombiDrawPolygon::Save(std::ofstream &b_out)
{
	DrawPolygon::Save(b_out);
	f_in.Save(b_out);
}

// загружаем параметры фигуры из файла в класс DrawPolygon
void CombiDrawPolygon::Load(std::ifstream &b_in)
{
	DrawPolygon::Load(b_in);
	f_in.Load(b_in);
}