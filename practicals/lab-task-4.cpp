#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node* head = nullptr;

Node* createNode(int val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void insertAtBeginning(int val) {
    Node* newNode = createNode(val);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void insertAtEnd(int val) {
    Node* newNode = createNode(val);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
    newNode->prev = curr;
}

void insertAtPosition(int val, int pos) {
    if (pos < 1) {
    }
    if (pos == 1) {
        insertAtBeginning(val);
    }
    Node* curr = head;
    for (int i = 1; i < pos - 1 && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr) {
    }
    Node* newNode = createNode(val);
    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next != nullptr) {
        curr->next->prev = newNode;
    }
    curr->next = newNode;
}

void deleteFromBeginning() {
    if (head == nullptr) {
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}

void deleteFromEnd() {
    if (head == nullptr) {
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    Node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->prev->next = nullptr;
    delete curr;
}

void deleteFromPosition(int pos) {
    if (pos < 1 || head == nullptr) {
        return;
    }
    if (pos == 1) {
        deleteFromBeginning();
        return;
    }
    Node* curr = head;
    for (int i = 1; i < pos && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr) {
        return;
    }
    if (curr->prev != nullptr) {
        curr->prev->next = curr->next;
    }
    if (curr->next != nullptr) {
        curr->next->prev = curr->prev;
    }
    delete curr;
}

void displayForward() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    cout << "List (Forward): ";
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data << " <-> ";
        curr = curr->next;
    }
    cout << "NULL\n";
}

void displayReverse() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    Node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    cout << "List (Reverse): ";
    while (curr != nullptr) {
        cout << curr->data << " <-> ";
        curr = curr->prev;
    }
    cout << "NULL\n";
}

void searchValue(int val) {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    Node* curr = head;
    int pos = 1;
    int found = 0;
    cout << "Value " << val << " found at position(s): ";
    while (curr != nullptr) {
        if (curr->data == val) {
            cout << pos << " ";
            found = 1;
        }
        curr = curr->next;
        pos++;
    }
    if (found == 0) {
        cout << "Not found!";
    }
    cout << "\n";
}

void updateAtPosition(int pos, int newVal) {
    if (pos < 1) {
    }
    Node* curr = head;
    for (int i = 1; i < pos && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr) {
    }
    curr->data = newVal;
}

int countNodes() {
    int count = 0;
    Node* curr = head;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}

void displayMenu() {
    cout << "\nDoubly Linked List Operations\n";
    cout << "1. Insert at beginning\n";
    cout << "2. Insert at end\n";
    cout << "3. Insert at specific position\n";
    cout << "4. Delete from beginning\n";
    cout << "5. Delete from end\n";
    cout << "6. Delete from specific position\n";
    cout << "7. Display list in forward direction\n";
    cout << "8. Display list in reverse direction\n";
    cout << "9. Search for a value\n";
    cout << "10. Update value at position\n";
    cout << "11. Count total nodes\n";
    cout << "12. Exit\n";
}

int main() {
    int choice, val, pos, newVal;

    cout << "Doubly Linked List Program\n";

    while (1) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "Enter value to insert: ";
                cin >> val;
                insertAtBeginning(val);
                cout << "Node " << val << " inserted at beginning.\n";
                break;
            }
            case 2: {
                cout << "Enter value to insert: ";
                cin >> val;
                insertAtEnd(val);
                cout << "Node " << val << " inserted at end.\n";
                break;
            }
            case 3: {
                cout << "Enter value to insert: ";
                cin >> val;
                cout << "Enter position: ";
                cin >> pos;
                insertAtPosition(val, pos);
                cout << "Node " << val << " inserted at position " << pos << ".\n";
                break;
            }
            case 4: {
                deleteFromBeginning();
                cout << "Node deleted from beginning.\n";
                break;
            }
            case 5: {
                deleteFromEnd();
                cout << "Node deleted from end.\n";
                break;
            }
            case 6: {
                cout << "Enter position to delete: ";
                cin >> pos;
                deleteFromPosition(pos);
                cout << "Node deleted from position " << pos << ".\n";
                break;
            }
            case 7: {
                displayForward();
                break;
            }
            case 8: {
                displayReverse();
                break;
            }
            case 9: {
                cout << "Enter value to search: ";
                cin >> val;
                searchValue(val);
                break;
            }
            case 10: {
                cout << "Enter position to update: ";
                cin >> pos;
                cout << "Enter new value: ";
                cin >> newVal;
                updateAtPosition(pos, newVal);
                cout << "Node at position " << pos << " updated to " << newVal << ".\n";
                break;
            }
            case 11: {
                int count = countNodes();
                if (count == 0) {
                    cout << "List is empty!\n";
                } else {
                    cout << "Total nodes in the list: " << count << "\n";
                }
                break;
            }
            case 12: {
                cout << "Exiting program!\n";
                return 0;
            }
            default: {
                cout << "Invalid choice! Please try again.\n";
            }
        }
    }
    
    return 0;
}