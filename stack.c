/*
 * Q1: Stack using an array (no built-in stack library)
 * Operations: PUSH, POP, PEEK, DISPLAY
 * Handles: Stack Overflow and Stack Underflow
 */
#include <stdio.h>

#define MAX 5               /* fixed capacity of the stack */

int stack[MAX];
int top = -1;               /* -1 means the stack is empty */

int isEmpty(void) { return top == -1; }
int isFull(void)  { return top == MAX - 1; }

void push(int x) {
    if (isFull()) {
        printf("Stack Overflow! Cannot push %d (capacity = %d)\n", x, MAX);
        return;
    }
    stack[++top] = x;
    printf("%d pushed onto the stack\n", x);
}

int pop(void) {
    if (isEmpty()) {
        printf("Stack Underflow! Nothing to pop\n");
        return -1;
    }
    int val = stack[top--];
    printf("%d popped from the stack\n", val);
    return val;
}

int peek(void) {
    if (isEmpty()) {
        printf("Stack is empty! Nothing to peek\n");
        return -1;
    }
    printf("Top element = %d\n", stack[top]);
    return stack[top];
}

void display(void) {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (top -> bottom): ");
    for (int i = top; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
}

int main(void) {
    int choice, x;
    while (1) {
        printf("\n--- STACK MENU ---\n");
        printf("1. PUSH\n2. POP\n3. PEEK\n4. DISPLAY\n5. EXIT\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {        /* guard against bad input */
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                if (scanf("%d", &x) == 1) push(x);
                else { printf("Invalid input!\n"); while (getchar() != '\n'); }
                break;
            case 2: pop();     break;
            case 3: peek();    break;
            case 4: display(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}
