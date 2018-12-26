	#include "dlist.h"
#include <iostream>
#include <fstream>
#include "polygon.h"

// создаем элемент с установкой левого и правого указателя
DNode *DList::CreateNode(CPolygon& data)
{
	DNode *p = new DNode(data);

	if (p == NULL)
	{
		std::cerr << "CreateNode: не достаточно памяти" << std::endl;
		exit(1);
	}
	return p;
}

//  удаляем элемент
void DList::FreeNode(DNode *p)
{
	delete p;
}

// копирование списка
void DList::CopyList(const DList& L)
{
	if (size != 0) ClearList(); // если список не пустой, отчищаем перед копированием в него

	// по элементно вставляем каждый элемент с начала списка
	for (DNode *p = L.GetFront(); p != NULL; p = p->NextRight())
		//InsertAfter(*p->data);
		InsertAfter(*p->GetData());
 
	curr = L.GetCurrent(); // делаем текущий указатель на тот который в был в копируемом списке
	curr_pos = L.GetCurrentPosition(); // делаем текущий индекс на тот который в был в копируемом списке
}

DList::DList()
{}

DList::DList(const DList& L)
{
	CopyList(L);
}

DList::~DList()
{
	ClearList();
}

// оператор присваивания (копирования)
DList& DList::operator=(const DList& dl)
{
	// исключаем возможность присвоить самому себе
	if (this == &dl) return *this; 

	CopyList(dl); // копируем список
	
	return *this;
}

// получить указатель на первый элемент
DNode* DList::GetFront() const
{
	return front;
}
	
// получить указатель на последний элемент
DNode* DList::GetRear() const
{
	return rear;
}

// получить указатель на текущий элемент	
DNode* DList::GetCurrent() const
{
	return curr;
}

// получить индекс текущей позиции в списке
int DList::GetCurrentPosition() const
{
	return curr_pos;
}

// получение размерности списка
int DList::GetSize() const
{
	return size;     
}

// получения статуса списка о его пустоте 
bool DList::IsEmpty() const
{
	return size == 0; // front == NULL
}

// установка текущей позиции
void DList::Reset(int pos)
{
	if (size == 0) return; // если список пустой front == NULL, ничего не делаем

	// если позиция указана неверная - выходим
	if (pos < 0 || pos > size - 1)
	{
		std::cerr << "Reset: установка позиции за границы списка: " << pos << std::endl;
		return;
	}
	if (pos == curr_pos) return; // если выбрана текущая позиция	
	
	if (pos == 0) // если выбрана первая позиция
	{
		curr = front;
	}
	else if (pos == size - 1) // если выбрана последняя позиция
	{
		curr = rear;
	}
	else // если выбрано где то в середине списка
	{
		// ищем фиксированный указатель который ближе всех к позиции pos
		int d_front = pos, d_rear = size - 1 - pos;
		int d_curr = (curr_pos > pos) ? curr_pos - pos : pos - curr_pos;

		// нахождение минимума среди трех значенийиvs[ для перемещения в нужную позицию
		// т.е. кол-во перемещений по узлам необходимых для достижения нужной позиции
		int min = d_front;
		if (d_rear < min) min = d_rear;
		if (d_curr < min) min = d_curr;

		// сдвигаем относительно фиксированного указателя на min кол-во узлов 
		DNode *p;
		DNode *(DNode::*Next)() const; // указатель на константный метод - шаги
		if (min == d_front) // если ближе всех указатель начала списка
		{
			p = front; // установим начальный указатель
			Next = &DNode::NextRight; // направление вперед (вправо)
		}
		else if (min == d_rear) // если ближе всех указатель конца списка
		{
			p = rear; // установим начальный указатель
			Next = &DNode::NextLeft; // направление назад (влево)
		}
		else if (min == d_curr) // если ближе всех указатель текущ. позиции
		{
			p = curr; // установим начальный указатель
			if (curr_pos > pos) Next = &DNode::NextLeft; // направление назад (влево)
			else Next = &DNode::NextRight; // направление вперед (вправо)
		}
		// делаем перемещения в нужном направлении в кол-ве min к нужной позиции
		for (int i = 0; i < min; i++) p = (p->*Next)();
		curr = p;
	}
	curr_pos = pos;
}

// установка текущей позиции на начало	
void DList::SetFront()
{
	Reset(0);
}

// установка текущей позиции на конец
void DList::SetRear()
{
	Reset(size - 1);
}

// передвигаем текущую позицию на предыдущий элемент
void DList::Previous()
{
   if (curr != NULL) // если не достигли границы списка
   {
      curr = curr->NextLeft();
      curr_pos--;
   }
}

// передвигаем текущую позицию на следующий элемент
void DList::Next()
{
   if (curr != NULL) // если не достигли границы списка
   {
      curr = curr->NextRight();
      curr_pos++;
   }
}

// признак границы списка
bool DList::EndOfList(void) const
{
	return curr == NULL;
}

// вставка элемента после текущей позиции
void DList::InsertAfter(CPolygon& data)
{
	DNode *p = CreateNode(data); // создаем элемент

	if (size == 0) // если список пустой front == NULL
	{
		// первый и последний указатели и тек. указатель указывает на первый вставленный элемент
		front = curr = rear = p;
	}
	else // если список уже не пустой
	{	
		curr->InsertRight(p); // вставка элемента после (справа) от текущей позиции
		// если текущая позиция установлена на последний элемент	
		if (curr == rear) rear = p; // значит обновляем указатель конца списка
		curr = p; // текущ. элемент становится этим узлом
	}
	curr_pos++; // позиция свдигается до этого номера элемента (т.е. +1)
	size++; // увеличиваем размерность
}

// вставка элемента в конец списка
void DList::InsertRear(CPolygon& data)
{
	curr_pos = size-1; // устанавливаем текущ. позицию в конец
	curr = rear; // устанавливает текущ. указатель в конец
	InsertAfter(data);
}

// вставка элемента перед текущей позицией
void DList::InsertBefore(CPolygon& data)
{
	DNode *p = CreateNode(data); // создаем элемент

	if (size == 0) // если список пустой front == NULL
	{
		// первый и последний указатели и тек. указатель указывает на первый вставленный элемент
		front = curr = rear = p;
		curr_pos = 0;
	}
	else // если список уже не пустой
	{
		curr->InsertLeft(p); // вставка элемента перед (слева) от текущей позиции
		// если текущая позиция установлена на первый элемент	
		if (curr == front) front = p; // значит обновляем указатель головы списка
		curr = p; // текущ. элемент становится этим узлом
		// индекс curr_pos остается прежним, т.к. должен указывать на новый элемент
	}
	size++; // увеличиваем размерность
}

// вставка элемента в начало списка
void DList::InsertFront(CPolygon& data)
{
	curr_pos = 0; // устанавливаем текущ. позицию в начало
	curr = front; // устанавливает текущ. указатель в начало
	InsertBefore(data);
}

// удаление элемента текущей позиции
void DList::DeleteAt()
{
	// если достугнута граница списка, ничего не делаем
	if (curr == NULL) return;
	
	DNode *p_next; // элемент который станет на место удаленного
	if (curr == front) // если текущий элемент первый элемент списка
	{
		p_next = curr->NextRight(); // сохраняем адрес следующего элемента
		front = p_next; // теперь он будет первыйм узлом
		// индекс текущей позиции curr_pos не изменится
	}
	else if (curr == rear) // если текущий элемент последний элемент списка 
	{
		p_next = curr->NextLeft(); // сохраняем адрес предыдущего элемента
		rear = p_next; // теперь он будет последним узлом
		curr_pos--; // индекс текущей позиции сдвинется назад
	}
	else // если текущий элемент находится в середине списка
	{
		p_next = curr->NextRight(); // сохраняем адрес следующего элемента
		// индекс текущей позиции curr_pos не изменится
	}
	// вырезаем текущий элемент из списка, но сохраняем его адрес
	DNode *p = curr->Delete();
	FreeNode(p); // освобождаем по этому адресу элемент
	curr = p_next;
	size--;
}

// удаление элемента первой позиции
void DList::DeleteFront()
{
	curr_pos = 0; // устанавливаем текущ. позицию в начало
	curr = front; // устанавливает текущ. указатель в начало
	DeleteAt();
}

// удаление элемента последней позиции
void DList::DeleteRear()
{
	curr_pos = size - 1; // устанавливаем текущ. позицию в конец
	curr = rear; // устанавливает текущ. указатель в конец
	DeleteAt();
}

// получение блока данных текущего элемента
CPolygon* DList::Data()
{
	// если достугнута граница списка, ошибка
	if (curr == NULL)
	{
		std::cerr << "Data: неверная ссылка на получение данных" << std::endl;
		exit(1);
	}
	//return curr->data;
	return curr->GetData();
}

// получение данных для модификации ключа
int DList::Key()
{
	// если достугнута граница списка, ошибка
	if (curr == NULL)
	{
		std::cerr << "Key: неверная ссылка на получение данных" << std::endl;
		exit(1);
	}
	return curr->GetKey();
}

// удаление списка
void DList::ClearList()
{
	if (size == 0) return; // если список пустой, выходим, отчищать нечего

	for (DNode *p = front, *p_next; p != NULL; p = p_next)
	{
		p_next = p->NextRight(); // получаем адрес след. правого элемента
		FreeNode(p); // удаляем текущий элемент
	}
	front = rear = NULL;
	curr = NULL;
	curr_pos = -1;
	size = 0;
}

// функция ищет первый элемент по заданному ключу начиная с текущей позиции
CPolygon* DList::Find(int key, bool start)
{
	CPolygon* p = NULL;

	if (start) Reset(0);
	for (; !EndOfList(); Next())
	{
		if (key == Key())
		{
			p = Data();
			Next();
			break;
		}
	}
	return p;
}

// сохранение списка в файл
void DList::Save(std::ofstream &b_out) const
{
	CPolygon *pol;
	for (DNode *p = front; p != NULL; p = p->NextRight())
	{
		//pol = p->data;
		pol = p->GetData();
		pol->Save(b_out);
	}
}

// загрузка списка из файла
void DList::Load(std::ifstream &b_in)
{
	ClearList(); // отчистка списка перед загрузкой новой коллекции

	while (!b_in.eof())
	{
		CPolygon *pol = new CPolygon;
		if (pol->Load(b_in)) // если достигнут конец файла
		{
			delete pol; // удаляем заготовку для многоугольника
			break;
		}
		InsertAfter(*pol);
	}
}

// сохранение списка в файл, перегрузка <<
std::ostream& operator<<(std::ofstream& b_out, const DList& l)
{
	l.Save(b_out);
	return b_out;
}

// загрузка списка из файла, перегрузка >>
std::istream& operator>>(std::ifstream& b_in, DList& l)
{
	l.Load(b_in);
	return b_in;
}