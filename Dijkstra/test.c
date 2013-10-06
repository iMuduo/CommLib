#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

#define SP ", .;" 
main()
{
	int x,y,vertex,*result;
	char input[1000],*num;
	tGraph *graph;
	printf("input vertex count of your gragdddp:")   ;
	scanf("%d",&vertex);

	graph=CreateGraph(vertex);

	printf("input your graph use matrix \n");
	for (x=0;x<vertex;x++)
	{
		scanf("%s",input);
		num=strtok(input,SP);
		y=0;
		while(num!=NULL)
		{
			if(isdigit(num[0])) SetVertex(graph,x,y,atoi(num));
			num=strtok(NULL,SP);
			y++;
		}
	}
	for (x=0;x<vertex;x++)
		for(y=0;y<vertex;y++)
			printf("%d ",GetVertex(graph,x,y)),y==vertex-1?printf("\n"):0;
	
	result=CalcShortestPath(graph,0,vertex-1);
	x=0;
	if (result!=NULL)
	{
		while (result[x]!=vertex-1)
			printf("%d-->",result[x++]);
		printf("%d\n",result[x]);
	}
	else
		printf("no way!\n");
	system("pause");
}