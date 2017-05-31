#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT 255
/* A character that is going to be encrypted */
struct Character{
    char data;
    int freq;
    struct Character *left, *right;
};
/* Huffman Tree */
struct Tree{
    int size;
    int capacity;
    struct Character **array;
};
/* Function to create a new node for each input character */
struct Character* newChar(char data, int freq){
    struct Character* temp = 
    (struct Character*) malloc(sizeof(struct Character));
    temp ->left = NULL;
    temp ->right= NULL;
    temp ->data=data;
    temp -> freq= freq;
    return temp;
}
/* Function to create tree with given capacity */

struct Tree* CreateTree(int capacity)
{
    struct Tree* HTree =
    (struct Tree*) malloc(sizeof(struct Tree));
    HTree -> size=0; 
    HTree -> capacity = capacity;
    HTree -> array = 
    (struct Character**)malloc(HTree -> capacity * sizeof(struct Character*));
    return HTree;
}

/*Function to swap location of characters */
void swap(struct Character** a, struct Character** b)
{
    struct Character* t= *a;
    *a= *b;
    *b=t;
}

/* Function to arranging tree */
void Treefy(struct Tree* HTree, int x)
{
    int smallest = x;
    int left= 2 * x + 1;
    int right= 2 * x +2;

    if (left < HTree ->size && 
    HTree->array[left]->freq < HTree->array[smallest]->freq)
    smallest=left;

    if(right < HTree->size &&
    HTree->array[right]->freq < HTree->array[smallest]->freq)
    smallest = right;

    if(smallest != x)
    {
        swap(&HTree->array[smallest], &HTree->array[x]);
        Treefy(HTree, smallest);
    }
}

/*Checking size of Huffman Tree */
int SizeOne(struct Tree* HTree)
{
    return (HTree-> size ==1);
}

/*Extract characters with least freq */
struct Character* extractMin(struct Tree* HTree)
{
    struct Character* temp = HTree->array[0];
    HTree->array[0] = HTree->array[HTree->size - 1];
    --HTree->size;
    Treefy(HTree, 0);
    return temp;
}

/*Create a new slot in tree */
void insert(struct Tree* HTree, struct Character* character)
{
    ++HTree->size;
    int i = HTree->size -1;
    while (i && character->freq < HTree->array[(i-1)/2] -> freq)
    {
        HTree ->array[i] = HTree ->array[(i-1)/2];
        i= (i-1)/2;
    }
    HTree->array[i] = character;
}

/* Function building Tree */
void build(struct Tree* HTree)
{
    int n = HTree->size -1;
    int i;
    for (i = (n-1) / 2; i >= 0; --i)
    Treefy(HTree, i);
}

/* printing array */
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    printf("%d", arr[i]);
    printf("\n");
}

/*Check if node is leaf in tree */
int Leaf(struct Character* root)
{
    return !(root->left) && !(root->right) ;
}

/*Create equal size character slots */
struct Tree* createAndBuild(char data[], int freq[], int size)
{
    struct Tree* HTree = CreateTree(size);
    int i;
    for (i=0; i<size; ++i)
    HTree ->array[i] = newChar(data[i], freq[i]);
    HTree->size = size;
    build(HTree);
    return HTree;
}

/*Main for building HUffman Tree */
struct Character* BuildHuffmanTree(char data[], int freq[], int size)
{
    struct Character *left, *right, *top;
    
    struct Tree* HTree = createAndBuild(data, freq, size);

    while (!SizeOne(HTree))
    {
        left = extractMin(HTree);
        right = extractMin(HTree);
        top = newChar('$', left->freq + right ->freq);
        top ->left = left;
        top -> right = right;
        insert(HTree, top);
    }

    return extractMin(HTree);
}

void print(struct Character* root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        print(root->left, arr, top +1);
    }

    if (root->right)
    {
        arr[top] =1;
        print(root->right, arr, top + 1);
    }

    if(Leaf(root))
    {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

void Huffman(char data[], int freq[], int size)
{
    struct Character* root = BuildHuffmanTree(data, freq, size);
    int arr[MAX_HEIGHT], top =0;
    print(root, arr, top);
}

void Decode(struct Character* root, char *s)
{
    int i;
    int x= sizeof(s);
    char ans= ' ';
    struct Character* temp = root;
    for (i=0; i < x ; i++)
    {
        if (s[i] == '0')
        {
            temp = temp -> left;
        }
        else
        {
            temp = temp -> right;
        }
        if (!temp ->left && !temp -> right)
        {
            ans = ans + temp -> data;
            temp =root;
        }
    }
    printf("%d \n", ans);
} 

/*void Decode(struct Character* root, int* encoded) 
{
    int i;
    struct Character *temp = root;
    for (i = 0; encoded[i] != -1; i++)
    {
        if (temp->data != '$')
        {
            printf("%c", temp->data);
            temp = root;
            continue;
        }
    }
}
*/


int main()
{
    char arr[] = {'?', 'M', '1', 'd', 'e', 'a'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr)/sizeof(arr[0]);
    struct Character *start = BuildHuffmanTree(arr, freq, size);
    int encoded[500]={-1};

   
    Huffman(arr, freq, size);
    printf("\n Decoded string: ");
    Decode(start, encoded);
    return 0;
}
