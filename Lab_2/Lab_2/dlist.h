#pragma once

#include "dnode.h"
#include <iostream>

class DList
{
	DNode *front = NULL; // ��������� �� ������ ������� ������ (������) �� ������� ������ ��-��
	DNode *rear = NULL; // ��������� �� ��������� ������� ������ (�����) �� ������� ������� ��-�� 
	DNode *curr = NULL; // ��������� �� ������� ������� � ������

	int curr_pos = -1; // ������� ������� � ������
	int size = 0; // ���-�� ����� � ������

	// �������� ������ ������
	DNode *CreateNode(CPolygon& item); 	// ������� �������
	void FreeNode(DNode *p); // ������������ ��������
	void CopyList(const DList& dl); // ����������� ������ � ������� ������

public:
	DList();
	DList(const DList& dl);
	~DList();
	
	// ������ ��������� ����� ������
	DNode* GetFront() const; // �������� ��������� �� ������ �������
	DNode* GetRear() const; // �������� ��������� �� ��������� �������
	DNode* GetCurrent() const; // �������� ��������� �� ������� �������
	int GetCurrentPosition() const; // �������� ������ ������� ������� � ������

	// ������ �������� ������� ������
	int GetSize() const; // ��������� ����������� ������
	bool IsEmpty() const; // ��������� ������� ������ � ��� ������� 
	
	// ������ ������ ������
	void Reset(int pos = 0); // ��������� ������� �������
	void SetFront(); // ��������� ������� ������� �� ������	
	void SetRear(); // ��������� ������� ������� �� �����
	void Previous(); // ����������� ������� ������� �� ���������� �������
	void Next(); // ����������� ������� ������� �� ��������� �������
	bool EndOfList(void) const;

	// ������ ������� (������� ������� ��������� �� ����������� �������)
	void InsertAfter(CPolygon& data); // ������� �������� ����� ������� �������
	void InsertRear(CPolygon& data); // ������� �������� � ����� ������
	void InsertBefore(CPolygon& data); // ������� �������� � ������� ������� (����� ���)
	void InsertFront(CPolygon& data); // ������� �������� � ������ ������

	// ������ ��������
	void DeleteAt(); // �������� �������� ������� �������
	void DeleteRear(); // �������� �������� ��������� �������
	void DeleteFront(); // �������� �������� ������ �������
	void ClearList(); // �������� ������

	// ������ ��������� ������
	CPolygon* Data(); // ��������� ��������� �� ������ ��������
	int Key(); // ��������� �����
	CPolygon* Find(int k, bool start = true); // ��������� �������� � ������ ������

	// ������ ����������/�������� ������
	void Save(std::ofstream &b_out) const; // ���������� ������ � ����
	void Load(std::ifstream &b_in); // �������� ������ �� �����

	// ���������� ����������
	DList& operator=(const DList& dl); // ����������� ������ � ������� ������ ����� �������� =
	friend std::ostream& operator<<(std::ofstream& b_out, const DList& l);
	friend std::istream& operator>>(std::ifstream& b_in, DList& l);
};