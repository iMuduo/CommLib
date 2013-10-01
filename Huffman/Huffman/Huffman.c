#include "Huffman.h"
#include <malloc.h>
#include <string.h>

/*prepend char */
char *prependChar(char *des,char c)
{
	int i=0;
	int len=des==NULL ? 0 : strlen(des);
	char *orign=des;
	des=malloc(len+2);
	des[0]=c;
	for (i=1;i<len+1;i++)
		des[i]=orign[i-1];
	des[len+1]='\0';
	return des;
}

tHuffList *CreateHuffList()
{
	tHuffList *list=malloc(sizeof(tHuffList));
	list->head=NULL;
	list->count=0;
	return list;
}
void PutHuffNode(tHuffList *list,tHuffEm *em)
{
	tHuffNode *node=malloc(sizeof(tHuffNode));
	node->em.cost=em->cost;
	node->em.val=malloc(sizeof(em->val)+1);
	strcpy(node->em.val,em->val);
	node->parent=NULL;

	node->next=list->head;
	list->head=node;
	list->count++;
}
tHuffEm *CalcHuffCode(tHuffList *list)
{
	int index=0,i;
	tHuffNode *minest,*miner,*curr,*addNode,*now;
	tHuffEm *result =malloc(list->count*sizeof(tHuffEm)),em;
	list->auxiliary=malloc(list->count*sizeof(tHuffNode *));

	/*construct huff reverse tree*/
	while(index!=list->count-1)
	{
		curr=list->head;
		minest=miner=NULL;
		/* iterate huff node*/
		while(curr!=NULL)
		{
			if(curr->parent==NULL)
			{
				if(miner==NULL || minest==NULL)
				{
					if(minest==NULL)
						minest=curr;
					else if(minest->em.cost>curr->em.cost)
						miner=minest,minest=curr;
					else
						miner=curr;
				}
				else
				{
					if(curr->em.cost < miner->em.cost && curr->em.cost >=minest->em.cost)
						miner=curr;
					else if(curr->em.cost < minest->em.cost)
						miner=minest,minest=curr;
				}
			}
			curr=curr->next;
		}
		/* iterate add node*/
		for (i=0;i<index;i++)
		{
			if(list->auxiliary[i]->parent!=NULL) continue;
			if(miner==NULL || minest==NULL)
			{
				if(minest==NULL)
					minest=list->auxiliary[i];
				else if(minest->em.cost>list->auxiliary[i]->em.cost)
					miner=minest,minest=list->auxiliary[i];
				else
					miner=list->auxiliary[i];
			}
			else
			{
				if(list->auxiliary[i]->em.cost< miner->em.cost && list->auxiliary[i]->em.cost >=minest->em.cost)
					miner=list->auxiliary[i];
				else if(list->auxiliary[i]->em.cost < minest->em.cost)
					miner=minest,minest=list->auxiliary[i];
			}
		}
		/*create new node */
		addNode=malloc(sizeof(tHuffNode));
		addNode->em.cost=minest->em.cost+miner->em.cost;
		addNode->sgin=1;
		addNode->parent=NULL;

		minest->sgin=1;
		miner->sgin=0;
		miner->parent=addNode;
		minest->parent=addNode;

		list->auxiliary[index++]=addNode;
	}
	/*construct result to return*/
	index=0;
	curr=list->head;
	while(curr!=NULL)
	{
		em.val=NULL;
		now=curr;
		em.cost=now->em.cost;
		while(now!=NULL)
		{
			em.val=prependChar(em.val,now->sgin+'0');
			now=now->parent;
		}
		memcpy(result+index++,&em,sizeof(tHuffEm));
		curr=curr->next;
	}
	return result;
}
