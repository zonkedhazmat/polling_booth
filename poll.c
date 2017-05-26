#include <stdio.h>
#define MAX_NAME_SIZE 11
#define MAX_PREFERENCES 10
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
void voteNow(void);
void printParty(void);
void printPref(int choice);
/*Prints the users preferences*/
int getPrefs(int* p);

int main(void)
{
	printMenu();
	voteNow();

return 0;
}
void printMenu(void)
{
	printf("\nWELCOME TO VOTE NOW\n");
	printf("\nA TRIAL DIGITAL VOTING SYSTEM\n\n\n");
}

void voteNow()
{	
	int i;
	int areyousure=5;	
	user_t user;
	printf("Please enter your first name>");
	scanf("%[^\n]%*c", user.firstName);
	printf("Please enter your last name>");
	scanf("%[^\n]%*c", user.lastName);
	printf("Hello %s %s,", user.firstName, user.lastName);
	/*
	printf("\n\nSelect from the following options\n");
	printf("1. I am voing above the line\n");
	printf("2. I am voting below the line\n");*/
	printf("You are voting in the Sydney electorate.\n");
	printf("Below are the parties you may choose from:\n");
	printParty();
	printf("Please make your selection by enetering your preferences in order\n");
	int* p = user.above;
	getPrefs(p);
	

	/*gets the users input. can be done in function, but requires parsing
	- would probably be best as a function, since if they want to redo,
	this would need to be called*/
	printf("Your preferences are from highest to lowest as follows:\n");
	for(i=0;i<=MAX_PREFERENCES;i++)
	{	
		printf("\n>");
		printPref(user.above[i]);
	}
	/*prints the users preferences*/

	while(areyousure != 0)
	{
		printf("Are you happy with these preferences?\n");
		printf("Enter 1 to confirm. Enter 2 to redo\n");
		scanf("%d", &areyousure);
		if(areyousure != 1)
		{
			printf("Please make your selection by enetering your preferences in order\n");
			getPrefs(p);
			printf("Your preferences are from highest to lowest as follows:\n");
			for(i=0;i<=MAX_PREFERENCES;i++)
			{	
				printf("\n>");
				printPref(user.above[i]);
			}
		}
		else
		{
			areyousure = 0;
		}
	}
	printf("Thank you for voting");

	
}
void printParty()
{
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
}


void printPref(int choice)
{
	switch(choice)
	{
		case 1:
			printf("Labor");
			break;
		case 2:
			printf("Coalition");
			break;
		case 3:
			printf("Greens");
			break;
		case 4:
			printf("Christian Democrats Party");
			break;
		case 5:
			printf("Animal Justice Party");
			break;
		case 6:
			printf("Socialist Allience");
			break;
		case 7:
			printf("Science Party");
			break;
		case 8:
			printf("Australian Sex Party");
			break;
		case 9:
			printf("Sustainable Australia");
			break;
		case 10:
			printf("Online Direct Democracy");
			break;
	}
}


int getPrefs(int* p)
{
	int i=0;
	for(i=0;i<MAX_PREFERENCES;i++)
		{
			printf(">");
			scanf("%d", &p[i]);
		}
	return 1;
}
