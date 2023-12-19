#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct Stack 
{
    int top;
    int items[MAX_SIZE];
} 
Stack;

void initialize(Stack *stack) 
{
    stack->top = -1;
}

int isEmpty(Stack *stack) 
{
    // Returns 1 if the stack is empty (top is -1) and 0 otherwise
    return (stack->top == -1);
}

int isFull(Stack *stack) 
{
    return (stack->top == MAX_SIZE - 1);
}

void push(Stack *stack, int item) 
{
    if (isFull(stack)) 
    {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

int pop(Stack *stack) 
{
    if (isEmpty(stack)) 
    {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

int evaluatePostfix(const char *expression) {
    Stack stack;
    initialize(&stack);

    for (int i = 0; expression[i] != '\0'; i++) 
    {
        if (isdigit(expression[i])) 
        {
            push(&stack, expression[i] - '0');
        } 
        else 
        {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);

            switch (expression[i]) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
                default:
                    printf("Invalid expression\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    return pop(&stack);

}

int main() {
    char *postfixExpression = malloc(MAX_SIZE * sizeof(char));

    if (postfixExpression == NULL) {
        printf("Memory allocation failed\n");
        return 1;  
    }

    printf("Enter a postfix expression: ");
    scanf("%s", postfixExpression);

    int result = evaluatePostfix(postfixExpression);
    printf("Result of the postfix expression '%s' is: %d\n", postfixExpression, result);
    free(postfixExpression);

    return 0;
}