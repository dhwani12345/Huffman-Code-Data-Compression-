/*
Program : This code will encode and decode the text which is present in "file.txt"
            The code will automatically make the two file
            One will be "encode.txt" which will have binary string
            Second will be "decode.txt" which will decode the binary string to give back the original string
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#define HEIGHT 1
#define size 100

//structure for Queue, binary tree, Linked List
struct node
{
   int num;
   char data;
   int height;
   //pointers
   struct node* left;
   struct node* root;
   struct node* right;
   struct node* ptr;
   struct node* next;
};

//structure for decoding the encoded file
struct node_decode
{
    char dec_data;
    char dec_add[20];
    struct node_decode* link;

}*beg,*end;

//function for creating a new node
struct node* Get_Node(int val, char val_data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = val_data;
    new_node->num = val;
    new_node->height = HEIGHT;

    return new_node;
}

//function for determining height of the AVL tree while insertion
int Tree_GetHeight(struct node* root)
{
    if(!root)
        return 0;
    else
        return root->height;
}

//Function to get balancing factor of the tree
int Get_BalHeight(struct node* root)
{
   if(!root)
        return 0;
   return
        (Tree_GetHeight(root->left) - Tree_GetHeight(root->right));
}

//Function for returning the maximum height among the 2 passed
int max(int a, int b)
{
   return (a > b) ? a : b;
}

//Function for rotating the subtree towards left
struct node* Rotate_AVL_Left(struct node* root)
{
    struct node* right = root->right;
    struct node* left = right->left;
    //perform rotation
    right->left = root;
    root->right = left;
    //update heights of the rotated nodes
    root->height = max(Tree_GetHeight(root->left), Tree_GetHeight(root->right)) + 1;
    right->height = max(Tree_GetHeight(right->left), Tree_GetHeight(right->right)) + 1;
    //return new root
    return right;
}


//Function for rotating the subtree towards right
struct node* Rotate_AVL_Right(struct node* root)
{
    struct node* left = root->left;
    struct node* right = left->right;
    //perform rotation
    left->right = root;
    root->left = right;
    //update heights of the rotated nodes
    root->height = max(Tree_GetHeight(root->left), Tree_GetHeight(root->right)) + 1;
    left->height = max(Tree_GetHeight(left->left), Tree_GetHeight(left->right)) + 1;
    //return new root
    return left;
}

//function for inserting node into AVL Tree
struct node* Insert_AVL(struct node* root, int val, char val_data)
{
    //normal insertion
    if(!root)
    {
         struct node* new_node = Get_Node(val,val_data);
         return new_node;
    }

   if(root->num > val)
        root->left = Insert_AVL(root->left, val, val_data);
   else
        root->right = Insert_AVL(root->right, val, val_data);
   //update height of root
    root->height = max(Tree_GetHeight(root->left), Tree_GetHeight(root->right)) + 1;
   //check for balancing
    int bal = Get_BalHeight(root);
   //left-left case
    if(bal > 1 && root->left->num > val)
    {
        root = Rotate_AVL_Right(root);
    }
   //right-right case
    else if(bal < -1 && root->right->num < val)
    {
        root = Rotate_AVL_Left(root);
    }
   //left-right case
   else if(bal > 1 && root->left->num < val)
   {
        root->left = Rotate_AVL_Left(root->left);
        root = Rotate_AVL_Right(root);
   }
   //right-left case
   else if(bal < -1 && root->right->num > val)
   {
        root->right = Rotate_AVL_Right(root->right);
        root = Rotate_AVL_Left(root);
   }
   return root;
}

//function for inorder traversal of the AVL tree
void Inorder_AVL(struct node* root)
{
    if(!root)
    {
        return;
    }
    //calling functions
    Inorder_AVL(root->left);
    Insert_Queue(root->num,root->data);
    Inorder_AVL(root->right);
}

//initializing the pointers as NULL
struct node* front=NULL;
struct node* rear=NULL;
struct node* temp_front=NULL;
struct node* right = NULL;
struct node* left = NULL;
struct node* ptr = NULL;
struct node* root = NULL;

//global Decleration
int arr[size], count_enc[size];
int cnt_enc=-1;
int top=0,inum,temp1,temp2,len,count_dec=-1, len;
char str_dec[5000], cnt_dec[5000]="", output[5000]="";

//main method
void main()
{
    //file pointer (File that is to be compressed)
    FILE *fp;

    //decleration of local variables and arrays
    int len2, i, j, k, alpha_len,cnt, flag,flag1=0,counter=-1,n;
    int freq[5000];                                                    //freq - array for storing frequency of all characters
    char str[5000], temp_str[5000],char_freq[5000];                    //str - array for storing all characters in the file
                                                                       //temp_str - array for storing all unique characters in the file
    //reading the file                                                 //char_freq - array for storing frequency of all unique characters
    fp = fopen("file.txt", "r");

    if(fp)
    {
        fscanf(fp, "%[^\n]", str);
        strcpy(str_dec,str);
        printf("\nYour String is :: %s", str);
    }
    else
        printf("File does not exist!");

    len = strlen(str);

    struct node* root = NULL;

    printf("\nYour string length is :: %d\n", len);
    printf("\nNumber of bits before encoding :: %d\n", len*8);

    //computation of frequency of each character
    for(i=0;i<len;i++)
    {
        cnt=1,flag=0;
        for(j=i+1;j<=len;j++)
        {
            if(str[i]!='\0')
            {
                flag1++;
                if(str[i] == str[j])
                {
                    temp_str[i] = str[i];
                    cnt++;
                    str[j]='\0';                 //elements that repeat are made null
                }
            }
        }
        if(cnt>=1 && str[i]!='\0')
        {
            temp_str[i] = str[i];
            if(cnt==1)
            {
                if(str[i]!='\0')
                {
                    counter++;
                    freq[counter]=cnt;
                    char_freq[counter]=str[i];
                    root= Insert_AVL(root,freq[counter], char_freq[counter]);
                }
            }
            else if(cnt>1 )
            {
                if(str[i]!='\0')
                {
                    counter++;
                    freq[counter]=cnt;
                    char_freq[counter]=str[i];
                    //all unique characters are inserted into the AVL tree
                    root= Insert_AVL(root,freq[counter], char_freq[counter]);
                }
            }
        }
    }
    printf("\n---------------------------------------------\n");
    printf("\nFrequency of characters ::\n");

    for(i=0;i<=counter;i++)
    {
         printf("\nFrequency of %c is %d",char_freq[i],freq[i]);
    }
    printf("\n");
    printf("\n---------------------------------------------\n");

    //calling function Inorder_AVL(root)
    Inorder_AVL(root);
    //calling function Display_Queue()
    Display_Queue();
    //calling function Make_Tree()
    Make_Tree();

    printf("\n Encoded File is: %s",cnt_dec);
    printf("\n Number of bits after encoding: %d",strlen(cnt_dec));
    printf("\n---------------------------------------------\n");

    //calling of the function encode_decode()
    encode_decode();

    //file for storing the encoded data
    FILE *enc_f;
    enc_f = fopen("encode.txt", "w");
    fprintf(enc_f, "Encoded data :: %s", cnt_dec);
    fclose(enc_f);

    //file for storing the decoded data
    FILE *dec_f;
    dec_f = fopen("decode.txt", "w");
    fprintf(dec_f, "Decoded data :: %s", output);
    fclose(dec_f);

}

//function for measuring the size of the queue
int Queue_Size()
{
    int cnt=0;
    struct node* temp;
    temp = front;

    while(temp!=NULL)
    {
         cnt++;
         temp=temp->next;
    }
    return cnt;
}


//funtion for Insertion of nodes into the queue
void Insert_Queue(int num , char data)
{
    struct node* temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->left = NULL;
    temp->right=NULL;

    //queue is empty
    if(front==NULL && rear==NULL)
    {
        front=rear=temp;
        temp->num = num;
        temp->data = data ;
        temp->next = NULL;
    }

    else if(rear != inum)
    {
        temp->num=num;
        rear->next=temp;
        temp->data = data ;
        temp->next=NULL;
        rear=temp;
    }
    printf("\nInserted into queue: ");
    printf("\nFrequency :: %d\t",temp->num);
    printf("Character :: %c\t\n",temp->data);
}


//function for displaying the queue
void Display_Queue()
{
    printf("\n---------------------------------------------\n");
    struct node *temp;
    temp = front;
    int cnt = 0;

    if(front == NULL)
    {
        printf("Queue is empty!!!");
    }

    while(temp!=NULL)
    {
        printf("\nFrequency :: %d, Data :: %c ", temp->num, temp->data);
        temp = temp->next;
        cnt++;
        printf("\n");
    }
    printf("\n");
    printf("size of the queue is %d\n",cnt);
}

//function for deleting the queue elements
void Delete_Queue()
{
    struct node* temp;
    temp_front=front;

    if(front->next!=NULL)
    {
        temp_front=temp_front->next;
        front=NULL;
        front=temp_front;
    }
    else
    {
        free(front);
        front=NULL;
        rear=NULL;
    }
}

//function for construction of the final tree
void Make_Tree()
{
    printf("\n---------------------------------------------\n");
    printf("\nSteps for making tree :: \n");

    int cnt;
    struct node* temp, *ptr1, *ptr2;

    cnt = Queue_Size();

    while(cnt!=1)
    {
        temp=(struct node*)malloc(sizeof(struct node));
        temp->left=(struct node*)malloc(sizeof(struct node));
        temp->right=(struct node*)malloc(sizeof(struct node));
        root=(struct node*)malloc(sizeof(struct node));

        temp->num = front->num + front->next->num ;
        temp->left = front;
        temp->right = front->next;
        temp->left->data = front->data ;
        temp->right->data = front->next->data ;
        temp->data = '$';
        int flag = 0;

        for(ptr1 = front, ptr2=ptr1->next; ptr2!=NULL ; ptr1=ptr1->next, ptr2=ptr2->next)
        {
            if(temp->num < ptr2->num)
            {
                flag = 1;
                ptr1->next = temp;
                temp->next = ptr2;
                break;
            }
        }

        if(flag==0)
        {
            rear->next=temp;
            rear=temp;
            root=rear;
            rear->next=NULL;
        }
        //when a new node is created the front two nodes are deleted
        Delete_Queue();
        Delete_Queue();
        Display_Queue();
        cnt--;
    }
    printf("\n---------------------------------------------\n");
    printf("\nInorder Traversal\n");
    Inorder_Tree(root);
    printf("\n");
    Data_Encode(root, arr, top);
    String_Compare(len);
}


//function for inorder traversal of the final tree
void Inorder_Tree(struct node* temp)
{
    if(temp->left!=NULL)
        Inorder_Tree(temp->left);

    printf("%d  ", temp->num);

    if(temp->right!=NULL)
        Inorder_Tree(temp->right);
}

//function to check if the given node is leaf node
int isLeaf(struct node* root)
{
    return !(root->left) && !(root->right) ;
}

//Function for encoding the data i.e assigning 0 to left child and 1 to right child
void Data_Encode(struct node* root, int arr[], int top)
{
    //if the left child of the root node exists
    if (root->left)
    {
        arr[top] = 0;
        Data_Encode(root->left, arr, top + 1);
    }
    //if the right child of the root node exists
    if (root->right)
    {
        arr[top] = 1;
        Data_Encode(root->right, arr, top + 1);
    }
    //if the node is the leaf node
    if (isLeaf(root))
    {
        printf("\n%c: ", root->data);
        //calling the function Leaf_Traversal for assigning the node its character and the encoded value
        Leaf_Traversal(arr, top, root->data);
    }
}

//function for determining the encode value of the node and assigning it its character
void Leaf_Traversal(int arr[], int num, char data)
{
    int i;
    char str1[10]="";
    char stemp[20]="";
    for (i = 0; i < num; ++i)
    {
		printf("%d", arr[i]);
		sprintf(str1,"%d",arr[i]);
        count_enc[++cnt_enc] = arr[i];
        strcat(stemp,str1);
    }

    decode_Queue(stemp,data);
    printf("\n");
}

//Function for decoding the elements back to the original string
void decode_Queue(char dec_add[],char dec_data)
{
    struct node_decode* temp;
    temp=(struct node*)malloc(sizeof(struct node));
    int i,l;
    if(beg==NULL && end==NULL)
    {
        l = strlen(dec_add);
        for(i=0; i<len; i++)
        {
            temp->dec_add[i] = dec_add[i];
        }
        temp->dec_data = dec_data;
        temp->link = NULL;
        beg=end=temp;
    }
    else if(end != inum)
    {
        l = strlen(dec_add);
        for(i=0; i<len; i++)
        {
            temp->dec_add[i] = dec_add[i];
        }
        end->link=temp;
        temp->dec_data = dec_data;
        temp->link=NULL;
        end=temp;
    }
}

//Function is used for comparing the encoded string with the original string
void String_Compare(int len)
{
    struct node_decode* ref;

    int i;
    printf("\n\n---------------------------------------------\n");
    for(i=0;i<len;i++)
    {
        ref=beg;
        while(ref!=NULL)
        {
            if(str_dec[i]==ref->dec_data)
            {
                printf("\n%c - %s",ref->dec_data,ref->dec_add);
                strcat(cnt_dec,ref->dec_add);
            }
            ref=ref->link;
        }
    }
    int lnum=0;
    lnum = strlen(cnt_dec);
    printf("\n\n---------------------------------------------\n");
    decode_tree(root, cnt_dec, lnum);
}

//Function is used for assigning 0 to the left node and 1 to the right node
void decode_tree(struct node* root, char array[], int length)
{
    int i, j=0;
    struct node* point;
    point = root;
    printf(" Decoded file   : ");
    for(i=0; i<length; i++)
    {
        if(array[i]=='1')
        {
            point = point->right;
            if(isLeaf(point))
            {
                printf("%c", point->data);
                output[j] = point->data;
                j++;
                point=root;
            }
        }
        else
        {
            point = point->left;
            if(isLeaf(point))
            {
                printf("%c", point->data);
                output[j] = point->data;
                j++;
                point=root;
            }
        }
    }
}


//Function is used for calculating the percentage of the compression
void encode_decode()
{
    float temp;
    int a,b;
    a=len*8;
    b=strlen(cnt_dec);
    temp=((a-b)*100)/a;
    printf("Percentage of compression: %f",temp);
    printf("\n\n---------------------------------------------\n");

}

