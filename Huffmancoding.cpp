#include "Huffmancoding.h"

//INPUT the original code into the input array 
//Make sure the input numbers are different. 
void INPUT(int *input, int n)
{
  int i;
  printf("Input the original code: "); 
  for(i=0;i<n;i++)
  {
    scanf("%d",&input[i]); 
  }
}
//Sequence the INPUT code in ascending order and save into the OUTPUT
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
//Build a new node 
int Init_Node(TREE *T,int value)
{
  *T = (TREE)malloc(sizeof(Node));
  if(!(*T)) exit(OVERFLOW);
  (*T)->data = value;
  (*T)->lchild = (*T)->rchild = NULL;
  (*T)->flag = 0;
  return OK;
}
//Generate a new node linked by lts left and right child
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
//Generate the entire huffman tree
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
//Preorder traversal of the binary tree
void PRINT(TREE T)
{
  if(T!=NULL)
  {
    printf("%d,",T->data);
    PRINT(T->lchild);
    PRINT(T->rchild);
  }
}
//Return the depth of the tree
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
//Init the single linked list with a header for storing the encoded binary numbers
/*The encoding process is updated using the list. Once encounting a leaf,the 
  corresponding list is printed and returned to the encoder. */
int Init_List(LIST *L)
{
	(*L) = (LIST)malloc(sizeof(LinkedList));
	if(!(*L))	exit(OVERFLOW);
	//(*L)->data_list = NULL;
	(*L)->next = NULL;
	return OK;
}
//Insert a binary value to the end of the list
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
//Return the length of the list
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
//Print list
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
//Delete the last value of the list
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
//Encoding all the input numbers basd on the breadth search algorithm 
void Encoding_Tree(TREE T,int **encoder)
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
			encoder[t] = (int*)malloc(length*sizeof(int));
			for(j = 0;j<length;j++)
			{
				encoder[t][j] = *point++;
			}
			printf("%d: ",parent[i].data);
			for(int tt = 0;tt<length;tt++)
			{
				printf("%d",encoder[t][tt]);
			}
			printf("\n");
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
//Decoding process.
void Decoding_Tree(TREE T, int buffer_out[])
{
	TREE searchT;
	int bit_count = 0;
	searchT = T;
	while(buffer_out[bit_count] == 0 || buffer_out[bit_count] == 1)
	{
		while(buffer_out[bit_count]==0 && searchT->lchild!=NULL)
		{
				searchT = searchT->lchild;
				if(searchT->lchild==NULL &searchT->rchild==NULL)
				{
					printf("%d ",searchT->data);
					searchT = T;
				}
				bit_count++;
		}
		while(buffer_out[bit_count]==1 && searchT->rchild!=NULL)
		{
				searchT = searchT->rchild;
				if(searchT->lchild==NULL &searchT->rchild==NULL)
				{
					printf("%d ",searchT->data);
					searchT = T;
				}
				bit_count++;
		}
	}
	if(searchT!=T)
	{
		printf("Error!");
	}
	printf("\n"); 
} 

int main()
{
  TREE T;
  int buffer[6];
  int buf_out[6];
  int *Encoder[6];
  int Decoder_input[50];

  INPUT(&buffer[0],6);
  ORDER(&buffer[0], buf_out,6);
  printf("The sequenced code is: ");
  for(int i = 0;i<6;i++)
  {
    printf("%d ",buf_out[i]);
  }
  
  printf("\nThe preoder traversal of the generated Huffman Tree is: ");
  Insert_Tree(&T,buf_out,6);
  PRINT(T);
  
  int depth = Depth_Tree(T);
  printf("\nThe depth of the tree is: %d\n",depth);
  
  printf("The coding result is: \n"); 
  Encoding_Tree(T, Encoder);
  printf("\n");
  
  printf("Input the encoded stream: ");
  int bit,j;
  j = bit = 0;
  while(bit!=-1)
  {
  	scanf("%d",&bit);
  	Decoder_input[j++] = bit;
  }
  printf("The decoded result is: ");
  Decoding_Tree(T, Decoder_input);
  return 0; 
}
