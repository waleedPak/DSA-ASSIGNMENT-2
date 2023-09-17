#include <stdio.h>
#include <stdlib.h>

struct node
{
    int id;
    int amount;
    struct node *next;
};

struct node *head = NULL;

void add_transaction(int id, int amount)
{
    struct node *new_node = malloc(sizeof(struct node));
    new_node->id = id;
    new_node->amount = amount;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        struct node *curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}

void delete_fraud_trans(int fraudulent_transaction_id)
{
    if (head == NULL)
    {
        return;
    }
    if (head->id == fraudulent_transaction_id)
    {
        struct node *temp = head;
        head = head->next;
        free(temp);
        return;
    }
    struct node *curr = head;
    while (curr->next != NULL && curr->next->id != fraudulent_transaction_id)
    {
        curr = curr->next;
    }
    if (curr->next != NULL)
    {
        struct node *temp = curr->next;
        curr->next = temp->next;
        free(temp);
    }
}

void print_transactions()
{
    struct node *ptr = head;
    while (ptr != NULL)
    {
        printf("Transaction ID: %d  Transaction Amount: %d\n", ptr->id, ptr->amount);
        ptr = ptr->next;
    }
}

int main()
{
    FILE *fp;
    fp = fopen("file.txt", "r");
    int num_trans;
    int num_fraud_trans;
    fscanf(fp, "%d", &num_trans);
    fscanf(fp, "%d", &num_fraud_trans);

    int transaction_id;
    int transaction_amount;
    int fraudulent_transaction_id;

    for (int i = 0; i < num_trans; i++)
    {
        fscanf(fp, "%d", &transaction_id);
        fgetc(fp);
        fscanf(fp, "%d", &transaction_amount);
        add_transaction(transaction_id, transaction_amount);
    }

    for (int i = 0; i < num_fraud_trans; i++)
    {
        fscanf(fp, "%d", &fraudulent_transaction_id);
        delete_fraud_trans(fraudulent_transaction_id);
    }

    print_transactions();

    fclose(fp);
    return 0;
}