
//
// Created by Антон on 19.04.2022.
//

#ifndef CALCULUS_STACKS_H
#define CALCULUS_STACKS_H
struct NodeInt{
    float value;
    NodeInt* next;
};
struct NodeChar{
    char value;
    NodeChar* next;
};
struct NodeVariable{
    NodeChar* name;
    float value;
    NodeVariable* next;
};
struct NodeExpression{
    char expr[256];
    NodeExpression* next;
};
void pushInt(float value,NodeInt*& stack);
float popInt(NodeInt*& stack);
float topInt(NodeInt* stack);
void pushChar(char value,NodeChar*& stack);
char popChar(NodeChar*& stack);
char topChar(NodeChar* stack);
int lenchar(NodeChar* stack);
int equalstack(NodeChar* stack1,NodeChar* stack2);
void pushVariable(NodeChar* name,float value,NodeVariable*& stack);
float inarr(NodeChar* name,NodeVariable* stack);
#endif //CALCULUS_STACKS_H