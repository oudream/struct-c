#include "stdafx.h"


/*
������ϣ��
*/
HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	//�����ϣ��ṹ�洢�ռ䲢���ñ��С
	H = (HashTable)malloc(sizeof(struct HashTb));
	if (NULL == H)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	H->TableSize = TableSize;

	//�����ϣ��洢��Ԫ�洢�ռ�
	H->TheCells = (Cell*)malloc(sizeof(struct HashEntry) * H->TableSize);
	if (NULL == H->TheCells)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	//��ÿ���洢��Ԫ�ĳ�ʼ״̬����Ϊ��
	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;

	return H;
}

/*
��ϣ����
*/
Position Hash(ElementType key, int TableSize)
{
	return key % TableSize;
}

/*
ʹ��ƽ��̽��ɢ�з���������
*/
Position Find(ElementType key, HashTable H)
{
	Position currentPos;	//�ؼ���ɢ�б�λ��
	int collisionNum=0;		//��ͻ������������

	currentPos = Hash(key, H->TableSize);	//����ɢ�б�λ��
	while (H->TheCells[currentPos].Info != Empty && H->TheCells[currentPos].Element != key)
	{	
		//����һλ���������Ʋ���һ��F(i)=F(i-1)+2*i-1
		//����λ�������飬��ɢ�б�λ�����ص���Χ��
		currentPos += 2 * ++collisionNum - 1;
		if (currentPos >= H->TableSize)
			currentPos -= H->TableSize;
	}
	return currentPos;
}

/*
ʹ��ƽ��̽��ɢ�б�Ĳ�������
*/
void Insert(ElementType key, HashTable H)
{
	Position Pos;

	//ͨ��Find�������ҹ�ϣ����key�ؼ����Ƿ��ڱ���
	//��������������������������Find���ҵ��Ŀ�λ���ϲ���ùؼ���
	Pos = Find(key, H);
	if (H->TheCells[Pos].Info != Legitimate)
	{
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Element = key;
	}
}

/*
ʹ��ƽ��̽��ɢ�б��ɾ������
*/
int Delete(ElementType key, HashTable H)
{
	Position Pos;

	Pos = Find(key, H);
	if (H->TheCells[Pos].Info == Legitimate)
	{
		H->TheCells[Pos].Info = Deleted;
		return 1;
	}

	return 0;
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
		printf("|           5.Exit.                           |\n");
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
				if (H->TheCells[pos].Info == Legitimate)
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
				else
					printf("Delete failed.\n");
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

