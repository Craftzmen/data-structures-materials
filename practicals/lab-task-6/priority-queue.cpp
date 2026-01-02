#include <iostream>

using namespace std;

class Node {
public:
    int data;
    int priority;
    Node* next;
    Node(int val, int prio) : data(val), priority(prio), next(nullptr) {}
};

class PriorityQueue {
private:
    Node* front;

public:
    PriorityQueue() : front(nullptr) {}
    void enqueue(int val, int prio) {
        Node* newNode = new Node(val, prio);
        
        if (front == nullptr || prio > front->priority) {
            newNode->next = front;
            front = newNode;
        } else {
            Node* temp = front;
            while (temp->next != nullptr && temp->next->priority >= prio) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Priority Queue is empty. Cannot dequeue.\n";
            return;
        }
        Node* temp = front;
        cout << "Element " << front->data << " with priority " << front->priority << " dequeued successfully.\n";
        front = front->next;
        delete temp;
    }

    void displayQueue() {
        if (front == nullptr) {
            cout << "Priority Queue is empty." << endl;
            return;
        }
        Node* temp = front;
        cout << "Priority Queue elements " << endl;
        cout << "Data and Priority:" << endl;
        while (temp != nullptr) {
            cout << "Data: " << temp->data;
            cout << "\tPriority: " << temp->priority << endl;
            temp = temp->next;
        }
    }

    ~PriorityQueue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    PriorityQueue pq;
    int choice, value, priority;

    do {
        cout << "\nPriority Queue Operations" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Display Queue" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                cout << "Enter priority (higher value = higher priority): ";
                cin >> priority;
                pq.enqueue(value, priority);
                cout << "Element " << value << " with priority " << priority << " enqueued successfully." << endl;
                break;
            case 2:
                pq.dequeue();
                break;
            case 3:
                cout << "Queue: " << endl;
                pq.displayQueue();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 4);

    return 0;
}