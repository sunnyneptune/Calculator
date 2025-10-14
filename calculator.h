//
//  calculator.h
//
//
//  Created by Жуль on 23.07.2023.
//
#ifndef calculator_h
#define calculator_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int length;
  char *tokens;
} calc_stack;

typedef struct {
  int length;
  double *tokens;
} double_stack;

enum suchnosti {
  OPEN_BRACKET = 0,
  TRIG = 4,
  PLUS = 1,
  MULT = 2,
  POW = 3,
  UNARY_MINUS = 5,
};

// stack
void init_stack(calc_stack *new_stack);
void init_d_stack(double_stack *new_stack);
int is_stack_empty(calc_stack *stack);
int is_stack_full(calc_stack *stack);
void push(calc_stack *stack, char token);
char peek(calc_stack *stack);
void push_d(double_stack *stack, double token);
double pop_d(double_stack *stack);
double peek_d(double_stack *stack);
char pop(calc_stack *stack);
int is_stack_empty_d(double_stack *stack);
void remove_stack(calc_stack *stack);
void remove_stack_d(double_stack *stack);

// main and auxiliary
int validation(char *input);
int to_lexemes(char *input_orig, char *polish_output, char *x);
int brackets_validate(char *input);
int symbol_count(char *input, char symbol);
void append(char *input, char symbol);
int find_index_left(char *input, char symbol);
int find_index_right(char *input, char symbol);
char transcript(char *func);
int get_priority(char input);
void reverse(char *to_number);
double s21_strtold(char *buffer);
int calculate_result(calc_stack *buffer, char *output);
void close_brackets(calc_stack *operators, calc_stack *buffer);
int to_polish_notation(char *input, char *output);
void perform_operation(double_stack *d_stack, char action);
void perform_trigonometry(double_stack *d_stack, char action);
int calculator(char *input, char *x, char *output);
#endif /* calculator_h */
