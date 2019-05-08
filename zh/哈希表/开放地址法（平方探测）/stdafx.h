#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
typedef int Position;
enum KindOfEntry {Legitimate, Empty, Deleted};

/*
���ŵ�ַ��ʵ�ֹ�ϣ��ƽ��̽�ⷨ�����ͻ
*/
typedef struct HashEntry	//�洢��Ԫ
{
	ElementType Element;
	enum KindOfEntry Info;//״̬
}Cell;

typedef struct HashTb
{
	int TableSize;
	Cell *TheCells;//�洢��Ԫ����
}*HashTable;


//������ϣ��
HashTable InitializeTable(int);

//��ϣ����
Position Hash(ElementType, int);

//ʹ��ƽ��̽��ɢ�б�Ĳ�������
Position Find(ElementType, HashTable);

//ʹ��ƽ��̽��ɢ�б�Ĳ�������
void Insert(ElementType, HashTable);

//ʹ��ƽ��̽��ɢ�б��ɾ������
int Delete(ElementType, HashTable);