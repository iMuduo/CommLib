/**********************************************************************/
/*   Copyright (C) Muduo,2013-2014                                    */
/*   FileName              : tree.h                                   */
/*   Author                : Muduo                                    */
/*   Module Name           : tree                                     */
/*   Language              : C                                        */
/*   Target Environment    : Any                                      */
/*   Date of First Release : 2013/09/28                               */
/*   Description           : A common tree for all					  */
/**********************************************************************/

/*
 *  Revision Log:
 *	
 *  Create by Muduo,2013/09/28
 * 
 *
 */
#ifndef _TREE_H
#define _TREE_H
#include <stddef.h>
#include "selfdef.h"
#include "stack.h"

typedef void * tTreeData;

typedef struct TreeNode{
	tTreeData data;
	struct TreeNode *left;
	struct TreeNode *right;
}tTreeNode;
tTreeNode *_tTreeNode(tTreeNode *this);

typedef struct Tree
{
	int (*cmp)(const tTreeData currData,const tTreeData operData);
	void (*iterator)(const tTreeData *currData);
	tTreeNode *root;
}tTree;

tTree *_tTree(tTree *this,void *cmp,void *iterator);
tTreeData *InsertData(tTree *this,tTreeData *data,int size);
tTreeData *DeleteData(tTree *this,void *find);
tTreeData *UpdateData(tTree *this,tTreeData *newData,int size,void *find);
tTreeData *QueryData(tTree *this,void *find);
void IteratorTree(tTree *this);
#endif
