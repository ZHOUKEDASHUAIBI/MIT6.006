#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ListNode
{
	char* Element;
	struct ListNode* next;	
};

struct Hashing
{
	int TableSize;
	struct ListNode** TheList;
}; 

typedef Hashing* HashTable;
typedef ListNode* List;
typedef int position;

bool Prime(int n);
int NextPrime(int TableSize);
HashTable Initialize(int TableSize);
position Hash(const char* key, int TableSize);
List Find(const char* key, HashTable H);
void Insert(const char* key, HashTable H);
void Delete(const char* key, HashTable H);
List FindPrev(const char* key, List L, HashTable H);
void PrintHash(HashTable H);

int main()
{
	char* a[7] = {"amy","jack","lucy","allen","john","bob","Dylan"};
	HashTable H = Initialize(8);
	int i;
	for(i = 0; i < 7; i++)
	{
		Insert(a[i], H);
	}
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
	HashTable H = (HashTable)malloc(sizeof(Hashing));
	int i;
	H->TableSize = NextPrime(TableSize);
	H->TheList = (List*)malloc(sizeof(List) * H->TableSize);
	for(i = 0; i < H->TableSize; i++)
	{
		H->TheList[i] = (List)malloc(sizeof(struct ListNode));
		H->TheList[i]->next = NULL;
	}
	return H;
}

position Hash(const char* key, int TableSize)
{
	unsigned int Hashval = 0;
	while(*key != '\0')
	{
		Hashval = (Hashval << 5) + *key++;
	}
	return Hashval % TableSize;
}

List Find(const char* key, HashTable H)
{
	int index = Hash(key, H->TableSize);
	List tmp = H->TheList[index]->next;
	while(tmp != NULL && tmp->Element != key)
	{
		tmp = tmp->next;
	}
	return tmp;
}

void Insert(const char* key, HashTable H)
{
	int index = Hash(key, H->TableSize);
	List tmp = (List)malloc(sizeof(struct ListNode));
	tmp->Element = (char*)malloc(sizeof(char));
	strcpy(tmp->Element, key);
	List node = H->TheList[index];
	while(node->next != NULL)
	{
		node = node->next;
	}
	node->next = tmp;
	tmp->next = NULL;
}

void Delete(const char* key, HashTable H)
{
	int index = Hash(key, H->TableSize);
	List tmp = H->TheList[index]->next;
	List tmp1;
	while(tmp != NULL && !strcmp(tmp->Element,key))
	{
		tmp = tmp->next;	
	} 
	tmp1 = FindPrev(key, H->TheList[index], H);
	tmp1->next = tmp->next;
	tmp->next = NULL;
	free(tmp);
}

List FindPrev(const char* key, List L, HashTable H)
{
	int index = Hash(key, H->TableSize);
	List tmp = L;
	while(tmp != NULL && !strcmp(tmp->next->Element,key))
	{
		tmp = tmp->next;
	}
	return tmp;
}

void PrintHash(HashTable H)
{
	int n = H->TableSize, i = 0;
	List tmp;
	while(i < n)
	{
		printf("TheList[%d] -> ", i); 
		tmp = H->TheList[i];
		if(tmp->next == NULL)
			printf("NULL\n");
		else
		{
			tmp = tmp->next;
			while(tmp->next != NULL)
			{
				printf("%s -> ",tmp->Element);
				tmp = tmp->next;
			}
			printf("%s -> NULL\n",tmp->Element);
		}
		i++;
	}
}
