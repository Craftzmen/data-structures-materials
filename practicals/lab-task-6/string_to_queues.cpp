#include <iostream>

using namespace std;

class Node {
public:
    char data;
    Node* next;
    Node(char val) : data(val), next(nullptr) {}
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(char val) {
        Node* newNode = new Node(val);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void displayQueue() {
        if (front == nullptr) {
            cout << "Empty";
            return;
        }
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) {
                cout << " → ";
            }
            temp = temp->next;
        }
    }

    Node* getFront() {
        return front;
    }

    ~Queue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    Queue queues[100];
    int queueCount = 0;
    int i = 0;

    while (i < input.length()) {
        while (i < input.length() && input[i] == ' ') {
            i++;
        }
        if (i < input.length()) {
            while (i < input.length() && input[i] != ' ') {
                queues[queueCount].enqueue(input[i]);
                i++;
            }
            queueCount++;
        }
    }

    for (int j = 0; j < queueCount; j++) {
        cout << "Q" << (j + 1) << " = ";
        queues[j].displayQueue();
        cout << endl;
    }

    cout << "\nConcatenating all queues:" << endl;
    Queue finalQueue;
    
    for (int j = 0; j < queueCount; j++) {
        Node* temp = queues[j].getFront();
        while (temp != nullptr) {
            finalQueue.enqueue(temp->data);
            temp = temp->next;
        }
    }

    cout << "Final Queue = ";
    finalQueue.displayQueue();

    return 0;
}