#pragma once

#include "dnode.h"
#include <iostream>
#include <fstream>

// ����� �������������� ������
template <class T>
class DList
{
	// ��������� �� ������ ������� ������ (������) �� ������� ������ ��-��
	DNode<T> *front = NULL; 
	// ��������� �� ��������� ������� ������ (�����) �� ������� ������� ��-�� 
	DNode<T> *rear = NULL;
	// ��������� �� ������� ������� � ������
	DNode<T> *curr = NULL; 

	// ������� ������� � ������
	int curr_pos = -1; 
	// ���-�� ����� � ������
	int size = 0; 

	// �������� ������ ������
	// ������� �������
	DNode<T> *CreateNode(const T& item, int key);
	// ������������ ��������
	void FreeNode(DNode<T> *p); 
	// ����������� ������ � ������� ������
	void CopyList(const DList<T>& dl); 

public:
	DList();
	// ����������� ����������� ������ �� �������
	DList(const DList<T>& dl);
	~DList();
	
	// ������ ��������� ����� ������
	// �������� ��������� �� ������ �������
	DNode<T>* GetFront() const; 
	// �������� ��������� �� ��������� �������
	DNode<T>* GetRear() const; 
	// �������� ��������� �� ������� �������
	DNode<T>* GetCurrent() const; 
	// �������� ������ ������� ������� � ������
	int GetCurrentPosition() const; 

	// ������ �������� ������� ������
	// ��������� ����������� ������
	int GetSize() const; 
	// ��������� ������� ������ � ��� ������� 
	bool IsEmpty() const; 
	
	// ������ ������ ������
	// ��������� ������� �������
	void Reset(int pos = 0); 
	// ��������� ������� ������� �� ������	
	void SetFront(); 
	// ��������� ������� ������� �� �����
	void SetRear(); 
	// ����������� ������� ������� �� ���������� �������
	void Previous(); 
	// ����������� ������� ������� �� ��������� �������
	void Next(); 
	
	bool EndOfList(void) const;

	// ������ ������� (������� ������� ��������� �� ����������� �������)
	// ������� �������� ����� ������� �������
	void InsertAfter(T& data, int key); 
	// ������� �������� � ����� ������
	void InsertRear(T& data, int key); 
	// ������� �������� � ������� ������� (����� ���)
	void InsertBefore(T& data, int key); 
	// ������� �������� � ������ ������
	void InsertFront(T& data, int key); 

	// ������ ��������
	// �������� �������� ������� �������
	void DeleteAt(); 
	// �������� �������� ��������� �������
	void DeleteRear(); 
	// �������� �������� ������ �������
	void DeleteFront(); 
	// �������� ������
	void ClearList(); 

	// ������ ��������� ������
	// ��������� ��������� �� ������ ��������
	T& Data(); 
	// ��������� �����
	int Key(); 
	// ��������� �������� � ������ ������
	T& Find(int k); 

	// ������ ����������/�������� ������
	// ���������� ������ � ����
	void Save(std::ofstream &b_out); 
	 // �������� ������ �� �����
	void Load(std::ifstream &b_in);

	// ���������� ����������
	// ����������� ������ � ������� ������ ����� �������� =
	DList<T>& operator=(const DList<T>& dl); 
	
	friend std::ostream& operator<<(std::ofstream& b_out, const DList<T>& l);
	
	friend std::istream& operator>>(std::ifstream& b_in, DList<T>& l);
};

// ������� ������� � ���������� ������ � ������� ���������
template <class T>
DNode<T> *DList<T>::CreateNode(const T& data, int key)
{
	DNode<T> *p = new DNode<T>(data, key);

	if (p == NULL)
	{
		std::cerr << "CreateNode: �� ���������� ������" << std::endl;
		exit(1);
	}
	return p;
}

//  ������� �������
template <class T>
void DList<T>::FreeNode(DNode<T> *p)
{
	delete p;
}

// ����������� ������
template <class T>
void DList<T>::CopyList(const DList<T>& L)
{
	if (size != 0) ClearList(); // ���� ������ �� ������, �������� ����� ������������ � ����

	// �� ��������� ��������� ������ ������� � ������ ������
	for (DNode<T> *p = L.GetFront(); p != NULL; p = p->NextRight())
		//InsertAfter(*p->data);
		InsertAfter(*p->GetData());
 
	curr = L.GetCurrent(); // ������ ������� ��������� �� ��� ������� � ��� � ���������� ������
	curr_pos = L.GetCurrentPosition(); // ������ ������� ������ �� ��� ������� � ��� � ���������� ������
}

template <class T>
DList<T>::DList()
{}

// ����������� ����������� ������ �� �������
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

// �������� ������������ (�����������)
template <class T>
DList<T>& DList<T>::operator=(const DList<T>& dl)
{
	// ��������� ����������� ��������� ������ ����
	if (this == &dl) return *this; 

	CopyList(dl); // �������� ������
	
	return *this;
}

// �������� ��������� �� ������ �������
template <class T>
DNode<T>* DList<T>::GetFront() const
{
	return front;
}
	
// �������� ��������� �� ��������� �������
template <class T>
DNode<T>* DList<T>::GetRear() const
{
	return rear;
}

// �������� ��������� �� ������� �������	
template <class T>
DNode<T>* DList<T>::GetCurrent() const
{
	return curr;
}

// �������� ������ ������� ������� � ������
template <class T>
int DList<T>::GetCurrentPosition() const
{
	return curr_pos;
}

// ��������� ����������� ������
template <class T>
int DList<T>::GetSize() const
{
	return size;     
}

// ��������� ������� ������ � ��� ������� 
template <class T>
bool DList<T>::IsEmpty() const
{
	return size == 0; // front == NULL
}

// ��������� ������� �������
template <class T>
void DList<T>::Reset(int pos)
{
	if (size == 0) return; // ���� ������ ������ front == NULL, ������ �� ������

	// ���� ������� ������� �������� - �������
	if (pos < 0 || pos > size - 1)
	{
		std::cerr << "Reset: ��������� ������� �� ������� ������: " << pos << std::endl;
		return;
	}
	if (pos == curr_pos) return; // ���� ������� ������� �������	
	
	if (pos == 0) // ���� ������� ������ �������
	{
		curr = front;
	}
	else if (pos == size - 1) // ���� ������� ��������� �������
	{
		curr = rear;
	}
	else // ���� ������� ��� �� � �������� ������
	{
		// ���� ������������� ��������� ������� ����� ���� � ������� pos
		int d_front = pos, d_rear = size - 1 - pos;
		int d_curr = (curr_pos > pos) ? curr_pos - pos : pos - curr_pos;

		// ���������� �������� ����� ���� ��������, ��� ����������� � ������ �������
		// �.�. ���-�� ����������� �� �����, ����������� ��� ���������� ������ �������
		int min = d_front;
		if (d_rear < min) min = d_rear;
		if (d_curr < min) min = d_curr;

		// �������� ������������ �������������� ��������� �� min ���-�� ����� 
		DNode<T> *p;
		DNode<T> *(DNode<T>::*Next)() const; // ��������� �� ����������� ����� - ���
		if (min == d_front) // ���� ����� ���� ��������� ������ ������
		{
			p = front; // ��������� ��������� ���������
			Next = &DNode<T>::NextRight; // ����������� ������ (������)
		}
		else if (min == d_rear) // ���� ����� ���� ��������� ����� ������
		{
			p = rear; // ��������� ��������� ���������
			Next = &DNode<T>::NextLeft; // ����������� ����� (�����)
		}
		else if (min == d_curr) // ���� ����� ���� ��������� �����. �������
		{
			p = curr; // ��������� ��������� ���������
			if (curr_pos > pos) Next = &DNode<T>::NextLeft; // ����������� ����� (�����)
			else Next = &DNode<T>::NextRight; // ����������� ������ (������)
		}
		// ������ ����������� � ������ ����������� � ���-�� min ����� � ������ �������
		for (int i = 0; i < min; i++) p = (p->*Next)();
		curr = p;
	}
	curr_pos = pos;
}

// ��������� ������� ������� �� ������	
template <class T>
void DList<T>::SetFront()
{
	Reset(0);
}

// ��������� ������� ������� �� �����
template <class T>
void DList<T>::SetRear()
{
	Reset(size - 1);
}

// ����������� ������� ������� �� ���������� �������
template <class T>
void DList<T>::Previous()
{
   if (curr != NULL) // ���� �� �������� ������� ������
   {
      curr = curr->NextLeft();
      curr_pos--;
   }
}

// ����������� ������� ������� �� ��������� �������
template <class T>
void DList<T>::Next()
{
   if (curr != NULL) // ���� �� �������� ������� ������
   {
      curr = curr->NextRight();
      curr_pos++;
   }
}

// ������� ������� ������
template <class T>
bool DList<T>::EndOfList(void) const
{
	return curr == NULL;
}

// ������� �������� ����� ������� �������
template <class T>
void DList<T>::InsertAfter(T& data, int key)
{
	DNode<T> *p = CreateNode(data, key); // ������� �������

	if (size == 0) // ���� ������ ������ front == NULL
	{
		// ������ � ��������� ��������� � ���. ��������� ��������� �� ������ ����������� �������
		front = curr = rear = p;
	}
	else // ���� ������ ��� �� ������
	{	
		curr->InsertRight(p); // ������� �������� ����� (������) �� ������� �������
		// ���� ������� ������� ����������� �� ��������� �������	
		if (curr == rear) rear = p; // ������ ��������� ��������� ����� ������
		curr = p; // �����. ������� ���������� ���� �����
	}
	curr_pos++; // ������� ���������� �� ����� ������ �������� (�.�. +1)
	size++; // ����������� �����������
}

// ������� �������� � ����� ������
template <class T>
void DList<T>::InsertRear(T& data, int key)
{
	curr_pos = size-1; // ������������� �����. ������� � �����
	curr = rear; // ������������� �����. ��������� � �����
	InsertAfter(data, key);
}

// ������� �������� ����� ������� ��������
template <class T>
void DList<T>::InsertBefore(T& data, int key)
{
	DNode<T> *p = CreateNode(data, key); // ������� �������

	if (size == 0) // ���� ������ ������ front == NULL
	{
		// ������ � ��������� ��������� � ���. ��������� ��������� �� ������ ����������� �������
		front = curr = rear = p;
		curr_pos = 0;
	}
	else // ���� ������ ��� �� ������
	{
		curr->InsertLeft(p); // ������� �������� ����� (�����) �� ������� �������
		// ���� ������� ������� ����������� �� ������ �������	
		if (curr == front) front = p; // ������ ��������� ��������� ������ ������
		curr = p; // �����. ������� ���������� ���� �����
		// ������ curr_pos �������� �������, �.�. ������ ��������� �� ����� �������
	}
	size++; // ����������� �����������
}

// ������� �������� � ������ ������
template <class T>
void DList<T>::InsertFront(T& data, int key)
{
	curr_pos = 0; // ������������� �����. ������� � ������
	curr = front; // ������������� �����. ��������� � ������
	InsertBefore(data, key);
}

// �������� �������� ������� �������
template <class T>
void DList<T>::DeleteAt()
{
	// ���� ���������� ������� ������, ������ �� ������
	if (curr == NULL) return;
	
	DNode<T> *p_next; // ������� ������� ������ �� ����� ����������
	if (curr == front) // ���� ������� ������� ������ ������� ������
	{
		p_next = curr->NextRight(); // ��������� ����� ���������� ��������
		front = p_next; // ������ �� ����� ������� �����
		// ������ ������� ������� curr_pos �� ���������
	}
	else if (curr == rear) // ���� ������� ������� ��������� ������� ������ 
	{
		p_next = curr->NextLeft(); // ��������� ����� ����������� ��������
		rear = p_next; // ������ �� ����� ��������� �����
		curr_pos--; // ������ ������� ������� ��������� �����
	}
	else // ���� ������� ������� ��������� � �������� ������
	{
		p_next = curr->NextRight(); // ��������� ����� ���������� ��������
		// ������ ������� ������� curr_pos �� ���������
	}
	// �������� ������� ������� �� ������, �� ��������� ��� �����
	DNode<T> *p = curr->Delete();
	FreeNode(p); // ����������� �� ����� ������ �������
	curr = p_next;
	size--;
}

// �������� �������� ������ �������
template <class T>
void DList<T>::DeleteFront()
{
	curr_pos = 0; // ������������� �����. ������� � ������
	curr = front; // ������������� �����. ��������� � ������
	DeleteAt();
}

// �������� �������� ��������� �������
template <class T>
void DList<T>::DeleteRear()
{
	curr_pos = size - 1; // ������������� �����. ������� � �����
	curr = rear; // ������������� �����. ��������� � �����
	DeleteAt();
}

// �������� ������
template <class T>
void DList<T>::ClearList()
{
	if (size == 0) return; // ���� ������ ������, �������, �������� ������

	for (DNode<T> *p = front, *p_next; p != NULL; p = p_next)
	{
		p_next = p->NextRight(); // �������� ����� ����. ������� ��������
		FreeNode(p); // ������� ������� �������
	}
	front = rear = NULL;
	curr = NULL;
	curr_pos = -1;
	size = 0;
}

// ��������� ����� ������ �������� ��������
template <class T>
T& DList<T>::Data()
{
	// ���� ���������� ������� ������, ������
	if (curr == NULL)
	{
		std::cerr << "Data: �������� ������ �� ��������� ������" << std::endl;
		exit(1);
	}
	//return curr->data;
	return curr->GetData();
}

// ��������� ������ ��� ����������� �����
template <class T>
int DList<T>::Key()
{
	// ���� ���������� ������� ������, ������
	if (curr == NULL)
	{
		std::cerr << "Key: �������� ������ �� ��������� ������" << std::endl;
		exit(1);
	}
	return curr->GetKey();
}

// ������� ���� ������ ������� �� ��������� ����� ������� � ������� �������
template <class T>
T& DList<T>::Find(int key)
{
	T* p = NULL;

	// �������� ������ � ������� �������
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

// ���������� ������ � ����
template <class T>
void DList<T>::Save(std::ofstream &b_out)
{
	T *pol;
	int n = size;
	b_out.write((char*)&n, sizeof(n)); // ����� ���-�� ���������

	for (DNode<T> *p = front; p != NULL; p = p->NextRight())
	{
		pol = &p->GetData();
		pol->Save(b_out);
	}
}

// �������� ������ �� �����
template <class T>
void DList<T>::Load(std::ifstream &b_in)
{
	ClearList(); // �������� ������ ����� ��������� ����� ���������

	int n;
	b_in.read((char*)&n, sizeof(n)); // ������ ���-�� ������

	for (int i = 0; i < n; i++)
	{
		T *pol = new T;
		pol->Load(b_in);
		InsertAfter(*pol, pol->GetCountVertexes());
	}
}

// ���������� ������ � ����, ���������� <<
template <class T>
std::ostream& operator<<(std::ofstream& b_out, const DList<T>& l)
{
	l.Save(b_out);
	return b_out;
}

// �������� ������ �� �����, ���������� >>
template <class T>
std::istream& operator>>(std::ifstream& b_in, DList<T>& l)
{
	l.Load(b_in);
	return b_in;
}