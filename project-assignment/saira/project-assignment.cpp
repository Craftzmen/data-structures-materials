#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <climits>
#include <iomanip>
using namespace std;

// Question 1: Rotate array right
void recursiveReverse(double arr[], int start, int end) { 
    if (start >= end) {
        return;
    }
    double temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
    recursiveReverse(arr, start + 1, end - 1);
}
void rotateRight(double revenue[], int n, int k) {
    k = k % n;
    if (k == 0) return;
    recursiveReverse(revenue, 0, n - 1);
    recursiveReverse(revenue, 0, k - 1);
    recursiveReverse(revenue, k, n - 1);
}
void question1() {
    const int DAYS = 365;
    double dailyRevenue[DAYS];
    int k;
    for (int i = 0; i < DAYS; i++) {
        dailyRevenue[i] = i + 1.0;
    }
    cout << "Enter the number of positions to rotate to the right: ";
    cin >> k;
    if (k < 0) {
        cout << "Please enter a positive value" << endl;
        return;
    }
    rotateRight(dailyRevenue, DAYS, k);
    cout << "\nAfter rotating by " << k << " positions..." << endl;
    cout << "First 10 elements of the updated revenue array:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << fixed << setprecision(1) << dailyRevenue[i] << "  ";
    }
    cout << endl;
}

// Question 2: Rearrange negatives
void recursiveReverse(int arr[], int start, int end) {
    if (start >= end) return;
    swap(arr[start], arr[end]);
    recursiveReverse(arr, start + 1, end - 1);
}
int findFirstNegative(int arr[], int n) {
    int low = 0, high = n - 1;
    int firstNegIndex = n; // Default if no negatives found

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < 0) {
            firstNegIndex = mid;
            high = mid - 1; // Look further left
        } else {
            low = mid + 1;
        }
    }
    return firstNegIndex;
}
void rearrangeNegatives(int arr[], int n) {
    int firstNeg = findFirstNegative(arr, n);
    if (firstNeg == 0 || firstNeg == n) return;
    recursiveReverse(arr, 0, firstNeg - 1);
    recursiveReverse(arr, firstNeg, n - 1);
    recursiveReverse(arr, 0, n - 1);
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}
void question2() {
    int arr[] = {50, 30, 10, 0, -5, -15, -25};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Original Sorted (Descending): ";
    printArray(arr, n);
    rearrangeNegatives(arr, n);
    cout << "After Rearrangement:          ";
    printArray(arr, n);
}

// Question 3: Hospital queue
struct Node {
    string name;
    int emergencyLevel;
    Node* next;
    Node(string n, int level) {
        name = n;
        emergencyLevel = level;
        next = nullptr;
    }
};
class HospitalQueue {
private:
    Node* front;
    Node* tail;
public:
    HospitalQueue() {
        front = nullptr;
        tail = nullptr;
    }
    void InsertPriority(string name, int level) {
        Node* newNode = new Node(name, level);
        if (front == nullptr) {
            front = tail = newNode;
            return;
        }
        if (level >= front->emergencyLevel) {
            newNode->next = front;
            front = newNode;
        } else {
            Node* temp = front;
            while (temp->next != nullptr && temp->next->emergencyLevel >= level) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
    }
    void Display() {
        if (front == nullptr) {
            cout << "The queue is currently empty." << endl;
            return;
        }
        Node* temp = front;
        cout << "\n--- Current Hospital Patient List ---" << endl;
        cout << "System Status: [FRONT: " << front->name << " | TAIL: " << tail->name << "]" << endl;
        cout << "--------------------------------------" << endl;
        while (temp != nullptr) {
            cout << "Patient Name: " << temp->name
                 << "\t | Emergency Level: " << temp->emergencyLevel << endl;
            temp = temp->next;
        }
        cout << "--------------------------------------" << endl;
    }
};
void question3() {
    HospitalQueue hq;
    hq.InsertPriority("Ali", 2);
    hq.InsertPriority("Noor", 5);
    hq.InsertPriority("Ayesha", 5);
    hq.InsertPriority("Laiba", 8);
    hq.Display();
}

// Question 4: Palindrome linked list
struct NodeInt {
    int data;
    NodeInt* next;
    NodeInt(int val) : data(val), next(nullptr) {}
};
NodeInt* reverseList(NodeInt* head) {
    NodeInt* prev = nullptr;
    NodeInt* curr = head;
    while (curr != nullptr) {
        NodeInt* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}
bool isPalindrome(NodeInt* head) {
    if (!head || !head->next) return true;
    NodeInt* slow = head;
    NodeInt* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    NodeInt* secondHalfHead = reverseList(slow->next);
    NodeInt* firstHalfPointer = head;
    NodeInt* secondHalfPointer = secondHalfHead;
    bool match = true;
    while (secondHalfPointer != nullptr) {
        if (firstHalfPointer->data != secondHalfPointer->data) {
            match = false;
            break;
        }
        firstHalfPointer = firstHalfPointer->next;
        secondHalfPointer = secondHalfPointer->next;
    }
    slow->next = reverseList(secondHalfHead);
    return match;
}
void printListInt(NodeInt* head) {
    NodeInt* temp = head;
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
void question4() {
    int n, value;
    NodeInt* head = nullptr;
    NodeInt* tail = nullptr;
    cout << "Enter the number of elements in your list: ";
    cin >> n;
    if (n <= 0) {
        cout << "List is empty." << endl;
        return;
    }
    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        NodeInt* newNode = new NodeInt(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "\nYour List: ";
    printListInt(head);
    if (isPalindrome(head)) {
        cout << "RESULT: Yes, it is a Palindrome!" << endl;
    } else {
        cout << "RESULT: No, it is NOT a Palindrome." << endl;
    }
}

// Question 5: Merge sorted lists
struct NodeDouble {
    double price;
    NodeDouble* next;
    NodeDouble(double p) : price(p), next(nullptr) {}
};
NodeDouble* mergeSortedLists(NodeDouble* headA, NodeDouble* headB) {
    if (!headA) return headB;
    if (!headB) return headA;
    NodeDouble* dummy = new NodeDouble(0);
    NodeDouble* current = dummy;
    while (headA != nullptr && headB != nullptr) {
        if (headA->price <= headB->price) {
            current->next = headA;
            headA = headA->next;
        } else {
            current->next = headB;
            headB = headB->next;
        }
        current = current->next;
    }
    if (headA != nullptr) current->next = headA;
    else current->next = headB;
    NodeDouble* resultHead = dummy->next;
    delete dummy;
    return resultHead;
}
NodeDouble* createListDouble(int n) {
    if (n <= 0) return nullptr;
    double p;
    cout << "Enter price: ";
    cin >> p;
    NodeDouble* head = new NodeDouble(p);
    NodeDouble* tail = head;
    for (int i = 1; i < n; i++) {
        cout << "Enter price: ";
        cin >> p;
        tail->next = new NodeDouble(p);
        tail = tail->next;
    }
    return head;
}
void printListDouble(NodeDouble* head) {
    while (head) {
        cout << head->price << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}
void question5() {
    int n1, n2;
    cout << "--- Company A (Sorted Stock Prices) ---" << endl;
    cout << "How many records for Company A? ";
    cin >> n1;
    NodeDouble* listA = createListDouble(n1);
    cout << "\n--- Company B (Sorted Stock Prices) ---" << endl;
    cout << "How many records for Company B? ";
    cin >> n2;
    NodeDouble* listB = createListDouble(n2);
    cout << "\nMerging lists..." << endl;
    NodeDouble* mergedList = mergeSortedLists(listA, listB);
    cout << "Final Merged Sorted List: " << endl;
    printListDouble(mergedList);
}

// Question 6: Cycle detection
struct NodeChar {
    string data;
    NodeChar* next;
    NodeChar(string val) : data(val), next(nullptr) {}
};
class CycleDetector {
public:
    NodeChar* findCycleStart(NodeChar* head) {
        if (!head || !head->next) return nullptr;
        NodeChar* slow = head;
        NodeChar* fast = head;
        bool cycleFound = false;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                cycleFound = true;
                break;
            }
        }
        if (!cycleFound) return nullptr;
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
    void printCycleList(NodeChar* head, int n, int pos) {
        NodeChar* temp = head;
        for (int i = 0; i < n; i++) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        NodeChar* loopBack = head;
        for (int i = 0; i < pos; i++) loopBack = loopBack->next;
        cout << "(back to " << loopBack->data << ")" << endl;
    }
};
void question6() {
    CycleDetector detector;
    int n, pos;
    string val;
    cout << "Enter number of nodes: ";
    cin >> n;
    if (n <= 0) return;
    NodeChar* head = nullptr;
    NodeChar* tail = nullptr;
    NodeChar* cyclePoint = nullptr;
    for (int i = 0; i < n; i++) {
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> val;
        NodeChar* newNode = new NodeChar(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "Enter the index (0 to " << n-1 << ") to loop back to: ";
    cin >> pos;
    if (pos >= 0 && pos < n) {
        NodeChar* temp = head;
        for (int i = 0; i < pos; i++) temp = temp->next;
        tail->next = temp;
    }
    cout << "\n------------------------------------------" << endl;
    cout << "Question 6/20: Detect Cycle Start (Floyd's)" << endl;
    cout << "------------------------------------------" << endl;
    cout << "List with cycle: ";
    detector.printCycleList(head, n, pos);
    NodeChar* startNode = detector.findCycleStart(head);
    if (startNode) {
        cout << "Cycle detected! Start node value: " << startNode->data << endl;
    } else {
        cout << "No cycle detected." << endl;
    }
}

// Question 7: Remove consecutive absents
struct NodeInt2 {
    int data;
    NodeInt2* next;
    NodeInt2(int val) : data(val), next(nullptr) {}
};
class AttendanceList {
public:
    NodeInt2* RemoveConsecutiveAbsents(NodeInt2* head, int k) {
        NodeInt2* dummy = new NodeInt2(-1);
        dummy->next = head;
        NodeInt2* prev = dummy;
        NodeInt2* current = head;
        while (current != nullptr) {
            if (current->data == 0) {
                NodeInt2* temp = current;
                int count = 0;
                while (temp != nullptr && temp->data == 0) {
                    count++;
                    temp = temp->next;
                }
                if (count >= k) {
                    prev->next = temp;
                    current = temp;
                } else {
                    prev = current;
                    current = current->next;
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
        return dummy->next;
    }
    void DisplayList(NodeInt2* head) {
        if (!head) {
            cout << "[]" << endl;
            return;
        }
        cout << "[ ";
        NodeInt2* temp = head;
        while (temp) {
            cout << temp->data;
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << " ]" << endl;
    }
};
void question7() {
    AttendanceList listManager;
    int k = 3;
    vector<int> attendance = {1, 0, 0, 0, 1, 0, 1};
    NodeInt2* head = nullptr;
    NodeInt2* tail = nullptr;
    for (int val : attendance) {
        NodeInt2* newNode = new NodeInt2(val);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "Student attendance: 1=present, 0=absent." << endl;
    cout << "RemoveConsecutiveAbsents(k): Delete >=k consecutive 0's." << endl << endl;
    cout << "Original List (1=Present, 0=Absent): ";
    listManager.DisplayList(head);
    cout << "Remove consecutive absents >= " << k << endl;
    head = listManager.RemoveConsecutiveAbsents(head, k);
    cout << "Result List:                         ";
    listManager.DisplayList(head);
}

// Question 8: Delete node safely
void deleteNodeSafely(NodeInt2** head_ref, NodeInt2* target) {
    if (*head_ref == nullptr || target == nullptr) return;
    if (*head_ref == target) {
        *head_ref = target->next;
        delete target;
        return;
    }
    if (target->next != nullptr) {
        NodeInt2* nextNode = target->next;
        target->data = nextNode->data;
        target->next = nextNode->next;
        delete nextNode;
    } else {
        NodeInt2* prev = *head_ref;
        while (prev->next != target) {
            prev = prev->next;
        }
        prev->next = nullptr;
        delete target;
        cout << "\n[System]: Tail node safely deleted using O(n) traversal." << endl;
    }
}
void printListInt2(NodeInt2* head) {
    if (!head) { cout << "Empty List"; return; }
    while (head) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}
void question8() {
    int n, val, delVal;
    NodeInt2* head = nullptr;
    NodeInt2* tail = nullptr;
    cout << "Enter number of nodes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> val;
        NodeInt2* newNode = new NodeInt2(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "\nOriginal List: ";
    printListInt2(head);
    cout << "\nEnter the value of the node you want to delete: ";
    cin >> delVal;
    NodeInt2* targetNode = head;
    while (targetNode != nullptr && targetNode->data != delVal) {
        targetNode = targetNode->next;
    }
    if (targetNode == nullptr) {
        cout << "Value not found in list." << endl;
    } else {
        deleteNodeSafely(&head, targetNode);
        cout << "Updated List:  ";
        printListInt2(head);
    }
}

// Question 9: Deque
struct NodeInt3 {
    int data;
    NodeInt3* next;
    NodeInt3* prev;
    NodeInt3(int val) : data(val), next(nullptr), prev(nullptr) {}
};
class Deque {
private:
    NodeInt3* front;
    NodeInt3* rear;
public:
    Deque() : front(nullptr), rear(nullptr) {}
    void InsertFront(int val) {
        NodeInt3* newNode = new NodeInt3(val);
        if (front == nullptr) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        cout << "Inserted " << val << " at Front." << endl;
    }
    void InsertRear(int val) {
        NodeInt3* newNode = new NodeInt3(val);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
        cout << " Inserted " << val << " at Rear." << endl;
    }
    void RemoveFront() {
        if (front == nullptr) {
            cout << " Deque is empty." << endl;
            return;
        }
        NodeInt3* temp = front;
        int val = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        } else {
            front->prev = nullptr;
        }
        delete temp;
        cout << " Removed " << val << " from Front." << endl;
    }
    void RemoveRear() {
        if (rear == nullptr) {
            cout << " Deque is empty." << endl;
            return;
        }
        NodeInt3* temp = rear;
        int val = temp->data;
        rear = rear->prev;
        if (rear == nullptr) {
            front = nullptr;
        } else {
            rear->next = nullptr;
        }
        delete temp;
        cout << " Removed " << val << " from Rear." << endl;
    }
    void Display() {
        if (!front) { cout << "Deque is empty." << endl; return; }
        NodeInt3* temp = front;
        cout << "Current Deque: NULL <- ";
        while (temp) {
            cout << "" << temp->data << "";
            if (temp->next) cout << " <=> ";
            temp = temp->next;
        }
        cout << " -> NULL" << endl;
    }
};
void question9() {
    Deque dq;
    dq.InsertRear(10);
    dq.InsertRear(20);
    dq.InsertFront(5);
    dq.Display();
    dq.RemoveRear();
    dq.RemoveFront();
    dq.Display();
    dq.RemoveFront();
    dq.RemoveFront();
}

// Question 10: Merge sort linked list
NodeInt2* getTail(NodeInt2* head) {
    while (head && head->next) head = head->next;
    return head;
}
NodeInt2* sortedMerge(NodeInt2* a, NodeInt2* b) {
    if (!a) return b;
    if (!b) return a;
    NodeInt2* result = nullptr;
    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}
void split(NodeInt2* source, NodeInt2** front, NodeInt2** back) {
    NodeInt2* slow = source;
    NodeInt2* fast = source->next;
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}
NodeInt2* mergeSort(NodeInt2* head) {
    if (!head || !head->next) return head;
    NodeInt2 *a, *b;
    split(head, &a, &b);
    a = mergeSort(a);
    b = mergeSort(b);
    NodeInt2* tailA = getTail(a);
    if (tailA->data <= b->data) {
        tailA->next = b;
        return a;
    }
    return sortedMerge(a, b);
}
void printListInt3(NodeInt2* node) {
    while (node) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}
void question10() {
    int vals[] = {12, 3, 18, 5, 1, 9};
    NodeInt2 *head = new NodeInt2(vals[0]), *tail = head;
    for(int i=1; i<6; i++) {
        tail->next = new NodeInt2(vals[i]);
        tail = tail->next;
    }
    cout << "Original List: "; printListInt3(head);
    head = mergeSort(head);
    cout << "Sorted List:   "; printListInt3(head);
}

// Question 11: Sort stack
struct NodeInt4 {
    int data;
    NodeInt4* next;
    NodeInt4(int val) : data(val), next(nullptr) {}
};
class MyStack {
public:
    NodeInt4* top;
    MyStack() : top(nullptr) {}
    void push(int val) {
        NodeInt4* newNode = new NodeInt4(val);
        newNode->next = top;
        top = newNode;
    }
    int pop() {
        if (isEmpty()) return -1;
        int val = top->data;
        NodeInt4* temp = top;
        top = top->next;
        delete temp;
        return val;
    }
    int peek() {
        return (top != nullptr) ? top->data : -1;
    }
    bool isEmpty() {
        return top == nullptr;
    }
};
void sortedInsert(MyStack& s, int element) {
    if (s.isEmpty() || element <= s.peek()) {
        s.push(element);
        return;
    }
    int temp = s.pop();
    sortedInsert(s, element);
    s.push(temp);
}
void sortStack(MyStack& s) {
    if (s.isEmpty()) return;
    int temp = s.pop();
    sortStack(s);
    sortedInsert(s, temp);
}
void printStack(MyStack s) {
    NodeInt4* temp = s.top;
    while (temp) {
        cout << "| " << temp->data << " |" << endl;
        temp = temp->next;
    }
}
void question11() {
    MyStack s;
    s.push(30);
    s.push(-5);
    s.push(18);
    s.push(14);
    s.push(-3);
    cout << "Original Stack (Top to Bottom):" << endl;
    printStack(s);
    sortStack(s);
    cout << "\nSorted Stack (Smallest at Top):" << endl;
    printStack(s);
}

// Question 12: Bracket validation
struct NodeChar2 {
    char bracket;
    NodeChar2* next;
    NodeChar2(char b) : bracket(b), next(nullptr) {}
};
class BracketStack {
private:
    NodeChar2* top;
public:
    BracketStack() : top(nullptr) {}
    void push(char b) {
        NodeChar2* newNode = new NodeChar2(b);
        newNode->next = top;
        top = newNode;
    }
    char pop() {
        if (isEmpty()) return '\0';
        char b = top->bracket;
        NodeChar2* temp = top;
        top = top->next;
        delete temp;
        return b;
    }
    char peek() {
        return (top != nullptr) ? top->bracket : '\0';
    }
    bool isEmpty() {
        return top == nullptr;
    }
};
char getMatching(char b) {
    if (b == '(') return ')';
    if (b == '{') return '}';
    if (b == '[') return ']';
    if (b == '<') return '>';
    return '\0';
}
void validateExpression(string expr) {
    BracketStack s;
    bool errorFound = false;
    cout << "Expression: " << expr << endl;
    for (int i = 0; i < expr.length(); i++) {
        char current = expr[i];
        if (current == '(' || current == '{' || current == '[' || current == '<') {
            s.push(current);
        } else if (current == ')' || current == '}' || current == ']' || current == '>') {
            if (s.isEmpty()) {
                cout << " Extra closing bracket '" << current << "' found at position " << i + 1 << endl;
                errorFound = true;
                break;
            }
            char lastOpened = s.pop();
            char expected = getMatching(lastOpened);
            if (current != expected) {
                cout << " Wrong-type mismatch at position " << i + 1
                     << ". Expected '" << expected << "' but found '" << current << "'" << endl;
                errorFound = true;
                break;
            }
        }
    }
    if (!errorFound) {
        if (!s.isEmpty()) {
            cout << " Unclosed bracket(s) at end. Remaining: ";
            while (!s.isEmpty()) {
                cout << "'" << s.pop() << "' ";
            }
            cout << endl;
        } else {
            cout << " The expression is perfectly balanced." << endl;
        }
    }
}
void question12() {
    validateExpression("{[()<>]}");
    validateExpression("{(]}");
    validateExpression("()>");
    validateExpression("({[");
}

// Question 13: Stack using queues
struct NodeInt5 {
    int data;
    NodeInt5* next;
    NodeInt5(int val) : data(val), next(nullptr) {}
};
class MyQueue {
public:
    NodeInt5 *front, *rear;
    MyQueue() : front(nullptr), rear(nullptr) {}
    void enqueue(int val) {
        NodeInt5* newNode = new NodeInt5(val);
        if (!rear) { front = rear = newNode; return; }
        rear->next = newNode;
        rear = newNode;
    }
    int dequeue() {
        if (!front) return -1;
        int val = front->data;
        NodeInt5* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return val;
    }
    bool isEmpty() { return front == nullptr; }
};
class StackUsingQueues {
    MyQueue q1, q2;
public:
    void push(int x) {
        q2.enqueue(x);
        while (!q1.isEmpty()) {
            q2.enqueue(q1.dequeue());
        }
        MyQueue temp = q1;
        q1 = q2;
        q2 = temp;
        cout << " Pushed " << x << " to Stack." << endl;
    }
    void pop() {
        if (q1.isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return;
        }
        cout << " Popped " << q1.dequeue() << " from Stack." << endl;
    }
    void display() {
        NodeInt5* temp = q1.front;
        cout << "Stack (Top to Bottom): ";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
void question13() {
    StackUsingQueues s;
    s.push(5);
    s.push(7);
    s.push(1);
    s.push(3);
    s.display();
    s.pop();
    s.display();
}

// Question 14: Sort queue using stack
struct NodeInt6 {
    int data;
    NodeInt6* next;
    NodeInt6(int val) : data(val), next(nullptr) {}
};
class MyStack2 {
public:
    NodeInt6* top;
    MyStack2() : top(nullptr) {}
    void push(int v) {
        NodeInt6* n = new NodeInt6(v);
        n->next = top;
        top = n;
    }
    int pop() {
        if (!top) return -1;
        int v = top->data;
        NodeInt6* t = top;
        top = top->next;
        delete t;
        return v;
    }
    int peek() { return top ? top->data : -1; }
    bool isEmpty() { return top == nullptr; }
};
class MyQueue2 {
public:
    NodeInt6 *f, *r;
    MyQueue2() : f(nullptr), r(nullptr) {}
    void enqueue(int v) {
        NodeInt6* n = new NodeInt6(v);
        if (!r) { f = r = n; return; }
        r->next = n;
        r = n;
    }
    int dequeue() {
        if (!f) return -1;
        int v = f->data;
        NodeInt6* t = f;
        f = f->next;
        if (!f) r = nullptr;
        delete t;
        return v;
    }
    bool isEmpty() { return f == nullptr; }
    void display() {
        if (!f) { cout << "Empty"; return; }
        NodeInt6* temp = f;
        while (temp) {
            cout << "" << temp->data << "";
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }
};
void question14() {
    MyQueue2 Q1, Q2;
    MyStack2 S1;
    int arr[] = {3, 1, 4, 2};
    for(int i = 0; i < 4; i++) Q1.enqueue(arr[i]);
    cout << "Original Queue (Station A): ";
    Q1.display();
    while (!Q1.isEmpty()) {
        int current = Q1.dequeue();
        while (!S1.isEmpty() && S1.peek() < current) {
            Q2.enqueue(S1.pop());
        }
        S1.push(current);
        while (!Q2.isEmpty()) {
            S1.push(Q2.dequeue());
        }
    }
    while (!S1.isEmpty()) {
        Q1.enqueue(S1.pop());
    }
    cout << "Sorted Queue:  ";
    Q1.display();
}

// Question 15: Min stack
struct NodeLong {
    long long data;
    NodeLong* next;
    NodeLong(long long val) : data(val), next(nullptr) {}
};
class MinStack {
private:
    NodeLong* topNode;
    long long minVal;
public:
    MinStack() : topNode(nullptr), minVal(LLONG_MAX) {}
    void push(int x) {
        long long val = x;
        if (topNode == nullptr) {
            topNode = new NodeLong(val);
            minVal = val;
        } else {
            if (val < minVal) {
                topNode = new NodeLong(2 * val - minVal);
                minVal = val;
            } else {
                topNode = new NodeLong(val);
            }
        }
        cout << "Push(" << x << ")" << endl;
        displayStatus();
    }
    void pop() {
        if (topNode == nullptr) return;
        long long y = topNode->data;
        NodeLong* temp = topNode;
        topNode = topNode->next;
        if (y < minVal) {
            minVal = 2 * minVal - y;
        }
        delete temp;
        cout << "Pop()" << endl;
        displayStatus();
    }
    void displayStatus() {
        if (topNode == nullptr) {
            cout << "  Stack Empty" << endl;
        } else {
            long long currentTop = (topNode->data < minVal) ? minVal : topNode->data;
            cout << "  Top: " << currentTop << ", Min: " << minVal << endl;
        }
    }
};
void question15() {
    MinStack s;
    s.push(10);
    s.push(5);
    s.push(15);
    s.push(2);
    s.pop();
    s.pop();
}

// Question 16: Remove duplicates
void removeDuplicates(NodeInt2* head) {
    if (head == nullptr) return;
    unordered_set<int> seen;
    NodeInt2* current = head;
    NodeInt2* prev = nullptr;
    while (current != nullptr) {
        if (seen.find(current->data) != seen.end()) {
            prev->next = current->next;
            delete current;
        } else {
            seen.insert(current->data);
            prev = current;
        }
        current = prev->next;
    }
}
void printListInt4(NodeInt2* head) {
    while (head) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}
void question16() {
    int n, val;
    NodeInt2 *head = nullptr, *tail = nullptr;
    cout << "Enter number of elements: ";
    cin >> n;
    if (n <= 0) return;
    cout << "Enter the values: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> val;
        NodeInt2* newNode = new NodeInt2(val);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "\nOriginal List: ";
    printListInt4(head);
    removeDuplicates(head);
    cout << "After Removing Duplicates: ";
    printListInt4(head);
}

// Question 17: Nth to last
NodeInt2* findNthToLast(NodeInt2* head, int n) {
    if (head == nullptr || n <= 0) return nullptr;
    NodeInt2* fast = head;
    NodeInt2* slow = head;
    for (int i = 0; i < n; i++) {
        if (fast == nullptr) return nullptr;
        fast = fast->next;
    }
    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
void question17() {
    int total, val, n;
    NodeInt2 *head = nullptr, *tail = nullptr;
    cout << "Enter number of elements: ";
    cin >> total;
    if (total <= 0) return;
    cout << "Enter " << total << " integers:" << endl;
    for (int i = 0; i < total; i++) {
        cin >> val;
        NodeInt2* newNode = new NodeInt2(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "Enter N (to find Nth from last): ";
    cin >> n;
    NodeInt2* result = findNthToLast(head, n);
    if (result) {
        cout << "Element is: " << result->data << endl;
    } else {
        cout << "Invalid position or list too short." << endl;
    }
}

// Question 18: Delete node
struct NodeChar3 {
    char data;
    NodeChar3* next;
    NodeChar3(char val) : data(val), next(nullptr) {}
};
void deleteNode(NodeChar3* node) {
    if (node == nullptr || node->next == nullptr) {
        return;
    }
    NodeChar3* nextNode = node->next;
    node->data = nextNode->data;
    node->next = nextNode->next;
    delete nextNode;
}
void printListChar(NodeChar3* head) {
    while (head) {
        cout << head->data << (head->next ? "->" : "");
        head = head->next;
    }
    cout << endl;
}
void question18() {
    NodeChar3* a = new NodeChar3('a');
    NodeChar3* b = new NodeChar3('b');
    NodeChar3* c = new NodeChar3('c');
    NodeChar3* d = new NodeChar3('d');
    NodeChar3* e = new NodeChar3('e');
    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    cout << "Original: ";
    printListChar(a);
    deleteNode(c);
    cout << "After deleting 'c': ";
    printListChar(a);
}

// Question 19: Add two numbers
NodeInt2* addTwoNumbers(NodeInt2* l1, NodeInt2* l2) {
    NodeInt2* dummy = new NodeInt2(0);
    NodeInt2* curr = dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->data;
            l2 = l2->next;
        }
        carry = sum / 10;
        curr->next = new NodeInt2(sum % 10);
        curr = curr->next;
    }
    NodeInt2* result = dummy->next;
    delete dummy;
    return result;
}
NodeInt2* createListInt(int n) {
    if (n <= 0) return nullptr;
    int val;
    cin >> val;
    NodeInt2* head = new NodeInt2(val);
    NodeInt2* tail = head;
    for (int i = 1; i < n; i++) {
        cin >> val;
        tail->next = new NodeInt2(val);
        tail = tail->next;
    }
    return head;
}
void printInt(NodeInt2* n) {
    while (n) {
        cout << n->data << (n->next ? " -> " : "");
        n = n->next;
    }
    cout << endl;
}
void question19() {
    int n1, n2;
    cout << "Enter size and digits for List 1: ";
    cin >> n1;
    NodeInt2* l1 = createListInt(n1);
    cout << "Enter size and digits for List 2: ";
    cin >> n2;
    NodeInt2* l2 = createListInt(n2);
    NodeInt2* res = addTwoNumbers(l1, l2);
    cout << "Output: ";
    printInt(res);
}

// Question 20: Find beginning of loop
struct NodeChar4 {
    char data;
    NodeChar4* next;
    NodeChar4(char val) : data(val), next(nullptr) {}
};
NodeChar4* findBeginning(NodeChar4* head) {
    if (!head || !head->next) return nullptr;
    NodeChar4* slow = head;
    NodeChar4* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (!fast || !fast->next) return nullptr;
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
void question20() {
    int n, pos;
    char val;
    cout << "Enter number of nodes: ";
    cin >> n;
    if (n <= 0) return;
    NodeChar4 *head = nullptr, *tail = nullptr, *loopNode = nullptr;
    NodeChar4* nodes[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> val;
        nodes[i] = new NodeChar4(val);
        if (!head) head = tail = nodes[i];
        else { tail->next = nodes[i]; tail = nodes[i]; }
    }
    cout << "Enter index (0 to " << n - 1 << ") to loop back to: ";
    cin >> pos;
    if (pos >= 0 && pos < n) tail->next = nodes[pos];
    NodeChar4* result = findBeginning(head);
    if (result) cout << "Loop begins at node: " << result->data << endl;
    else cout << "No loop found." << endl;
}

// Question 28: Menu
int main() {
    int choice;
    do {
        cout << "\n=== Data Structures and Algorithms Menu ===" << endl;
        cout << "Choose a question to run (1-20) or 0 to exit:" << endl;
        for (int i = 1; i <= 20; i++) {
            cout << i << ". Question " << i << endl;
        }
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: question1(); break;
            case 2: question2(); break;
            case 3: question3(); break;
            case 4: question4(); break;
            case 5: question5(); break;
            case 6: question6(); break;
            case 7: question7(); break;
            case 8: question8(); break;
            case 9: question9(); break;
            case 10: question10(); break;
            case 11: question11(); break;
            case 12: question12(); break;
            case 13: question13(); break;
            case 14: question14(); break;
            case 15: question15(); break;
            case 16: question16(); break;
            case 17: question17(); break;
            case 18: question18(); break;
            case 19: question19(); break;
            case 20: question20(); break;
            case 0: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    return 0;
}