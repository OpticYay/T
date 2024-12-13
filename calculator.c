#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//new PR
int values[100];
char operators[100];
int top = -1, opTop = -1;
void push(int value) {
    values[++top] = value;
}
int pop() {
    return values[top--];
}
void pushOperator(char op) {
    operators[++opTop] = op;
}
char popOperator() {
    return operators[opTop--];
}
char peekOperator() {
    return opTop == -1 ? '\0' : operators[opTop];
}
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
int performOperation(int a, int b, char op) {
    if (op == '/' && b == 0) {
        printf("Error: Division by zero.\n");
        exit(1);
    }
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}
int evaluateExpression(const char* expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) continue; 

        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            push(num);
        } else if (expr[i] == '(') {
            pushOperator(expr[i]);
        } else if (expr[i] == ')') {
            while (peekOperator() != '(') {
                int b = pop();
                int a = pop();
                char op = popOperator();
                push(performOperation(a, b, op));
            }
            popOperator();
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (opTop != -1 && precedence(peekOperator()) >= precedence(expr[i])) {
                int b = pop();
                int a = pop();
                char op = popOperator();
                push(performOperation(a, b, op));
            }
            pushOperator(expr[i]);
        } else {
            printf("Error: Invalid expression.\n");
            exit(1);
        }
    }
    while (opTop != -1) {
        int b = pop();
        int a = pop();
        char op = popOperator();
        push(performOperation(a, b, op));
    }

    return pop();
}
int main() {
    char expression[100];

    printf("Enter a mathematical expression: ");
    fgets(expression, 100, stdin);

    int result = evaluateExpression(expression);
    printf("Result: %d\n", result);

    return 0;
}
