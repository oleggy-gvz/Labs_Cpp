	#include "dlist.h"
#include <iostream>
#include <fstream>
#include "polygon.h"

// ������� ������� � ���������� ������ � ������� ���������
DNode *DList::CreateNode(CPolygon& data)
{
	DNode *p = new DNode(data);

	if (p == NULL)
	{
		std::cerr << "CreateNode: �� ���������� ������" << std::endl;
		exit(1);
	}
	return p;
}

//  ������� �������
void DList::FreeNode(DNode *p)
{
	delete p;
}

// ����������� ������
void DList::CopyList(const DList& L)
{
	if (size != 0) ClearList(); // ���� ������ �� ������, �������� ����� ������������ � ����

	// �� ��������� ��������� ������ ������� � ������ ������
	for (DNode *p = L.GetFront(); p != NULL; p = p->NextRight())
		//InsertAfter(*p->data);
		InsertAfter(*p->GetData());
 
	curr = L.GetCurrent(); // ������ ������� ��������� �� ��� ������� � ��� � ���������� ������
	curr_pos = L.GetCurrentPosition(); // ������ ������� ������ �� ��� ������� � ��� � ���������� ������
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

// �������� ������������ (�����������)
DList& DList::operator=(const DList& dl)
{
	// ��������� ����������� ��������� ������ ����
	if (this == &dl) return *this; 

	CopyList(dl); // �������� ������
	
	return *this;
}

// �������� ��������� �� ������ �������
DNode* DList::GetFront() const
{
	return front;
}
	
// �������� ��������� �� ��������� �������
DNode* DList::GetRear() const
{
	return rear;
}

// �������� ��������� �� ������� �������	
DNode* DList::GetCurrent() const
{
	return curr;
}

// �������� ������ ������� ������� � ������
int DList::GetCurrentPosition() const
{
	return curr_pos;
}

// ��������� ����������� ������
int DList::GetSize() const
{
	return size;     
}

// ��������� ������� ������ � ��� ������� 
bool DList::IsEmpty() const
{
	return size == 0; // front == NULL
}

// ��������� ������� �������
void DList::Reset(int pos)
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

		// ���������� �������� ����� ���� ���������vs[ ��� ����������� � ������ �������
		// �.�. ���-�� ����������� �� ����� ����������� ��� ���������� ������ �������
		int min = d_front;
		if (d_rear < min) min = d_rear;
		if (d_curr < min) min = d_curr;

		// �������� ������������ �������������� ��������� �� min ���-�� ����� 
		DNode *p;
		DNode *(DNode::*Next)() const; // ��������� �� ����������� ����� - ����
		if (min == d_front) // ���� ����� ���� ��������� ������ ������
		{
			p = front; // ��������� ��������� ���������
			Next = &DNode::NextRight; // ����������� ������ (������)
		}
		else if (min == d_rear) // ���� ����� ���� ��������� ����� ������
		{
			p = rear; // ��������� ��������� ���������
			Next = &DNode::NextLeft; // ����������� ����� (�����)
		}
		else if (min == d_curr) // ���� ����� ���� ��������� �����. �������
		{
			p = curr; // ��������� ��������� ���������
			if (curr_pos > pos) Next = &DNode::NextLeft; // ����������� ����� (�����)
			else Next = &DNode::NextRight; // ����������� ������ (������)
		}
		// ������ ����������� � ������ ����������� � ���-�� min � ������ �������
		for (int i = 0; i < min; i++) p = (p->*Next)();
		curr = p;
	}
	curr_pos = pos;
}

// ��������� ������� ������� �� ������	
void DList::SetFront()
{
	Reset(0);
}

// ��������� ������� ������� �� �����
void DList::SetRear()
{
	Reset(size - 1);
}

// ����������� ������� ������� �� ���������� �������
void DList::Previous()
{
   if (curr != NULL) // ���� �� �������� ������� ������
   {
      curr = curr->NextLeft();
      curr_pos--;
   }
}

// ����������� ������� ������� �� ��������� �������
void DList::Next()
{
   if (curr != NULL) // ���� �� �������� ������� ������
   {
      curr = curr->NextRight();
      curr_pos++;
   }
}

// ������� ������� ������
bool DList::EndOfList(void) const
{
	return curr == NULL;
}

// ������� �������� ����� ������� �������
void DList::InsertAfter(CPolygon& data)
{
	DNode *p = CreateNode(data); // ������� �������

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
void DList::InsertRear(CPolygon& data)
{
	curr_pos = size-1; // ������������� �����. ������� � �����
	curr = rear; // ������������� �����. ��������� � �����
	InsertAfter(data);
}

// ������� �������� ����� ������� ��������
void DList::InsertBefore(CPolygon& data)
{
	DNode *p = CreateNode(data); // ������� �������

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
void DList::InsertFront(CPolygon& data)
{
	curr_pos = 0; // ������������� �����. ������� � ������
	curr = front; // ������������� �����. ��������� � ������
	InsertBefore(data);
}

// �������� �������� ������� �������
void DList::DeleteAt()
{
	// ���� ���������� ������� ������, ������ �� ������
	if (curr == NULL) return;
	
	DNode *p_next; // ������� ������� ������ �� ����� ����������
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
	DNode *p = curr->Delete();
	FreeNode(p); // ����������� �� ����� ������ �������
	curr = p_next;
	size--;
}

// �������� �������� ������ �������
void DList::DeleteFront()
{
	curr_pos = 0; // ������������� �����. ������� � ������
	curr = front; // ������������� �����. ��������� � ������
	DeleteAt();
}

// �������� �������� ��������� �������
void DList::DeleteRear()
{
	curr_pos = size - 1; // ������������� �����. ������� � �����
	curr = rear; // ������������� �����. ��������� � �����
	DeleteAt();
}

// ��������� ����� ������ �������� ��������
CPolygon* DList::Data()
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
int DList::Key()
{
	// ���� ���������� ������� ������, ������
	if (curr == NULL)
	{
		std::cerr << "Key: �������� ������ �� ��������� ������" << std::endl;
		exit(1);
	}
	return curr->GetKey();
}

// �������� ������
void DList::ClearList()
{
	if (size == 0) return; // ���� ������ ������, �������, �������� ������

	for (DNode *p = front, *p_next; p != NULL; p = p_next)
	{
		p_next = p->NextRight(); // �������� ����� ����. ������� ��������
		FreeNode(p); // ������� ������� �������
	}
	front = rear = NULL;
	curr = NULL;
	curr_pos = -1;
	size = 0;
}

// ������� ���� ������ ������� �� ��������� ����� ������� � ������� �������
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

// ���������� ������ � ����
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

// �������� ������ �� �����
void DList::Load(std::ifstream &b_in)
{
	ClearList(); // �������� ������ ����� ��������� ����� ���������

	while (!b_in.eof())
	{
		CPolygon *pol = new CPolygon;
		if (pol->Load(b_in)) // ���� ��������� ����� �����
		{
			delete pol; // ������� ��������� ��� ��������������
			break;
		}
		InsertAfter(*pol);
	}
}

// ���������� ������ � ����, ���������� <<
std::ostream& operator<<(std::ofstream& b_out, const DList& l)
{
	l.Save(b_out);
	return b_out;
}

// �������� ������ �� �����, ���������� >>
std::istream& operator>>(std::ifstream& b_in, DList& l)
{
	l.Load(b_in);
	return b_in;
}