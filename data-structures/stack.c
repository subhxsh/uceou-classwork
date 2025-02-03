#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int top;
    int* array;
    int size;
};

struct Stack* create_stack(int size) {
    struct Stack* stack = malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    stack->array = malloc(size*sizeof(int));
    if (!stack->array) {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->size = size;
    return stack;
}

int push(struct Stack* stack, int value) {
    if (!stack || stack->top + 1 == stack->size) return -1;
    stack->array[++stack->top] = value;
    return 0;
}

int pop(struct Stack* stack, int* out) {
    if (!stack || stack->top == -1) return -1;
    if (out != NULL) *out = stack->array[stack->top];
    stack->top--;
    return 0;
}

void display(struct Stack* stack) {
    if (stack->top == -1) {
        printf("> <empty>\n");
        return;
    }

    for (int i = stack->top; i >= 0; i--)
        printf("> %d\n", stack->array[i]);
}

void destroy(struct Stack* stack) {
    if (stack) {
        free(stack->array);
        free(stack);
    }
}

int main(void) {
    struct Stack* stack = create_stack(10);
    int choice, value = 0;

    for (;;) {
        system("clear");
        display(stack);
        printf("\n=== Stack Operations ===\n\n1. Push\n2. Pop\n3. Exit\n\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            case 2:
                pop(stack, NULL);
                break;
            case 3:
                destroy(stack);
                exit(0);
            default:
                break;
        }
    }

    return 0;
}
