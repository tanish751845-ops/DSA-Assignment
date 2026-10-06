/*
 * Q2: Circular Queue using an array
 * Operations: ENQUEUE, DEQUEUE, FRONT, DISPLAY
 * A separate 'count' variable distinguishes FULL from EMPTY.
 */
#include <stdio.h>

#define MAX 5

int queue[MAX];
int front = 0;      /* index of the first element            */
int rear  = -1;     /* index of the last element             */
int count = 0;      /* number of elements currently stored   */

int isEmpty(void) { return count == 0; }
int isFull(void)  { return count == MAX; }

void enqueue(int x) {
    if (isFull()) {
        printf("Queue Overflow! Cannot enqueue %d\n", x);
        return;
    }
    rear = (rear + 1) % MAX;        /* wrap around */
    queue[rear] = x;
    count++;
    printf("%d enqueued\n", x);
}

int dequeue(void) {
    if (isEmpty()) {
        printf("Queue Underflow! Nothing to dequeue\n");
        return -1;
    }
    int val = queue[front];
    front = (front + 1) % MAX;      /* wrap around */
    count--;
    printf("%d dequeued\n", val);
    return val;
}

int frontElement(void) {
    if (isEmpty()) {
        printf("Queue is empty! No front element\n");
        return -1;
    }
    printf("Front element = %d\n", queue[front]);
    return queue[front];
}

void display(void) {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (front -> rear): ");
    for (int i = 0; i < count; i++)
        printf("%d ", queue[(front + i) % MAX]);
    printf("\n");
}

int main(void) {
    int choice, x;
    while (1) {
        printf("\n--- CIRCULAR QUEUE MENU ---\n");
        printf("1. ENQUEUE\n2. DEQUEUE\n3. FRONT\n4. DISPLAY\n5. EXIT\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                if (scanf("%d", &x) == 1) enqueue(x);
                else { printf("Invalid input!\n"); while (getchar() != '\n'); }
                break;
            case 2: dequeue();      break;
            case 3: frontElement(); break;
            case 4: display();      break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}
