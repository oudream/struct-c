#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
//#define MinTableSize 10		//��ϣ����С��Χ
typedef int ElementType;


/*
���÷������ӷ�ʵ�ֵĹ�ϣ��
*/
typedef struct ListNode		//���ӽڵ�ṹ��ͷ�ڵ�
{
	ElementType data;	//�ؼ�����Ϣ
	struct ListNode *next;
}*Position, *List;

typedef struct HashTb		//��ϣ��ṹ
{
	int TableSize;	//��ϣ���С
	List *TheLists;	//ָ���ͷָ��
}*HashTable;


//������ϣ���ʼ��ͷ���
HashTable InitializeTable(int);

//��ϣ���и��ݹؼ��ֲ�������
Position Find(ElementType, HashTable);

//ɢ�к���
int Hash(ElementType, ElementType);

//��ϣ�����ؼ�������
void Insert(ElementType, HashTable);

//�ڹ�ϣ����ɾ���ؼ�������
int Delete(ElementType, HashTable);

//���ٹ�ϣ��
void Destroy(HashTable);