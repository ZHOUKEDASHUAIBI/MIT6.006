#include<stdio.h>
#include<stdlib.h>
#define EmptyTOS -1

struct StackRecord
{
	int capacity;
	int TopOFStack;
	int *Array;
};

typedef StackRecord* stack;

stack CreateStack(int Maxsize);
void MakeEmpty(stack S);
void push(int x,stack S);
void pop(stack S);
int isFull(stack S);
int isEmpty(stack S); 
int Top(stack S);
void PrintStack(stack S);

int main()
{
	stack S;
	S = CreateStack(3);
	//printf("%d\n",isEmpty(S));
	push(1,S);
	printf("%d\n",Top(S));
	push(2,S);
	printf("%d\n",Top(S));
	push(3,S);
	printf("%d\n",Top(S));
	//printf("%d\n",isFull(S));
	
	return 0;
}

void MakeEmpty(stack S)
{
	S->TopOFStack = EmptyTOS;
}

stack CreateStack(int Maxsize)
{
	stack S;
	S = (stack)malloc(sizeof(struct StackRecord));
	S->Array = (int*)malloc(sizeof(int)*Maxsize);
	S->capacity = Maxsize;
	MakeEmpty(S);
	return S;
}

int isFull(stack S)
{
	return S->TopOFStack + 1 == S->capacity;
}

int isEmpty(stack S)
{
	return S->TopOFStack == EmptyTOS;
}

void push(int x, stack S)
{
	if(isFull(S)) printf("stack overflow");
	else
	{
		S->Array[++(S->TopOFStack)] = x;
	}
}

void pop(stack S)
{
	if(isEmpty(S)) printf("stack underflow");
	else
	{
		S->TopOFStack--;
	}
}

int Top(stack S)
{
	if(isEmpty(S)) printf("No element");
	else 
		return S->Array[S->TopOFStack];
}

void PrintStack(stack S)
{
	int i = 0;
	while(i != S->TopOFStack + 1)
	{
		printf("%d ",S->Array[i]);
		i++;
	}
}
