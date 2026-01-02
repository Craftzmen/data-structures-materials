#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

Node *head = nullptr;

void insertInLinkedList(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayLinkedList() {
    if (head == nullptr) {
        cout << "Linked List is empty." << endl;
        return;
    } else {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
    }
    cout << endl;
}

void searchInLinkedList(int target) {
    if (head == nullptr) {
        cout << "Linked List is empty. Cannot perform search." << endl;
        return;
    } else {
        Node* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (temp->data == target) {
                found = true;
                cout << "Element " << target << " found in the linked list." << endl;
                return;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "Element " << target << " not found in the linked list." << endl;
        }
    }
}

void deleteInLinkedList(int target) {
    if (head == nullptr) {
        cout << "Linked List is empty. Cannot perform deletion." << endl;
        return;
    } else {
        if (head->data == target) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Element " << target << " deleted from the linked list." << endl;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != target) {
            temp = temp->next;
        }
        if (temp->next == nullptr) {
            cout << "Element " << target << " not found in the linked list." << endl;
        }
        Node *deleteNode = temp->next;
        temp->next = deleteNode->next;
        delete deleteNode;
        cout << "Element " << target << " deleted from the linked list." << endl;
    }
}

int main() {
    insertInLinkedList(10);
    insertInLinkedList(20);

    cout << "Linked List: ";
    displayLinkedList();

    int target = 20;

    if (head != nullptr) {
        searchInLinkedList(target);
    } else {
        cout << "Linked List is empty. Cannot perform search." << endl;
    }

    if (head != nullptr) {
        deleteInLinkedList(target);
    } else {
        cout << "Linked List is empty. Cannot perform deletion." << endl;
    }

    return 0;
}

