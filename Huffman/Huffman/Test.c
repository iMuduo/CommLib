#include "Huffman.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

main()
{
	int i;
	tHuffList *list=CreateHuffList();
	tHuffEm em,*result;
	time_t t=time(NULL);
	em.val=NULL;
	srand(t);
	for (i=0;i<100;i++)
	{
		em.cost=rand();
		em.val=prependChar(em.val,33+i);
		PutHuffNode(list,&em);
		em.val=NULL;
	}
	result=CalcHuffCode(list);
	for (i=0;i<100;i++)
	{
		printf("cost: %-6d ----- HuffCode:%-20s\n",result[i].cost,result[i].val);
	}
	system("pause");
}