#include <iostream>

using namespace std;

const int SIZE = 5;

struct Stack {
    int array[SIZE];
    int top;
};

int push(int value, Stack &s) {
    if (s.top == SIZE - 1) {
        return -1;
    }
    s.top++;
    s.array[s.top] = value;
    return 0;
}

int pop(Stack newStack) {
    if (newStack.top == -1) {
        return -1;
    }
    else {
        newStack.top--;
        return 0;
    }
}

int peek(Stack &newStack) {
     if (newStack.top == -1) {
        return -1;
    }
    else {
        return newStack.array[newStack.top];
    }
}

void display(Stack &newStack) {
    if (newStack.top == -1) {
        cout << "Stack is empty.\n";
    }
    for (int i = newStack.top; i>= 0; i--) {
        cout << newStack.array[i] << " ";
    }
}

int main() {
    int value;
    Stack newStack;

    newStack.top = -1;

    cout << "Enter value to push: ";
    cin >> value;

    int pushResult = push(value, newStack);

    if (pushResult != -1) {
        cout << "Pushed " << value << " to stack.\n";
    } else {
        cout << "Stack Overflow. Cannot push " << value << ".\n";
    }

    cout << "Stack Display" << endl;
    display(newStack);
    cout << endl;

    return 0;
}