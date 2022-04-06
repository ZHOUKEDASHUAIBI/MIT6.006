#include<stdio.h>
#include<stdlib.h>
#define Size 8

void Merge(int* Array, int start, int mid, int end);
void MergeSort(int* Array, int start, int end);
void PrintArray(int* Array);

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
	Array[7] = 10;
	PrintArray(Array);
	MergeSort(Array, 0, Size - 1);
	PrintArray(Array);
	
	return 0;
}
/*
	use loop
*/
void Merge(int* Array, int start, int mid, int end)
{
	int head1 = start, head2 = mid + 1;
	int end1 = mid, end2 = end;
	int	i = head1, j = head2, k = 0;
	int* A = (int*)malloc(end - start + 1);
	while(i <= end1 && j <= end2)
	{
		if(Array[i] < Array[j])
		{
			A[k] = Array[i];
			i++;
			k++;
		}
		else
		{
			A[k] = Array[j];
			j++;
			k++;
		}
	}
	while(i <= end1)
	{
		A[k] = Array[i];
		i++;
		k++;
	}
	while(j <= end2)
	{
		A[k] = Array[j];
		j++;
		k++;
	}
	k = start, i = 0;
	while(k <= end)
	{
		Array[k] = A[i];
		i++;
		k++;
	}
}

void MergeSort(int* Array, int start, int end)
{
	int mid;
	if(end - start > 1)
	{
		mid = (start + end + 1) / 2;
		MergeSort(Array, start, mid);
		MergeSort(Array, mid+1, end);
		Merge(Array, start, mid, end);
	}
	else if(end - start == 1)
	{	
		int temp;
		if(Array[start] > Array[end])
		{
			temp = Array[start];
			Array[start] = Array[end];
			Array[end] = temp;	
		}	
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
