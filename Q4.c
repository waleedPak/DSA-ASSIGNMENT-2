#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    struct node *prev;
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void addNode(int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}

void deleteNode()
{
    if (tail == NULL) 
    {
        return;
    }
    else if (head == tail)
    {
        free(head);
        head = NULL;
        tail = NULL;
    }
    else
    {
        tail = tail->prev;
        free(tail->next);
        tail->next = NULL;
    }
}

void addNodeIndex(int data, int index)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;

    struct node *ptr = head;
    for (int i = 0; i < index - 1; i++)
    {
        ptr = ptr->next;
        if (ptr == NULL)
        {
            printf("Invalid index\n");
            free(new_node);
            return;
        }
    }

    new_node->prev = ptr;
    new_node->next = ptr->next;
    ptr->next = new_node;
    if (new_node->next == NULL)
    {
        tail = new_node;
    }
    else
    {
        new_node->next->prev = new_node;
    }
}

void deleteNodeIndex(int index)
{
    struct node *ptr = head;
    for (int i = 0; i < index - 1; i++)
    {
        ptr = ptr->next;
        if (ptr == NULL)
        {
            printf("Invalid index\n");
            return;
        }
    }

    if (index == 1) 
    {
        head = ptr->next;
        head->prev = NULL;
    }
    else if (ptr->next == NULL) 
    {
        ptr->prev->next = NULL;
        tail = ptr->prev;
    }
    else 
    {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
    }

    free(ptr);
}

void printList()
{
    struct node *ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main()
{
    int data, index;
    FILE *fileReader = fopen("myFile.txt", "r");
    char operation[20];

    while (fscanf(fileReader, "%s", operation) != EOF)
    {
        if (strcmp(operation, "Add") == 0)
        {
            fscanf(fileReader, "%d", &data);
            addNode(data);
        }
        else if (strcmp(operation, "Delete") == 0)
        {
            deleteNode();
        }
        else if (strcmp(operation, "AddIndex") == 0)
        {
            fscanf(fileReader, "%d %d", &index, &data);
            addNodeIndex(data, index);
        }
        else if (strcmp(operation, "DeleteIndex") == 0)
        {
            fscanf(fileReader, "%d", &index);
            deleteNodeIndex(index);
        }
        else if (strcmp(operation, "Print") == 0)
        {
            printList();
        }
        else
        {
            printf("Invalid operation: %s\n", operation);
        }
    }

    fclose(fileReader);

    return 0;
}   