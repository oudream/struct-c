/*
��ӡ���һ������ 
*/
void printArray(int *array, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}

/*
��������Ԫ��
*/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
ȫ���к���
*/
void permute(int *array, int i, int length) 
{	//�ݹ�ĳ��ڣ�û��Ԫ�ؿ��Խ���
	if (length == i) 
	{	
		printArray(array, length);
		return;
	}

	int j;
	for (j = i; j < length; j++) 
	{
		swap(array + i, array + j);	//��һ��λ�õ�Ԫ�طֱ������λ���ϵ�Ԫ�ؽ���
		permute(array, i + 1, length);	//�ݹ������һ��λ�÷ֱ������λ���ϵ�Ԫ�ؽ���
		swap(array + i, array + j);	//���������״̬
	}
	return;
}



int main()
{
    int A[4] = { 1, 2, 3, 4 };
    permute(A, 0, 4);
    return 0;
}
