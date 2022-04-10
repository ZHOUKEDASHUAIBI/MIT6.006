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
HashTable ReHash(HashTable H); 
int Hash(int key, int TableSize);
int Find(int key, HashTable H);
void Insert(int key, HashTable H);
void Delete(int key, HashTable H);
void PrintHash(HashTable H);

int main()
{		
	int a[5] = {13,15,24,6,23};
	HashTable H = Initialize(5);
	int i;
	double ratio = 0.0, n = 0.0;
	for(i = 0; i < 5; i++)
	{
		Insert(a[i], H);
		n++;
	}
	PrintHash(H);
	ratio = (double)(n / H->TableSize);
	if(ratio > 0.5)
		H = ReHash(H);
	PrintHash(H);
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
		CNum++;
		Npos = Curpos + CNum;
		if(Npos >= H->TableSize)
			Npos -= H->TableSize;
	}
	return Npos;
}

void Insert(int key, HashTable H)
{
	int index = Find(key, H);
	if(H->TheCells[index].info != legitimate)
	{
		H->TheCells[index].Element = key;
		H->TheCells[index].info = legitimate;
	}
	else
	{
		printf("键值已存在");
	}
}

void Delete(int key, HashTable H)
{
	int index = Find(key, H);
	if(H->TheCells[index].info == legitimate)
	{
		H->TheCells[index].info = deleted;
	}
	else
	{
		printf("无该键值");
	}
}

void PrintHash(HashTable H)
{
	int i;
	for(i = 0; i < H->TableSize; i++)
	{
		if(H->TheCells[i].info == legitimate)
			printf("%d ",H->TheCells[i].Element);
		else
			printf("0 ");
	}
	printf("\n");
}

HashTable ReHash(HashTable H)
{
	HashTable NewH;
	int i;
	NewH = Initialize(2 * H->TableSize);
	for(i = 0; i < H->TableSize; i++)
	{
		if(H->TheCells[i].info == legitimate)
		{
			Insert(H->TheCells[i].Element, NewH);
		}
	}
	return NewH;
}
