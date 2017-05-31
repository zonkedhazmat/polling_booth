#include <stdio.h>
#include <string.h>
#define MAX_NAME_SIZE 11
#define MAX_PREFERENCES 10
#define MAX_USER_LIST 5
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
/*Defined the amount of preferences the user chooses*/

struct user
{
	char firstName[MAX_NAME_SIZE];
	char lastName[MAX_NAME_SIZE];
	int above[MAX_PREFERENCES];
	/*the users preferences are an array of ints*/
};
typedef struct user user_t;


void printMenu(void);
void voteNow(user_t* lp, int listpos, int debugFlag);
void printParty(void);
void printPref(int choice, int pos);
/*Prints the users preferences*/
void getPrefs(int* p, int debugFlag);
int checkpref(int* p, int position);
void printUserlist(user_t* lp, int listpos);

int main(void)
{
	char check[10];
	char exit[5] = "exit\0";
	char debug[6] = "debug\0";
	char buffer[1];
	int listpos=0;
	int i=0;
	int runningFlag =1;
	int debugFlag=0;
	user_t userlist[MAX_USER_LIST];
	user_t* lp = &userlist[listpos];
	

	while (runningFlag == 1)
	{
		i=0;
		printf("\nPlease press enter to continue\n");
		scanf("%c", &buffer[0]);

		while (buffer[0] != '\n')
		{
			while (i<6)
			{
				check[i] = buffer[0];
				i++;
				break;
			}
			scanf("%c", &buffer[0]);
		}
		check[i] = '\0';
		if (strcmp(debug,check) == 0)
		{
			if (debugFlag)
			{
				debugFlag=0;
			}
			else
			{
				debugFlag=1;
				printf("%sDebug activated %s\n", KGRN, KWHT);	
			}

		}
		
		if (strcmp(exit,check) == 0)
		{
			runningFlag = 0;
			break;
		}
			printMenu();
			voteNow(lp, listpos, debugFlag);
			listpos++;
	}
return 0;
}
void printMenu(void)
{
	printf("\nWELCOME TO VOTE NOW\n");
	printf("\nA TRIAL DIGITAL VOTING SYSTEM\n\n\n");
	
}

void voteNow(user_t* lp, int listpos, int debugFlag)
{	
	int i=0;
	int areyousure=5;	
	user_t user;
	int* p = user.above;
	char buffer[1];
	printf("Please enter your first name>");
	while (buffer[1] != '\n')
	{
		scanf("%c", &buffer[1]);									
		if (i<MAX_NAME_SIZE)
			{
				user.firstName[i] = buffer[1];
				i++;
			}
	}
	user.firstName[i-1] = '\0';
	i=0;
	printf("Please enter your last name>");
	while (buffer[0] != '\n')
	{
		scanf("%c", &buffer[0]);									
		if (i<MAX_NAME_SIZE)
			{
				user.lastName[i] = buffer[0];
				i++;
			}
	}
	user.lastName[i-1] = '\0';
	i=0;
	printf("Hello %s %s,", user.firstName, user.lastName);
	/*
	printf("\n\nSelect from the following options\n");
	printf("1. I am voing above the line\n");
	printf("2. I am voting below the line\n");*/
	printf("You are voting in the Sydney electorate.\n");
	printParty();
	getPrefs(p, debugFlag);
	

	/*gets the users input. can be done in function, but requires parsing
	- would probably be best as a function, since if they want to redo,
	this would need to be called*/
	printf("Your preferences are from highest to lowest as follows:\n");
	for(i=0;i<=MAX_PREFERENCES;i++)
	{	
		printf("\n");
		printPref(user.above[i], i);
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
			getPrefs(p, debugFlag);
			printf("Your preferences are from highest to lowest as follows:\n");
			for(i=0;i<=MAX_PREFERENCES;i++)
			{	
				printf("\n");
				printPref(user.above[i], i);
			}
		}
		else
		{
			areyousure = 0;
		}
	}
	lp[listpos] = user;
	printf("Thank you for voting\n");
	printUserlist(lp, listpos);
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


void getPrefs(int* p, int debugFlag)
{
	char skip;
	if (debugFlag == 1)
	{
		
		printf("%sDEBUG: Enter s here to skip%s\n", KGRN, KWHT);
		scanf("%c", &skip);
		if(skip == 's')
		{
			int j=0;
			for(j=0;j<MAX_PREFERENCES;j++)
			{
				p[j] = j+1;
			}
		}
	}
	
	if(debugFlag == 0 || skip != 's')
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


