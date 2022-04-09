#include<stdio.h>
#include<stdlib.h>
#include<math.h>

enum KindOfEntry {legitimate, empty, deleted};

typedef struct HashEntry Cell;
typedef struct Hashing* HashTable;

struct HashEntry
{
	int Element;
	enum KindOfEntry info;	
};

struct Hashing
{
	int TableSize;
	Cell* TheCells; 
}; 

bool Prime(int n);
int NextPrime(int TableSize);
HashTable Initialize(int TableSize);
int Hash(int key, int TableSize);
int Find(int key, HashTable H);
bool Insert(int key, HashTable H);
bool Delete(int key, HashTable H);

int main()
{		
	int a[9] = {10,21,32,1,12,7,18,20,11};
	HashTable H = Initialize(9);
	int i;
	bool flag;
	for(i = 0; i < 9; i++)
	{
		flag = Insert(a[i], H);
		printf("%d ",flag);
	}
	printf("\n");
	for(i = 0; i < 11; i++)
	{
		printf("%d ",H->TheCells[i].Element);
	}
	return 0;
}

bool Prime(int n)
{
	int i;
	for(i = 2; i < n; i++)
	{
		if(!(n % i))
		{
			return false;
			break;
		}
	}
	if(i == n) return true;
}

int NextPrime(int TableSize)
{
	int x = TableSize + 1;
	while(!Prime(x))
	{
		x++;
	}
	return x;
}

HashTable Initialize(int TableSize)
{
	HashTable H;
	int i;
	H = (HashTable)malloc(sizeof(Hashing));
	H->TableSize = NextPrime(TableSize);
	H->TheCells = (Cell*)malloc(sizeof(Cell) * H->TableSize);
	for( i = 0; i < H->TableSize; i++)
	{
		H->TheCells[i].info = empty;
		H->TheCells[i].Element = NULL;
	}
	return H;
}

int Hash(int key, int TableSize)
{
	return key % TableSize;
}

int Find(int key, HashTable H)
{
	int Npos = Hash(key, H->TableSize), Curpos = Npos;
	int CNum = 0;
	while(H->TheCells[Npos].info != empty && H->TheCells[Npos].Element != key)
	{
		if(++CNum % 2)
		{
			Npos = Curpos + pow(CNum + 1, 2) / 4;
			if(Npos >= H->TableSize)
				Npos = Npos - H->TableSize;
		}
		else
		{
			Npos = Curpos - pow(CNum, 2) / 4;
			if(Npos < 0)
				Npos = Npos + H->TableSize;
		}
	}
	return Npos;
}

bool Insert(int key, HashTable H)
{
	int index = Find(key, H);
	if(H->TheCells[index].info != legitimate)
	{
		H->TheCells[index].Element = key;
		H->TheCells[index].info = legitimate;
		return true;
	}
	else
	{
		printf("键值已存在");
		return false;
	}
}

bool Delete(int key, HashTable H)
{
	int index = Find(key, H);
	if(H->TheCells[index].info == empty)
	{
		H->TheCells[index].info = deleted;
		return true;
	}
	else
	{
		printf("无该键值");
		return false; 
	}
}
