#pragma once

#include "polygon.h"

// ������������ ������

#define NULL 0

class DNode
{
	DNode *left = NULL; // ��������� �� ����� �������
	DNode *right = NULL; // ��������� �� ������ �������
	
	CPolygon *data = NULL; // ��������� �� �����
	int key = 0;

public:

	DNode(CPolygon& p); 
	void InsertRight(DNode *p); // �������� ������� ������
	void InsertLeft(DNode *p); // �������� ������� �����
	DNode *Delete(); // �������� �������� ��������

	DNode *NextRight() const; // ����� ����. �������� ������
	DNode *NextLeft() const; // ����� ����. �������� �����

	CPolygon *GetData();
	int GetKey() const;
};