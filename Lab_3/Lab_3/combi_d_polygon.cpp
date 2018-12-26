#include "combi_d_polygon.h"
#include <conio.h>

CombiDrawPolygon::CombiDrawPolygon(DrawPolygon &dp_in, DrawPolygon &dp_out)
{
	SetCombiPolygon(dp_in, dp_out);
}

CombiDrawPolygon::~CombiDrawPolygon()
{
	delete f_in;
	delete f_out;
}

void CombiDrawPolygon::SetCombiPolygon(DrawPolygon &dp_out, DrawPolygon &dp_in)
{
		f_in = new DrawPolygon(dp_in);
		f_out = new DrawPolygon(dp_out);
}

void CombiDrawPolygon::Show()
{
	f_out->Show(); // рисуем внешнюю фигуру

	f_in->SetBrushColor(f_out->GetBackColor()); // установка заливки внутренней фигуры цветом фона фигуры внешней
	f_in->SetBrushStyle(-1); // задаем тон заливки - однотонный цвет
	f_in->UpdatePenBrush(); // обновляем системные перо и кисть
	f_in->SetUpdateScreen(false); // не перерисовываем экран при рисовании внутренней фигуры

	f_in->Show(); // внутреннюю фигуру
}