#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_HASH_TABLE_SIZE 1024
#define MAX_WORD 64

typedef struct item Item;
struct item{
	char word[MAX_WORD];
	Item *next;
};

Item g_hashTable[MAX_HASH_TABLE_SIZE]; 

/*
 * djb2 hash function
 */
static unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c; 

	for(c = 0; str[c]!= '\0'; c++){
		hash = ((hash<<5)+hash) +c; 
	}
	return hash;
}

static void hashInit()
{
	int i;
	
	for(i=0; i< MAX_HASH_TABLE_SIZE; i++)
		memset(g_hashTable, 0 , MAX_HASH_TABLE_SIZE);
}

/*
void printCollision(unsigned long hash)
{
	int index = hash % MAX_HASH_TABLE_SIZE;
	Item* p = g_hashTable[index]->next;
	printf("%d , %lu\n", index, hash);
	printf("%s , \n", g_hashTable[index]->next->word);


	while(p != NULL ){
		printf("%s ", p->word);
		p = p->next;
	}
}
*/

void addItem(char* word)
{
	int index;
	unsigned long h; 
	Item* p;

	//printf("input: %s\n", word);
	h = hash((unsigned char*)word);
	index = h % MAX_HASH_TABLE_SIZE;
	p = &g_hashTable[index];

	while(p != NULL){
		if(p->next == NULL){
			p->next = (Item*)malloc(sizeof(Item));
			strcpy(p->next->word , word);
			p->next->next = NULL;
			break;
		}
		p = p->next;
	}
}

void removeItem(char* word)
{
	int index;
	unsigned long h;
	Item* p;
	Item* prev;

	h = hash((unsigned char*)word);
	index = h % MAX_HASH_TABLE_SIZE;
	prev = &g_hashTable[index];
	p = prev->next;

	while(p != NULL){
		if( !strcmp(word, p->word)){
			//printf("DEBUG %s\n", p->word);
			prev->next = p->next;
			//printf("DEBUG %s, %s\n", p->word, prev->word);
			free(p);
			break;
		}
		else {
			prev = p;
			p = p->next;
		}
	}
}

void printHashTable()
{
	int i;
	Item* p;

	for(i =0; i < MAX_HASH_TABLE_SIZE; i++){
		p = g_hashTable[i].next;
		
		if (p == NULL)
			continue;
		printf("%p ", p);
		while(p != NULL){
			printf("%s ", p->word);
			p = p->next;
		}
		printf("\n");
	} 
}

int main()
{
	hashInit();

	addItem("hello");
	addItem("hello2");
	addItem("hello3");
	addItem("hello4");
	addItem("hello5");
	addItem("o5");
	printHashTable();
	removeItem("hello4");
	printHashTable();

	return 0;
}
