#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Macro determines max username and password length */
#define MAX_ACCOUNT 20

/* struct used to store login info */
struct Login{
char name[MAX_ACCOUNT];
char pass[MAX_ACCOUNT];
};

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
	struct user *next;
	/*the users preferences are an array of ints*/
};
struct count
{
    int pref1;
    int pref1count;
    struct count *next;
};

void occur(struct user *, struct count **);
void freeupuser(struct user **);
void freeupcount(struct count **);
void showvotes(struct user *);
void showcount(struct count *);
void readFile();
void displaypref1(struct user *userp);
void login(void);
int main(void)
{
	login();
	struct user *userp = NULL;
	struct user *temp = NULL;
	int i;
	/*count_t *occur =NULL;*/
	userp = malloc(sizeof(struct user));
	FILE * tempFile = fopen(DB_FILE_NAME, "r");
	for (i = 0; i < 4; i++)
	{
		temp =  (struct user *)malloc(sizeof(struct user));
		fscanf(tempFile,"%s %s %d %d %d %d %d %d %d %d %d %d \n", temp -> firstName, temp -> lastName,
		&temp -> pref1,
		&temp -> pref2,
		&temp -> pref3,
		&temp -> pref4,
		&temp -> pref5,
		&temp -> pref6,
		&temp -> pref7,
		&temp -> pref8,
		&temp -> pref9,
		&temp -> pref10);
		if (userp == NULL)
		{
			userp = temp;
			temp -> next = NULL;
		}
		else
		{
			temp -> next = userp;
			userp =temp;
		}
		printf("success\n");

	}
	printf("success final\n");
    
    struct count *head = NULL;
    printf("Votes:\n");
    showvotes(userp);
    occur(userp, &head);
    showcount(head);
    freeupuser(&userp);
    freeupcount(&head);
	fclose(tempFile);
	return 0;
}
void displaypref1(struct user *userp)
{
    printf("%s", userp->firstName);
    printf(" %s \n", userp->lastName);
    printf("preference 1: %d ", userp -> pref1);
}

/* login function
   Only allows authorised users to access database */
void login(void)
{
	/* hard coded login accounts. To be compared against admin to confirm 
	    correct login details */
	struct Login ad={"alexdonov","yayc"};
	struct Login am={"anh","123"};
	struct Login g={"georgina","222"};
	struct Login h={"harry","23524"};
	struct Login k={"kalist","list"};
	/* temporary storage for user input of username and password */
	struct Login admin;

	/* Gets username from user */
	printf("\nWelcome!\n");
	printf("Please login\n");
	printf("Username: ");
	/* input username stored in admin struct */
	scanf("%s", admin.name);

	/* admin username compared to hard coded usernames and appropriate 
	   if loop will then open */
	
	/* Alexa Donovan */
	if (strcmp(admin.name,ad.name)==0)
	{
		/* Gets password from user */
		printf("Password: ");
		/* input password stored in admin */
		scanf("%s", admin.pass);

		/* If password is correct prints 'Login Successful' */
		if (strcmp(admin.pass,ad.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		/* If password is wrong prints 'Wrong username or password */
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
	
	/* Anh Minh Tran */
	else if (strcmp(admin.name,am.name)==0)
	{
		/* Gets password from user */
		printf("Password: ");
		/* input password stored in admin */
		scanf("%s", admin.pass);

		/* If password is correct prints 'Login Successful' */
		if (strcmp(admin.pass,am.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		/* If password is wrong prints 'Wrong username or password */
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
	
	/* Georgina Szanyel */
	else if (strcmp(admin.name,g.name)==0)
	{
		/* Gets password from user */
		printf("Password: ");
		/* input password stored in admin */
		scanf("%s", admin.pass);

		/* If password is correct prints 'Login Successful' */
		if (strcmp(admin.pass,g.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		/* If password is wrong prints 'Wrong username or password */
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
	
	/* Harry Soiland */
	else if (strcmp(admin.name,h.name)==0)
	{
		/* Gets password from user */
		printf("Password: ");
		/* input password stored in admin */
		scanf("%s", admin.pass);

		/* If password is correct prints 'Login Successful' */
		if (strcmp(admin.pass,h.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		/* If password is wrong prints 'Wrong username or password */
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
	
	/* Kalist Uremovic */
	else if (strcmp(admin.name,k.name)==0)
	{
		/* Gets password from user */
		printf("Password: ");
		/* input password stored in admin */
		scanf("%s", admin.pass);

		/* If password is correct prints 'Login Successful' */
		if (strcmp(admin.pass,k.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		/* If password is wrong prints 'Wrong username or password */
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
}
void occur(struct user *head, struct count **result)
{
    struct user *userp;
    struct count *temp, *prev;
 
    userp = head;
    while (userp != NULL)
    {
        temp = *result;
        while (temp != NULL && temp->pref1 != userp->pref1)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)
        {
            temp = (struct count *)malloc(sizeof(struct count));
            temp->pref1 = userp->pref1;
            temp->pref1count = 1;
            temp->next = NULL;
            if (*result != NULL)
            {
                prev->next = temp;
            }
            else
            {
                *result = temp;
            }
        }
        else
        {
            temp->pref1count += 1;
        }
        userp = userp->next;
    }
}
 
void showvotes(struct user *userp)
{
    while (userp != NULL)
    {
        printf("%d\t", userp->pref1);
        userp = userp->next;
    }
    printf("\n");
}
 
void showcount(struct count *userp)
{
    while (userp != NULL)
    {
        printf("    %d\t\t%d\n", userp->pref1, userp->pref1count);
        userp = userp->next;
    }
}
 
void freeupuser(struct user **head)
{
    struct user *temp = *head;
    *head = (*head)->next;
    while ((*head) != NULL)
    {
        free(temp);
        temp = *head;
        (*head) = (*head)->next;
    }
}
 
void freeupcount(struct count **head)
{
    struct count *temp = *head;
    *head = (*head)->next;
    while ((*head) != NULL)
    {
        free(temp);
        temp = *head;
        (*head) = (*head)->next;
    }
}
