#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct Node 
{
    int value;
    struct Node* next;
} Node;


int pop(Node* top)
{
    int val = top->value;

    Node *new_top;
    new_top->value = top->next->value;
    new_top->next = top->next->next;
    top = new_top;

    return val;
}

void push(int value, Node* top)
{
    Node* new_top;
    new_top->value = value;
    new_top->next = top;

    top = new_top;
}

int peek(Node* top) 
{
    return top->value;
}

int isEmpty(Node* top)
{
    if (top == NULL) return true;
    return false;
}
