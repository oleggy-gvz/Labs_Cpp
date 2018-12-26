#pragma once

#include "draw_polygon.h"

class CombiDrawPolygon : public DrawPolygon
{
	DrawPolygon *f_out; // внешн€€ фигура
	DrawPolygon *f_in; // внутренн€€ фигура

public:
	CombiDrawPolygon(DrawPolygon &dp_in, DrawPolygon &dp_out);
	~CombiDrawPolygon();

	void SetCombiPolygon(DrawPolygon &dpp_in, DrawPolygon &dpp_out);
	void Show();
};