#include<stdio.h>
#include<stdlib.h>
#define Size 7

void InsertLast(int* A, int i);
void InsertionSort(int* A);
void PrintArray(int* A);

int main()
{
	int* Array = (int*)malloc(Size);
	Array[0] = 5;
	Array[1] = 2;
	Array[2] = 7;
	Array[3] = 1;
	Array[4] = 4;
	Array[5] = 8;
	Array[6] = 6;
	
	PrintArray(Array);
	InsertionSort(Array);
	PrintArray(Array);
	
	return 0;
}

void InsertLast(int* A, int i)
{	
	int temp;
	if(i > 0 && A[i] < A[i - 1])
	{
		temp = A[i];
		A[i] = A[i - 1];
		A[i - 1] = temp;
		InsertLast(A, i-1);
	}
}

void InsertionSort(int* A)
{
	static int i = 1;
	if(i < Size)
	{
		InsertLast(A, i);
		i++;
		InsertionSort(A);
	}
}

void PrintArray(int* A)
{
	int i = 0;
	while(i < Size)
	{
		printf("%d ",A[i]);
		i++;
	}
	printf("\n");
}
