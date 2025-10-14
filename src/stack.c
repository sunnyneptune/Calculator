#include "calculator.h"

// calc_stack *init_stack() {
//   calc_stack *new_stack = {0};
//   // calc_stack *new_stack =
//   new_stack->length = 0;
//   new_stack->tokens = (char *)calloc(300, sizeof(char *));
//   return new_stack;
// }

void init_stack(calc_stack *new_stack) {
  new_stack->length = 0;
  new_stack->tokens = (char *)calloc(300, sizeof(char *));
}

// double_stack *init_d_stack() {
//   double_stack *new_stack = {0};

//   new_stack->length = 0;
//   new_stack->tokens = (double *)calloc(300, sizeof(double *));
//   return new_stack;
// }

void init_d_stack(double_stack *new_stack) {
  new_stack->length = 0;
  new_stack->tokens = (double *)calloc(600, sizeof(double *));
}

int is_stack_empty(calc_stack *stack) { return stack->length == 0; }
int is_stack_full(calc_stack *stack) { return stack->length == 256; }
void push(calc_stack *stack, char token) {
  int position = stack->length;
  stack->tokens[position] = token;
  stack->length++;
}
char peek(calc_stack *stack) {
  int position = stack->length - 1;
  if (is_stack_empty(stack)) return 0;
  return stack->tokens[position];
}
void push_d(double_stack *stack, double token) {
  int position = stack->length;
  stack->tokens[position] = token;
  stack->length++;
}
double pop_d(double_stack *stack) {
  if (is_stack_empty_d(stack)) return 0;
  stack->length--;
  return stack->tokens[stack->length];
}
double peek_d(double_stack *stack) {
  int position = stack->length - 1;
  if (is_stack_empty_d(stack)) return 0;
  return stack->tokens[position];
}
char pop(calc_stack *stack) {
  if (is_stack_empty(stack)) return 0;
  stack->length--;
  return stack->tokens[stack->length];
}

int is_stack_empty_d(double_stack *stack) { return stack->length == 0; }

void remove_stack(calc_stack *stack) {
  free(stack->tokens);
  stack->length = 0;
  stack->tokens = NULL;
}

void remove_stack_d(double_stack *stack) {
  free(stack->tokens);
  stack->length = 0;
  stack->tokens = NULL;
}
