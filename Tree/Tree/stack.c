#include "stack.h"
#include <malloc.h>
#include <string.h>

tStackData *_tStackData(tStackData *this)
{
	this->data=NULL;
	this->next=NULL;
	return this;
}
tStack *_tStack(tStack *this)
{
	this->count=0;
	this->stack=NULL;
	return this;
}
void *Push(tStack *this,void *newData,int size)
{
	tStackData *stackData=new(tStackData);
	stackData->data=malloc(size);
	memcpy(stackData->data,newData,size);
	
	stackData->next=this->stack;
	this->stack=stackData;
	this->count++;

	return newData;
}
void *Pop(tStack *this)
{
	void *data;
	if(this->count==0)
		return NULL;
	data=this->stack->data;
	this->stack=this->stack->next;
	this->count--;
	return data;
}
void *Peek(tStack *this)
{
	if(this->count==0)
		return NULL;
	return this->stack->data;
}