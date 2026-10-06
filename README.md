# C DSA Assignment

**Topics:** Stack using Array, Circular Queue using Array
**Language:** C (no built-in stack/queue library used)

**Files**
- `stack.c` — Q1 solution
- `circular_queue.c` — Q2 solution

**Compile and run**
```
gcc stack.c -o stack && ./stack
gcc circular_queue.c -o cq && ./cq
```

---

# Q1. Stack Using an Array

## Concept
A stack is a linear data structure that follows **LIFO (Last In, First Out)**: the element inserted last is removed first. All operations happen at one end, called the **top**. It is implemented with an array `stack[MAX]` and an integer `top`, initially `-1` (empty).

## Operations
| Operation | Logic | Condition handled |
|---|---|---|
| PUSH(x) | `top++`, then `stack[top] = x` | **Overflow** if `top == MAX-1` |
| POP() | return `stack[top]`, then `top--` | **Underflow** if `top == -1` |
| PEEK() | return `stack[top]` without changing `top` | Empty stack |
| DISPLAY() | print from `top` down to index `0` | Empty stack |

- **Stack Overflow:** pushing into a full stack.
- **Stack Underflow:** popping/peeking from an empty stack.

## Program
See `stack.c`.

## Sample Output
```
Enter choice: 2   -> Stack Underflow! Nothing to pop
Push 10, 20, 30, 40, 50
Push 60           -> Stack Overflow! Cannot push 60 (capacity = 5)
Display           -> Stack (top -> bottom): 50 40 30 20 10
Peek              -> Top element = 50
Pop, Pop          -> 50 popped, 40 popped
Display           -> Stack (top -> bottom): 30 20 10
```

## Time and Space Complexity
| Operation | Time | Extra Space | Reason |
|---|---|---|---|
| PUSH | O(1) | O(1) | One index update and one assignment |
| POP | O(1) | O(1) | One read and one index update |
| PEEK | O(1) | O(1) | Direct access `stack[top]` |
| DISPLAY | O(n) | O(1) | Visits all n elements once |

The **total space** of the stack is O(MAX), the size of the array. Each operation needs only O(1) *extra* space (a few variables).

## What happens when a fixed-size stack is full?
The array has a fixed capacity (`MAX`). If the user pushes when `top == MAX-1`:
- Writing to `stack[MAX]` would go **beyond the array bounds**, which is undefined behaviour in C. It can overwrite neighbouring memory, corrupt data or crash the program (segmentation fault).
- The program therefore **checks `isFull()` before every push**, prints a *Stack Overflow* message and rejects the insertion, leaving the stack unchanged.
- To avoid this limit, the stack can be made **dynamic**: use `malloc`/`realloc` to double the array when full (amortised O(1) push), or use a linked list.

---

# Q2. Circular Queue Using an Array

## Concept
A queue follows **FIFO (First In, First Out)**. Insertion happens at the **rear** and deletion at the **front**. In a **circular queue**, the array is treated as a circle: after the last index, the pointer wraps to index `0` using the modulo operator:

```
rear  = (rear  + 1) % MAX
front = (front + 1) % MAX
```

## Distinguishing Full and Empty
In a circular queue, `front == rear` can mean either "empty" or "full", so the pointers alone are ambiguous. This program solves it with a `count` variable that stores the number of elements:

- **Empty:** `count == 0`
- **Full:** `count == MAX`

(The other common approach is to sacrifice one slot and say full when `(rear+1) % MAX == front`.)

## Operations
| Operation | Logic | Condition handled |
|---|---|---|
| ENQUEUE(x) | `rear = (rear+1)%MAX; queue[rear]=x; count++` | Overflow if `count == MAX` |
| DEQUEUE() | read `queue[front]; front=(front+1)%MAX; count--` | Underflow if `count == 0` |
| FRONT() | return `queue[front]` | Empty queue |
| DISPLAY() | print `queue[(front+i)%MAX]` for `i = 0..count-1` | Empty queue |

## Program
See `circular_queue.c`.

## Sample Output (MAX = 5)
```
Dequeue on empty        -> Queue Underflow! Nothing to dequeue
Enqueue 1,2,3,4,5       -> queue is now full
Enqueue 6               -> Queue Overflow! Cannot enqueue 6
Dequeue, Dequeue        -> 1 dequeued, 2 dequeued
Enqueue 7, Enqueue 8    -> reuse the freed slots at the start of the array
Display                 -> Queue (front -> rear): 3 4 5 7 8
Front                   -> Front element = 3
```
The last step shows wrap-around: 7 and 8 were stored in indices 0 and 1, which a linear queue could not reuse.

## Circular Queue vs Linear Queue

### 1. Why a circular queue uses memory better
In a linear queue, `front` only moves forward, so the slots before `front` are freed by dequeues but can **never be reused**. A circular queue wraps `rear` back to index 0, so every freed slot is reused. The queue reports "full" only when all `MAX` slots truly hold elements.

### 2. Time complexity of ENQUEUE and DEQUEUE
- ENQUEUE: **O(1)**
- DEQUEUE: **O(1)**

Both only update one pointer (with a modulo) and one array cell. No shifting of elements is required.

### 3. Space complexity
**O(n)**, more precisely O(MAX), for the array of fixed size. Extra space for `front`, `rear` and `count` is O(1).

### 4. Problem in a linear queue when REAR reaches the last index
When `rear == MAX-1`, a linear queue declares itself **full** even though positions `0 .. front-1` are empty after earlier dequeues. This is **false overflow**: memory is wasted although the queue is not actually full. Example with MAX = 5:

```
After enqueue 1..5 :  [1][2][3][4][5]   front=0, rear=4
After 3 dequeues   :  [ ][ ][ ][4][5]   front=3, rear=4
Enqueue(6)         :  rear == MAX-1  ->  "Queue Full"  (3 slots are empty!)
```
Fixes: shift all elements left after each dequeue (O(n), slow), or use a **circular queue** (O(1), no waste).

## Comparison Summary
| Feature | Linear Queue | Circular Queue |
|---|---|---|
| Memory reuse | No (false overflow) | Yes |
| Enqueue / Dequeue time | O(1) | O(1) |
| Space | O(MAX) | O(MAX) |
| Pointer update | `rear++`, `front++` | `(ptr+1) % MAX` |
| Full condition | `rear == MAX-1` | `count == MAX` |

---

## Conclusion
A stack (LIFO) and a circular queue (FIFO) can both be built with a plain array and give O(1) insertion and deletion. A fixed-size stack needs overflow checks to stay safe, and a circular queue fixes the memory waste of a linear queue by wrapping around the array.
