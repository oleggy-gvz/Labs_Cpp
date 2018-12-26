#pragma once

#include "polygon.h"

// двусвязанный список

#define NULL 0

class DNode
{
	DNode *left = NULL; // указатель на левый элемент
	DNode *right = NULL; // указатель на правый элемент
	
	CPolygon *data = NULL; // указатель на класс
	int key = 0;

public:

	DNode(CPolygon& p); 
	void InsertRight(DNode *p); // вставить элемент справа
	void InsertLeft(DNode *p); // вставить элемент слева
	DNode *Delete(); // удаление текущего элемента

	DNode *NextRight() const; // адрес след. элемента справа
	DNode *NextLeft() const; // адрес след. элемента слева

	CPolygon *GetData();
	int GetKey() const;
};