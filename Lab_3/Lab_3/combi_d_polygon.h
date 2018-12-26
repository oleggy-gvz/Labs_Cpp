#pragma once

#include "draw_polygon.h"

class CombiDrawPolygon : public DrawPolygon
{
	DrawPolygon *f_out; // ������� ������
	DrawPolygon *f_in; // ���������� ������

public:
	CombiDrawPolygon(DrawPolygon &dp_in, DrawPolygon &dp_out);
	~CombiDrawPolygon();

	void SetCombiPolygon(DrawPolygon &dpp_in, DrawPolygon &dpp_out);
	void Show();
};