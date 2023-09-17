#include <stdio.h>
#include <stdlib.h>

int count = 0;

struct node
{
    int customer_no;
    struct node *link;
};

struct node *head = NULL;

void insertion(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->customer_no = data;
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

void insertion_sort()
{
    struct node *temp1 = head->link;
    while (temp1 != NULL)
    {
        struct node *temp2 = head;
        while (temp2 != temp1)
        {
            if (temp2->customer_no > temp1->customer_no)
            {
                int temp = temp1->customer_no;
                temp1->customer_no = temp2->customer_no;
                temp2->customer_no = temp;
            }
            else
            {
                temp2 = temp2->link;
            }
        }
        temp1 = temp1->link;
    }
}

float median(){
    struct node *curr = head;
    int mid = count/2;
    if(count%2 == 0){
        for(int i=1;i<mid;i++){
            curr = curr->link;
        }
        float median = (curr->customer_no + curr->link->customer_no)/2.0;
        return median;
    }
    else{
        for(int i=1;i<=mid;i++){
            curr = curr->link;
        }
        return curr->customer_no;
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
    int data;
    FILE *filereader = fopen("file.txt", "r");
    while(fscanf(filereader, "%d", &data) != EOF)
    {
        insertion(data);
        insertion_sort();
        float is_median = median();
        printf(" Median : %.1f\n",is_median);
    }
    fclose(filereader);
    return 0;
}