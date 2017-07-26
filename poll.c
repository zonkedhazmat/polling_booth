
/*******************************************************************************
List of header files
*******************************************************************************/
#include <stdio.h>
/* Functions Used
 - scanf
 - printf
 - switch
 - fopen
 - fclose
 - fprintf */
#include <string.h>
/* Functions Used
 - strcmp */
#include <stdlib.h>
#include "xor.h"
/* Functions Used
 - xor_encrypt */
#include "HuffmanEncoder.h"
/* Functions Used
 - encode */
#define MAX_NAME_SIZE 11 /*Max number of chars for any strings*/
#define MAX_PREFERENCES 10 /*Max number of preferences for any user*/
#define MAX_USER_LIST 200 /*Max number of users*/
#define KGRN  "\x1B[32m"/*Green Text colour for Debug mode*/
#define KNRM  "\x1B[0m"/*Normal Text colour*/
#define DB_FILE_NAME "tempFile"

#define DEBUG /*Can be commented out to access debug features*/

/*user structure - contains the information for users*/
struct user
{
	char firstName[MAX_NAME_SIZE];
	char lastName[MAX_NAME_SIZE];
	int above[MAX_PREFERENCES];
	/*the users preferences are an array of ints*/
};
typedef struct user user_t;


void printMenu(void);
/*Prints the opening to the program*/
void getString(char* p);
/*Reads a string from the user*/
void voteNow(user_t* lp, int listpos);
/*The main function, creates and stores a user using other functions*/
void printParty(void);
/*Prints the party options for users to choose from*/
void getPrefs(int* p);
/*Gets the users preferences*/
void printPref(int choice, int pos);
/*Prints the users preferences*/
int checkpref(int* p, int position);
/*Checks whether the user has selected the party yet or not*/
void printUserlist(user_t* lp, int listpos);
/*Prints all the data of all the users*/
void printToFile(user_t *lp, int listpos);
/*Saves all the data of all users to the file*/

/*******************************************************************************
Main
*******************************************************************************/
int main(void)
{
	char check[10];
	char* cp = check;
	/*Used to check for additional functions*/
	user_t userlist[MAX_USER_LIST];
	user_t* lp = userlist;
	/*The array of all users struct user_t, and its pointer*/
	int listpos=0;
	/*The amount of users, position in the user array*/
	int runningFlag =1;
	/*Used for exiting the program*/
	#ifdef DEBUG
		printf("%sDebug mode is active%s", KGRN, KNRM);
	#endif
	while (runningFlag == 1)
	{
		printf("\nPlease press enter to continue\n");
		getString(cp);
	/*Generally skipped, to continue with the program, but entering debug
	or exit here, enters debug mode, or exits the program respectively.*/	
		if (strcmp("exit\0",check) == 0)
		{
			runningFlag = 0;
			break;
		}
			printMenu();
			voteNow(lp, listpos);
			/*Creates a new user*/
			listpos++;
			/*Increases the amount of users*/
			#ifdef DEBUG
			printf("%slistpos = %d%s", KGRN, listpos, KNRM);
			#endif	
			/*Debug: listposition is accurate*/
			
	}
return 0;
}


/*******************************************************************************
printMenu
This function prints the initial menu
inputs:
- none
outputs:
- none
*******************************************************************************/
void printMenu(void)
{
	printf("\nWELCOME TO VOTE NOW\n");
	printf("\nA TRIAL DIGITAL VOTING SYSTEM\n\n\n");
	
}


/*******************************************************************************
voteNow
This function creates a user and collects their information before adding
them to the array.
inputs:
- pointer to the array of users
- how many users exist (position in the list)
outputs:
- Does not return anything, but alters arrays based on pointers
*******************************************************************************/
void voteNow(user_t* lp, int listpos)
{	
	int i=0;
	/*Used for various loops*/
	int areyousure=1;	
	/*Used as a flag, if users need to re-enter input*/
	user_t user;
	int* p = user.above;
	/*New user, and its pointer*/
	char* first = user.firstName;
	char* last = user.lastName;
	/*pointers for getString*/
	printf("Please enter your first name>");
	getString(first);
	printf("Please enter your last name>");
	getString(last);
	printf("Hello %s %s,", user.firstName, user.lastName);
	printf("You are voting in the Sydney electorate.\n");
	printParty();
	/*Prints the selection of parties*/
	getPrefs(p);
	/*gets the users input for their preferences, debug features*/
	printf("Your preferences are from highest to lowest as follows:\n");
	for(i=0;i<MAX_PREFERENCES;i++)
	{	
		printf("\n");
		printPref(user.above[i], i);
	}
	/*prints the users preferences*/

	while(areyousure != 0)
	/*Allows for a loop until the user confirms their choices*/
	{
		printf("\nAre you happy with these preferences?\n");
		printf("Enter 1 to confirm. Enter 2 to redo\n");
		scanf("%d", &areyousure);
		while (getchar()!='\n');
		if(areyousure != 1)
		{
			printf("\n");
			printParty();
			getPrefs(p);
			/*if the user was unsure, allows them to redo*/
			printf("Your preferences are"); 
			printf("from highest to lowest as follows:\n");
			for(i=0;i<MAX_PREFERENCES;i++)
			{	
				printf("\n");
				printPref(user.above[i], i);
			}
			/*Prints the user's redone preferences*/
		}
		else
		{
			areyousure = 0;
		}
		/*exits the loop once confirmed*/
	}
	lp[listpos] = user;
	/*assigns the new user, into the userlist array*/
	printf("Thank you for voting\n");
	#ifdef DEBUG
		printUserlist(lp, listpos);
	#endif
	printToFile(lp, listpos);
}


/*******************************************************************************
getString
This function reads user input and stores it as a string.
inputs:
- pointer for where the string is to be stored
outputs:
- Does not return anything, but alters string based on pointers
*******************************************************************************/
void getString(char* p)
{
	char buffer[1];
	int i;
	i=0;
	buffer[0] = '\0';
	while (buffer[0] != '\n')
	/*buffer array to read infinite characters until new line is entered*/
	{
		scanf("%c", &buffer[0]);				
		if (i<MAX_NAME_SIZE)
			{
				p[i] = buffer[0];
				i++;
			}
			/*Only a certain amount of 
			characters are actually stored*/
	}
	p[i-1] = '\0';
	#ifdef DEBUG
			printf("%sstored string is = %s%s", KGRN, p, KNRM);
	#endif	
	/*Null termination is important!*/
}

/*******************************************************************************
printParty
This function prints the available parties to the user.
inputs:
- none
outputs:
- none
*******************************************************************************/
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
	printf("Please make your selection by");
	printf("enetering your preferences in order\n");	
}

/*******************************************************************************
getPrefs
This function reads the preferences input from the user. Debug to skip
inputs:
- pointer to where the preferences will be stored
outputs:
- Does not return anything but alters using pointers and arrays
*******************************************************************************/
void getPrefs(int* p)
{
	char skip ='\0';
	#ifdef DEBUG
	
	{
		printf("%sDEBUG: Enter s here to skip%s\n", KGRN, KNRM);
		scanf("%c", &skip);
		if(skip == 's')
		{
			int j=0;
			for(j=0;j<MAX_PREFERENCES;j++)
			{
				p[j] = j+1;
			}
		}
		else skip = '\0';
	}
	#endif
	/*Debug feature, saves having to input 1-10 every time, 
	defaults in order*/
	if (skip == '\0')
	{
	int i=0;
	for(i=0;i<MAX_PREFERENCES;i++)
		{
			printf(">");
			if (1 != (scanf("%d", &p[i])))
				/*Checks whether input was valid*/
			{
				printf("Error;Integer Expected\n");
				printf("Please make a new choice\n");
				while(getchar() != '\n');
				i--;
			}
			/*Handles non-integer input*/
			else if (checkpref(p, i) != 0)
			{
				printf("Please make a new choice\n");
				i--;
			}
			/*Handles invalid integer input*/
		}
	}
}

/*******************************************************************************
checkpref
This function checks the user's preference input to be valid for data type, 
range, and if it has already been selected.
inputs:
- pointer to the current array of user's preferences
- integer of how many preferences the user has already selected
outputs:
- Returns 1 if there was an error
- Returns 0 if no error
*******************************************************************************/
int checkpref(int* p, int position)
{
	if(MAX_PREFERENCES < p[position] || p[position] <= 0)
	{
		printf("Error;please enter an integer within the range.\n");
		return 1;
		/*returns if error*/
	}
	/*Handles integers outside the expected range*/
	int i=0;
	for(i=0;i<position;i++)
	{
		if (p[position] == p[i])
		{
			printf("Error;you have already selected that party.\n");
			return 1;
			/*returns if error*/
		}
	}
	/*Checks if the user has already selected that party*/
	return 0;
	/*returns if success*/
}

/*******************************************************************************
printUserlist
This function is for debug purposes and prints the preferences for all users
inputs:
- pointer to user list
- integer of amount of users
outputs:
- none
*******************************************************************************/
void printUserlist(user_t* lp, int listpos)
{
	int i=0;
	int j=0;
	for(i=0;i<listpos+1;i++)
	{
		printf("\nUser's First Name: %s\n", lp[i].firstName);
		printf("User's Last Name: %s\n", lp[i].lastName);
		printf("User's Prefs are\n");
		for(j=0;j<MAX_PREFERENCES;j++)
		{	
			printf("%d", lp[i].above[j]);
		}
	}
	/*mostly for debug, goes through the list of users, prints their data*/
}

/*******************************************************************************
printPref
This function is run through a loop and prints the users preferences with 
the labels in order.
inputs:
- the users preference as an int
- the current position in the array of user's preferences
outputs:
- none
*******************************************************************************/
void printPref(int choice, int pos)
{
	switch(choice)
	/*Prints the user's preferences in order, with their labels*/
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

/*******************************************************************************
printToFile
Very similar to printUser, writes the data for all users to a file, then 
compresses and encrypts it.
inputs:
- pointer to the array of users
- the amount of users as an int
outputs:
- none
*******************************************************************************/
void printToFile(user_t* lp, int listpos)
{
	FILE * tempFile = fopen(DB_FILE_NAME, "w");

	int i;
	int j=0;
	for(i=0;i<listpos+1;i++)
	{
		fprintf(tempFile,"%s ", lp[i].firstName);
		fprintf(tempFile,"%s ", lp[i].lastName);
		for(j=0;j<=MAX_PREFERENCES-1;j++)
		{	
			fprintf(tempFile,"%d ", lp[i].above[j]);
		}
		fprintf(tempFile, "\n");
	}
	fclose(tempFile);
	encode();
	xor_encrypt();
	
}


