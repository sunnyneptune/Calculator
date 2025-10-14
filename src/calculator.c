#include "calculator.h"

int calculator(char *input_orig, char *x, char *output) {
  int is_correct = 1;
  is_correct = validation(input_orig);
  if (is_correct) is_correct *= to_lexemes(input_orig, output, x);
  return is_correct;
}

int to_lexemes(char *input, char *polish_output, char *x) {
  int is_correct = 1;
  int length = strlen(input);
  char stack[256] = "\0";
  char trig[5] = "\0";
  int i = 0;
  int ind = 0;
  for (int k = 0; k < length; k++) {
    if (input[k] == '(' || input[k] == ')') {
      stack[i++] = input[k];
      stack[i++] = ';';
    } else if (input[k] == 'x') {
      if (x[ind] == '-') {
        stack[i++] = '~';
        append(stack, ';');
        i++;
        ind++;
      }
      while (strchr("0123456789.", x[ind]) && x[ind] != '\0') {
        stack[i++] = x[ind++];
      }
      ind = 0;
      append(stack, ';');
      i++;
    } else if (strchr("0123456789.", input[k])) {
      while (strchr("0123456789.", input[k]) && k < length) {
        stack[i++] = input[k++];
      }
      append(stack, ';');
      i++;
      k--;
    } else if (strchr("+-/^*", input[k])) {
      if (strchr("*/-+^%(", input[k - 1]) && input[k] == '-') {
        stack[i] = '~';
        append(&stack[i + 1], ';');
        i += 2;
      } else {
        stack[i] = input[k];
        append(&stack[i + 1], ';');
        i += 2;
      }
    } else {
      char sym = 0;
      int j = 0;
      while (!strchr("0123456789.+-/^*()", input[k])) {
        trig[j] = input[k];
        j++;
        k++;
      }
      k--;
      sym = transcript(trig);
      stack[i] = sym;
      append(&stack[i + 1], ';');
      i += 2;
    }
  }
  is_correct = to_polish_notation(stack, polish_output);
  return is_correct;
}

int get_priority(char input) {
  int p = 0;
  if (input == '+' || input == '-')
    p = PLUS;
  else if (strchr("*/%", input))
    p = MULT;
  else if (input == '^')
    p = POW;
  else if (input == '(')
    p = OPEN_BRACKET;
  else if (strchr("sctiCTlnq~", input))
    p = TRIG;
  return p;
}

void close_brackets(calc_stack *operators, calc_stack *buffer) {
  int j = operators->length - 1;
  if (peek(operators) == '(') {
    pop(operators);
    push(buffer, operators->tokens[j - 1]);
    push(buffer, ' ');
  }
  while (operators->tokens[j] != '(') {
    push(buffer, operators->tokens[j]);
    push(buffer, ' ');
    pop(operators);
    j--;
  }
  pop(operators);
}

int to_polish_notation(char *input, char *output) {
  int is_correct = 1;
  calc_stack buffer = {0};
  init_stack(&buffer);
  calc_stack operators = {0};
  init_stack(&operators);
  int i = 0;
  int priority = 0;
  char last_op = 0;
  char sym = 0;
  while (input[i] != '\0') {
    priority = get_priority(input[i]);
    if (input[i] == '(') {
      push(&operators, '(');
    } else if (input[i] == ')') {
      close_brackets(&operators, &buffer);
    } else if (strchr("0123456789.", input[i])) {
      while (strchr("0123456789.", input[i])) {
        push(&buffer, input[i]);
        i++;
      }
      i--;
      push(&buffer, ' ');
    } else if (strchr("sctiCTlnq~", input[i])) {
      push(&operators, input[i]);
    } else if (strchr("+-*/^%", input[i])) {
      if (is_stack_empty(&operators)) {
        push(&operators, input[i]);
      } else {
        last_op = peek(&operators);  // на предыдущей ячейке, текущая пустая
        if (get_priority(last_op) < priority) {
          push(&operators, input[i]);
        } else {
          while (get_priority(last_op) >= priority &&
                 !(is_stack_empty(&operators))) {
            sym = peek(&operators);
            if (sym == '(') {
              pop(&operators);
            } else {
              push(&buffer, sym);
              push(&buffer, ' ');
              pop(&operators);
            }
            last_op = peek(&operators);
          }
          push(&operators, input[i]);
        }
      }
    }
    i += 2;
  }
  while (!(is_stack_empty(&operators))) {
    if (peek(&operators) == '(') {
      pop(&operators);
    } else {
      sym = peek(&operators);
      push(&buffer, sym);
      push(&buffer, ' ');
      pop(&operators);
    }
  }
  is_correct = calculate_result(&buffer, output);
  remove_stack(&operators);
  return is_correct;
}

int calculate_result(calc_stack *buffer, char *output) {
  reverse(buffer->tokens);
  int is_correct = 1;
  double_stack d_stack = {0};
  init_d_stack(&d_stack);
  calc_stack c_stack = {0};
  init_stack(&c_stack);
  double number;
  char action = 0;
  while (!(is_stack_empty(buffer))) {
    if (strchr(" ", peek(buffer))) {
      pop(buffer);
    } else if (strchr("+-*/^%", peek(buffer))) {
      action = peek(buffer);
      perform_operation(&d_stack, action);
      pop(buffer);
    } else if (strchr("0123456789.", peek(buffer))) {
      while (strchr("0123456789.", peek(buffer)) && buffer->length != 0) {
        push(&c_stack, peek(buffer));
        pop(buffer);
      }
      number = s21_strtold(c_stack.tokens);
      push_d(&d_stack, number);
      while (!is_stack_empty(&c_stack)) {
        push(&c_stack, '\0');
        c_stack.length--;
        c_stack.length--;
      }
    } else if (strchr("sctiCTlnq~", peek(buffer))) {
      action = peek(buffer);
      if (action == 'l' && peek_d(&d_stack) == 0) {
        is_correct = 0;
        sprintf(output, "%s", "nan");
        break;
      }
      perform_trigonometry(&d_stack, action);
      pop(buffer);
    }
  }
  if (is_correct) sprintf(output, "%.7lf", d_stack.tokens[0]);
  if (strstr(output, "nan") || strstr(output, "inf")) {
    is_correct = 0;
  }
  remove_stack(buffer);
  remove_stack_d(&d_stack);
  remove_stack(&c_stack);
  return is_correct;
}

void perform_trigonometry(double_stack *d_stack, char action) {
  double right_op = pop_d(d_stack);
  switch (action) {
    case 'c':
      push_d(d_stack, cos(right_op));
      break;
    case 'l':
      push_d(d_stack, log10f(right_op));
      break;
    case 'q':
      push_d(d_stack, sqrt(right_op));
      break;
    case 'n':
      push_d(d_stack, log(right_op));
      break;
    case 's':
      push_d(d_stack, sin(right_op));
      break;
    case 't':
      push_d(d_stack, tan(right_op));
      break;
    case 'T':
      push_d(d_stack, atan(right_op));
      break;
    case 'C':
      push_d(d_stack, acos(right_op));
      break;
    case 'i':
      push_d(d_stack, asin(right_op));
      break;
    case '~':
      push_d(d_stack, right_op * (-1));
      break;
    default:
      break;
  }
}

void perform_operation(double_stack *d_stack, char action) {
  double right_op = pop_d(d_stack);
  double left_op = pop_d(d_stack);
  switch (action) {
    case '+':
      push_d(d_stack, left_op + right_op);
      break;
    case '*':
      push_d(d_stack, left_op * right_op);
      break;
    case '/':
      push_d(d_stack, left_op / right_op);
      break;
    case '-':
      push_d(d_stack, left_op - right_op);
      break;
    case '^':
      push_d(d_stack, pow(left_op, right_op));
      break;
    case '%':
      push_d(d_stack, fmod(left_op, right_op));
      break;
    default:
      break;
  }
}

void reverse(char *to_number) {
  char temp;
  int length = strlen(to_number);
  for (int i = 0; i < length / 2; i++) {
    temp = to_number[i];
    to_number[i] = to_number[length - i - 1];
    to_number[length - i - 1] = temp;
  }
}

char transcript(char *func) {
  char sym = 0;
  if (strstr(func, "acos"))
    sym = 'C';
  else if (strstr(func, "cos"))
    sym = 'c';
  else if (strstr(func, "asin"))
    sym = 'i';
  else if (strstr(func, "sin"))
    sym = 's';
  else if (strstr(func, "atan"))
    sym = 'T';
  else if (strstr(func, "tan"))
    sym = 't';
  else if (strstr(func, "sqrt"))
    sym = 'q';
  else if (strstr(func, "log"))
    sym = 'l';
  else if (strstr(func, "ln"))
    sym = 'n';
  else if (strstr(func, "mod"))
    sym = '%';
  return sym;
}

int validation(char *input) {
  int is_correct = 1;
  is_correct *= brackets_validate(input);
  while (*input != '\0') {
    if (*input == '+' || *input == '-') {
      if (!strchr("1234567890satcl(x", *(input + 1))) is_correct = 0;
      break;
    } else if (strchr("/*", *input) &&
               (!strchr("1234567890x)", *(input - 1)) ||
                !strchr("1234567890satcxl(", *(input + 1)))) {
      is_correct = 0;
      break;
    } else if (*input == 'l' && *(input + 1) == 'o' && *(input + 4) == '0') {
      is_correct = 0;
      break;
    } else if (*input == 'm' && *(input + 1) == 'o' && *(input + 2) == 'd') {
      if (*(input + 3) == '0' ||
          (!(strchr("x1234567890(", *(input - 1))) ||
           (!(strchr("x123456789satcl(", *(input + 3)))))) {
        is_correct = 0;
        break;
      }
    } else if (*input == '.' && (!strchr("x1234567890", *(input + 1)) ||
                                 !strchr("x1234567890", *(input - 1)))) {
      is_correct = 0;
      break;
    } else if (*input == 's' && *(input + 1) == 'q') {
      if (strchr("-", *(input + 5))) {
        is_correct = 0;
        break;
      }
    } else if ((*input == '/' && *(input + 1) == '0')) {
      is_correct = 0;
      break;
    } else if (*input == '(' && strchr("x1234567890.", *(input - 1)) &&
               *(input - 1) != 0) {
      is_correct = 0;
      break;
    } else if (*input == ')' && strchr("x1234567890.satclm", *(input + 1)) &&
               *(input + 1) != 0) {
      is_correct = 0;
      break;
    }
    input++;
  }
  return is_correct;
}

int brackets_validate(char *input) {
  int is_correct = 1;
  if (symbol_count(input, ')') != symbol_count(input, '(')) is_correct = 0;
  if (find_index_left(input, '(') > find_index_left(input, ')')) is_correct = 0;
  return is_correct;
}

int symbol_count(char *input, char symbol) {
  int count = 0;
  char *c_input = input;
  for (; *c_input != '\0'; c_input++) {
    if (*c_input == symbol) count++;
  }
  return count;
}

void append(char *input, char symbol) {
  int length = strlen(input);
  input[length] = symbol;
  input[length + 1] = '\0';
}

double s21_strtold(char *buffer) {
  double result = 0.0L;
  double sign = 1.0L;
  int found_digit = 0;
  int count = 0;
  if (buffer[count] == '-') {
    sign = -1.0L;
    count++;
  }
  while (buffer[count] >= '0' && buffer[count] <= '9') {
    result = result * 10.0L + (double)(buffer[count] - '0');
    found_digit = 1;
    count++;
  }
  if (buffer[count] == '.') {
    count++;
    double fraction = 0.1L;
    while (buffer[count] >= '0' && buffer[count] <= '9') {
      result += (double)(buffer[count] - '0') * fraction;
      fraction *= 0.1L;
      found_digit = 1;
      count++;
    }
  }
  if (found_digit) result *= sign;
  return result;
}

int find_index_left(char *input, char symbol) {
  int length = strlen(input);
  int i = 0;
  for (; i < length; i++)
    if (input[i] == symbol) break;
  return i;
}

int find_index_right(char *input, char symbol) {
  int i = strlen(input) - 1;
  while (i != 0) {
    if (input[i] == symbol) break;
    i--;
  }
  return i;
}
