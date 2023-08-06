/*********************************
 * Reviewer: 				
 * Author: yisrael fisch			
 * File: calculator.c					
 * ******************************/

#include <stdlib.h> /* strtod */
#include <string.h> /* strlen */
#include <assert.h> /*assert*/
#define _BSD_SOURCE
#include <math.h> /* NAN */
#undef _BSD_SOURCE
#include "stack.h"
#include "calculator.h"

double NAN = 0.0/0.0;

static char *HandleOperands(const char *exp);
static char *HandleOperators(const char *exp);
static char *HandlerOpenParenthesis(const char *exp);
static char *HandlerCloseParenthesis(const char *exp);
static char *HandlerSpaces(const char *exp);

static char Operate(char operator);

static double Add(double first_operand, double second_operand);
static double Sub(double first_operand, double second_operand);
static double Mul(double first_operand, double second_operand);
static double Div(double first_operand, double second_operand);

typedef char *(*handl_funcs_t)(const char*);
typedef double (*operators_func_t)(double, double);

static handl_funcs_t g_handlers[128] = {NULL};
static int g_precedences_array[128] = {0};
static operators_func_t g_operators_array[128] = {NULL};

static stack_t *g_operands_stack = NULL;
static stack_t *g_operators_stack = NULL;

static void InitHandlers()
{
    g_handlers['0'] = HandleOperands;
    g_handlers['1'] = HandleOperands;
    g_handlers['2'] = HandleOperands;
    g_handlers['3'] = HandleOperands;
    g_handlers['4'] = HandleOperands;
    g_handlers['5'] = HandleOperands;
    g_handlers['6'] = HandleOperands;
    g_handlers['7'] = HandleOperands;
    g_handlers['8'] = HandleOperands;
    g_handlers['9'] = HandleOperands;
    g_handlers[' '] = HandlerSpaces;
    g_handlers['+'] = HandleOperators;
    g_handlers['-'] = HandleOperators;
    g_handlers['*'] = HandleOperators;
    g_handlers['/'] = HandleOperators;
    g_handlers['('] = HandlerOpenParenthesis;
    g_handlers[')'] = HandlerCloseParenthesis;
}

static void InitPrecedences()
{
    g_precedences_array['('] = 0;
    g_precedences_array['+'] = 1;
    g_precedences_array['-'] = 1;
    g_precedences_array['*'] = 2;
    g_precedences_array['/'] = 2;
}

static void InitOperators()
{
    g_operators_array['+'] = Add;
    g_operators_array['-'] = Sub;
    g_operators_array['*'] = Mul;
    g_operators_array['/'] = Div;
}

static void InitLUTS()
{
    InitHandlers();
    InitPrecedences();
    InitOperators();
}

double Calculate(const char *exp)
{
    double result = 0.0;
    char first_operator = '(';
    assert((char *)exp);

    g_operands_stack = StackCreate(strlen(exp) / 2 + 1, sizeof(double));
    g_operators_stack = StackCreate(strlen(exp) / 2 + 1, sizeof(char));

    if(!g_operands_stack || !g_operators_stack) 
    {
        return NAN;
    }

    StackPush(g_operators_stack, &first_operator);

    InitLUTS();

    while(*exp)
    {
        exp = g_handlers[(int)*exp](exp);
    }

    HandlerCloseParenthesis(exp);

    StackPeek(g_operands_stack, &result);

    StackDestroy(g_operands_stack);
    StackDestroy(g_operators_stack);

    return result;
}

static char *HandleOperands(const char *exp)
{
    double num = 0.0;
    char *new_position = NULL;

    num = strtod(exp, &new_position);
    StackPush(g_operands_stack, &num);

    return new_position;
}

static char *HandleOperators(const char *exp)
{
    char operator = '\0';

    StackPeek(g_operators_stack, &operator);

    while(g_precedences_array[(int)operator] >= g_precedences_array[(int)*exp])
    {
        operator = Operate(operator);
       
    }

    StackPush(g_operators_stack, (void *)exp);

    return (char *)++exp;
}

static char Operate(char operator)
{
    double first_operand = 0.0;
    double second_operand = 0.0;
    double result = 0.0;
    


    StackPeek(g_operands_stack, &second_operand);
    StackPop(g_operands_stack);
    
    StackPeek(g_operands_stack, &first_operand);
    StackPop(g_operands_stack);
    
    result = g_operators_array[(int)operator](first_operand, second_operand);
    StackPush(g_operands_stack, &result);
    
    StackPop(g_operators_stack);
    StackPeek(g_operators_stack, &operator);

    return operator;
    
}

static char *HandlerOpenParenthesis(const char *exp)
{
    StackPush(g_operators_stack, (char *)exp);

    return (char *)++exp;
}

static char *HandlerCloseParenthesis(const char *exp)
{
    char operator = '\0';

    StackPeek(g_operators_stack, &operator);

    while(operator != '(')
    {
        operator = Operate(operator);
    
        StackPeek(g_operators_stack, &operator);
    }

    StackPop(g_operators_stack);

    return (char *)++exp;
}

static char *HandlerSpaces(const char *exp)
{
    return (char *)++exp; 
}

static double Add(double first_operand, double second_operand)
{
    return first_operand + second_operand;
}

static double Sub(double first_operand, double second_operand)
{
    return first_operand - second_operand;
}

static double Mul(double first_operand, double second_operand)
{
    return first_operand * second_operand;
}

static double Div(double first_operand, double second_operand)
{
    return first_operand / second_operand;
}
