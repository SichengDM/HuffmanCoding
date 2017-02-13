/***************************
内容：Huffman coding and decoding  
文件名：Huffmancoding.h
日期：2016年2月12号 
****************************/

#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define ERROR 0
#define OK 1

typedef struct Node
{
  int data;
  struct Node *lchild;
  struct Node *rchild;
  int flag;
}Node;
typedef Node* TREE;

typedef struct LinkedList
{
	int data_list;
	struct LinkedList *next;
}LinkedList;
typedef LinkedList* LIST;

void INPUT(int *input, int n);
void ORDER(int *input, int output[],int n);

int  Init_Node(TREE *T,int value);
TREE Create_Tree(TREE *T1, TREE *T2);
void Insert_Tree(TREE *T, int *output, int n);
void PRINT(TREE T);

int Depth_Tree(TREE T);
int Init_List(LIST *L);
int Create_List(LIST *L, int value);
int List_length(LIST L);
int* List_Print(LIST L);
LIST Delete_List_value(LIST *L);

void Encoding_Tree(TREE T,int **encoder);
void Decodint_Tree(TREE T, int buffer_out[]);

#endif
