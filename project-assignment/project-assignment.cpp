#include <iostream>
#include <string>
#include <stack>
#include <climits>
#include <algorithm>
#include <unordered_set>

using namespace std;

class ArrayProblems {
public:
    void reverse(int arr[], int start, int end) {
        if (start >= end) return;
        swap(arr[start], arr[end]);
        reverse(arr, start + 1, end - 1);
    }

    void rotateRight(int arr[], int n, int k) {
        k = k % n;
        if (k == 0) return;
        reverse(arr, 0, n - 1);
        reverse(arr, 0, k - 1);
        reverse(arr, k, n - 1);
    }

    void rearrangeNegativesFirst(int arr[], int n) {
        int i = 0;
        int j = n - 1;
        while (i < j) {
            if (arr[i] < 0) {
                i++;
            } else if (arr[j] >= 0) {
                j--;
            } else {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
    }
};

class QueueProblems {
public:
    struct Node {
        string name;
        int emergencyLevel;
        Node* next;
    };

    Node* head;
    Node* tail;

    QueueProblems() {
        head = nullptr;
        tail = nullptr;
    }

    ~QueueProblems() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void InsertPriority(string name, int emergencyLevel) {
        Node* newNode = new Node{name, emergencyLevel, nullptr};
        if (!head) {
            head = tail = newNode;
            return;
        }
        if (emergencyLevel < head->emergencyLevel) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* curr = head;
        while (curr->next && curr->next->emergencyLevel <= emergencyLevel) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
};

class SimpleNode {
public:
    int data;
    SimpleNode* next;
    SimpleNode(int val) : data(val), next(nullptr) {}
};

class SimpleQueue {
private:
    SimpleNode* front;
    SimpleNode* rear;
public:
    SimpleQueue() : front(nullptr), rear(nullptr) {}
    ~SimpleQueue() {
        while (front) {
            SimpleNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
    void enqueue(int val) {
        SimpleNode* newNode = new SimpleNode(val);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    int dequeue() {
        if (!front) return -1;
        int val = front->data;
        SimpleNode* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return val;
    }
    bool isEmpty() {
        return front == nullptr;
    }
};

class SimpleStack {
private:
    SimpleNode* top;
public:
    SimpleStack() : top(nullptr) {}
    ~SimpleStack() {
        while (top) {
            SimpleNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
    void push(int val) {
        SimpleNode* newNode = new SimpleNode(val);
        newNode->next = top;
        top = newNode;
    }
    int pop() {
        if (!top) return -1;
        int val = top->data;
        SimpleNode* temp = top;
        top = top->next;
        delete temp;
        return val;
    }
    bool isEmpty() {
        return top == nullptr;
    }
};

void sortQueue(SimpleQueue& input, SimpleQueue& output) {
    SimpleStack S;
    SimpleQueue tempQ;
    while (!input.isEmpty()) {
        int minVal = INT_MAX;
        while (!input.isEmpty()) {
            int x = input.dequeue();
            S.push(x);
            if (x < minVal) minVal = x;
        }
        bool found = false;
        while (!S.isEmpty()) {
            int x = S.pop();
            if (x == minVal && !found) {
                output.enqueue(x);
                found = true;
            } else {
                tempQ.enqueue(x);
            }
        }
        while (!tempQ.isEmpty()) {
            input.enqueue(tempQ.dequeue());
        }
    }
}

class StackUsingQueues {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    struct Queue {
        Node* front;
        Node* rear;
        Queue() : front(nullptr), rear(nullptr) {}
        ~Queue() {
            while (front) {
                Node* temp = front;
                front = front->next;
                delete temp;
            }
        }
        void enqueue(int val) {
            Node* newNode = new Node(val);
            if (!rear) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }
        int dequeue() {
            if (!front) return -1;
            int val = front->data;
            Node* temp = front;
            front = front->next;
            if (!front) rear = nullptr;
            delete temp;
            return val;
        }
        bool isEmpty() {
            return front == nullptr;
        }
    };

    Queue q1, q2;

public:
    ~StackUsingQueues() {}
    void push(int val) {
        while (!q1.isEmpty()) {
            q2.enqueue(q1.dequeue());
        }
        q1.enqueue(val);
        while (!q2.isEmpty()) {
            q1.enqueue(q2.dequeue());
        }
    }
    int pop() {
        if (q1.isEmpty()) return -1;
        return q1.dequeue();
    }
    int top() {
        if (q1.isEmpty()) return -1;
        return q1.front->data;
    }
    bool isEmpty() {
        return q1.isEmpty();
    }
};

class LinkedListProblems {
public:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* reverseList(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    bool isPalindrome(Node* head) {
        if (!head || !head->next) return true;

        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node* second = reverseList(slow->next);
        slow->next = nullptr;

        Node* first = head;
        bool isPal = true;
        while (first && second) {
            if (first->data != second->data) {
                isPal = false;
                break;
            }
            first = first->next;
            second = second->next;
        }

        slow->next = reverseList(second);

        return isPal;
    }

    Node* mergeSortedLists(Node* list1, Node* list2) {
        if (!list1) return list2;
        if (!list2) return list1;
        Node* head;
        if (list1->data < list2->data) {
            head = list1;
            list1 = list1->next;
        } else {
            head = list2;
            list2 = list2->next;
        }
        Node* curr = head;
        while (list1 && list2) {
            if (list1->data < list2->data) {
                curr->next = list1;
                list1 = list1->next;
            } else {
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }
        if (list1) curr->next = list1;
        if (list2) curr->next = list2;
        return head;
    }

    Node* detectCycleStart(Node* head) {
        if (!head || !head->next) return nullptr;
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }

    Node* RemoveConsecutiveAbsents(Node* head, int k) {
        if (!head || k <= 0) return head;
        Node* dummy = new Node(-1);
        dummy->next = head;
        Node* prev = dummy;
        while (prev->next) {
            Node* curr = prev->next;
            if (curr->data == 0) {
                int count = 0;
                Node* temp = curr;
                while (temp && temp->data == 0) {
                    count++;
                    temp = temp->next;
                }
                if (count >= k) {
                    prev->next = temp;
                    Node* toDel = curr;
                    while (toDel != temp) {
                        Node* next = toDel->next;
                        delete toDel;
                        toDel = next;
                    }
                } else {
                    for (int i = 0; i < count; i++) {
                        prev = prev->next;
                    }
                }
            } else {
                prev = prev->next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }

    bool deleteNode(Node* node) {
        if (!node || !node->next) return false;
        Node* next = node->next;
        node->data = next->data;
        node->next = next->next;
        delete next;
        return true;
    }

    Node* findMid(Node* head) {
        if (!head) return nullptr;
        Node* slow = head;
        Node* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node* mergeSort(Node* head) {
        if (!head || !head->next) return head;
        bool sorted = true;
        Node* curr = head;
        while (curr->next) {
            if (curr->data > curr->next->data) {
                sorted = false;
                break;
            }
            curr = curr->next;
        }
        if (sorted) return head;
        Node* mid = findMid(head);
        Node* left = head;
        Node* right = mid->next;
        mid->next = nullptr;
        left = mergeSort(left);
        right = mergeSort(right);
        return mergeSortedLists(left, right);
    }

    Node* removeDuplicates(Node* head) {
        if (!head) return head;
        unordered_set<int> seen;
        Node* curr = head;
        Node* prev = nullptr;
        while (curr) {
            if (seen.find(curr->data) != seen.end()) {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            } else {
                seen.insert(curr->data);
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }

    Node* findNthFromEnd(Node* head, int n) {
        if (!head || n <= 0) return nullptr;
        Node* fast = head;
        Node* slow = head;
        for (int i = 0; i < n; i++) {
            if (!fast) return nullptr;
            fast = fast->next;
        }
        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }

    void deleteMiddleNode(Node* node) {
        if (!node || !node->next) return;
        Node* next = node->next;
        node->data = next->data;
        node->next = next->next;
        delete next;
    }

    Node* addTwoNumbers(Node* l1, Node* l2) {
        Node* dummy = new Node(0);
        Node* curr = dummy;
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
            curr->next = new Node(sum % 10);
            curr = curr->next;
        }
        return dummy->next;
    }
};

class Deque {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    Deque() : front(nullptr), rear(nullptr) {}

    ~Deque() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void InsertFront(int val) {
        Node* newNode = new Node(val);
        if (!front) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void InsertRear(int val) {
        Node* newNode = new Node(val);
        if (!rear) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
    }

    int RemoveFront() {
        if (!front) return -1;
        int val = front->data;
        Node* temp = front;
        front = front->next;
        if (front) {
            front->prev = nullptr;
        } else {
            rear = nullptr;
        }
        delete temp;
        return val;
    }

    int RemoveRear() {
        if (!rear) return -1;
        int val = rear->data;
        Node* temp = rear;
        rear = rear->prev;
        if (rear) {
            rear->next = nullptr;
        } else {
            front = nullptr;
        }
        delete temp;
        return val;
    }
};

class StackProblems {
public:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    class Stack {
    private:
        Node* top;
    public:
        Stack() : top(nullptr) {}
        ~Stack() {
            while (top) {
                Node* temp = top;
                top = top->next;
                delete temp;
            }
        }
        void push(int val) {
            Node* newNode = new Node(val);
            newNode->next = top;
            top = newNode;
        }
        int pop() {
            if (!top) return -1;
            int val = top->data;
            Node* temp = top;
            top = top->next;
            delete temp;
            return val;
        }
        int peek() {
            return top ? top->data : -1;
        }
        bool isEmpty() {
            return top == nullptr;
        }
    };

    void sortStack(Stack& s) {
        if (s.isEmpty()) return;
        int temp = s.pop();
        sortStack(s);
        insertSorted(s, temp);
    }

    void insertSorted(Stack& s, int val) {
        if (s.isEmpty() || val >= s.peek()) {
            s.push(val);
            return;
        }
        int temp = s.pop();
        insertSorted(s, temp);
        s.push(val);
    }

    string checkBrackets(string s) {
        stack<char> st;
        for (size_t i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(' || c == '{' || c == '[' || c == '<') {
                st.push(c);
            } else if (c == ')' || c == ']' || c == '}' || c == '>') {
                if (st.empty()) {
                    return "Extra closing bracket '" + string(1, c) + "' at position " + to_string(i + 1);
                }
                char top = st.top();
                st.pop();
                char expected;
                if (c == ')') expected = '(';
                else if (c == ']') expected = '[';
                else if (c == '}') expected = '{';
                else if (c == '>') expected = '<';
                if (top != expected) {
                    return "Wrong-type mismatch: expected '" + string(1, expected) + "' but found '" + string(1, c) + "' at position " + to_string(i + 1);
                }
            }
        }
        if (!st.empty()) {
            string unclosed;
            while (!st.empty()) {
                unclosed = st.top() + unclosed;
                st.pop();
            }
            return "Unclosed brackets: " + unclosed;
        }
        return "Balanced";
    }

    class MinStack {
    private:
        struct MinNode {
            int val;
            int min;
            MinNode* next;
            MinNode(int v, int m) : val(v), min(m), next(nullptr) {}
        };
        MinNode* top;
    public:
        MinStack() : top(nullptr) {}
        ~MinStack() {
            while (top) {
                MinNode* temp = top;
                top = top->next;
                delete temp;
            }
        }
        void push(int val) {
            int currentMin = top ? top->min : INT_MAX;
            int newMin = min(currentMin, val);
            MinNode* newNode = new MinNode(val, newMin);
            newNode->next = top;
            top = newNode;
        }
        void pop() {
            if (!top) return;
            MinNode* temp = top;
            top = top->next;
            delete temp;
        }
        int getTop() {
            return top ? top->val : -1;
        }
        int getMin() {
            return top ? top->min : -1;
        }
        bool isEmpty() {
            return top == nullptr;
        }
    };
};

// ==================== MENU FUNCTIONS ====================

void displayMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   DATA STRUCTURES PROJECT ASSIGNMENT\n";
    cout << "========================================\n";
    cout << "PART-1 (ARRAY & LINKED LIST):\n";
    cout << "1.  Rotate Array (Right K Positions)\n";
    cout << "2.  Rearrange Negatives First\n";
    cout << "3.  Priority Queue (Hospital)\n";
    cout << "4.  Detect Palindrome (Linked List)\n";
    cout << "5.  Merge Two Sorted Lists\n";
    cout << "6.  Detect Cycle Start (Floyd's)\n";
    cout << "7.  Remove Consecutive Absents\n";
    cout << "8.  Delete Node (Given Pointer Only)\n";
    cout << "9.  Double-Ended Queue (Deque)\n";
    cout << "10. Merge Sort Linked List\n";
    cout << "\nPART-2 (STACK & QUEUE):\n";
    cout << "11. Sort Stack (Recursion)\n";
    cout << "12. Check Brackets Balance (Extended)\n";
    cout << "13. Stack Using Two Queues\n";
    cout << "14. Sort Queue Using Stack\n";
    cout << "15. Min Stack Implementation\n";
    cout << "\nPART-3 (CRACKING THE CODE):\n";
    cout << "16. Remove Duplicates (Unsorted List)\n";
    cout << "17. Nth to Last Element\n";
    cout << "18. Delete Middle Node\n";
    cout << "19. Add Two Numbers (Lists)\n";
    cout << "20. Find Loop Beginning\n";
    cout << "\n0.  Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

void printList(LinkedListProblems::Node* head) {
    cout << "[";
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << "]";
}

void question1() {
    cout << "\n========================================\n";
    cout << "   Question 1: Reverse Array (Recursion)\n";
    cout << "========================================\n";
    
    ArrayProblems ap;
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    
    cout << "Original Array: ";
    printArray(arr, n);
    cout << endl;
    
    ap.reverse(arr, 0, n - 1);
    
    cout << "Reversed Array: ";
    printArray(arr, n);
    cout << endl;
}

void question2() {
    cout << "\n========================================\n";
    cout << "   Question 1: Rotate Array (Right K Positions)\n";
    cout << "========================================\n";
    cout << "Company stores daily revenue of 365 days.\n";
    cout << "Rotate array by k positions using recursion.\n\n";
    
    ArrayProblems ap;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = 7;
    int k = 3;
    
    cout << "Original Array: ";
    printArray(arr, n);
    cout << endl;
    cout << "Rotate right by: " << k << " positions" << endl;
    
    ap.rotateRight(arr, n, k);
    
    cout << "Rotated Array:  ";
    printArray(arr, n);
    cout << endl;
}

void question3() {
    cout << "\n========================================\n";
    cout << "   Question 2: Rearrange Negatives First\n";
    cout << "========================================\n";
    cout << "Rearrange negative numbers before positive.\n";
    cout << "Keep original sorted order with minimum swaps.\n\n";
    
    ArrayProblems ap;
    int arr[] = {-12, 11, -13, -5, 6, -7, 5, -3, -6};
    int n = 9;
    
    cout << "Original Array: ";
    printArray(arr, n);
    cout << endl;
    
    ap.rearrangeNegativesFirst(arr, n);
    
    cout << "Rearranged:     ";
    printArray(arr, n);
    cout << endl;
    cout << "(All negatives moved to the left)" << endl;
}

void question4() {
    cout << "\n========================================\n";
    cout << "   Question 3: Priority Queue (Hospital)\n";
    cout << "========================================\n";
    cout << "Hospital queue with InsertPriority(name, emergencyLevel).\n";
    cout << "Insert before any patient with higher emergencyLevel.\n\n";
    
    QueueProblems pq;
    
    cout << "Inserting patients into emergency queue:\n";
    pq.InsertPriority("John", 3);
    cout << "  - John (Priority: 3)\n";
    pq.InsertPriority("Sarah", 1);
    cout << "  - Sarah (Priority: 1)\n";
    pq.InsertPriority("Mike", 2);
    cout << "  - Mike (Priority: 2)\n";
    pq.InsertPriority("Emma", 1);
    cout << "  - Emma (Priority: 1)\n";
    
    cout << "\nPatients in priority order:\n";
    auto curr = pq.head;
    int pos = 1;
    while (curr) {
        cout << "  " << pos++ << ". " << curr->name << " (Priority: " << curr->emergencyLevel << ")\n";
        curr = curr->next;
    }
}

void question5() {
    cout << "\n========================================\n";
    cout << "   Question 14: Sort Queue Using Stack\n";
    cout << "========================================\n";
    cout << "Train bogies arranged in Queue must leave sorted.\n";
    cout << "Use one extra queue + one stack.\n\n";
    
    SimpleQueue input, output;
    int values[] = {5, 1, 4, 2, 3};
    int n = 5;
    
    cout << "Original Queue: [";
    for (int i = 0; i < n; i++) {
        input.enqueue(values[i]);
        cout << values[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
    
    sortQueue(input, output);
    
    cout << "Sorted Queue:   [";
    bool first = true;
    while (!output.isEmpty()) {
        if (!first) cout << ", ";
        cout << output.dequeue();
        first = false;
    }
    cout << "]\n";
}

void question6() {
    cout << "\n========================================\n";
    cout << "   Question 13: Stack Using Two Queues\n";
    cout << "========================================\n";
    cout << "Implement Stack where Push is O(n) and Pop is O(1).\n";
    cout << "Using 2 Queues only.\n\n";
    
    StackUsingQueues stack;
    
    cout << "Pushing elements: 10, 20, 30\n";
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    cout << "Top element: " << stack.top() << endl;
    cout << "Pop: " << stack.pop() << endl;
    cout << "Top element: " << stack.top() << endl;
    cout << "Pop: " << stack.pop() << endl;
    cout << "Push: 40\n";
    stack.push(40);
    cout << "Top element: " << stack.top() << endl;
}

void question7() {
    cout << "\n========================================\n";
    cout << "   Question 7: Reverse Linked List\n";
    cout << "========================================\n";
    
    LinkedListProblems llp;
    LinkedListProblems::Node* head = new LinkedListProblems::Node(1);
    head->next = new LinkedListProblems::Node(2);
    head->next->next = new LinkedListProblems::Node(3);
    head->next->next->next = new LinkedListProblems::Node(4);
    head->next->next->next->next = new LinkedListProblems::Node(5);
    
    cout << "Original List: ";
    printList(head);
    cout << endl;
    
    head = llp.reverseList(head);
    
    cout << "Reversed List: ";
    printList(head);
    cout << endl;
    
    while (head) {
        auto temp = head;
        head = head->next;
        delete temp;
    }
}

void question8() {
    cout << "\n========================================\n";
    cout << "   Question 4: Detect Palindrome (Linked List)\n";
    cout << "========================================\n";
    cout << "Check if linked list is palindrome (e.g., 1→3→7→3→1).\n";
    cout << "O(n) time, O(1) space using mid-split + reverse.\n\n";
    
    LinkedListProblems llp;
    LinkedListProblems::Node* head = new LinkedListProblems::Node(1);
    head->next = new LinkedListProblems::Node(2);
    head->next->next = new LinkedListProblems::Node(3);
    head->next->next->next = new LinkedListProblems::Node(2);
    head->next->next->next->next = new LinkedListProblems::Node(1);
    
    cout << "List: ";
    printList(head);
    cout << endl;
    
    bool isPal = llp.isPalindrome(head);
    cout << "Is Palindrome: " << (isPal ? "Yes" : "No") << endl;
    
    while (head) {
        auto temp = head;
        head = head->next;
        delete temp;
    }
}

void question9() {
    cout << "\n========================================\n";
    cout << "   Question 5: Merge Two Sorted Lists\n";
    cout << "========================================\n";
    cout << "Merge two sorted lists (stock prices A & B).\n";
    cout << "Only pointer relinking, no new nodes created.\n\n";
    
    LinkedListProblems llp;
    
    LinkedListProblems::Node* list1 = new LinkedListProblems::Node(1);
    list1->next = new LinkedListProblems::Node(3);
    list1->next->next = new LinkedListProblems::Node(5);
    
    LinkedListProblems::Node* list2 = new LinkedListProblems::Node(2);
    list2->next = new LinkedListProblems::Node(4);
    list2->next->next = new LinkedListProblems::Node(6);
    
    cout << "List 1: ";
    printList(list1);
    cout << endl;
    
    cout << "List 2: ";
    printList(list2);
    cout << endl;
    
    LinkedListProblems::Node* merged = llp.mergeSortedLists(list1, list2);
    
    cout << "Merged: ";
    printList(merged);
    cout << endl;
    
    while (merged) {
        auto temp = merged;
        merged = merged->next;
        delete temp;
    }
}

void question10() {
    cout << "\n========================================\n";
    cout << "   Question 6/20: Detect Cycle Start (Floyd's)\n";
    cout << "========================================\n";
    cout << "Use Floyd's Cycle Algorithm to find loop start.\n";
    cout << "Example: A→B→C→D→E→C (returns C)\n\n";
    
    LinkedListProblems llp;
    LinkedListProblems::Node* head = new LinkedListProblems::Node(1);
    head->next = new LinkedListProblems::Node(2);
    head->next->next = new LinkedListProblems::Node(3);
    head->next->next->next = new LinkedListProblems::Node(4);
    head->next->next->next->next = new LinkedListProblems::Node(5);
    
    head->next->next->next->next->next = head->next->next;
    
    cout << "List with cycle: 1 -> 2 -> 3 -> 4 -> 5 -> (back to 3)\n";
    
    LinkedListProblems::Node* cycleStart = llp.detectCycleStart(head);
    
    if (cycleStart) {
        cout << "Cycle detected! Start node value: " << cycleStart->data << endl;
    } else {
        cout << "No cycle detected." << endl;
    }
    
    head->next->next->next->next->next = nullptr;
    while (head) {
        auto temp = head;
        head = head->next;
        delete temp;
    }
}

void question11() {
    cout << "\n========================================\n";
    cout << "   Question 7: Remove Consecutive Absents\n";
    cout << "========================================\n";
    cout << "Student attendance: 1=present, 0=absent.\n";
    cout << "RemoveConsecutiveAbsents(k): Delete ≥k consecutive 0's.\n\n";
    
    LinkedListProblems llp;
    LinkedListProblems::Node* head = new LinkedListProblems::Node(1);
    head->next = new LinkedListProblems::Node(0);
    head->next->next = new LinkedListProblems::Node(0);
    head->next->next->next = new LinkedListProblems::Node(0);
    head->next->next->next->next = new LinkedListProblems::Node(1);
    head->next->next->next->next->next = new LinkedListProblems::Node(0);
    head->next->next->next->next->next->next = new LinkedListProblems::Node(1);
    
    int k = 3;
    
    cout << "Original List (1=Present, 0=Absent): ";
    printList(head);
    cout << endl;
    cout << "Remove consecutive absents >= " << k << endl;
    
    head = llp.RemoveConsecutiveAbsents(head, k);
    
    cout << "Result List:                          ";
    printList(head);
    cout << endl;
    
    while (head) {
        auto temp = head;
        head = head->next;
        delete temp;
    }
}

void question12() {
    cout << "\n========================================\n";
    cout << "   Question 8/18: Delete Node (Given Pointer Only)\n";
    cout << "========================================\n";
    cout << "Delete a node when only pointer to that node is given.\n";
    cout << "Example: Delete 'c' from a→b→c→d→e → a→b→d→e\n\n";
    
    LinkedListProblems llp;
    LinkedListProblems::Node* head = new LinkedListProblems::Node(1);
    head->next = new LinkedListProblems::Node(2);
    LinkedListProblems::Node* target = new LinkedListProblems::Node(3);
    head->next->next = target;
    head->next->next->next = new LinkedListProblems::Node(4);
    head->next->next->next->next = new LinkedListProblems::Node(5);
    
    cout << "Original List: ";
    printList(head);
    cout << endl;
    cout << "Delete node with value: 3\n";
    
    llp.deleteNode(target);
    
    cout << "Result List:   ";
    printList(head);
    cout << endl;
    
    while (head) {
        auto temp = head;
        head = head->next;
        delete temp;
    }
}

void question13() {
    cout << "\n========================================\n";
    cout << "   Question 10: Merge Sort Linked List\n";
    cout << "========================================\n";
    cout << "Sort linked list using Merge Sort.\n";
    cout << "Optimized to detect when already sorted.\n\n";
    
    LinkedListProblems llp;
    LinkedListProblems::Node* head = new LinkedListProblems::Node(5);
    head->next = new LinkedListProblems::Node(2);
    head->next->next = new LinkedListProblems::Node(8);
    head->next->next->next = new LinkedListProblems::Node(1);
    head->next->next->next->next = new LinkedListProblems::Node(9);
    head->next->next->next->next->next = new LinkedListProblems::Node(3);
    
    cout << "Original List: ";
    printList(head);
    cout << endl;
    
    head = llp.mergeSort(head);
    
    cout << "Sorted List:   ";
    printList(head);
    cout << endl;
    
    while (head) {
        auto temp = head;
        head = head->next;
        delete temp;
    }
}

void question14() {
    cout << "\n========================================\n";
    cout << "   Question 16: Remove Duplicates (Unsorted List)\n";
    cout << "========================================\n";
    cout << "Remove duplicates from an unsorted linked list.\n\n";
    
    LinkedListProblems llp;
    LinkedListProblems::Node* head = new LinkedListProblems::Node(1);
    head->next = new LinkedListProblems::Node(2);
    head->next->next = new LinkedListProblems::Node(3);
    head->next->next->next = new LinkedListProblems::Node(2);
    head->next->next->next->next = new LinkedListProblems::Node(4);
    head->next->next->next->next->next = new LinkedListProblems::Node(1);
    
    cout << "Original List: ";
    printList(head);
    cout << endl;
    
    head = llp.removeDuplicates(head);
    
    cout << "After Removal: ";
    printList(head);
    cout << endl;
    
    while (head) {
        auto temp = head;
        head = head->next;
        delete temp;
    }
}

void question15() {
    cout << "\n========================================\n";
    cout << "   Question 17: Nth to Last Element\n";
    cout << "========================================\n";
    cout << "Find the Nth to last element of singly linked list.\n\n";
    
    LinkedListProblems llp;
    LinkedListProblems::Node* head = new LinkedListProblems::Node(1);
    head->next = new LinkedListProblems::Node(2);
    head->next->next = new LinkedListProblems::Node(3);
    head->next->next->next = new LinkedListProblems::Node(4);
    head->next->next->next->next = new LinkedListProblems::Node(5);
    
    int n = 2;
    
    cout << "List: ";
    printList(head);
    cout << endl;
    cout << "Find " << n << "nd node from end\n";
    
    LinkedListProblems::Node* result = llp.findNthFromEnd(head, n);
    
    if (result) {
        cout << "Result: " << result->data << endl;
    } else {
        cout << "Node not found." << endl;
    }
    
    while (head) {
        auto temp = head;
        head = head->next;
        delete temp;
    }
}

void question16() {
    cout << "\n========================================\n";
    cout << "   Question 19: Add Two Numbers (Lists)\n";
    cout << "========================================\n";
    cout << "Numbers represented as linked lists (reverse order).\n";
    cout << "Example: (3→1→9→9) + (5→9→2) = (8→0→2→0→1)\n\n";
    
    LinkedListProblems llp;
    
    LinkedListProblems::Node* l1 = new LinkedListProblems::Node(2);
    l1->next = new LinkedListProblems::Node(4);
    l1->next->next = new LinkedListProblems::Node(3);
    
    LinkedListProblems::Node* l2 = new LinkedListProblems::Node(5);
    l2->next = new LinkedListProblems::Node(6);
    l2->next->next = new LinkedListProblems::Node(4);
    
    cout << "Number 1: ";
    printList(l1);
    cout << " (represents 342)" << endl;
    
    cout << "Number 2: ";
    printList(l2);
    cout << " (represents 465)" << endl;
    
    LinkedListProblems::Node* sum = llp.addTwoNumbers(l1, l2);
    
    cout << "Sum:      ";
    printList(sum);
    cout << " (represents 807)" << endl;
    
    // Cleanup
    while (l1) {
        auto temp = l1;
        l1 = l1->next;
        delete temp;
    }
    while (l2) {
        auto temp = l2;
        l2 = l2->next;
        delete temp;
    }
    while (sum) {
        auto temp = sum;
        sum = sum->next;
        delete temp;
    }
}

void question17() {
    cout << "\n========================================\n";
    cout << "   Question 9: Double-Ended Queue (Deque)\n";
    cout << "========================================\n";
    cout << "Linked List based Deque supporting:\n";
    cout << "InsertFront, InsertRear, RemoveFront, RemoveRear\n\n";
    
    Deque dq;
    
    cout << "InsertFront(10)\n";
    dq.InsertFront(10);
    cout << "InsertRear(20)\n";
    dq.InsertRear(20);
    cout << "InsertFront(5)\n";
    dq.InsertFront(5);
    cout << "InsertRear(30)\n";
    dq.InsertRear(30);
    
    cout << "\nOperations:\n";
    cout << "RemoveFront: " << dq.RemoveFront() << endl;
    cout << "RemoveRear:  " << dq.RemoveRear() << endl;
    cout << "RemoveFront: " << dq.RemoveFront() << endl;
    cout << "RemoveFront: " << dq.RemoveFront() << endl;
}

void question18() {
    cout << "\n========================================\n";
    cout << "   Question 11: Sort Stack (Recursion)\n";
    cout << "========================================\n";
    cout << "Sort stack in ascending order recursively.\n";
    cout << "No extra stack/array allowed.\n\n";
    
    StackProblems sp;
    StackProblems::Stack stack;
    
    int values[] = {5, 2, 8, 1, 9, 3};
    cout << "Pushing elements: ";
    for (int i = 0; i < 6; i++) {
        stack.push(values[i]);
        cout << values[i] << " ";
    }
    cout << endl;
    
    sp.sortStack(stack);
    
    cout << "Sorted Stack (top to bottom): ";
    while (!stack.isEmpty()) {
        cout << stack.pop() << " ";
    }
    cout << endl;
}

void question19() {
    cout << "\n========================================\n";
    cout << "   Question 12: Check Brackets Balance (Extended)\n";
    cout << "========================================\n";
    cout << "Validate expression with mixed brackets: () {} [] <>\n";
    cout << "Detects: extra closing, unclosed, wrong-type mismatch\n\n";
    
    StackProblems sp;
    
    string test1 = "{[()]}";
    string test2 = "{[(])}";
    string test3 = "{{[[(())]]}}";
    string test4 = "{[}";
    
    cout << "Test 1: \"" << test1 << "\"\n";
    cout << "Result: " << sp.checkBrackets(test1) << "\n\n";
    
    cout << "Test 2: \"" << test2 << "\"\n";
    cout << "Result: " << sp.checkBrackets(test2) << "\n\n";
    
    cout << "Test 3: \"" << test3 << "\"\n";
    cout << "Result: " << sp.checkBrackets(test3) << "\n\n";
    
    cout << "Test 4: \"" << test4 << "\"\n";
    cout << "Result: " << sp.checkBrackets(test4) << "\n";
}

void question20() {
    cout << "\n========================================\n";
    cout << "   Question 15: Min Stack Implementation\n";
    cout << "========================================\n";
    cout << "Every push/pop maintains minimum in constant time.\n";
    cout << "No extra arrays/lists allowed.\n\n";
    
    StackProblems::MinStack minStack;
    
    cout << "Push(5)\n";
    minStack.push(5);
    cout << "  Top: " << minStack.getTop() << ", Min: " << minStack.getMin() << endl;
    
    cout << "Push(3)\n";
    minStack.push(3);
    cout << "  Top: " << minStack.getTop() << ", Min: " << minStack.getMin() << endl;
    
    cout << "Push(7)\n";
    minStack.push(7);
    cout << "  Top: " << minStack.getTop() << ", Min: " << minStack.getMin() << endl;
    
    cout << "Push(2)\n";
    minStack.push(2);
    cout << "  Top: " << minStack.getTop() << ", Min: " << minStack.getMin() << endl;
    
    cout << "Pop()\n";
    minStack.pop();
    cout << "  Top: " << minStack.getTop() << ", Min: " << minStack.getMin() << endl;
    
    cout << "Pop()\n";
    minStack.pop();
    cout << "  Top: " << minStack.getTop() << ", Min: " << minStack.getMin() << endl;
}

int main() {
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: question2(); break;   // Rotate Array
            case 2: question3(); break;   // Rearrange Negatives
            case 3: question4(); break;   // Priority Queue
            case 4: question8(); break;   // Palindrome
            case 5: question9(); break;   // Merge Sorted Lists
            case 6: question10(); break;  // Detect Cycle Start
            case 7: question11(); break;  // Remove Consecutive Absents
            case 8: question12(); break;  // Delete Node (pointer only)
            case 9: question17(); break;  // Deque
            case 10: question13(); break; // Merge Sort List
            case 11: question18(); break; // Sort Stack
            case 12: question19(); break; // Check Brackets
            case 13: question6(); break;  // Stack using Queues
            case 14: question5(); break;  // Sort Queue
            case 15: question20(); break; // Min Stack
            case 16: question14(); break; // Remove Duplicates
            case 17: question15(); break; // Nth from End
            case 18: question12(); break; // Delete Middle Node
            case 19: question16(); break; // Add Two Numbers
            case 20: question10(); break; // Find Loop Beginning
            case 0:
                cout << "\n========================================\n";
                cout << "The end of DSA! Boooooyaaaahhhhh!\n";
                cout << "========================================\n";
                break;
            default:
                cout << "\nInvalid choice! Please enter 0-20.\n";
        }
        
        if (choice != 0 && choice >= 1 && choice <= 20) {
            char runAnother;
            cout << "\n========================================\n";
            cout << "Would you like to run another question? (Y/N): ";
            cin >> runAnother;
            
            if (runAnother == 'N' || runAnother == 'n') {
                cout << "\n========================================\n";
                cout << "The end of DSA! Boooooyaaaahhhhh!\n";
                cout << "========================================\n";
                break;
            }
        }
        
    } while (choice != 0);
    
    return 0;
}