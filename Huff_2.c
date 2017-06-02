#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct Node
{
    char character;
    int frequency;
    struct Node *left;
    struct Node *right;
}*temp = NULL, *node1 = NULL, *node2 = NULL;


struct Node *newNode(char character, int frequency)
{
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
    temp->left = NULL;
    temp->right = NULL;
    temp->character = character;
    temp->frequency = frequency;
return temp;
}

struct Node *newNodeWithChilds(char character, int frequency,struct Node *leftNode,struct Node *rightNode)
{
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
    temp->left = leftNode;
    temp->right = rightNode;
    temp->character = character;
    temp->frequency = frequency;
    return temp;
}

void sort(struct Node **minheapArray, int size)
{
    int i,j;
    for (i = 0; i < size; i++)
    {
        for ( j = i + 1; j < size; j++)
        {
            if ((minheapArray[i]->frequency > minheapArray[j]->frequency))
            {
                struct Node* temp = minheapArray[i];
                minheapArray[i] = minheapArray[j];
                minheapArray[j] = temp;
            }
        }
    }
}

void printArray(int ints[], int len)
{
    int i;
    for (i=0; i<len; i++)
    {
        printf("%d ", ints[i]);
    }
    printf("\n");
}

int isLeaf(struct Node* root)
{
    return !(root->left) && !(root->right) ;
}

void printCodes(struct Node* root, int array[], int top,int **characters)
{
/* Assign 0 to left edge and recur */
    int i;
    if (root->left!=NULL)
    {
        array[top] = 0;
        printCodes(root->left, array, top + 1,characters);
    }
    if (root->right!=NULL)
    {
        array[top] = 1;
        printCodes(root->right, array, top + 1,characters);
    }

    if (isLeaf(root))
    {
        int index=(int)root->character;
        for(i=0;i<top;i++)
        {
            characters[index][i]=array[i];
        }
        printf("\n%c -> ",(char)index);
        for(i=0;i<top;i++)
        {
            printf("%d",characters[index][i]);
        }
        characters[index][top]=-1;
        printf("\n");
    }
}

struct Node *buildHuffManTree(char characters[], int frequency[], int size)
{
    struct Node *minheapArray[size];
    struct Node *root;
    int i;
    for (i = 0; i < size; i++) {
    minheapArray[i] = newNode(characters[i], frequency[i]);
}

if (size >= 2)
{
    while (minheapArray[1]->frequency != 999999 )
    {
    root = newNode('$',(minheapArray[0]->frequency + minheapArray[1]->frequency));
    root->left = newNodeWithChilds(minheapArray[0]->character,minheapArray[0]->frequency
,minheapArray[0]->left,minheapArray[0]->right);
    root->right = newNodeWithChilds(minheapArray[1]->character,minheapArray[1]->frequency
,minheapArray[1]->left,minheapArray[1]->right);
/*printf(" minheapArray[1] %c->%d", minheapArray[1]->character, minheapArray[1]->frequency); */
    minheapArray[0] = newNodeWithChilds(root->character,root->frequency,root->left,root->right);
    minheapArray[1]->right=NULL;
    minheapArray[1]->left=NULL;
    minheapArray[1]->character='$';
    minheapArray[1]->frequency = 999999;
    sort(minheapArray, size);
    }
/*root=minheapArray[0]; */
}

return root;
}

void decode(struct Node* root, int *encodeString)
{
    int i;
    struct Node* temp = root;
    for (i=0;encodeString[i]!=-1;i++)
    {
    if (encodeString[i]==1)
    {
        temp = temp -> right;
    }
else
    {
        temp = temp -> left;
    }

    if (isLeaf(temp))
    {
    printf("%c",temp->character);
    temp =root;
    }

    }

}

int main()
{
/*printf("\nStarted Main"); */
    char arr[] = { 'h', 'a', 'i', 'l', 'o','e'};
    int freq[] = { 5, 9, 12, 13, 16,34};
    int size = sizeof(arr);
    int a=(int)arr[0];
    printf("Test : %d",a);
/*printf("\nStarted Main %d",size); */

    struct Node *start = buildHuffManTree(arr, freq, size);
    int path[100];
    printf("\nfinal");
    int i,j,s, *encoded[256];
    for (i=0; i<256; i++)
    encoded[i] = (int *)malloc(100 * sizeof(int));
    printCodes(start,path,0,encoded);
    char plainString[] = { 'h', 'a', 'i', 'h', 'e', 'l', 'l', 'l', 'o', '\0' };
    printf("\n String before encoding(%lu) : %s",sizeof(plainString),plainString);

    int encodedString[500]={-1};

    i=0;
    s=0;
/*printf("Test %d ->",(int)plainString[i]);
for(int j=0;j<sizeof(encoded[(int)plainString[i]])-1;j++){
printf("%d",encoded[(int)plainString[i]][j]);
}*/
    while(plainString[i]!='\0')
    {
        printf("\nsize of %c - > %lu ->",plainString[i],sizeof(encoded[(int)plainString[i]]));
        for(j=0;encoded[(int)plainString[i]][j]!=-1;j++)
        {
            encodedString[s]=encoded[(int)plainString[i]][j];
            s++;
        }
/*for(int j=0;encoded[(int)plainString[i]][j]!=-1;j++){
encodedString[s]=encoded[(int)plainString[i]][j];
s++;
}*/
        i++;
    }
    encodedString[s]=-1;

    printf("\n Encoded string: ");
    for(j=0;encodedString[j]!=-1;j++)
    {
        printf("%d",encodedString[j]);
    }
    printf("\n Decoded string: ");
    decode(start,encodedString);
    printf("\n");
return 0;
}
