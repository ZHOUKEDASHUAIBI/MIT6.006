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
int ChoosePrime(int max);
HashTable Initialize(int TableSize);
int Hash1(int key, int TableSize);
int Hash2(int index);
int Find(int key, HashTable H);
bool Insert(int key, HashTable H);
bool Delete(int key, HashTable H);
void PrintHash(HashTable H);

int main()
{		
	int a[9] = {10,21,32,1,12,8,18,20,11};
	HashTable H = Initialize(9);
	int i;
	bool flag;
	for(i = 0; i < 9; i++)
	{
		flag = Insert(a[i], H);
		printf("%d ",flag);
	}
	printf("\n");
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

int ChoosePrime(int max)
{
	int n = max - 1;
	while(n >= 2)
	{
		if(Prime(n))
		{
			return n;
			break;
		}
		n--;
	}
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

int Hash1(int key, int TableSize)
{
	return key % TableSize;
}

int Hash2(int index, HashTable H)
{
	int prime = ChoosePrime(H->TableSize);
	return prime - (index % prime);
}

int Find(int key, HashTable H)
{
	int Npos = Hash1(key, H->TableSize), Curpos = Npos;
	int CNum = 0;
	while(H->TheCells[Npos].info != empty && H->TheCells[Npos].Element != key)
	{
		CNum++;
		Npos = CNum * Hash2(Npos, H);
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
	if(H->TheCells[index].info == legitimate)
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

void PrintHash(HashTable H)
{
	int i;
	for(i = 0; i < 11; i++)
	{
		if(H->TheCells[i].info == legitimate)
			printf("%d ",H->TheCells[i].Element);
		else
			printf("0 ");
	}
	printf("\n");
}
