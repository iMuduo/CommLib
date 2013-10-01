#ifndef _STACK_H
#define _STACK_H
#include "selfdef.h"


typedef struct stackData
{
	void *data;
	struct tStack *next;
}tStackData;

typedef struct
{
	int count;
	tStackData *stack;
}tStack;

tStackData *_tStackData(tStackData *this);
tStack *_tStack(tStack *this);
void *Push(tStack *this,void *data,int size);
void *Pop(tStack *this);
void *Peek(tStack *this);
#endif

