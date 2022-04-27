//
// Created by Антон on 19.04.2022.
//
#include "stacks.h"
#include <stdio.h>
#include <stdlib.h>
void pushInt(float value,NodeInt*& stack){
    NodeInt* NewNode;
    NewNode=(NodeInt*)malloc(sizeof(NodeInt));
    NewNode->value=value;
    if(stack){
        NewNode->next=stack;
        stack=NewNode;
    }
    else {
        stack = NewNode;
        NewNode->next = NULL;
    }
}
float popInt(NodeInt*& stack){
    float temp = stack->value;
    stack=stack->next;
    return temp;
}
float topInt(NodeInt* stack){
    return stack->value;
}
void pushChar(char value,NodeChar*& stack){
    NodeChar* NewNode;
    NewNode=(NodeChar*)malloc(sizeof(NodeChar));
    NewNode->value=value;
    if(stack){
        NewNode->next=stack;
        stack=NewNode;
    }
    else {
        stack = NewNode;
        NewNode->next = NULL;
    }
}
char popChar(NodeChar*& stack){
    char temp = stack->value;
    stack=stack->next;
    return temp;
}
char topChar(NodeChar* stack){
    return stack->value;
}
int lenchar(NodeChar* stack){
    int len=0;
    while(stack){
        ++len;
        stack=stack->next;
    }
    return len;
}
int equalstack(NodeChar* stack1,NodeChar* stack2){
    if(lenchar(stack1)!= lenchar(stack2))
        return 0;
    else{
        while(stack1){
            if(stack1->value!=stack2->value){
                return 0;
            }
            stack1=stack1->next;
            stack2=stack2->next;
        }
        return 1;
    }
}
void pushVariable(NodeChar* var_name,float value,NodeVariable*& stack){
    NodeVariable* NewNode;
    NewNode=(NodeVariable*)malloc(sizeof(NodeVariable));
    NewNode->name=var_name;
    NewNode->value=value;
    if(stack){
        NewNode->next=stack;
        stack=NewNode;
    }
    else {
        stack = NewNode;
        NewNode->next = NULL;
    }
}
float inarr(NodeChar* name,NodeVariable* stack){
    while(stack){
        if(equalstack(name,stack->name)){
            return stack->value;
        }
        stack=stack->next;
    }
    return -1;
}