#pragma once

#define NULL 0

// �������������  ������������� �������
template <class T>
class DNode
{
	DNode<T> *left = NULL; // ��������� �� ����� �������
	DNode<T> *right = NULL; // ��������� �� ������ �������
	
	T data; //  ���� ������
	int key = 0; // ����

public:

	DNode(const T& p, int k);
	void InsertRight(DNode<T> *p); // �������� ������� ������
	void InsertLeft(DNode<T> *p); // �������� ������� �����
	DNode<T> *Delete(); // �������� �������� ��������

	DNode<T> *NextRight() const; // ����� ����. �������� ������
	DNode<T> *NextLeft() const; // ����� ����. �������� �����

	T &GetData(); // ��������� ������ �� ���� ������ ��������
	int GetKey() const; // ��������� ����� ��������
};

// ����������� � �������������� ������
template <class T>
DNode<T>::DNode(const T &p, int k) : data(p), key(k)
{}

// ���������� ��-�� � ������ �� �������� ��������
template <class T>
void DNode<T>::InsertRight(DNode<T> *p)
{
	// ��������� ���������� � ������������ ������ ��������
	p->right = right; // ������ ����. ��������� �� ������ ������ �������
	p->left = this; // ����� ����. ��������� �� ������� �������

	// ������. ��������� � ������ ��-��� ��� ��������� ������ ��������
	// ����� ����. � ������� ������� �������� ��������� �� ����������� ����� �������
	if (right != NULL) right->left = p;
	right = p; // ������ ����. � �������� �������� ��������� �� ����������� ����� �������
}

// ���������� ��-�� ����� �� �������� ��������
template <class T>
void DNode<T>::InsertLeft(DNode<T> *p)
{
	// ��������� ���������� � ������������ ������ ��������
	p->left = left; // ����� ����. ��������� �� ������ ����� �������
	p->right = this; // ������ ����. ��������� �� ������� �������

	// ������. ��������� � ������ ��-��� ��� ��������� ������ ��������
	if (left != NULL) left->right = p; // ������ ����. � ������� ������ �������� ��������� �� ����������� ����� �������
	left = p; // ����� ����. � �������� �������� ��������� �� ����������� ����� �������
}

// �������� �������� ��������
template <class T>
DNode<T> *DNode<T>::Delete()
{
	// � ������ ��-�� ��� ������ ����. ��������� �� ������ ����. �������� ��������
	if (left != NULL) left->right = right;
	// � ������� ��-�� ��� ����� ����. ��������� �� ����� ����. �������� ��������
	if (right != NULL) right->left = left;

	return this;
}

// ������� ��������� �� ������� ������ �� �������� ��������
template <class T>
DNode<T> *DNode<T>::NextRight() const
{
	return right;
}

// ������� ��������� �� ������� ����� �� �������� ��������
template <class T>
DNode<T> *DNode<T>::NextLeft() const
{
	return left;
}

// ��������� ������ �� ���� ������ ��������
template <class T>
T &DNode<T>::GetData()
{
	return data;
}

// ��������� ����� ��������
template <class T>
int DNode<T>::GetKey() const
{
	return key;
}