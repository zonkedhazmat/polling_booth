#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

/*******************************************************************************
List structs - Maintains character and its frequency in a structure
*******************************************************************************/
struct Node 
{
	char character;
        int frequency;
	struct Node * left;
	struct Node * right;
} * temp = NULL, * node1 = NULL, * node2 = NULL;
/* declare the temp, node1 ,node2 so that in lower function, 
just have to initialize*/

/*******************************************************************************
newNode
Function to create a new node without a child
*******************************************************************************/
struct Node * newNode(char character, int frequency) 
{
        struct Node * temp = (struct Node * ) malloc(sizeof(struct Node));
        temp -> left = NULL;
        temp -> right = NULL;
        temp -> character = character;
        temp -> frequency = frequency;
        return temp;
}
/*******************************************************************************
newNodeWithChilds
Function to create a new node with children
*******************************************************************************/
struct Node * newNodeWithChilds(char character, 
int frequency, struct Node * leftNode, struct Node * rightNode) 

{
        struct Node * temp = (struct Node * ) malloc(sizeof(struct Node));
        temp -> left = leftNode;
        temp -> right = rightNode;
        temp -> character = character;
        temp -> frequency = frequency;
        return temp;
}

/*******************************************************************************
sort
Sort the given input array using bubble sort algorithm
*******************************************************************************/
void sort(struct Node ** minheapArray, int size) 
{
        int i = 0;
        int j = 0;
        for (i = 0; i < size; i++) 
        {
                for (j = i + 1; j < size; j++) 
                {
                if ((minheapArray[i]->frequency > minheapArray[j]->frequency)) 
                {
                        struct Node * temp = minheapArray[i];
                        minheapArray[i] = minheapArray[j];
                        minheapArray[j] = temp;
                }
                }
        }
}

/*******************************************************************************
isLeaf
Check if given node is leaf of the tree
*******************************************************************************/
int isLeaf(struct Node * root) 
{
        return !(root -> left) && !(root -> right);
}

/*******************************************************************************
printCodes
generates the individual binary codes of characters from the huffman tree
*******************************************************************************/
void printCodes(struct Node * root, int array[], int top, int * * characters) 
{
        
        /*if node has left node */
	if (root -> left != NULL) 
        {
                array[top] = 0;
                printCodes(root -> left, array, top + 1, characters);
        }
		/*if node has right node */
        if (root -> right != NULL) 
        {
                array[top] = 1;
                printCodes(root -> right, array, top + 1, characters);
        }

		/*if node is a leaf, then its a character */
        if (isLeaf(root)) 
        {
                /*Choose index base on the ascii value */
                int index = (int) root -> character;
                int i = 0;
                for (i = 0; i < top; i++) 
                {
                        characters[index][i] = array[i];
                }
                printf("\n%c -> ", (char) index);

                for (i = 0; i < top; i++) 
                {
                        printf("%d", characters[index][i]);
                }
                characters[index][top] = -1;
                printf("\n");
        }
}

/*******************************************************************************
buildHuffManTree
Main function to build Huffman Tree
*******************************************************************************/
struct Node * buildHuffManTree(char characters[], int frequency[], int size) 
{

        struct Node * minheapArray[size];
        struct Node * root;
        int i = 0;
		
		/*initial array contains all the characters as individual node
		(in sorted manner - called sorting) */
        for (i = 0; i < size; i++) 
        {
                minheapArray[i] = newNode(characters[i], frequency[i]);
        }
		sort(minheapArray, size);
		
        if (size >= 2) 
        {
	/*during every iteration the first 2 nodes (as they are minimum) 
	will be taken and formed and kept in first node and second node
 	will be harcoded This will be either an already clubbed node, 
	or a new node. And the added array nodes will be sorted again
	This will be repeated untill we get one root node at the top
	i.e a second default node during the start of the iteration */
                while (minheapArray[1] -> frequency != 999999) 
		{
                        root = newNode('$',
                                (minheapArray[0] -> frequency 
				+ minheapArray[1] -> frequency));
                        root -> left = newNodeWithChilds(minheapArray[0] 
			-> character, minheapArray[0] -> frequency, 
			minheapArray[0] -> left, minheapArray[0] -> right);

                        root -> right = newNodeWithChilds(minheapArray[1] 
			-> character, minheapArray[1] -> frequency, 
			minheapArray[1] -> left, minheapArray[1] -> right);
                       
			minheapArray[0] = newNodeWithChilds(root -> character, 
			root -> frequency, root -> left, root -> right);

                        minheapArray[1] -> right = NULL;
                        minheapArray[1] -> left = NULL;
                        minheapArray[1] -> character = '$';
                        minheapArray[1] -> frequency = 999999;
                        sort(minheapArray, size);
                }
               
        }
		/* Free the other pointers, good practice */
		for (i = 1; i < size; i++) 
                {
                free(minheapArray[i]);
                }
        return root;
}

/*******************************************************************************
readFile
Function to read input file
*******************************************************************************/
char * readFile(char * inputFile) 
{
        FILE * file = fopen(inputFile, "r");
        char * characters;
        size_t n = 0;
        int c;

        if (file == NULL)
                return NULL;

        characters = malloc(32000);

        while ((c = fgetc(file)) != EOF) 
        {
                characters[n++] = (char) c;
        }
        characters[n] = '\0';

        return characters;
}

/*******************************************************************************
writeTree
Function to write tthe Huffman tree for decoding
*******************************************************************************/
void writeTree(struct Node * root, FILE * fp)
{
	if(isLeaf(root))
        {
		fprintf(fp,"1");
		fprintf(fp,"%c",root->character);
	}
	else
	{
		fprintf(fp,"0");
		writeTree(root->left,fp);
		writeTree(root->right,fp);
	}
}

/*******************************************************************************
Main
*******************************************************************************/
int encode() 
{
        char * characters;
        characters = readFile("tempFile");
        printf("\nRead from file : %s\n\n", characters);
        int i = 0;
        int j = 0;

        int index, frequency[256] = {0};
        for (index = 0; characters[index] != '\0'; index++) 
        {
                frequency[(int) characters[index]]++;
        }
        i = 0;
        int size = 0;
        for (index = 0; index < 256; index++) 
        {
                if (frequency[index] != 0) 
                {
                        size++;
                }
        }
        char arr[size];
        int freq[size];
        printf("\nCharacter   Frequency\n");
        for (index = 0; index < 256; index++) 
        {
                if (frequency[index] != 0) 
                {
                        arr[i] = (char) index;
                        freq[i] = frequency[index];
                        printf("%5c%10d\n", index, frequency[index]);
                        i++;
                }
        }

        arr[i] = '\0';
       
        struct Node * start = buildHuffManTree(arr, freq, size);
        int path[100];
        int * encoded[256];

        for (i = 0; i < 256; i++)
                encoded[i] = (int * ) malloc(100 * sizeof(int));
        printCodes(start, path, 0, encoded);

        printf("\n String before encoding : %s", characters);

        int encodedString[32000] = {-1};

        int s = 0;

        FILE *fp;
		char output[]="EncodedOutput.txt";
		fp=fopen(output,"w");
        for (index = 0; characters[index] != '\0'; index++) 
        {
                for (j = 0; encoded[(int) characters[index]][j] != -1; j++) 
                {
                        encodedString[s] = encoded[(int) characters[index]][j];
                        s++;
                }
        }
		
        encodedString[s] = -1;
        printf("\n Encoded string: ");
        for (j = 0; encodedString[j] != -1; j++) 
        {
                printf("%d", encodedString[j]);
				fprintf(fp,"%d",encodedString[j]);
        }
		fclose(fp);
        printf("\n");
		FILE *fp1;
		char output1[]="HuffManTree.txt";
		fp1=fopen(output1,"w");
		writeTree(start,fp1);
		fclose(fp1);

        return 0;
}
