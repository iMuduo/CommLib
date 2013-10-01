
#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#pragma warning(disable:4996)
#include <malloc.h>

typedef struct
{
	int cost;
	char *val;
}tHuffEm;

typedef struct HuffNode
{
	tHuffEm em;
	int sgin;
	struct HuffNode *parent;
	struct HuffNode *next;
}tHuffNode;

typedef struct
{
	tHuffNode *head;
	int count;
	tHuffNode **auxiliary;
}tHuffList;

char *prependChar(char *des,char c);
tHuffList *CreateHuffList();
void PutHuffNode(tHuffList *list,tHuffEm *em);
tHuffEm *CalcHuffCode(tHuffList *list);
#endif
