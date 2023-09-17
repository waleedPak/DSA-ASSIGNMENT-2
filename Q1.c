#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0;

struct node
{
    struct node *prev;
    int customer_no;
    struct node *link;
};

struct node *head = NULL;
struct node *median = NULL;

void insertion(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->customer_no = data;
    newnode->link = NULL;
    if (head == NULL)
    {
        head = newnode;
        median = head;
        head->prev = NULL;
    }
    else
    {
        struct node *ptr = head;
        while (ptr->link != NULL)
        {
            ptr = ptr->link;
        }
        ptr->link = newnode;
        newnode->prev = ptr;
    }
    if (count % 2 != 0)
    {
        median = median->link;
    }
    count++;
}

void delete()
{
    if (head == NULL)
    {
        return;
    }
    struct node *temp = head;
    if (head->link == NULL)
    {
        head = NULL;
        median = NULL;
        free(temp);
        count--;
        return;
    }
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->prev->link = NULL;
    if (count % 2 != 0)
    {
        median = median;
    }
    else
    {
        median = median->prev;
    }
    count--;
    free(temp);
}

void getmedian(){
    if (head == NULL)
    {
        printf("No customers in the queue.\n");
        return;
    }
    if (count % 2 != 0)
    {
        printf("%d\n", median->customer_no);
    }
    else
    {
        printf("%d,%d\n" , median->customer_no , median->link->customer_no);
    }
}

void printlist()
{
    struct node *ptr = head;
    while (ptr != NULL)
    {
        printf("%d\n", ptr->customer_no);
        ptr = ptr->link;
    }
}

int main()
{
    int customer_no;
    FILE *filereader =  fopen("file.txt" , "r");
    char a[10];
    while(fscanf(filereader, "%s" , a ) != EOF ){
        if (strcmp(a, "ADD") == 0) {
            fscanf(filereader, "%d" , &customer_no);
            insertion(customer_no);
        }
        else if (strcmp(a, "DELETE") == 0) {
            delete();
        }
        else if (strcmp(a, "END") == 0) {
            getmedian();
        }
        else{
            printf("Invalid command\n");
        }
    }
    return 0;
}