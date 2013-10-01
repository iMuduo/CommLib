/**********************************************************************/
/*   Copyright (C) Muduo,2013-2014                                    */
/*   FileName              : tree.c                                   */
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
#include "tree.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

tTreeNode *_tTreeNode(tTreeNode *this)
{
	this->left=NULL;
	this->right=NULL;
	this->data=NULL;
	return this;
}
tTree *_tTree(tTree *this,void *cmp,void *iterator)
{
	this->cmp=cmp;
	this->iterator=iterator;
	this->root=NULL;
	return this;
}
tTreeData *InsertData(tTree *this,tTreeData *data,int size)
{
	tTreeNode *root=this->root;
	tTreeNode *node=new(tTreeNode);
	node->data=malloc(size);
	memcpy(node->data,data,size);

	while (root!=NULL)
	{
		if (this->cmp(root->data,data)>=0 && root->left!=NULL)
			root=root->left;
		else if(this->cmp(root->data,data)<0 && root->right !=NULL)
			root=root->right;
		else break;
	}
	if (root==NULL)
		this->root=node;
	else if(this->cmp(root->data,data)>=0)
		root->left=node;
	else
		root->right=node;
	return  node;
}
tTreeData *DeleteData(tTree *this,void *find)
{
	tTreeNode *parent=this->root,*goal,*replaceParent,*replace;
	if(parent==NULL) return NULL;
	while(parent!=NULL)
	{
		if(this->cmp(parent->data,find)>0 && parent->left!=NULL)
		{
			if(this->cmp(parent->left->data,find)==0)
			{
				goal=parent->left;
				if(goal->left==NULL)
				{
					parent->left=goal->right;
					return goal->data;
				}
				else if(goal->left->right==NULL)
				{
					goal->data=goal->left->data;
					goal->left=goal->left->left;
					return goal->data;
				}
				else
				{
					replace=replaceParent=goal->left->right;
					while (replaceParent->right!=NULL)
					{
						replace=replaceParent->right;
						if (replace->right==NULL)
							break;
						replaceParent=replace;
					}
					if(replace==replaceParent)
						goal->left->right=replace->left;
					else
						if(replace->left==NULL)
							replaceParent->right=NULL;
						else
							replaceParent->right=replace->left;
					goal->data=replace->data;
					return goal->data;
				}
			}
			parent=parent->left;
		}
		else if (this->cmp(parent->data,find)<0 && parent->right!=NULL)
		{
			if(this->cmp(parent->right->data,find)==0)
			{
				goal=parent->right;
				if(goal->left==NULL)
				{
					parent->right=goal->right;
					return goal->data;
				}
				else if(goal->left->right==NULL)
				{
					goal->data=goal->left->data;
					goal->left=goal->left->left;
					return goal->data;
				}
				else
				{
					replace=replaceParent=goal->left->right;
					while (replaceParent->right!=NULL)
					{
						replace=replaceParent->right;
						if (replace->right==NULL)
							break;
						replaceParent=replace;
					}
					if(replace==replaceParent)
						goal->left->right=replace->left;
					else
						if(replace->left==NULL)
							replaceParent->right=NULL;
						else
							replaceParent->right=replace->left;
					goal->data=replace->data;
					return goal->data;
				}
			}
			parent=parent->left;
		}
	}
	return NULL;
}
tTreeData *UpdateData(tTree *this,tTreeData *newData,int size,void *find)
{
	tTreeNode *parent=this->root;
	while(parent!=NULL)
	{
		if(this->cmp(parent->data,find)>0)
			parent=parent->left;
		else if(this->cmp(parent->data,find)<0)
			parent=parent->right;
		else
			break;
	}
	if (parent!=NULL)
	{
		memcpy(parent->data,newData,size);
		return parent->data;
	}
	return NULL;
}
tTreeData *QueryData(tTree *this,void *find)
{
	tTreeNode *parent=this->root;
	while(parent!=NULL)
	{
		if(this->cmp(parent->data,find)>0)
			parent=parent->left;
		else if(this->cmp(parent->data,find)<0)
			parent=parent->right;
		else
			return parent->data;
	}
	return NULL;
}
void IteratorTree(tTree *this)// ÖÐ¸ù
{
	tStack *stack=new(tStack);
	tTreeNode *parent,*left,*right;
	if(this->root==NULL) return NULL;
	Push(stack,this->root,sizeof(tTreeNode));
	while(stack->count!=0)
	{
		parent=Pop(stack);
		left=parent->left;
		right=parent->right;
		parent->left=parent->right=NULL;

		if(left==NULL && right==NULL)
			this->iterator(parent->data);
		else
		{
			if (right !=NULL)
				Push(stack,right,sizeof(tTreeNode));
			Push(stack,parent,sizeof(tTreeNode));
			if(left!=NULL)
				Push(stack,left,sizeof(tTreeNode));	
		}
	}
	return NULL;
}


typedef struct 
{
	int key;
	char *val;
}tData;
int cmp(tData *curr,tData *find)
{
	return CMP(curr->key,find->key);
}
void iterator(const tData *currData)
{
	printf("%d--%s\n",currData->key,currData->val);
}
main()
{
	tData data;
	char str[100];
	tTree *tree=new(tTree,cmp,iterator);
	while(1)
	{
		scanf("%d",&data.key);
		if(data.key<0) break;
		scanf("%s",str);
		data.val=malloc(strlen(str)+1);
		strcpy(data.val,str);
		InsertData(tree,&data,sizeof(tData));
	}
	IteratorTree(tree);
	while(1)
	{
		scanf("%d",&data.key);
		if(data.key<0) break;
		DeleteData(tree,&data.key);
	}
	IteratorTree(tree);
	system("pause");
}