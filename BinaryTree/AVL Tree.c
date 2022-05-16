#include<stdio.h>
#include<stdlib.h>
#include<math.h> 
#define SIZE 100

struct AVLTree
{
	int element;
	int height;
	int size;
	struct AVLTree* left;
	struct AVLTree* right;
}; 

typedef struct AVLTree* Tree;

Tree LR(Tree T);
Tree RR(Tree T);
Tree RLR(Tree T);
Tree LRR(Tree T);
int Max(int a, int b);
int Height(Tree T);
int Size(Tree T);
void swap(Tree T1, Tree T2);
Tree FindMax(Tree T);
Tree Insert(Tree T, int x);
Tree Delete(Tree T, int x);
struct AVLTree** CreateQueue(int* front, int* rear); 
void Enqueue(struct AVLTree* x,struct AVLTree** queue, int* rear);
Tree Dequeue(struct AVLTree** queue, int* front);
void TreeVisual(Tree T);
void TreeLineVisual(Tree T);
void PrintTree(int* val, int h, int len);

int main()
{
	Tree T = (Tree)malloc(sizeof(struct AVLTree));
	T->element = 8;
	T->left = NULL;
	T->right = NULL;
	T->height = 0;
	T->size = 0;
	T = Insert(T, 5);
	T = Insert(T, 10);
	T = Insert(T, 3);
	T = Insert(T, 7);
	T = Insert(T, 9);
	T = Insert(T, 12);
	T = Insert(T, 2);
	T = Insert(T, 4);
	T = Insert(T, 6);
	T = Insert(T, 11);
	T = Insert(T, 1); 
	printf("%d", T->left->size);
	TreeLineVisual(T);
	T = Delete(T, 5);
	TreeLineVisual(T);
	T = Delete(T, 8);
	TreeLineVisual(T);
	T = Delete(T, 4);
	TreeLineVisual(T);
	T = Delete(T, 9);
	TreeLineVisual(T);
	T = Delete(T, 3);
	TreeLineVisual(T);
	T = Delete(T, 2);
	TreeLineVisual(T);
	T = Delete(T, 7);
	TreeLineVisual(T);
	T = Delete(T, 1);
	TreeLineVisual(T);
	T = Delete(T, 12);
	TreeLineVisual(T);
	T = Delete(T, 6);
	TreeLineVisual(T);
	T = Delete(T, 10);
	TreeLineVisual(T);
	T = Delete(T, 11);
	TreeLineVisual(T);
	return 0;
}

Tree LR(Tree T)
{
	Tree tmp = T->left;
	T->left = tmp->right;
	tmp->right = T; 
	T->height = Max(Height(T->left), Height(T->right)) + 1;
	tmp->height = Max(Height(tmp->left), Height(tmp->right)) + 1;
	T->size = Size(T->left) + Size(T->right) + 1;
	tmp->size = Size(tmp->left) + Size(tmp->right) + 1;
	return tmp;					
}

Tree RR(Tree T)
{
	Tree tmp = T->right;
	T->right = tmp->left;
	tmp->left = T;
	T->height = Max(Height(T->left), Height(T->right)) + 1;
	tmp->height = Max(Height(tmp->left), Height(tmp->right)) + 1;
	T->size = Size(T->left) + Size(T->right) + 1;
	tmp->size = Size(tmp->left) + Size(tmp->right) + 1;
	return tmp;
}

Tree RLR(Tree T)
{
	Tree tmp;
	tmp = RR(T->left);
	T->left = tmp;
	tmp = LR(T);
	return tmp;
}

Tree LRR(Tree T)
{
	Tree tmp;
	tmp = LR(T->right);
	T->right = tmp;
	tmp = RR(T);
	return tmp;
}

int Max(int a, int b)
{
	if(a > b) return a;
	else return b;
}

int Height(Tree T)
{
	if(T == NULL) return -1;
	else return T->height;
}

int Size(Tree T)
{
	if(T == NULL) return 0;
	else return T->size;
}

void swap(Tree T1, Tree T2)
{
	int tmp = T1->element;
	T1->element = T2->element;
	T2->element = tmp;
}


Tree FindMax(Tree T)
{
	if(T == NULL) return NULL;
	if(T->right == NULL) return T;
	else return FindMax(T->right);
}

Tree Insert(Tree T, int x)
{
	if(T == NULL)
	{
		T = (Tree)malloc(sizeof(struct AVLTree));
		T->element = x;
		T->left = NULL;
		T->right = NULL;
		T->height = 0;
	}
	else if(x > T->element)
	{	
		T->right = Insert(T->right, x);
		if(Height(T->right) - Height(T->left) == 2)
		{
			if(x > T->right->element) T = RR(T);
			else T = LRR(T);
		}
	}
	else if(x < T->element)
	{
		T->left = Insert(T->left, x);
		if(Height(T->left) - Height(T->right) == 2)
		{
			if(x < T->left->element) T = LR(T);
			else T = RLR(T);
		}
	}
	T->height = Max(Height(T->left), Height(T->right)) + 1;
	T->size = Size(T->left) + Size(T->right) + 1;
	return T;
}

Tree Delete(Tree T, int x)
{
	Tree tmp;
	if(T == NULL) return NULL;
	if(x < T->element) T->left = Delete(T->left, x);
	else if(x > T->element) T->right = Delete(T->right, x);
	else
	{	
		if(T->right == NULL && T->left == NULL) return NULL;
		else if(T->right && T->left)
		{
			tmp = FindMax(T->left);
			swap(T, tmp);
			T->left = Delete(T->left, x);
		}
		else if(T->right) T = T->right;
		else T = T->left;
	}
	T->height = 1 + Max(Height(T->left), Height(T->right));
	T->size = Size(T->left) + Size(T->right) + 1;
	if(Height(T->left) - Height(T->right) == 2)
	{
		if(Height(T->left->left) >= Height(T->left->right)) T = LR(T);
		else T = RLR(T);
	}
	else if(Height(T->right) - Height(T->left) == 2)
	{
		if(Height(T->right->right) >= Height(T->right->left)) T = RR(T);
		else T = LRR(T);
	}
	
	return T;
}

struct AVLTree** CreateQueue(int* front, int* rear)
{
	struct AVLTree** queue = (struct AVLTree**)malloc(sizeof(struct AVLTree*) * SIZE);
	*front = 0;
	*rear = 0;
	return queue;
}

void Enqueue(struct AVLTree* x, struct AVLTree **queue, int *rear)
{
	queue[*rear] = x;
	(*rear)++;
}

Tree Dequeue(struct AVLTree** queue, int* front)
{	
	(*front)++;
	return queue[*front - 1];
}

void TreeVisual(Tree T)
{
	int rear, front;
	struct AVLTree** queue = CreateQueue(&front, &rear);
	Tree tmp = T;
	Enqueue(tmp, queue, &rear);
	int count = 0, len, h = T->height;
	int val[100];
	while(rear != front && count <= pow(2, h + 1) - 1)
	{	
		tmp = Dequeue(queue, &front);
		if(tmp)
		{
			Enqueue(tmp->left, queue, &rear);
			Enqueue(tmp->right, queue, &rear);
		}
		else
		{
			Enqueue(NULL, queue, &rear);
			Enqueue(NULL, queue, &rear);
		}
		if(tmp == NULL) val[count] = 0;
		else val[count] = tmp->element;
		count++;
	}	
	len = pow(2, h + 1) - 1;
	PrintTree(val, h, len);
}

void PrintTree(int* val, int h, int len)
{	
	int index[57] = {0,2,1,3,4,2,6,1,3,5,7,8,4,12,2,6,10,14,1,3,5,7,9,11,13,15,16,8,24,4,12,20,28,2,6,10,14,18,22,26,30,1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31};
	int count = 0, i = 0, j;
	int begin;
	begin = pow(2, h + 1) - h - 2;
	while(i <= h && count <= len)
	{
		j = 0;
		while(j < len)
		{
			if(j + 1 == index[begin + count])
			{
				if(val[count] == 0) printf("%d", 0);
				else printf("%d", val[count]);
				count++;
			}
			else
			{
				printf(" ");
			}
			j++;
		}
		printf("\n");
		i++;
	}
}

void TreeLineVisual(Tree T)
{
	int rear, front;
	struct AVLTree** queue = CreateQueue(&front, &rear);
	Tree tmp = T;
	if(T == NULL)
	{
		printf("Empty!");
		return;
	}
	Enqueue(tmp, queue, &rear);
	while(rear != front)
	{	
		tmp = Dequeue(queue, &front);
		if(tmp->left) Enqueue(tmp->left, queue, &rear);
		if(tmp->right) Enqueue(tmp->right, queue, &rear);
		printf("%d ", tmp->element);	
	}	
	printf("\n");
}
