/*
 * C Program to Find Number of Occurences of All Elements in a Linked List 
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME_SIZE 11
/*struct user
{
    int num;
    struct node *next;
};*/
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
 
int main()
{
    struct user *userp = NULL;
    struct count *head = NULL;
    printf("Votes:\n");
    showvotes(userp);
    occur(userp, &head);
    showcount(head);
    freeupuser(&userp);
    freeupcount(&head);
 
    return 0;
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
