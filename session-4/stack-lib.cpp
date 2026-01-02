#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> s;

    cout << "Stack Implementation" << endl;

    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Peek\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> value;
                s.push(value);
                cout << value << " pushed onto stack." << endl;
                break;
            case 2:
                if (!s.empty()) {
                    cout << s.top() << " popped from stack." << endl;
                    s.pop();
                } else {
                    cout << "Stack is empty. Cannot pop." << endl;
                }
                break;
            case 3:
                if (!s.empty()) {
                    cout << "Top element is: " << s.top() << endl;
                } else {
                    cout << "Stack is empty." << endl;
                }
                break;
            case 4:
                if (s.empty()) {
                    cout << "Stack is empty." << endl;
                } else {
                    stack<int> temp = s;
                    cout << "Stack elements: ";
                    while (!temp.empty()) {
                        cout << temp.top() << " ";
                        temp.pop();
                    }
                    cout << endl;
                }
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}