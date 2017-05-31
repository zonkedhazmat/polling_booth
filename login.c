#include<stdio.h>
#include<string.h>

#define MAX_ACCOUNT 20

struct Login{
char name[MAX_ACCOUNT];
char pass[MAX_ACCOUNT];
};


int main(void)
{
	struct Login ad={"alexdonov","yayc"};
	struct Login am={"anh","123"};
	struct Login g={"georgina","222"};
	struct Login h={"harry","23524"};
	struct Login k={"kalist","list"};
	struct Login admin;

	
	printf("\nWelcome!\n");
	printf("Please login\n");
	printf("Username: ");
	scanf("%s", admin.name);

	if (strcmp(admin.name,ad.name)==0)
	{
		printf("Password: ");
		scanf("%s", admin.pass);

		if (strcmp(admin.pass,ad.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
	
	else if (strcmp(admin.name,am.name)==0)
	{
		printf("Password: ");
		scanf("%s", admin.pass);

		if (strcmp(admin.pass,am.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
	
	else if (strcmp(admin.name,g.name)==0)
	{
		printf("Password: ");
		scanf("%s", admin.pass);

		if (strcmp(admin.pass,g.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
	
	else if (strcmp(admin.name,h.name)==0)
	{
		printf("Password: ");
		scanf("%s", admin.pass);

		if (strcmp(admin.pass,h.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		else
		{
			printf("Wrong username or password\n\n");
		}
	}
	
	else if (strcmp(admin.name,k.name)==0)
	{
		printf("Password: ");
		scanf("%s", admin.pass);

		if (strcmp(admin.pass,k.pass)==0)
		{
			printf("Login Successful\n\n");
		}
		else
		{
			printf("Wrong username or password\n\n");
		}
