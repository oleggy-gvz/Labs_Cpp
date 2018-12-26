#pragma once

#include "dnode.h"
#include <iostream>

class DList
{
	DNode *front = NULL; // указатель на первый элемент списка (начало) не имеющий левого эл-та
	DNode *rear = NULL; // указатель на последний элемент списка (конец) не имеющий правого эл-та 
	DNode *curr = NULL; // указатель на текущий элемент в списке

	int curr_pos = -1; // текущая позиция в списке
	int size = 0; // кол-во узлов в списке

	// закрытые методы списка
	DNode *CreateNode(CPolygon& item); 	// создаем элемент
	void FreeNode(DNode *p); // освобождение элемента
	void CopyList(const DList& dl); // копирование списка в текущий список

public:
	DList();
	DList(const DList& dl);
	~DList();
	
	// методы получения узлов списка
	DNode* GetFront() const; // получить указатель на первый элемент
	DNode* GetRear() const; // получить указатель на последний элемент
	DNode* GetCurrent() const; // получить указатель на текущий элемент
	int GetCurrentPosition() const; // получить индекс текущей позиции в списке

	// методы проверки статуса списка
	int GetSize() const; // получение размерности списка
	bool IsEmpty() const; // получения статуса списка о его пустоте 
	
	// методы обхода списка
	void Reset(int pos = 0); // установка текущей позиции
	void SetFront(); // установка текущей позиции на начало	
	void SetRear(); // установка текущей позиции на конец
	void Previous(); // передвигаем текущую позицию на предыдущий элемент
	void Next(); // передвигаем текущую позицию на следующий элемент
	bool EndOfList(void) const;

	// методы вставки (текущая позиция указывает на вставленный элемент)
	void InsertAfter(CPolygon& data); // вставка элемента после текущей позиции
	void InsertRear(CPolygon& data); // вставка элемента в конец списка
	void InsertBefore(CPolygon& data); // вставка элемента в текущую позицию (перед ней)
	void InsertFront(CPolygon& data); // вставка элемента в начало списка

	// методы удаления
	void DeleteAt(); // удаление элемента текущей позиции
	void DeleteRear(); // удаление элемента последней позиции
	void DeleteFront(); // удаление элемента первой позиции
	void ClearList(); // отчистка списка

	// методы получения данных
	CPolygon* Data(); // получение указателя на данные элемента
	int Key(); // получение ключа
	CPolygon* Find(int k, bool start = true); // получение элемента с занным ключем

	// методы сохранения/загрузки списка
	void Save(std::ofstream &b_out) const; // сохранение списка в файл
	void Load(std::ifstream &b_in); // загрузка списка из файла

	// перегрузка операторов
	DList& operator=(const DList& dl); // копирование списка в текущий список через оператор =
	friend std::ostream& operator<<(std::ofstream& b_out, const DList& l);
	friend std::istream& operator>>(std::ifstream& b_in, DList& l);
};