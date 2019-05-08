#include "stdafx.h"


/*
������ϣ���ʼ��ͷ���
*/
HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	//�˴�Ӧ��Ϊ�жϹ�ϣ���ȴ�С������������Ϊ����
	//�Ȳ�ȡ���������ķ�ʽ��֮��������
	//if (TableSize < MinTableSize)
	//{
	//	printf("Table size too smal.\n");
	//	return NULL;
	//}

	//����ϣ��ṹ����ռ�
	H = (HashTable)malloc(sizeof(struct HashTb));
	if (NULL == H)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	H->TableSize = TableSize;

	//����ϣ��TheLists����ռ�
	H->TheLists = (List*)malloc(sizeof(List) * H->TableSize);
	if (NULL == H->TheLists)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	//��TheLists��ÿ��List����ռ䲢����ͷ���
	for (i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
		if (NULL == H->TheLists[i])
		{
			printf("Out of space.\n");
			exit(-1);
		}
		else
			H->TheLists[i]->next = NULL;
	}

	return H;
}

/*
ɢ�к���
*/
int Hash(ElementType key, ElementType TableSize)
{
	return key % TableSize;
}

/*
��ϣ���и��ݹؼ��ֲ�������
����ָ�룬��ָ��ָ�����key���Ǹ���Ԫ
*/
Position Find(ElementType key, HashTable H)
{
	Position P;
	List L;

	//ͨ��ɢ�к����ҵ��ؼ������ڵ�ɢ�б������ñ���ҹؼ�������λ��
	L = H->TheLists[Hash(key, H->TableSize)];
	P = L->next;
	while (NULL != P && key != P->data)
		P = P->next;
	return P;
}

/*
��ϣ�����ؼ�������
*/
void Insert(ElementType key, HashTable H)
{
	Position pos, newCell;
	List L;

	//����֮ǰ�Ȳ��ҹؼ��֣���δ�ܷ��ֹؼ��֣�
	//�����ڵ㣬������뵽�ؼ�����ɢ�е���ɢ�б�ͷ���֮��
	pos = Find(key, H);
	if (NULL == pos)
	{
		newCell = (Position)malloc(sizeof(struct ListNode));
		if (NULL == newCell)
		{
			printf("Out of space.\n");
			exit(-1);
		}
		else
		{
			L = H->TheLists[Hash(key, H->TableSize)];
			newCell->next = L->next;
			newCell->data = key;
			L->next = newCell;
		}
	}
	else
		printf("The key element is exists.\n");
}

/*
�ڹ�ϣ����ɾ���ؼ�������
*/
int Delete(ElementType key, HashTable H)
{
	Position pos, pre;
	List L;

	//ɾ��֮ǰ�Ȳ��ҹؼ���
	pos = Find(key, H);
	if (NULL != pos)		//�����ҹؼ��ֳɹ�ɾ���ؼ��ֽڵ�
	{
		L = H->TheLists[Hash(key, H->TableSize)];
		pre = L;			//ǰ��
		while (pos != pre->next)
		{
			pre = pre->next;
		}
		pre->next = pos->next;
		free(pos);
		return 1;
	}

	return 0;
}

/*
���ٹ�ϣ��
*/
void Destroy(HashTable H)
{
	Position pos, temp;
	List L;
	int i;

	//����ϣ��Ĵ�С���ٿռ�
	for (i = 0; i < H->TableSize; i++)
	{
		L = H->TheLists[i];
		pos = L->next;
		L->next = NULL;
		while (pos)	//��ɢ�б�Ϊ�գ��ͷ�ɢ�б�ռ�
		{
			temp = pos;
			pos = pos->next;
			free(temp);
		}
		free(L);	//����ɢ�б�ͷ���
	}

	free(H);
}









int main()
{
	int flag=1, c, size, key;
	HashTable H=NULL;
	Position pos;

	while(flag)
	{
		if (NULL == H)
			printf("HashTable is NULL, please create a hashtable.\n");

		printf("|-------------------Choices-------------------|\n");
		printf("|           1.Create Hashtable                |\n");
		printf("|           2.Find element in Hashtable       |\n");
		printf("|           3.Insert element in Hashtable     |\n");
		printf("|           4.Delete element in Hashtable     |\n");
		printf("|           5.Destroy Hashtable               |\n");
		printf("|---------------------------------------------|\n");

		printf("Please input the choice.\n");
		scanf("%d", &c);
		switch (c)
		{
		case 1:
			printf("Please input the hashtable size.\n");
			scanf("%d", &size);
			H = InitializeTable(size);
			break;

		case 2:
			if (H)
			{
				printf("Please input the want find key.\n");
				scanf("%d", &key);
				pos = Find(key, H);
				if (pos)
					printf("Key %d is in the hashtable.\n", key);
				else
					printf("Key %d is not in the hashtable.\n", key);
				break;
			}
			else
				printf("Hashtable is not create.\n");

		case 3:
			if (H)
			{
				printf("Please input the want insert key.\n");
				scanf("%d", &key);
				Insert(key, H);
				printf("Insert success.\n");
				break;
			}
			else
				printf("Hashtable is not create.\n");

		case 4:
			if (H)
			{
				printf("Please input the want delete key.\n");
				scanf("%d", &key);
				if (Delete(key, H))
					printf("Delete success.\n");
				break;
			}
			else
				printf("Hashtable is not create.\n");

		case 5:
			if (H)
			{
				Destroy(H);
				printf("Destroy hashtable success.\n");
				break;
			}
			else
				printf("Hashtable is not create.\n");

		default:
			flag = 0;
			printf("�������н�������������˳���\n");
		}
	}

    return 0;
}

