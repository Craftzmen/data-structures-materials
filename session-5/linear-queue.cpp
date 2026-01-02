#include <iostream>

using namespace std;

const int SIZE = 5;

struct Queue {
    int items[SIZE];
    int front;
    int rear;
};

void initQueue(Queue &q) {
    q.front = -1;
    q.rear = -1;
}

bool isFull(Queue &q) {
    return (q.rear == SIZE - 1);
}

bool isEmpty(Queue &q) {
    return (q.front == -1 || q.front > q.rear);
}

void enqueue(Queue &q, int value) {
    if (isFull(q)) {
        cout << "Queue is full! Cannot insert " << value << endl;
        return;
    }
    if (q.front == -1)
        q.front = 0;
    q.rear++;
    q.items[q.rear] = value;
    cout << value << " inserted into the queue." << endl;
}

void dequeue(Queue &q) {
    if (isEmpty(q)) {
        cout << "Queue is empty! Cannot dequeue." << endl;
        return;
    }
    cout << q.items[q.front] << " removed from the queue." << endl;
    q.front++;
}

void peek(Queue &q) {
    if (isEmpty(q)) {
        cout << "Queue is empty! Nothing to peek." << endl;
        return;
    }
    cout << "Front element is: " << q.items[q.front] << endl;
}

void display(Queue &q) {
    if (isEmpty(q)) {
        cout << "Queue is empty!" << endl;
        return;
    }
    cout << "Queue elements are: ";
    for (int i = q.front; i <= q.rear; i++)
        cout << q.items[i] << " ";
    cout << endl;
}

int main() {
    Queue q;
    initQueue(q);

    int choice, value;

    do {
        cout << "\nQueue Operations Menu" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Peek" << endl;
        cout << "4. Display" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            enqueue(q, value);
            break;
        case 2:
            dequeue(q);
            break;
        case 3:
            peek(q);
            break;
        case 4:
            display(q);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
