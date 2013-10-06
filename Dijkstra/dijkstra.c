#include "dijkstra.h"
/* x >y */
tGraph *CreateGraph(int vertexCount)
{
	int x=0,y;
	tGraph *graph=(tGraph *)malloc(sizeof(tGraph));
	graph->count=vertexCount;
	graph->graph=(int **)malloc(sizeof(int **)*graph->count);
	for (x=0;x<graph->count;x++)
		graph->graph[x]=(int *)malloc(sizeof(int)*graph->count);
	for (x=0;x<vertexCount;x++)
		for(y=0;y<vertexCount;y++)
			graph->graph[x][y]=MAX;
	return graph;
}
void SetVertex(tGraph *graph,int x,int y,int cost)
{
	if(x==y)
		printf("error path:%d-->%d \n",x,y);
	if(x!=y && graph->graph[x][y]==MAX && graph->graph[y][x]==MAX)
	{
		graph->graph[x][y]=cost;
		graph->graph[y][x]=cost;
	}
 }
int GetVertex(tGraph *graph,int x,int y)
{
	return graph->graph[x][y];
}
void MergPath(int *des ,int *source,int len,int vertex)
{
	int i;
	for (i=0;i<len+1;i++)
		des[i]=source[i];
	des[i]=vertex;
}
int *CalcShortestPath(tGraph *graph,int from ,int to)
{
	int i,shortest;
	tVector *v=(tVector *)malloc(sizeof(tVector)* graph->count);
	for (i=0;i<graph->count;i++)
	{
		v[i].count=1;
		v[i].path=(int *)malloc(sizeof(int)*graph->count);
		v[i].path[0]=from;
		v[i].path[1]=i;
		v[i].cost=GetVertex(graph,from,i);
		v[i].shortest=FALSE;
	}
	while(1)
	{
		shortest=-1;
		for (i=0;i<graph->count;i++)
		{
			if(v[i].cost==MAX || i==from) 
				continue;
			if(v[i].shortest==FALSE && shortest==-1)
				shortest=i;
			else if(v[i].shortest==FALSE && v[i].cost<v[shortest].cost)
				shortest=i;	
		}
		if(shortest==-1 || v[shortest].path[v[shortest].count] ==to) break;
		else v[shortest].shortest=TRUE;
		for (i=0;i<graph->count;i++)
		{
			if (v[i].shortest==FALSE && i!=from &&GetVertex(graph,shortest,i)+v[shortest].cost < v[i].cost )
			{
				MergPath(v[i].path,v[shortest].path,v[shortest].count,i);
				v[i].count=v[shortest].count+1;
				v[i].cost=GetVertex(graph,shortest,i)+v[shortest].cost;
			}
		}
	}
	if(v[to].cost==MAX) return NULL;
	return v[to].path;
}