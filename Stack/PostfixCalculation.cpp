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

int main()
{
	stack S;
	char ch;
	int sum = 0;
	int a, b;
	S = CreateStack(100);
	while((ch = getchar()) != '\n')
	{
		if(ch >= '0' && ch <= '9')
		{
			push(ch - '0' ,S);
		}
		else
		{
			b = Top(S);
			pop(S);
			a = Top(S);
			pop(S);
			switch(ch)
			{
				case '+': sum = a + b; 
					  push(sum,S);
					  break;
				case '-': sum = a - b; 
					  push(sum,S);
					  break;
				case '*': sum = a * b;
					  push(sum,S);
					  break;
				case '/': sum = a / b;
					  push(sum,S);
					  break;
			} 
		}
		if(getchar() == '\n') break;
	}
	printf("%d",sum);
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
