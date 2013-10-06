#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#define MAX 65535
#define FALSE 0
#define TRUE 1
typedef struct
{
	int **graph;
	int count;
}tGraph;
typedef struct  
{
	int shortest;
	int *path;
	int count;
	int cost;
}tVector;
tGraph *CreateGraph(int vertexCount);
void SetVertex(tGraph *graph,int x,int y,int cost);
int GetVertex(tGraph *graph,int x,int y);
void MergPath(int **des ,int *source,int len,int vertex);
int *CalcShortestPath(tGraph *graph,int form ,int to);
#endif