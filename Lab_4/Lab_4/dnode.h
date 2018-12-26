#pragma once

#define NULL 0

// классэлемента  двусвязанного списока
template <class T>
class DNode
{
	DNode<T> *left = NULL; // указатель на левый элемент
	DNode<T> *right = NULL; // указатель на правый элемент
	
	T data; //  блок данных
	int key = 0; // ключ

public:

	DNode(const T& p, int k);
	void InsertRight(DNode<T> *p); // вставить элемент справа
	void InsertLeft(DNode<T> *p); // вставить элемент слева
	DNode<T> *Delete(); // удаление текущего элемента

	DNode<T> *NextRight() const; // адрес след. элемента справа
	DNode<T> *NextLeft() const; // адрес след. элемента слева

	T &GetData(); // получение ссылки на блок данных элемента
	int GetKey() const; // получение ключа элемента
};

// конструктор с инициализацией данных
template <class T>
DNode<T>::DNode(const T &p, int k) : data(p), key(k)
{}

// добавление эл-та в справа от текущего элемента
template <class T>
void DNode<T>::InsertRight(DNode<T> *p)
{
	// установка указателей у вставляемого нового элемента
	p->right = right; // правый указ. ссылается на старый правый элемент
	p->left = this; // левый указ. ссылается на текущий элемент

	// обновл. указатели у старых эл-тов для включения нового элемента
	// левый указ. у старого правого элемента ссылается на вставляемый новый элемент
	if (right != NULL) right->left = p;
	right = p; // правый указ. у текущего элемента ссылается на вставляемый новый элемент
}

// добавление эл-та слева от текущего элемента
template <class T>
void DNode<T>::InsertLeft(DNode<T> *p)
{
	// установка указателей у вставляемого нового элемента
	p->left = left; // левый указ. ссылается на старый левый элемент
	p->right = this; // правый указ. ссылается на текущий элемент

	// обновл. указатели у старых эл-тов для включения нового элемента
	if (left != NULL) left->right = p; // правый указ. у старого левого элемента ссылается на вставляемый новый элемент
	left = p; // левый указ. у текущего элемента ссылается на вставляемый новый элемент
}

// удаление текущего элемента
template <class T>
DNode<T> *DNode<T>::Delete()
{
	// у левого эл-та его правый указ. ссылается на правый указ. текущего элемента
	if (left != NULL) left->right = right;
	// у правого эл-та его левый указ. ссылается на левый указ. текущего элемента
	if (right != NULL) right->left = left;

	return this;
}

// возврат указателя на элемент справа от текущего элемента
template <class T>
DNode<T> *DNode<T>::NextRight() const
{
	return right;
}

// возврат указателя на элемент слева от текущего элемента
template <class T>
DNode<T> *DNode<T>::NextLeft() const
{
	return left;
}

// получение ссылки на блок данных элемента
template <class T>
T &DNode<T>::GetData()
{
	return data;
}

// получение ключа элемента
template <class T>
int DNode<T>::GetKey() const
{
	return key;
}