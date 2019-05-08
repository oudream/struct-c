/*
�鲢����

˼·������˼��

�������Ƚ�����ݹ�İ��ն԰�ֵķ�ʽ�ֽ�Ϊһ��Ԫ�أ���ʱ����Ϊǰ��һ���λ��������飬Ȼ��ͨ��merge��������������ϲ���

�ܽ᣺ʱ�临�Ӷ�O��N*logN����ȱ����Ҫ�����ڴ棨���Ӷ�֤����Ҫ�˽⣩��

�ǵݹ�д����https://www.cnblogs.com/bluestorm/archive/2012/09/06/2673138.html
*/
//��������ϵ����Ӻ��Լ���д��
//Lpos,Rpos, RightEnd��Ϊ�±�
void Merge(ElementType A[], int Lpos, int Rpos, int RightEnd)
{
	int start = Lpos;			//������ڽ�����TempArray��ֵ����A������ʼ�±�
	int LeftEnd = Rpos - 1;			//�������±�
	int NumElements = RightEnd - Lpos + 1;					//Ҫ�鲢������Ԫ�ظ���
	int *TempArray = (int *)malloc(sizeof(int)*(RightEnd - Lpos + 1));	//��Ž������

	//TempArray���±�0��ʼ�洢�鲢����õ�Ԫ��
	int i = 0;
	while(Lpos <= LeftEnd && Rpos <= RightEnd)
	{
		if (A[Lpos] <= A[Rpos])
			TempArray[i++] = A[Lpos++];
		else
			TempArray[i++] = A[Rpos++];
	}

	//�Ҳ��ѹ鲢����
	while (Lpos <= LeftEnd)
		TempArray[i++] = A[Lpos++];
	//����ѹ鲢����
	while (Rpos <= RightEnd)
		TempArray[i++] = A[Rpos++];

	//��TempArray������õ�Ԫ�ظ�ֵA,�ǵ�A�е���һ��Ԫ�ش�������״̬
	int j;
	for (j = 0; j < NumElements; j++)
		A[j + start] = TempArray[j];

	free(TempArray);
}

//��������
void MSort(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (Left < Right)
	{
		MSort(A, Left, Center);
		MSort(A, Center + 1, Right);
		Merge(A, Left, Center + 1, Right);
	}
}

//����д��
void Merge1(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;	//�˴������溯��ʵ�ֲ�ͬ��ʹ��TempArray�������Aͬ��,�������ظ�ʹ��TempArray�Ĳ���
	NumElements = RightEnd - Lpos + 1;

	while (Lpos <= LeftEnd && Rpos <= RightEnd)
	{
		if (A[Lpos] < A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];
	}

	while (Lpos <= LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];
	while (Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];

	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];

}

//����д��
void MSort1(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
	int Center;

	if (Left < Right)
	{
		Center = (Left + Right) / 2;
		MSort1(A, TmpArray, Left, Center);
		MSort1(A, TmpArray, Center + 1, Right);
		Merge1(A, TmpArray, Left, Center + 1, Right);
	}
}







int main()
{
	int b[10];
	int i;
	int a[10] = { 2, 4, 67, 12, 43, 78, 5, 3, 8, 87};

	MSort(a, 0, 9);
	for (i = 0; i < 10; i++)
		printf("%d,", a[i]);

    return 0;
}

