#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_SIZE 11
#define MAX_PREFERENCES 10
#define MAX_USER_LIST 5
/*Defined the amount of preferences the user chooses*/

struct user
{
	char firstName[MAX_NAME_SIZE];
	char lastName[MAX_NAME_SIZE];
	int pref1;
	int pref2;
	int pref3;
	int pref4;
	int pref5;
	int pref6;
	int pref7;
	int pref8;
	int pref9;
	int pref10;
	struct node *next;
	/*the users preferences are an array of ints*/
};
typedef struct user user_t;

struct temp
{
	char firstName[MAX_NAME_SIZE];
	char lastName[MAX_NAME_SIZE];
	int above[MAX_PREFERENCES];
	/*the users preferences are an array of ints*/
};
typedef struct temp temp_t;

void printMenu(void);
void voteNow(int listpos);
void printParty(void);
void printPref(int choice, int pos);
/*Prints the users preferences*/
void getPrefs(int* p);
int checkpref(int* p, int position);
void printUserlist(temp_t templist[], int listpos);

int main(void)
{

	char check[10];
	char exit[5] = "exit";
	char debug[6] = "debug";
	int listpos=0;
		do
		{
			printf("\nPlease press enter to continue\n");
			scanf("%s", check);
			while (getchar()!='\n');
			if (strcmp(debug,check) == 0)
				printf("this is a placeholder\n");
			printMenu();
			voteNow(listpos);
			listpos++;
			
		}while (check != 0);

return 0;
}
void printMenu(void)
{
	printf("\nWELCOME TO VOTE NOW\n");
	printf("\nA TRIAL DIGITAL VOTING SYSTEM\n\n\n");
	
}

void voteNow(int listpos)
{	
	
	user_t * userp = NULL;
	userp = malloc(sizeof(user_t));
	int i;
	int areyousure=5;
	temp_t temp;
	temp_t templist[MAX_USER_LIST];
	int* p = temp.above;
	printf("Please enter your first name>");
	fgets(temp.firstName, sizeof(temp.firstName), stdin);
	fflush(stdin);
	/*char *firstPos;
	if ((firstPos=strchr(temp.firstName, '\n')) != NULL)
    {
    	*firstPos = '\0';
	}*/
	printf("Please enter your last name>");
	fgets(temp.lastName, sizeof(temp.lastName), stdin);
	 fflush(stdin);
	/*char *lastPos;
	if ((lastPos=strchr(temp.lastName, '\n')) != NULL)
    {
    	*lastPos = '\0';
	}*/
	userp = (user_t*) malloc (sizeof(user_t));
	strcpy(userp -> firstName, temp.firstName);
	strcpy(userp -> lastName, temp.lastName);
	printf("\n");
	printf("\n");
	printf("Hello %s %s,\n", userp->firstName, userp->lastName);
	/*
	printf("\n\nSelect from the following options\n");
	printf("1. I am voing above the line\n");
	printf("2. I am voting below the line\n");*/
	printf("You are voting in the Sydney electorate.\n");
	printParty();
	getPrefs(p);


	/*gets the users input. can be done in function, but requires parsing
	- would probably be best as a function, since if they want to redo,
	this would need to be called*/
	printf("Your preferences are from highest to lowest as follows:\n");
	for(i=0;i<=MAX_PREFERENCES;i++)
	{	
		printf("\n");
		printPref(temp.above[i], i);
	}
	/*prints the users preferences*/

	while(areyousure != 0)
	{
		printf("Are you happy with these preferences?\n");
		printf("Enter 1 to confirm. Enter 2 to redo\n");
		scanf("%d", &areyousure);
		while (getchar()!='\n');
		if(areyousure != 1)
		{
			printf("\n");
			printParty();
			getPrefs(p);
			printf("Your preferences are from highest to lowest as follows:\n");
			for(i=0;i<=MAX_PREFERENCES;i++)
			{	
				printf("\n");
				printPref(temp.above[i], i);
			}
		}
		else
		{
			areyousure = 0;
		}
	}
	userp -> pref1 = temp.above[1];
	userp -> pref2 = temp.above[2];
	userp -> pref3 = temp.above[3];
	userp -> pref4 = temp.above[4];
	userp -> pref5 = temp.above[5];
	userp -> pref6 = temp.above[6];
	userp -> pref7 = temp.above[7];
	userp -> pref8 = temp.above[8];
	userp -> pref9 = temp.above[9];
	userp -> pref10 = temp.above[10];
	userp -> next = NULL;
	templist[listpos] = temp;
	printf("Thank you for voting\n");
	printUserlist(templist, listpos);
}

void printParty()
{
	printf("Below are the parties you may choose from:\n");
	printf("1. Labor\n");
	printf("2. Coalition\n");		
	printf("3. Greens\n");
	printf("4. Christian Democrats Party\n");		
	printf("5. Animal Justice Party\n");		
	printf("6. Socialist Allience\n");		
	printf("7. Science Party\n");		
	printf("8. Australian Sex Party\n");		
	printf("9. Sustainable Australia\n");		
	printf("10. Online Direct Democracy\n");	
	printf("Please make your selection by enetering your preferences in order\n");	
}


void getPrefs(int* p)
{
	int i=0;
	for(i=0;i<MAX_PREFERENCES;i++)
		{
			printf(">");
			if (1 != (scanf("%d", &p[i])))
			{
				printf("Error; Integer Expected\n");
				printf("Please make a new choice\n");
				while(getchar() != '\n');
				i--;
			}
			else if (checkpref(p, i) != 0)
			{
				printf("Please make a new choice\n");
				i--;
			}
		}
}

int checkpref(int* p, int position)
{
	if(MAX_PREFERENCES < p[position] || p[position] <= 0)
	{
		printf("Error; please enter an integer within the range.\n");
		return 1;
	}
	int i=0;
	for(i=0;i<position;i++)
	{
		if (p[position] == p[i])
		{
			printf("Error; you have already selected that party.\n");
			return 1;
		}
	}
	return 0;
}

void printUserlist(temp_t templist[], int listpos)
{
	int i=0;
	int j=0;
	for(i=0;i<listpos+1;i++)
	{
		printf("\nUser's First Name: %s", templist[i].firstName);
		printf("\n");
		printf("User's Last Name: %s", templist[i].lastName);
		printf("\n");
		for(j=0;j<=MAX_PREFERENCES-1;j++)
		{	
			printf("%d", templist[i].above[j]);
		}
	}
}

void printPref(int choice, int pos)
{
	switch(choice)
	{
		case 1:
			printf("%d. ", (pos+1));
			printf("Labor");
			break;
		case 2:
			printf("%d. ", (pos+1));
			printf("Coalition");
			break;
		case 3:
			printf("%d. ", (pos+1));
			printf("Greens");
			break;
		case 4:
			printf("%d. ", (pos+1));
			printf("Christian Democrats Party");
			break;
		case 5:
			printf("%d. ", (pos+1));
			printf("Animal Justice Party");
			break;
		case 6:
			printf("%d. ", (pos+1));
			printf("Socialist Allience");
			break;
		case 7:
			printf("%d. ", (pos+1));
			printf("Science Party");
			break;
		case 8:
			printf("%d. ", (pos+1));
			printf("Australian Sex Party");
			break;
		case 9:
			printf("%d. ", (pos+1));
			printf("Sustainable Australia");
			break;
		case 10:
			printf("%d. ", (pos+1));
			printf("Online Direct Democracy");
			break;
	}
}

