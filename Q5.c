#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
};

int count = 0;

struct node *head = NULL;

void insertion(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->link = NULL;
    if (head == NULL)
    {
        head = newnode;
    }
    else
    {
        struct node *ptr = head;
        while (ptr->link != NULL)
        {
            ptr = ptr->link;
        }
        ptr->link = newnode;
    }
    count++;
}

void delete()
{
    struct node *ptr = head;
    struct node *temp = head->link;
    while (temp->link != NULL)
    {
        temp = temp->link;
        ptr = ptr->link;
    }
    ptr->link = temp->link;
    free(temp);
    count--;
}

void last_3rd_element()
{
    struct node *ptr = head;
    while (ptr->link->link->link != NULL)
    {
        ptr = ptr->link;
    }
    printf("\nThe third last element is: %d\n", ptr->data);
}

void printlist()
{
    struct node *ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->link;
    }
}

int main()
{
    int data;
    FILE *filereader = fopen("file.txt", "r");
    while (fscanf(filereader, "%d", &data) != EOF)
    {
        insertion(data);
    }
    printlist();
    if (count >= 3)
    {
        last_3rd_element();
    }
    else
    {
        printf("3rd last element does not exist!");
    }
    fclose(filereader);
    return 0;
}