#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

/*******************************************************************************
List structs - Maintains character and its frequency in a structure
*******************************************************************************/
struct Node {
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
decode
Function to decode the encoded characters
*******************************************************************************/
void decode(struct Node * root, char * encodeString) {
        int i;
        struct Node * temp = root;
		FILE *fp;
		char output[]="DecodedOutput.txt";
		fp=fopen(output,"w");
        for (i = 0; encodeString[i] != '\0'; i++) {

                if (encodeString[i] == '1') {
                        temp = temp -> right;
                } else {
                        temp = temp -> left;
                }

                if (isLeaf(temp)) {
                        printf("%c", temp -> character);
						fprintf(fp,"%c",temp -> character);
                        temp = root;
                }

        }
		fclose(fp);

}

/*******************************************************************************
readFile
Function to read input file
*******************************************************************************/
char * readFile(char * inputFile) {
        FILE * file = fopen(inputFile, "r");
        char * characters;
        size_t n = 0;
        int c;

        if (file == NULL)
                return NULL;

        characters = malloc(1000);

        while ((c = fgetc(file)) != EOF) {
                characters[n++] = (char) c;
        }
        characters[n] = '\0';

        return characters;
}

/*******************************************************************************
readTree
Function to read the Huffman tree for decoding
*******************************************************************************/
struct Node * readTree(FILE * fp){
	int c=fgetc(fp);
	if(c==EOF)
		return NULL;
	if(((char)c)=='1'){
		c=fgetc(fp);
		return newNode(((char)c),0);
	}
	else
	{
		struct Node *leftChild=readTree(fp);
		struct Node *rightChild=readTree(fp);
		return newNodeWithChilds('\0',0,leftChild,rightChild);
	}
}

/*******************************************************************************
Main
*******************************************************************************/
int main() 
{

	FILE *fp1;
	char output1[]="HuffManTree.txt";
	fp1=fopen(output1,"r");
	struct Node *root=readTree(fp1);
	fclose(fp1);
	int path[100];
        int * encoded[256];
        int i;
        for (i = 0; i < 256; i++)
                encoded[i] = (int * ) malloc(100 * sizeof(int));

	printCodes(root, path, 0, encoded);
	char * characters;
	characters = readFile("EncodedOutput.txt");
	printf("\nRead from file : %s\n\n", characters);

	printf("\nDecoded string: ");
	decode(root, characters);
	printf("\n");
        return 0;
}
