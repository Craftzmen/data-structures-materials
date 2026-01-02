#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = nullptr;

Node* createNode(int val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->next = nullptr;
    return newNode;
}

void display() {
    if (head == nullptr) {
        cout << "List is empty!\n";
        return;
    }
    cout << "List: ";
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << "NULL\n";
}

void insertAtBeginning(int val) {
    Node* newNode = createNode(val);
    newNode->next = head;
    head = newNode;
}

void insertAtEnd(int val) {
    Node* newNode = createNode(val);
    if (head == nullptr) {
        head = newNode;
    }
    Node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newNode;
}

void insertAtPosition(int val, int pos) {
    if (pos < 1) {
    }
    if (pos == 1) {
        insertAtBeginning(val);
    }
    Node* curr = head;
    int i = 1;
    while (i < pos - 1 && curr != nullptr) {
        curr = curr->next;
        i++;
    }
    if (curr == nullptr) {
    }
    Node* newNode = createNode(val);
    newNode->next = curr->next;
    curr->next = newNode;
}

void insertAfterValue(int val, int newVal) {
    Node* curr = head;
    while (curr != nullptr && curr->data != val) {
        curr = curr->next;
    }
    if (curr == nullptr) {
    }
    Node* newNode = createNode(newVal);
    newNode->next = curr->next;
    curr->next = newNode;
}

void deleteFromBeginning() {
    if (head == nullptr) {
    }
    Node* temp = head;
    head = head->next;
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
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
}

void deleteFromPosition(int pos) {
    if (pos < 1 || head == nullptr) {
    }
    if (pos == 1) {
        deleteFromBeginning();
    }
    Node* curr = head;
    for (int i = 1; i < pos - 1 && curr != nullptr; i++) {
        curr = curr->next;
    }
    if (curr == nullptr || curr->next == nullptr) {
    }
    Node* temp = curr->next;
    curr->next = temp->next;
    delete temp;
}

void deleteByValue(int val) {
    if (head == nullptr) {
    }
    if (head->data == val) {
        deleteFromBeginning();
    }
    Node* curr = head;
    while (curr->next != nullptr && curr->next->data != val) {
        curr = curr->next;
    }
    if (curr->next == nullptr) {
    }
    Node* temp = curr->next;
    curr->next = temp->next;
    delete temp;
}

int deleteAllByValue(int val) {
    if (head == nullptr) {
        return 0;
    }
    int deletedCount = 0;
    while (head != nullptr && head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        deletedCount++;
    }
    Node* curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->next->data == val) {
            Node* temp = curr->next;
            curr->next = temp->next;
            delete temp;
            deletedCount++;
        } else {
            curr = curr->next;
        }
    }
    return deletedCount;
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

int updateByValue(int val, int newVal) {
    if (head == nullptr) {
        return 0;
    }
    Node* curr = head;
    int count = 0;
    while (curr != nullptr) {
        if (curr->data == val) {
            curr->data = newVal;
            count++;
        }
        curr = curr->next;
    }
    return count;
}

void reverseList() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
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

int findMax() {
    if (head == nullptr) {
        return 0;
    }
    int maxVal = head->data;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data > maxVal) {
            maxVal = curr->data;
        }
        curr = curr->next;
    }
    return maxVal;
}

int findMin() {
    if (head == nullptr) {
        return 0;
    }
    int minVal = head->data;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data < minVal) {
            minVal = curr->data;
        }
        curr = curr->next;
    }
    return minVal;
}

void mergeList(Node* otherHead) {
    if (head == nullptr) {
        head = otherHead;
        return;
    }
    Node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = otherHead;
}

void displayMenu() {
    cout << "\nLinked List Operations\n";
    cout << "1. Insert at beginning\n";
    cout << "2. Insert at end\n";
    cout << "3. Insert at specific position\n";
    cout << "4. Insert after a value\n";
    cout << "5. Delete from beginning\n";
    cout << "6. Delete from end\n";
    cout << "7. Delete from specific position\n";
    cout << "8. Delete by value (first occurrence)\n";
    cout << "9. Delete all nodes with a given value\n";
    cout << "10. Search for a value\n";
    cout << "11. Update value at position\n";
    cout << "12. Update all nodes with a value\n";
    cout << "13. Reverse the list\n";
    cout << "14. Display statistics\n";
    cout << "15. Display list\n";
    cout << "16. Merge with another list\n";
    cout << "17. Exit\n";
}

int main() {
    Node* head2 = nullptr;
    int choice, val, pos, newVal;

    cout << "Singly Linked List Program\n\n";

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
                cout << "Enter value after which to insert: ";
                cin >> val;
                cout << "Enter new value to insert: ";
                cin >> newVal;
                insertAfterValue(val, newVal);
                cout << "Node " << newVal << " inserted after " << val << ".\n";
                break;
            }
            case 5: {
                deleteFromBeginning();
                cout << "Node deleted from beginning.\n";
                break;
            }
            case 6: {
                deleteFromEnd();
                cout << "Node deleted from end.\n";
                break;
            }
            case 7: {
                cout << "Enter position to delete: ";
                cin >> pos;
                deleteFromPosition(pos);
                cout << "Node deleted from position " << pos << ".\n";
                break;
            }
            case 8: {
                cout << "Enter value to delete: ";
                cin >> val;
                deleteByValue(val);
                cout << "Node " << val << " deleted.\n";
                break;
            }
            case 9: {
                cout << "Enter value to delete all occurrences: ";
                cin >> val;
                int deletedCount = deleteAllByValue(val);
                if (deletedCount > 0) {
                    cout << deletedCount << " node(s) with value " << val << " deleted.\n";
                } else {
                    cout << "Value " << val << " not found in list!\n";
                }
                break;
            }
            case 10: {
                cout << "Enter value to search: ";
                cin >> val;
                searchValue(val);
                break;
            }
            case 11: {
                cout << "Enter position to update: ";
                cin >> pos;
                cout << "Enter new value: ";
                cin >> newVal;
                updateAtPosition(pos, newVal);
                cout << "Node at position " << pos << " updated to " << newVal << ".\n";
                break;
            }
            case 12: {
                cout << "Enter value to update: ";
                cin >> val;
                cout << "Enter new value: ";
                cin >> newVal;
                int count = updateByValue(val, newVal);
                if (count > 0) {
                    cout << count << " node(s) with value " << val 
                         << " updated to " << newVal << ".\n";
                } else {
                    cout << "Value " << val << " not found in list!\n";
                }
                break;
            }
            case 13: {
                reverseList();
                cout << "List reversed successfully.\n";
                break;
            }
            case 14: {
                if (head == nullptr) {
                    cout << "List is empty! No statistics available.\n";
                } else {
                    int count = countNodes();
                    int maxVal = findMax();
                    int minVal = findMin();
                    cout << "\n=== Statistics ===\n";
                    cout << "Total nodes: " << count << "\n";
                    cout << "Maximum value: " << maxVal << "\n";
                    cout << "Minimum value: " << minVal << "\n";
                }
                break;
            }
            case 15: {
                display();
                break;
            }
            case 16: {
                cout << "Enter values for second list (enter -1 to stop): \n";
                int temp;
                while (1) {
                    cout << "Enter value: ";
                    cin >> temp;
                    if (temp == -1) break;
                    Node* tempNode = createNode(temp);
                    if (head2 == nullptr) {
                        head2 = tempNode;
                    } else {
                        Node* curr = head2;
                        while (curr->next != nullptr) {
                            curr = curr->next;
                        }
                        curr->next = tempNode;
                    }
                }
                cout << "Second list: ";
                Node* curr2 = head2;
                if (curr2 == nullptr) {
                    cout << "List is empty!\n";
                } else {
                    while (curr2 != nullptr) {
                        cout << curr2->data << " -> ";
                        curr2 = curr2->next;
                    }
                    cout << "NULL\n";
                }
                mergeList(head2);
                cout << "Lists merged successfully.\n";
                break;
            }
            case 17: {
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