#pragma once

#include "dnode.h"
#include <iostream>
#include <fstream>

// класс двухсвязанного списка
template <class T>
class DList
{
	// указатель на первый элемент списка (начало) не имеющий левого эл-та
	DNode<T> *front = NULL; 
	// указатель на последний элемент списка (конец) не имеющий правого эл-та 
	DNode<T> *rear = NULL;
	// указатель на текущий элемент в списке
	DNode<T> *curr = NULL; 

	// текущая позиция в списке
	int curr_pos = -1; 
	// кол-во узлов в списке
	int size = 0; 

	// закрытые методы списка
	// создаем элемент
	DNode<T> *CreateNode(const T& item, int key);
	// освобождение элемента
	void FreeNode(DNode<T> *p); 
	// копирование списка в текущий список
	void CopyList(const DList<T>& dl); 

public:
	DList();
	// конструктор копирования списка из другого
	DList(const DList<T>& dl);
	~DList();
	
	// методы получения узлов списка
	// получить указатель на первый элемент
	DNode<T>* GetFront() const; 
	// получить указатель на последний элемент
	DNode<T>* GetRear() const; 
	// получить указатель на текущий элемент
	DNode<T>* GetCurrent() const; 
	// получить индекс текущей позиции в списке
	int GetCurrentPosition() const; 

	// методы проверки статуса списка
	// получение размерности списка
	int GetSize() const; 
	// получения статуса списка о его пустоте 
	bool IsEmpty() const; 
	
	// методы обхода списка
	// установка текущей позиции
	void Reset(int pos = 0); 
	// установка текущей позиции на начало	
	void SetFront(); 
	// установка текущей позиции на конец
	void SetRear(); 
	// передвигаем текущую позицию на предыдущий элемент
	void Previous(); 
	// передвигаем текущую позицию на следующий элемент
	void Next(); 
	
	bool EndOfList(void) const;

	// методы вставки (текущая позиция указывает на вставленный элемент)
	// вставка элемента после текущей позиции
	void InsertAfter(T& data, int key); 
	// вставка элемента в конец списка
	void InsertRear(T& data, int key); 
	// вставка элемента в текущую позицию (перед ней)
	void InsertBefore(T& data, int key); 
	// вставка элемента в начало списка
	void InsertFront(T& data, int key); 

	// методы удаления
	// удаление элемента текущей позиции
	void DeleteAt(); 
	// удаление элемента последней позиции
	void DeleteRear(); 
	// удаление элемента первой позиции
	void DeleteFront(); 
	// отчистка списка
	void ClearList(); 

	// методы получения данных
	// получение указателя на данные элемента
	T& Data(); 
	// получение ключа
	int Key(); 
	// получение элемента с занным ключем
	T& Find(int k); 

	// методы сохранения/загрузки списка
	// сохранение списка в файл
	void Save(std::ofstream &b_out); 
	 // загрузка списка из файла
	void Load(std::ifstream &b_in);

	// перегрузка операторов
	// копирование списка в текущий список через оператор =
	DList<T>& operator=(const DList<T>& dl); 
	
	friend std::ostream& operator<<(std::ofstream& b_out, const DList<T>& l);
	
	friend std::istream& operator>>(std::ifstream& b_in, DList<T>& l);
};

// создаем элемент с установкой левого и правого указателя
template <class T>
DNode<T> *DList<T>::CreateNode(const T& data, int key)
{
	DNode<T> *p = new DNode<T>(data, key);

	if (p == NULL)
	{
		std::cerr << "CreateNode: не достаточно памяти" << std::endl;
		exit(1);
	}
	return p;
}

//  удаляем элемент
template <class T>
void DList<T>::FreeNode(DNode<T> *p)
{
	delete p;
}

// копирование списка
template <class T>
void DList<T>::CopyList(const DList<T>& L)
{
	if (size != 0) ClearList(); // если список не пустой, отчищаем перед копированием в него

	// по элементно вставляем каждый элемент с начала списка
	for (DNode<T> *p = L.GetFront(); p != NULL; p = p->NextRight())
		//InsertAfter(*p->data);
		InsertAfter(*p->GetData());
 
	curr = L.GetCurrent(); // делаем текущий указатель на тот который в был в копируемом списке
	curr_pos = L.GetCurrentPosition(); // делаем текущий индекс на тот который в был в копируемом списке
}

template <class T>
DList<T>::DList()
{}

// конструктор копирования списка из другого
template <class T>
DList<T>::DList(const DList<T>& L)
{
	CopyList(L);
}

template <class T>
DList<T>::~DList()
{
	ClearList();
}

// оператор присваивания (копирования)
template <class T>
DList<T>& DList<T>::operator=(const DList<T>& dl)
{
	// исключаем возможность присвоить самому себе
	if (this == &dl) return *this; 

	CopyList(dl); // копируем список
	
	return *this;
}

// получить указатель на первый элемент
template <class T>
DNode<T>* DList<T>::GetFront() const
{
	return front;
}
	
// получить указатель на последний элемент
template <class T>
DNode<T>* DList<T>::GetRear() const
{
	return rear;
}

// получить указатель на текущий элемент	
template <class T>
DNode<T>* DList<T>::GetCurrent() const
{
	return curr;
}

// получить индекс текущей позиции в списке
template <class T>
int DList<T>::GetCurrentPosition() const
{
	return curr_pos;
}

// получение размерности списка
template <class T>
int DList<T>::GetSize() const
{
	return size;     
}

// получения статуса списка о его пустоте 
template <class T>
bool DList<T>::IsEmpty() const
{
	return size == 0; // front == NULL
}

// установка текущей позиции
template <class T>
void DList<T>::Reset(int pos)
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

		// нахождение минимума среди трех значений, для перемещения в нужную позицию
		// т.е. кол-во перемещений по узлам, необходимых для достижения нужной позиции
		int min = d_front;
		if (d_rear < min) min = d_rear;
		if (d_curr < min) min = d_curr;

		// сдвигаем относительно фиксированного указателя на min кол-во узлов 
		DNode<T> *p;
		DNode<T> *(DNode<T>::*Next)() const; // указатель на константный метод - шаг
		if (min == d_front) // если ближе всех указатель начала списка
		{
			p = front; // установим начальный указатель
			Next = &DNode<T>::NextRight; // направление вперед (вправо)
		}
		else if (min == d_rear) // если ближе всех указатель конца списка
		{
			p = rear; // установим начальный указатель
			Next = &DNode<T>::NextLeft; // направление назад (влево)
		}
		else if (min == d_curr) // если ближе всех указатель текущ. позиции
		{
			p = curr; // установим начальный указатель
			if (curr_pos > pos) Next = &DNode<T>::NextLeft; // направление назад (влево)
			else Next = &DNode<T>::NextRight; // направление вперед (вправо)
		}
		// делаем перемещения в нужном направлении в кол-ве min шагов к нужной позиции
		for (int i = 0; i < min; i++) p = (p->*Next)();
		curr = p;
	}
	curr_pos = pos;
}

// установка текущей позиции на начало	
template <class T>
void DList<T>::SetFront()
{
	Reset(0);
}

// установка текущей позиции на конец
template <class T>
void DList<T>::SetRear()
{
	Reset(size - 1);
}

// передвигаем текущую позицию на предыдущий элемент
template <class T>
void DList<T>::Previous()
{
   if (curr != NULL) // если не достигли границы списка
   {
      curr = curr->NextLeft();
      curr_pos--;
   }
}

// передвигаем текущую позицию на следующий элемент
template <class T>
void DList<T>::Next()
{
   if (curr != NULL) // если не достигли границы списка
   {
      curr = curr->NextRight();
      curr_pos++;
   }
}

// признак границы списка
template <class T>
bool DList<T>::EndOfList(void) const
{
	return curr == NULL;
}

// вставка элемента после текущей позиции
template <class T>
void DList<T>::InsertAfter(T& data, int key)
{
	DNode<T> *p = CreateNode(data, key); // создаем элемент

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
template <class T>
void DList<T>::InsertRear(T& data, int key)
{
	curr_pos = size-1; // устанавливаем текущ. позицию в конец
	curr = rear; // устанавливает текущ. указатель в конец
	InsertAfter(data, key);
}

// вставка элемента перед текущей позицией
template <class T>
void DList<T>::InsertBefore(T& data, int key)
{
	DNode<T> *p = CreateNode(data, key); // создаем элемент

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
template <class T>
void DList<T>::InsertFront(T& data, int key)
{
	curr_pos = 0; // устанавливаем текущ. позицию в начало
	curr = front; // устанавливает текущ. указатель в начало
	InsertBefore(data, key);
}

// удаление элемента текущей позиции
template <class T>
void DList<T>::DeleteAt()
{
	// если достугнута граница списка, ничего не делаем
	if (curr == NULL) return;
	
	DNode<T> *p_next; // элемент который станет на место удаленного
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
	DNode<T> *p = curr->Delete();
	FreeNode(p); // освобождаем по этому адресу элемент
	curr = p_next;
	size--;
}

// удаление элемента первой позиции
template <class T>
void DList<T>::DeleteFront()
{
	curr_pos = 0; // устанавливаем текущ. позицию в начало
	curr = front; // устанавливает текущ. указатель в начало
	DeleteAt();
}

// удаление элемента последней позиции
template <class T>
void DList<T>::DeleteRear()
{
	curr_pos = size - 1; // устанавливаем текущ. позицию в конец
	curr = rear; // устанавливает текущ. указатель в конец
	DeleteAt();
}

// удаление списка
template <class T>
void DList<T>::ClearList()
{
	if (size == 0) return; // если список пустой, выходим, отчищать нечего

	for (DNode<T> *p = front, *p_next; p != NULL; p = p_next)
	{
		p_next = p->NextRight(); // получаем адрес след. правого элемента
		FreeNode(p); // удаляем текущий элемент
	}
	front = rear = NULL;
	curr = NULL;
	curr_pos = -1;
	size = 0;
}

// получение блока данных текущего элемента
template <class T>
T& DList<T>::Data()
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
template <class T>
int DList<T>::Key()
{
	// если достугнута граница списка, ошибка
	if (curr == NULL)
	{
		std::cerr << "Key: неверная ссылка на получение данных" << std::endl;
		exit(1);
	}
	return curr->GetKey();
}

// функция ищет первый элемент по заданному ключу начиная с текущей позиции
template <class T>
T& DList<T>::Find(int key)
{
	T* p = NULL;

	// начинаем искать с текущей позиции
	for (; !EndOfList(); Next())
	{
		if (key == Key())
		{
			p = &Data();
			break;
		}
	}
	return *p;
}

// сохранение списка в файл
template <class T>
void DList<T>::Save(std::ofstream &b_out)
{
	T *pol;
	int n = size;
	b_out.write((char*)&n, sizeof(n)); // пишем кол-во элементов

	for (DNode<T> *p = front; p != NULL; p = p->NextRight())
	{
		pol = &p->GetData();
		pol->Save(b_out);
	}
}

// загрузка списка из файла
template <class T>
void DList<T>::Load(std::ifstream &b_in)
{
	ClearList(); // отчистка списка перед загрузкой новой коллекции

	int n;
	b_in.read((char*)&n, sizeof(n)); // читаем кол-во вершин

	for (int i = 0; i < n; i++)
	{
		T *pol = new T;
		pol->Load(b_in);
		InsertAfter(*pol, pol->GetCountVertexes());
	}
}

// сохранение списка в файл, перегрузка <<
template <class T>
std::ostream& operator<<(std::ofstream& b_out, const DList<T>& l)
{
	l.Save(b_out);
	return b_out;
}

// загрузка списка из файла, перегрузка >>
template <class T>
std::istream& operator>>(std::ifstream& b_in, DList<T>& l)
{
	l.Load(b_in);
	return b_in;
}