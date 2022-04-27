
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stacks.h"
#include <math.h>

int priority(char opertr) {
    if (opertr == '+' || opertr == '-')
        return 1;
    else if (opertr == '*' || opertr == '/')
        return 2;
    else if (opertr == '^')
        return 3;
    else if (opertr == 's')
        return 5;
    else if (opertr == 'c')
        return 5;
    else if (opertr == '!')//ln
        return 5;
    else if (opertr == '$')//sqrt
        return 5;
    else if (opertr == '@')
        return 5;
    else if (opertr == '(')
        return 999;
    else if (opertr == ')')
        return -999;
    else
        return -1;
}

float operation(float num1, float num2, char opertr) {
    switch (opertr) {
        case '+':
            return num1 + num2;
            break;
        case '-':
            return num2 - num1;
            break;
        case '*':
            return num1 * num2;
            break;
        case '/':
            return num2 / num1;
            break;
        case '^': {
            return pow(num2, num1);
        }
            break;
        default:
            return num1;
    }
}
float functions(float num1,char f){
    switch (f) {
        case 's':
            return sin(num1);
            break;
        case 'c':
            return cos(num1);
            break;
        case '$':
            return sqrt(num1);
            break;
        case '!':
            return log(num1);
            break;
        case '@':
            return exp(num1);
            break;
        default:
            return num1;
    }
}
int main() {
    char expr[256];
    gets(expr);
    NodeChar *Operations = NULL;
    NodeInt *Numbers = NULL;
    NodeInt *num = NULL;
    int fl_variable = 0;
    NodeVariable *arr_var = NULL;
    int var_count = 0;
    NodeChar *variable = NULL;
    //Считает число переменных
    for (int i = 0; i < strlen(expr); ++i) {
        if ((expr[i] >= 'a' && expr[i] <= 'z') || ((expr[i] >= 'A' && expr[i] <= 'Z' && expr[i]!='I'))) {
            if (fl_variable == 0) {
                fl_variable = 1;
            }
            pushChar(expr[i], variable);

        } else if (expr[i] >= '0' && expr[i] <= '9') {
            if (fl_variable == 1) {
                pushChar(expr[i], variable);
            }
        } else {
            fl_variable = 0;
            NodeChar* const_PI=NULL;
            NodeChar* const_e=NULL;
            NodeChar* temp_funsin=NULL;
            NodeChar* temp_funcos=NULL;
            NodeChar* temp_funsqrt=NULL;
            NodeChar* temp_funln=NULL;
            NodeChar* temp_funexp=NULL;
            pushChar('e',const_e);
            pushChar('P',const_PI);pushChar('I',const_PI);
            pushChar('s',temp_funsin);pushChar('i',temp_funsin);pushChar('n',temp_funsin);
            pushChar('c',temp_funcos);pushChar('o',temp_funcos);pushChar('s',temp_funcos);
            pushChar('s',temp_funsqrt);pushChar('q',temp_funsqrt);pushChar('r',temp_funsqrt);pushChar('t',temp_funsqrt);
            pushChar('l',temp_funln);pushChar('n',temp_funln);
            pushChar('e',temp_funexp);pushChar('x',temp_funexp);pushChar('p',temp_funexp);
            if (inarr(variable, arr_var) && variable && !equalstack(variable,temp_funsin) && !equalstack(variable,temp_funcos) && !equalstack(variable,temp_funsqrt) && !equalstack(variable,temp_funln) && !equalstack(variable,temp_funexp) && !equalstack(variable,const_PI) && !equalstack(variable,const_e))
                pushVariable(variable, 0, arr_var);
            variable = NULL;
        }
    }
    if (fl_variable) {
        fl_variable = 0;
        if (inarr(variable, arr_var))
            pushVariable(variable, 0, arr_var);
        variable = NULL;
    }
    while (arr_var) {
        ++var_count;
        arr_var = arr_var->next;
    }
    variable = NULL;
    arr_var = NULL;
    int fl_equal = 0;
    //Считываем переменные
    while (var_count) {
        char user_var[256];
        NodeChar *user_name = NULL;
        NodeInt *user_int = NULL;
        gets(user_var);
        int len_num = 0;
        int fl_num = -1;
        int unar_min = 0;
        for (int i = 0; i < strlen(user_var); ++i) {
            if (!fl_equal) {
                if (user_var[i] == '=') {
                    fl_equal = 1;
                    continue;
                }
                pushChar(user_var[i], user_name);
            }
                //a=2.3 (2.3)
            else {
                if (user_var[i] == '-') {
                    unar_min = 1;
                    continue;
                }
                float n = user_var[i] - '0';
                if (user_var[i] == '.') {
                    fl_num = len_num;
                    continue;
                }
                pushInt(n, user_int);
                ++len_num;
            }
        }
        //формирую число для переменной
        float res = 0;
        float d = 1;
        if (fl_num != -1)
            for (int i = 0; i < len_num - fl_num; ++i) {
                d /= 10;
            }
        res = res + d * user_int->value;
        d *= 10;
        len_num = 1;
        while (user_int->next != nullptr) {
            user_int = user_int->next;
            res = res + d * user_int->value;
            d *= 10;
        }
        if (unar_min)
            res = 0 - res;
        pushVariable(user_name, res, arr_var);
        --var_count;
        fl_equal = 0;
    }
    int fl_num = -1;
    int len_num = 0;
    float res = 0;
    int unbreakets=1;
    //Константы
    NodeChar* const_PI=NULL;
    NodeChar* const_e=NULL;
    pushChar('e',const_e);
    pushChar('P',const_PI);pushChar('I',const_PI);
    pushVariable(const_e, exp(1), arr_var);
    pushVariable(const_PI, 3.14159265358979323846, arr_var);
    //Основная строка и подсчеты
    for (int i = 0; i < strlen(expr); ++i) {
        //NUMERUS
        if ((expr[i] >= 'a' && expr[i] <= 'z') || (expr[i] >= 'A' && expr[i] <= 'Z')) {
            pushChar(expr[i], variable);
            fl_variable = 1;
        } else if (expr[i] == '.')
            fl_num = len_num;
        else if (expr[i] >= '0' && expr[i] <= '9') {
            if (fl_variable == 1) {
                pushChar(expr[i], variable);
                continue;
            }
            float tn = expr[i] - '0';
            pushInt(tn, num);
            ++len_num;
            //OPERATIONS
        } else {
            //ADD NUMERUS
            //сравни переменную с теми,что в стеки и сунь валью в стек чисел
            //А еще тут функции
            if (variable) {
                NodeChar* temp_funsin=NULL;
                NodeChar* temp_funcos=NULL;
                NodeChar* temp_funsqrt=NULL;
                NodeChar* temp_funln=NULL;
                NodeChar* temp_funexp=NULL;
                pushChar('s',temp_funsin);pushChar('i',temp_funsin);pushChar('n',temp_funsin);
                pushChar('c',temp_funcos);pushChar('o',temp_funcos);pushChar('s',temp_funcos);
                pushChar('s',temp_funsqrt);pushChar('q',temp_funsqrt);pushChar('r',temp_funsqrt);pushChar('t',temp_funsqrt);
                pushChar('l',temp_funln);pushChar('n',temp_funln);
                pushChar('e',temp_funexp);pushChar('x',temp_funexp);pushChar('p',temp_funexp);
                if(equalstack(variable,temp_funsin)){
                    pushChar('s',Operations);
                }
                else if(equalstack(variable,temp_funcos)){
                    pushChar('c',Operations);
                }
                else if(equalstack(variable,temp_funsqrt)){
                    pushChar('$',Operations);
                }
                else if(equalstack(variable,temp_funln)){
                    pushChar('!',Operations);
                }
                else if(equalstack(variable,temp_funexp)){
                    pushChar('@',Operations);
                }
                //Функция пушится в операции
                else {
                    float var_value = inarr(variable, arr_var);
                    pushInt(var_value, Numbers);
                }
                variable = NULL;
            }
            if (num) {
                res = 0;
                float d = 1;
                if (fl_num != -1)
                    for (int i = 0; i < len_num - fl_num; ++i) {
                        d /= 10;
                    }
                res = res + d * num->value;
                d *= 10;
                len_num = 1;
                while (num->next != nullptr) {
                    num = num->next;
                    res = res + d * num->value;
                    d *= 10;
                }
                pushInt(res, Numbers);
                num = NULL;
            }
            fl_variable = 0;
            //ADD OPERATIONS
            if (!Operations)
                pushChar(expr[i], Operations);
            else {
                if ((priority(topChar(Operations)) == 999 && expr[i]!=')') || priority(expr[i]) > priority(topChar(Operations)))
                    pushChar(expr[i], Operations);
                else {
                    while (Operations == NULL || priority(topChar(Operations)) >= priority(expr[i])) {
                        if (Operations && (topChar(Operations) == '(')) {
                            if(expr[i]==')')
                                popChar(Operations);
                            break;
                        }
                        if (Operations == NULL) {
                            break;
                        }
                        float num1 = topInt(Numbers);
                        popInt(Numbers);
                        float ans=0;
                        if(topChar(Operations)!='s' && topChar(Operations)!='c' && topChar(Operations)!='$' && topChar(Operations)!='!' && topChar(Operations)!='@') {
                            float num2 = topInt(Numbers);
                            popInt(Numbers);
                            ans = operation(num1, num2, topChar(Operations));
                        }
                        else
                            ans = functions(num1,topChar(Operations));
                        popChar(Operations);
                        pushInt(ans, Numbers);
                    }
                    if (expr[i] != ')')
                        pushChar(expr[i], Operations);
                }
            }
        }
    }
    if (variable) {
        float var_value = inarr(variable, arr_var);
        pushInt(var_value, Numbers);
        variable = NULL;
    }
    if (num) {
        //Требуется функция форм инт
        res = 0;
        float d = 1;
        if (fl_num != -1)
            for (int i = 0; i < len_num - fl_num; ++i) {
                d /= 10;
            }
        res = res + d * num->value;
        d *= 10;
        len_num = 1;
        while (num->next != nullptr) {
            num = num->next;
            res = res + d * num->value;
            d *= 10;
        }
        pushInt(res, Numbers);
    }
    while (Operations) {
        if(topChar(Operations)=='('){
            popChar(Operations);
            break;
        }
        float num1 = topInt(Numbers);
        popInt(Numbers);
        float ans=0;
        if(topChar(Operations)!='s' && topChar(Operations)!='c' && topChar(Operations)!='$' && topChar(Operations)!='!' && topChar(Operations)!='@') {
            float num2 = topInt(Numbers);
            popInt(Numbers);
            ans = operation(num1, num2, topChar(Operations));
        }
        else{
            ans= functions(num1, topChar(Operations));
        }
        popChar(Operations);
        pushInt(ans, Numbers);
    }
    printf("%f", Numbers->value);
    return 0;
}
