/*
��������

˼·������������N-1��������ɣ�����P=1�˵�P=N-1�ˣ���������֤λ��0��λ��PΪ������״̬��λ��0��λ��P-1�����Ź���ġ�

ʵ�֣��ڵ�P�ˣ���λ��P�ϵ�Ԫ���ƶ���ǰP+1��Ԫ����ȷ��λ���ϡ�

����ͨ����������Ԫ�ؽ���������κ��㷨ƽ����Ҫ����N2��ʱ��
*/

//�������˼·�����Ӷ�ΪO��N2������ʹ���ڶ���˳�������¡�
void MyInsertionSort(ElementType A[], int N)
{
	int j, P;

	ElementType tmp, exc;
	for (P = 1; P < N; P++)
	{
		tmp = A[P];
		for (j = P; j > 0; j--)
		{
			if (A[j-1] > tmp)
			{
				exc = A[j-1];
				A[j-1] = A[j];
				A[j] = exc;
			}
			tmp = A[j - 1];
		}
	}
}

//���ϵ��㷨�����㷨��˳�������±��ҵĿ죬��Ϊ�ڲ�forѭ��������������ж�����������ֹ
void InsertionSort(ElementType A[], int N)
{
	int j, P;

	ElementType tmp;
	for (P = 1; P < N; P++)
	{
		tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > tmp; j--)//�����������㣬��ʱj��ֵ�Ѽ�һ
			A[j] = A[j - 1];
		A[j] = tmp;
	}
}







int main()
{
	int i;
	int a[10] = { 2, 4, 67, 12, 43, 78, 5, 3, 8, 65 };

	MyInsertionSort(a, 10);
	for (i = 0; i < 10; i++)
		printf("%d,", a[i]);

    return 0;
}

