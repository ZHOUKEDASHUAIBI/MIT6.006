#include<stdio.h>
#include<stdlib.h>
#define Size 7

int PreMax(int* Array, int i);
void SelectionSort(int* Array);
void PrintArray(int* Array);

int main()
{
	int* Array = (int*)malloc(sizeof(Size));
	Array[0] = 5;
	Array[1] = 2;
	Array[2] = 7;
	Array[3] = 1;
	Array[4] = 4;
	Array[5] = 8;
	Array[6] = 6;
	PrintArray(Array);
	SelectionSort(Array);
	PrintArray(Array);
	
	return 0;
}

int PreMax(int* Array, int i)
{	
	int j;
	if(i > 0)
	{
		j = PreMax(Array, i-1);
		if(Array[i] < Array[j])
			return j;
		return i;
	}
}

void SelectionSort(int* Array)
{	
	static int i = Size;
	int j, temp;
	if(i > 0)
	{
		j = PreMax(Array, i);
		temp = Array[j];
		Array[j] = Array[i];
		Array[i] = temp;
		i--;
		SelectionSort(Array);
	}
}

void PrintArray(int* Array)
{
	int i = 0;
	while(i < Size)
	{
		printf("%d ",Array[i]);
		i++;
	}
	printf("\n");
}
