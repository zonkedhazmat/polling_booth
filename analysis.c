#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_SIZE 11
#define DB_FILE_NAME "tempFile"

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
struct count
{
    int pref1;
    int p1count;
    struct node_count *next;
};
typedef struct count count_t;

void count(user_t *user, count_t **occur )
void readFile();
void display(user_t *userp);

int main(void)
{
	user_t *userp = NULL;
	count_t *occur =NULL;
	user_t *userp;
	userp = NULL;
	userp = malloc(sizeof(user_t));
	FILE * tempFile = fopen(DB_FILE_NAME, "r");
	while (EOF != fscanf(tempFile,"%s %s %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d ", userp -> firstName, userp -> lastName,
		&userp -> pref1,
		&userp -> pref2,
		&userp -> pref3,
		&userp -> pref4,
		&userp -> pref5,
		&userp -> pref6,
		&userp -> pref7,
		&userp -> pref8,
		&userp -> pref9,
		&userp -> pref10))
	{
		printf("success\n");
	}

	fclose(tempFile);
}
void display(user_t *userp)
{
    printf("%s", userp->firstName);
    printf(" %s \n", userp->lastName);
    printf("preference 1: %d ", userp -> pref1);
    ??????????????????????????????
}
void countingTheVotes(user_t *user, count_t **occur)
{
	user_t *check;
	count_t *temp, *prev;

	p = userp;
	while (check != NULL)
	{
		temp = *occur
	}
}
