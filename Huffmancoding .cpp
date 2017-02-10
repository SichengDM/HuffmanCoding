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

/*void INPUT(int *input, int n);
void ORDER(int *input, int output[],int n);
int  Init_Node(TREE *T,int value);
void Insert_Tree(TREE *T, int *output, int n);
void Encoding_Tree(TREE T,int *encoder);
TREE Create_Tree(TREE *T1, TREE *T2);
void PRINT(TREE T);
int Depth_Tree(TREE T);*/

void INPUT(int *input, int n)
{
  int i;
  
  for(i=0;i<n;i++)
  {
    scanf("%d",&input[i]);
  }
  /*for(i=0;i<n;i++)
  {
    printf("%d,",*--input);
  }*/
}

void ORDER(int *input, int output[],int n)
{
  int i,j;
  int temp,point;
  for(i=n;i>=2;i--)
  {
    for(j=n-2;j>=(n-i);j--)
    {
      if(input[j+1]<input[j])
      {
        temp = input[j];
        input[j] = input[j+1];
        input[j+1] = temp;
      }
    }
  }
  for(i = 0;i<n;i++)
  {
    output[i] = input[i];
  }
}

int Init_Node(TREE *T,int value)
{
  *T = (TREE)malloc(sizeof(Node));
  if(!(*T)) exit(OVERFLOW);
  (*T)->data = value;
  (*T)->lchild = (*T)->rchild = NULL;
  (*T)->flag = 0;
  return OK;
}

TREE Create_Tree(TREE *T1, TREE *T2)
{
  TREE temp;
  temp = (TREE)malloc(sizeof(Node));
  temp->data = (*T1)->data + (*T2)->data;
  temp->lchild = (*T1);
  temp->rchild = (*T2);
  temp->flag = 0;
  return temp;
}

void Insert_Tree(TREE *T, int *output, int n)
{
  TREE min1,min2,temp_tree,new_snode;
  int i = 0;
  int j, temp_data,locate_j;
  locate_j = 0;
  {
    Init_Node(&min1,output[i++]);
    Init_Node(&min2,output[i++]);
    (*T) = new_snode = Create_Tree(&min1,&min2);
  }
  while(i<n)
  {
    if(i==locate_j)
	{
		min1 = temp_tree;
	}
	else
	{
		Init_Node(&min1,output[i]);
	}
	if((i+1)==locate_j)
	{
		min2 = temp_tree;
	}
	else
	{
		Init_Node(&min2,output[i+1]);
	}
    
	//Init_Node(&min1,output[i]);
	//Init_Node(&min2,output[i+1]); 
	
	if(new_snode->data <= min1->data)
	{
		(*T) = Create_Tree(&new_snode, &min1);
		new_snode = (*T);
		//printf("%d,",(*T)->data);
	}
	else if((new_snode->data > min1->data && new_snode->data <= min2->data)|| i==(n-1))
	{
		(*T) = Create_Tree(&min1, &new_snode);
		new_snode = (*T);
		//printf("%d,",(*T)->data);
	}
	else
	{
		(*T) = Create_Tree(&min1, &min2);
		j = i+1;
		output[j] = new_snode->data;
		temp_tree = new_snode;
		
		while(j<n-1 && output[j] > output[j+1])
		{
			temp_data = output[j];
			output[j] = output[j+1];
			output[j+1] = temp_data;
			j++;
		}
		locate_j = j;
		new_snode = (*T);
		//printf("%d,",(*T)->data);
	}
	i++;	
  }
}

void PRINT(TREE T)
{
  if(T!=NULL)
  {
    printf("%d,",T->data);
    PRINT(T->lchild);
    PRINT(T->rchild);
  }
}

int Depth_Tree(TREE T)
{
	int depth = 0;
	if(T!=NULL)
	{
		int Llength = Depth_Tree(T->lchild);
		int Rlength = Depth_Tree(T->rchild);
		//循环嵌套，当最后一次T==NULL时，直接返回depth，而没有定义Llength
		//和Rlength，所以下面一行求depth的值语句必须在if条件内。 
		depth = ((Llength>=Rlength)? Llength:Rlength)+1;
	}
	return depth;
}

int Init_List(LIST *L)
{
	(*L) = (LIST)malloc(sizeof(LinkedList));
	if(!(*L))	exit(OVERFLOW);
	//(*L)->data_list = NULL;
	(*L)->next = NULL;
	return OK;
}
int Create_List(LIST *L, int value)
{
	LIST p;
	p = (LIST)malloc(sizeof(LinkedList));
	if(!(p))	exit(OVERFLOW);
	p->data_list = value;
	p->next = NULL;
	if(*L)
	{
		(*L)->next = p;
		(*L) = p;
	}	
	return OK;	
}

int List_length(LIST L)
{
	int length=0;
	while(L->next)	
	{
		length+=1;
		L = L->next;
	}
	return length;
}

int* List_Print(LIST L)
{
	LIST P;
	int length = List_length(L);
	int list_show[length],*prt,i;
	prt = list_show;
	P = L;
	i = 0;
	while(P->next)
	{
		P = P->next;
		list_show[i++] = P->data_list;
	}
	return prt;
} 

LIST Delete_List_value(LIST *L)
{
	LIST P,Q;
	Q = *L;
	if((*L)->next !=NULL)
	{
		P = (*L)->next;
		while(P->next)
		{
			Q = P;
			P = P->next;
		}
		free(P);
		Q->next = NULL;
	} 
	return Q;
}

void Encoding_Tree(TREE T,int encoder[][6])
{
	Node parent[6];
	LIST buffer, head;
	int i,j,t;
	int *point;
	
	i = j = t = 0;
	parent[i] = *T;
	Init_List(&buffer);
	head = buffer;
	
	while(i>=0)
	{
		while(parent[i].lchild!=NULL)
		{
			parent[i+1] = *(parent[i].lchild);
			parent[i].lchild = NULL;
			parent[i].flag = 1;
			i++;
			Create_List(&buffer,0);
		}
		if(parent[i].rchild==NULL && parent[i].flag == 0)
		{
			point = List_Print(head);
			int length = List_length(head);
			for(j = 0;j<length;j++)
			{
				encoder[t][j] = *point++;
			}
			t++;
			i--;
			buffer = Delete_List_value(&head);
		}
		if(parent[i].rchild==NULL && parent[i].flag == 1)
		{
			i--;
			buffer = Delete_List_value(&head);
		}
		else if(parent[i].rchild!=NULL)
		{
			parent[i+1] = *(parent[i].rchild);
			parent[i].rchild = NULL;
			i++;
			Create_List(&buffer,1);
		}		
	}		
}

int main()
{
  TREE T;
  int buffer[6];
  int buf_out[6];
  int Encoder[6][6];

  INPUT(&buffer[0],6);
  ORDER(&buffer[0], buf_out,6);
  printf("排序后的源码为：");
  for(int i = 0;i<6;i++)
  {
    printf("%d",buf_out[i]);
  }
  
  printf("\n生成的霍夫曼树经过前序遍历为：");
  Insert_Tree(&T,buf_out,6);
  PRINT(T);
  
  int depth = Depth_Tree(T);
  printf("\n霍夫曼树的深度为：%d\n",depth);
  
  //测试线性单链表
 /* LIST TEST,start;
  Init_List(&TEST);
  start = TEST;
  Create_List(&TEST, 6);
  int length = List_length(start); */
  
  Encoding_Tree(T, Encoder);
  return 0; 
}
