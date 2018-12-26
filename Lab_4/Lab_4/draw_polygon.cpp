#include <windowsx.h>
#include <iostream>
#include "draw_polygon.h"

void CopyHwnd(DrawPolygon &dest, const DrawPolygon &scr)
{
	// искользуем дескриптор существующего окна
	dest.hwnd = scr.hwnd;
	// не перерисовываем окно
	dest.change_output = false;
}

// выбираем/открываем окно вывода изображения
void DrawPolygon::CreateGDIOutput()
{
	DeleteGDIOutput(); // удаляем старое окно

	switch (out)
	{
	case CONSOL:
		hwnd = GetConsoleWindow(); // получаем идентификатор окна
		break;
	case NOTEPAD:
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
		si.dwX = 100;
		si.dwY = 100;
		si.dwXSize = 100;
		si.dwYSize = 100;

		/*
		// 2-ой параметр lpCommandLine должен передаватся только переменной, иначе - исключение
		// TCHAR -> tchar.h
		TCHAR szCmdLine[] = _T("c:\\Windows\\notepad.exe");
		CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		*/
		DWORD dwExitCode;
		if (CreateProcess(L"c:\\Windows\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			// ждем пока пока процесс не будет готов или + не истечет интервал в 100 мс
			dwExitCode = WaitForSingleObject(pi.hProcess, 100);
		}
		else
		{
			std::cerr << "CreateGDIOutput: ошибка " << GetLastError() << std::endl;
		}
		hwnd = FindWindow(L"Notepad", NULL);
		break;
	}
}

// забываем/закрываем окно вывода изображения
void DrawPolygon::DeleteGDIOutput()
{
	if (hwnd == NULL) return; // если окно не было выбрано
	if (pi.hProcess == NULL) return; // если не был открыт процесс
	
	TerminateProcess(pi.hProcess, NO_ERROR); // закрываем процесс
	CloseHandle(pi.hProcess); // закрываем дескриптор созданного окна
	CloseHandle(pi.hThread);

	hwnd = NULL;
}

// создаем перо и кисть GDI на оcновании Paint
void DrawPolygon::CreateGDIPenBrush()
{
	if (hwnd == NULL)
	{
		std::cerr << "UpdatePenBrush: не установлен дескриптор окна" << std::endl;
		return;
	}
	hdc = GetDC(hwnd); // получаем контекст отображения

	// устанавливаем текущие значения GDI пера из пера Pant
	PEN pan = GetPen();
	COLORREF pan_c = RGB(pan.color.r, pan.color.g, pan.color.b);
	curr_PB.hPen = CreatePen(pan.style, pan.width, pan_c);

	// устанавливаем текущие значения GDI кисти из кисти Pant
	BRUSH brush = GetBrush();
	COLORREF bush_c = RGB(brush.color.r, brush.color.g, brush.color.b);
	
	// устанавливаем текущие значения GDI цвета фона из цвета фона Pant
	COLOR сol = GetBackColor();
	COLORREF back_c = RGB(сol.r, сol.g, сol.b);

	if (brush.style == -1) // однотонная заливка цветом кисти
		curr_PB.hBrush = CreateSolidBrush(bush_c);
	else if (brush.style == -2) // сплошная заливка цветом фона
		curr_PB.hBrush = CreateSolidBrush(back_c);
	else // заливка - штриховка
		curr_PB.hBrush = CreateHatchBrush(brush.style, bush_c);

	// устанавливаем текущие значения цвета фона
	SetBkColor(hdc, back_c);

	// создаем цвет пера и кисти для отрисовки фона
	//back_PB.hPen = CreatePen(PS_NULL, 0, s.GetBackColorCR());
	back_PB.hPen = GetStockPen(NULL_PEN);
	back_PB.hBrush = CreateSolidBrush(back_c);

	// сохраняем предыдущие значения пера и кисти
	// если значения ненулевые значит ранее уже были сохранены пред. знач.
	if (old_PB.hPen == NULL) old_PB.hPen = SelectPen(hdc, curr_PB.hPen);
	else SelectPen(hdc, curr_PB.hPen);

	if (old_PB.hBrush == NULL) old_PB.hBrush = SelectBrush(hdc, curr_PB.hBrush);
	else SelectBrush(hdc, curr_PB.hBrush);
}

// удаляем перо и кисть GDI 
void DrawPolygon::DeleteGDIPenBrush()
{
	if (hdc == NULL) return; // если контекст отображения не был создан

	// восстанавливаем предыдущие значения пера и кисти
	SelectPen(hdc, old_PB.hPen);
	SelectBrush(hdc, old_PB.hBrush);
	// удаляем текущие значения пера и кисти
	DeletePen(curr_PB.hPen);
	DeleteBrush(curr_PB.hBrush);
	// удаляем значения пера и кисти для отрисовки фона
	DeletePen(back_PB.hPen);
	DeleteBrush(back_PB.hBrush);

	ReleaseDC(hwnd, hdc); // освобождаем контекст отображения
}

// конструктор по умолчанию
DrawPolygon::DrawPolygon()
{}

// конструктор создания рисуемого цветного многоугольника
DrawPolygon::DrawPolygon(const CPolygon &p, const Paint &s, output o)
{
	SetDrawPolygon(p, s, o);
}

// конструктор копирования рисуемого цветного многоугольника из другого
DrawPolygon::DrawPolygon(const DrawPolygon &dp)
{
	CopyDrawPolygon(dp);
}

DrawPolygon::~DrawPolygon()
{
	DeleteGDIPenBrush();
	DeleteGDIOutput();
}

// создание рисуемого цветного многоугольника
void DrawPolygon::SetDrawPolygon(const CPolygon &p, const Paint &s, output o)
{	
	CopyPolygon(p);
	CopyPaint(s);
	SetOutput(o);
}

// конструктор копирования рисуемого цветного многоугольника из другого
void DrawPolygon::CopyDrawPolygon(const DrawPolygon &dp)
{
	CopyPolygon(dp);
	CopyPaint(dp);
	SetOutput(dp.GetOutput());
}

// установка способа вывода изображения
void DrawPolygon::SetOutput(output o)
{
	if (o != out) // если тип вывода поменялся
	{
		out = o;
		change_output = true; // при рисовании сменим окно на новое
	}
}

// получение способа вывода изображения
output DrawPolygon::GetOutput() const
{
	return out;
}

// отчищаем экран цветом заднего фона
void DrawPolygon::ClearScreen()
{
	// устанавливаем перо и кисть
	HPEN hCurrPen = SelectPen(hdc, back_PB.hPen);
	HBRUSH hCurrBrush = SelectBrush(hdc, back_PB.hBrush);

	GetClientRect(hwnd, &rt); // получаем размер окна
	POINT screen[4] = { { 0, 0 },{ 0, rt.bottom },{ rt.right, rt.bottom },{ rt.right, 0 } };
	Polygon(hdc, screen, 4); // зарисовываем многоугольник пером/кистью back_PB

	SelectPen(hdc, hCurrPen);
	SelectBrush(hdc, hCurrBrush);
}

void DrawPolygon::SetUpdateScreen(bool upd)
{
	update_screen = upd;
}

	// показать раскрашенный многоугольник на экране
bool DrawPolygon::Show()
{
	// если окно не нужно создавать, проверяем не закрыто ли оно уже
	// если закрыто, окно нужно создать повторно
	if (!change_output && GetDC(hwnd) == NULL) change_output = true;
	if (change_output)
	{
			CreateGDIOutput(); // создаем новое окно при выводе окна вывода
			change_output = false; // в последующих вызовах создавать окно вывода не нужно
	}
	// всегда обновляем перо и кисть и фон т.к. в родительском класе
	// мог быть изменен стиль собственными методами
	CreateGDIPenBrush(); 

	if (update_screen) ClearScreen(); // обновление экрана
	try
	{
		if (!IsExist()) throw 1;
	}
	catch (int i) // обработка ошибок
	{
		std::cerr << "многоугольник имеет меньше 3-х вершин, и не может быть нарисован" << std::endl;
		std::cerr << "выводим таблицу вершин:" << std::endl;
		CPolygon::Show();

		return false;
	}

	int n = GetCountVertexes();
	POINT *v = new POINT[n];
	for (int i = 0; i < n; i++)	v[i] = GetVertex(i); // получаем вершины
	Polygon(hdc, v, n); // рисуем прямоугольник
	delete []v;

	return true;
}

// сохраняем параметры фигуры из класса DrawPolygon в файл
void DrawPolygon::Save(std::ofstream &b_out)
{
	CPolygon::Save(b_out);

	// сохраниим данные стиля
	PEN pen = GetPen(); // данные пера
	BRUSH brush = GetBrush(); // данные кисти (заливки)
	COLOR c_bak = GetBackColor(); // цвет фона

	b_out.write((char*)&pen, sizeof(pen)); // данные пера
	b_out.write((char*)&brush, sizeof(brush)); // данные кисти (заливки)
	b_out.write((char*)&c_bak, sizeof(c_bak));  // цвет фона

	b_out.write((char*)&out, sizeof(out));  // вывод
	b_out.write((char*)&update_screen, sizeof(update_screen)); // обновление экрана
}

// загружаем параметры фигуры из файла в класс DrawPolygon
void DrawPolygon::Load(std::ifstream &b_in)
{
	CPolygon::Load(b_in);

	PEN pen; // данные пера
	BRUSH brush; // данные кисти (заливки)
	COLOR c_bak; // цвет фона

	b_in.read((char*)&pen, sizeof(pen)); // данные пера
	b_in.read((char*)&brush, sizeof(brush)); // данные кисти (заливки)
	b_in.read((char*)&c_bak, sizeof(c_bak)); // цвет фона

	SetPaint(pen, brush, c_bak); // установим стиль

	b_in.read((char*)&out, sizeof(out)); // вывод
	b_in.read((char*)&update_screen, sizeof(update_screen)); // обновление экрана
}