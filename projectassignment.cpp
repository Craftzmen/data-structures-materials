#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

void shiftRightByOne(int arr[], int pos) {
    if (pos == 1) return;
    int temp = arr[pos];
    arr[pos] = arr[pos - 1];
    arr[pos - 1] = temp;
    shiftRightByOne(arr, pos - 1);
}
void rotateRight(int arr[], int n, int k) {
    if (k == 1) return;
    shiftRightByOne(arr, n - 1);
    rotateRight(arr, n, k - 1);
}
void q1() {
    int arr[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = 10;
    int k = 5;
    cout << "Original Array:\n";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    rotateRight(arr, n, k);
    cout << "\n\nArray after rotating right by " << k << " positions:\n";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

void rearrange(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            int temp = arr[i];
            int j = i;
            while (j > 0 && arr[j - 1] >= 0) {
                arr[j] = arr[j - 1];
                j--;
            }
            arr[j] = temp;
        }
    }
}
void displayArrayQ2(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}
void q2() {
    int arr[] = {10, -1, 20, -5, -8, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "actual array: ";
    displayArrayQ2(arr, n);
    rearrange(arr, n);
    cout << "Rearranged array: ";
    displayArrayQ2(arr, n);
}

class Patient {
public:
    string name;
    int el;
    Patient* next;
    Patient(string n, int e) { name = n; el = e; next = NULL; }
};
class HospitalQueueLevel {
private:
    Patient* front;
    Patient* tail;
public:
    HospitalQueueLevel() { front = NULL; tail = NULL; }
    void InsertPriority(string name, int el) {
        Patient* newPatient = new Patient(name, el);
        if (front == NULL) { front = tail = newPatient; return; }
        if (el < front->el) { newPatient->next = front; front = newPatient; return; }
        Patient* curr = front;
        while (curr->next != NULL && curr->next->el <= el) { curr = curr->next; }
        newPatient->next = curr->next;
        curr->next = newPatient;
        if (newPatient->next == NULL) { tail = newPatient; }
    }
    void DisplayQueue() {
        Patient* temp = front;
        while (temp != NULL) {
            cout << temp->name << " [Priority: " << temp->el << "]  ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
void q3() {
    HospitalQueueLevel hq;
    hq.InsertPriority("ahmad", 3);
    hq.InsertPriority("ayesha", 5);
    hq.InsertPriority("rajpoot", 8);
    hq.InsertPriority("hamza", 1);
    hq.InsertPriority("zara", 4);
    hq.DisplayQueue();
}

namespace Q4 {
    class Node {
    public:
        int data;
        Node* next;
        Node(int d) { data = d; next = NULL; }
    };
    class SLL {
    private:
        Node* getMid(Node* head) {
            Node* slow = head;
            Node* fast = head->next;
            while (fast != NULL && fast->next != NULL) {
                fast = fast->next->next;
                slow = slow->next;
            }
            return slow;
        }
        Node* reverse(Node* head) {
            Node* curr = head; Node* prev = NULL; Node* next = NULL;
            while (curr != NULL) {
                next = curr->next; curr->next = prev;
                prev = curr; curr = next;
            }
            return prev;
        }
    public:
        bool Check_if_Palindrome(Node* head) {
            if (head == NULL || head->next == NULL) return true;
            Node* middle = getMid(head);
            Node* temp = middle->next;
            middle->next = reverse(temp);
            Node* p = head; Node* q = middle->next;
            while (q != NULL) {
                if (q->data != p->data) return false;
                p = p->next; q = q->next;
            }
            return true;
        }
    };
}
void q4() {
    using namespace Q4;
    Node* head = new Node(1);
    head->next = new Node(9);
    head->next->next = new Node(2);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(9);
    head->next->next->next->next->next = new Node(1);
    SLL s;
    if (s.Check_if_Palindrome(head)) cout << "Linked List is Palindrome" << endl;
    else cout << "Linked List is NOT Palindrome" << endl;
}

namespace Q5 {
    class Node {
    public:
        int price;
        Node* next;
        Node(int p) { price = p; next = NULL; }
    };
    class SMerger {
    public:
        Node* mergeSorted(Node* A, Node* B) {
            if (A == NULL) return B;
            if (B == NULL) return A;
            if (A->price <= B->price) { A->next = mergeSorted(A->next, B); return A; }
            else { B->next = mergeSorted(A, B->next); return B; }
        }
    };
    void display(Node* head) {
        while (head != NULL) { cout << head->price << "  "; head = head->next; }
        cout << endl;
    }
}
void q5() {
    using namespace Q5;
    Node* A = new Node(20); A->next = new Node(40); A->next->next = new Node(50);
    Node* B = new Node(50); B->next = new Node(90); B->next->next = new Node(100);
    cout << "Company A prices: "; display(A);
    cout << "Company B prices: "; display(B);
    SMerger sm;
    Node* merged = sm.mergeSorted(A, B);
    cout << "Merged stock prices: "; display(merged);
}

namespace LoopDetect {
    class Node {
    public:
        char data;
        Node* next;
        Node(char d) { data = d; next = NULL; }
    };
    Node* start_of_loop(Node* head) {
        Node* slow = head; Node* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next; fast = fast->next->next;
            if (slow == fast) break;
        }
        if (fast == NULL || fast->next == NULL) return NULL;
        slow = head;
        while (slow != fast) { slow = slow->next; fast = fast->next; }
        return slow;
    }
}
void q6() {
    using namespace LoopDetect;
    Node* A = new Node('A'); Node* B = new Node('B'); Node* C = new Node('C');
    Node* D = new Node('D'); Node* E = new Node('E');
    A->next = B; B->next = C; C->next = D; D->next = E; E->next = C;
    Node* loopStart = start_of_loop(A);
    if (loopStart != NULL) cout << "Loop starts at node: " << loopStart->data << endl;
    else cout << "No loop found" << endl;
}

namespace Q7 {
    class Node {
    public:
        int data;
        Node* next;
        Node(int d) { data = d; next = NULL; }
    };
    Node* RemoveConsecutivezero(Node* head, int k) {
        Node* curr = head; Node* prev = NULL;
        while (curr != NULL) {
            if (curr->data == 0) {
                Node* start = curr; int count = 0;
                while (curr != NULL && curr->data == 0) { curr = curr->next; count++; }
                if (count >= k) {
                    if (prev == NULL) head = curr;
                    else prev->next = curr;
                } else { prev = start; }
            } else { prev = curr; curr = curr->next; }
        }
        return head;
    }
    void display(Node* head) {
        while (head != NULL) { cout << head->data << " "; head = head->next; }
    }
}
void q7() {
    using namespace Q7;
    Node* head = new Node(1); head->next = new Node(0); head->next->next = new Node(0);
    head->next->next->next = new Node(0); head->next->next->next->next = new Node(1);
    head->next->next->next->next->next = new Node(0);
    head->next->next->next->next->next->next = new Node(0);
    head->next->next->next->next->next->next->next = new Node(1);
    cout << "Before list: "; display(head); cout << endl;
    head = RemoveConsecutivezero(head, 3);
    cout << "After list:  "; display(head); cout << endl;
}

namespace Q8 {
    class Node {
    public:
        int data;
        Node* next;
        Node(int val) { data = val; next = NULL; }
    };
    class SLL {
    public:
        void deleteNode(Node* node) {
            if (node == NULL) return;
            if (node->next == NULL) { cout << "Cannot delete Tail" << endl; return; }
            Node* temp = node->next;
            node->data = temp->data;
            node->next = temp->next;
            delete temp;
        }
    };
    void display(Node* head) {
        while (head) { cout << head->data << "  "; head = head->next; }
    }
}
void q8() {
    using namespace Q8;
    Node* head = new Node(4); head->next = new Node(5);
    head->next->next = new Node(1); head->next->next->next = new Node(9);
    SLL L; cout << "actual listt: "; display(head); cout << endl;
    cout << "Delete 5" << endl; L.deleteNode(head->next); display(head); cout << endl;
    cout << "Deleting Tail --(9)" << endl; L.deleteNode(head); display(head); cout << endl;
}

namespace Q9 {
    class Node {
    public:
        int data; Node* next; Node* prev;
        Node(int d) { data = d; next = prev = NULL; }
    };
    Node* front = NULL; Node* rear = NULL;
    void insertFront(int x) {
        Node* temp = new Node(x);
        if (front == NULL) front = rear = temp;
        else { temp->next = front; front->prev = temp; front = temp; }
    }
    void insertRear(int x) {
        Node* temp = new Node(x);
        if (rear == NULL) front = rear = temp;
        else { rear->next = temp; temp->prev = rear; rear = temp; }
    }
    void removeFront() {
        if (front == NULL) { cout << "Deque Underflow" << endl; return; }
        Node* temp = front;
        if (front == rear) front = rear = NULL;
        else { front = front->next; front->prev = NULL; }
        delete temp;
    }
    void removeRear() {
        if (rear == NULL) { cout << "Deque Underflow" << endl; return; }
        Node* temp = rear;
        if (front == rear) front = rear = NULL;
        else { rear = rear->prev; rear->next = NULL; }
        delete temp;
    }
    void display() {
        Node* curr = front; while (curr != NULL) { cout << curr->data << " "; curr = curr->next; }
        cout << endl;
    }
}
void q9() {
    using namespace Q9;
    insertFront(10); insertRear(70); insertFront(5); insertRear(50);
    cout << "Deque at start: "; display();
    removeFront(); removeRear();
    cout << "After deletions: "; display();
}

namespace Q10 {
    class Node {
    public:
        int data; Node* next;
        Node(int d) { data = d; next = NULL; }
    };
    void display(Node* head) {
        while (head != NULL) { cout << head->data << " "; head = head->next; }
        cout << endl;
    }
    Node* getMid(Node* head) {
        Node* slow = head; Node* fast = head->next;
        while (fast != NULL && fast->next != NULL) { slow = slow->next; fast = fast->next->next; }
        return slow;
    }
    bool LLisSorted(Node* head) {
        while (head->next != NULL) {
            if (head->data > head->next->data) return false;
            head = head->next;
        }
        return true;
    }
    Node* merge(Node* a, Node* b) {
        if (a == NULL) return b; if (b == NULL) return a;
        if (a->data <= b->data) { a->next = merge(a->next, b); return a; }
        else { b->next = merge(a, b->next); return b; }
    }
    Node* mergeSort(Node* head) {
        if (head == NULL || head->next == NULL) return head;
        if (LLisSorted(head)) return head;
        Node* mid = getMid(head); Node* right = mid->next; mid->next = NULL;
        Node* leftSorted = mergeSort(head); Node* rightSorted = mergeSort(right);
        return merge(leftSorted, rightSorted);
    }
}
void q10() {
    using namespace Q10;
    Node* head = new Node(1); head->next = new Node(2); head->next->next = new Node(3);
    head->next->next->next = new Node(7); head->next->next->next->next = new Node(5);
    cout << "LL Before sorting: "; display(head);
    head = mergeSort(head);
    cout << "LL After sorting:  "; display(head);
}

void sortedInsert(stack<int> &s, int x) {
    if (s.empty() || x < s.top()) {
        s.push(x); cout << "Pushed " << x << endl; return;
    }
    int temp = s.top(); s.pop();
    cout << "Popped " << temp << " to insert " << x << endl;
    sortedInsert(s, x); s.push(temp);
    cout << "Pushed " << temp << " back\n";
}
void sortStack(stack<int> &s) {
    if (!s.empty()) {
        int x = s.top(); s.pop();
        cout << "Popped " << x << " for sorting\n";
        sortStack(s); sortedInsert(s, x);
    }
}
void printStack(stack<int> s) {
    cout << "Stack top TO bottom: ";
    while (!s.empty()) { cout << s.top() << " "; s.pop(); }
}
void q11() {
    stack<int> s; s.push(20); s.push(30); s.push(10); s.push(40);
    cout << "Original stack:\n"; printStack(s);
    cout << "\nSorting stack...\n\n"; sortStack(s);
    cout << "\nSorted stack -> ascending:\n"; printStack(s); cout << endl;
}

bool isMatching(char open, char close) {
    return (open == '(' && close == ')') || (open == '{' && close == '}') ||
           (open == '[' && close == ']') || (open == '<' && close == '>');
}
void checkBrackets(const string &expr) {
    stack<pair<char,int>> s;
    for (int i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') { s.push({ch, i}); }
        else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
            if (s.empty()) { cout << "Error at position " << i << ": Extra closing bracket '" << ch << " " << endl; return; }
            char open = s.top().first; s.pop();
            if (!isMatching(open, ch)) {
                cout << "Error at position " << i << ": Wrong-type mismatch, expected ";
                switch(open) {
                    case '(': cout << ")"; break; case '{': cout << "}"; break;
                    case '[': cout << "]"; break; case '<': cout << ">"; break;
                }
                cout << " but found '" << ch << " " << endl; return;
            }
        }
    }
    if (!s.empty()) {
        while(!s.empty()) {
            cout << "Error at position " << s.top().second << ": Unclosed bracket '" << s.top().first << " " << endl;
            s.pop();
        }
        return;
    }
    cout << "Expression is balanced" << endl;
}
void q12() {
    string expr; cin.ignore();
    cout << "Enter expression with brackets: "; getline(cin, expr);
    checkBrackets(expr);
}

class StackUsingQueues {
    queue<int> q1, q2;
public:
    void push(int x) {
        q2.push(x);
        while(!q1.empty()) { q2.push(q1.front()); q1.pop(); }
        swap(q1, q2);
    }
    void pop() {
        if(q1.empty()) { cout << "Stack Underflow\n"; return; }
        cout << "Popped: " << q1.front() << endl; q1.pop();
    }
    void display() {
        queue<int> temp = q1; cout << "Stack: ";
        while(!temp.empty()) { cout << temp.front() << " "; temp.pop(); }
        cout << endl;
    }
};
void q13() {
    StackUsingQueues s;
    s.push(5); s.display(); s.push(7); s.display();
    s.push(1); s.display(); s.push(3); s.display();
    s.pop(); s.display(); s.pop(); s.display();
}

void sortBogieQueue(queue<int>& q1) {
    queue<int> q2; stack<int> s;
    while (!q1.empty()) {
        int n = q1.size(); int minBogie = INT_MAX;
        for (int i = 0; i < n; i++) {
            int bogie = q1.front(); q1.pop();
            if (bogie < minBogie) minBogie = bogie;
            q1.push(bogie);
        }
        bool minPushed = false;
        for (int i = 0; i < n; i++) {
            int bogie = q1.front(); q1.pop();
            if (bogie == minBogie && !minPushed) { s.push(bogie); minPushed = true; }
            else { q2.push(bogie); }
        }
        swap(q1, q2);
    }
    cout << "Sorted Bogies Leaving Station: ";
    while (!s.empty()) { cout << s.top() << " "; s.pop(); }
    cout << endl;
}
void q14() {
    queue<int> bogies; bogies.push(9); bogies.push(2); bogies.push(8); bogies.push(30);
    cout << "Original Bogies Queue: "; queue<int> temp = bogies;
    while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); }
    cout << endl; sortBogieQueue(bogies);
}

class MinStack {
    stack<int> s; int minEle;
public:
    void push(int x) {
        if (s.empty()) { s.push(x); minEle = x; }
        else if (x >= minEle) { s.push(x); }
        else { s.push(2 * x - minEle); minEle = x; }
    }
    void pop() {
        if (s.empty()) { cout << "Stack Underflow\n"; return; }
        int t = s.top(); s.pop();
        if (t < minEle) { minEle = 2 * minEle - t; }
    }
    int top() {
        if (s.empty()) return -1;
        int t = s.top(); return (t >= minEle) ? t : minEle;
    }
    int getMin() { return s.empty() ? -1 : minEle; }
};
void q15() {
    MinStack ms;
    ms.push(5); cout << "Push 5, Min: " << ms.getMin() << endl;
    ms.push(7); cout << "Push 7, Min: " << ms.getMin() << endl;
    ms.push(1); cout << "Push 1, Min: " << ms.getMin() << endl;
    ms.push(3); cout << "Push 3, Min: " << ms.getMin() << endl;
    ms.pop(); cout << "Pop, Min: " << ms.getMin() << endl;
}

namespace Q16 {
    class Node {
    public:
        int data; Node* next;
        Node(int d) { data = d; next = NULL; }
    };
    void removeDuplicates(Node* head) {
        Node* current = head;
        while (current != NULL) {
            Node* temp = current;
            while (temp->next != NULL) {
                if (temp->next->data == current->data) {
                    Node* delNode = temp->next; temp->next = temp->next->next; delete delNode;
                } else temp = temp->next;
            }
            current = current->next;
        }
    }
    void printList(Node* head) {
        while (head != NULL) { cout << head->data << " -> "; head = head->next; }
        cout << "NULL" << endl;
    }
}
void q16() {
    using namespace Q16;
    Node* head = new Node(3); head->next = new Node(20); head->next->next = new Node(3);
    head->next->next->next = new Node(50); head->next->next->next->next = new Node(20);
    cout << "Original list: "; printList(head);
    removeDuplicates(head); cout << "After removing duplicates: "; printList(head);
}

namespace Q17 {
    class Node {
    public:
        int data; Node* next;
        Node(int d) { data = d; next = NULL; }
    };
    void findNthTerm(Node* head, int n) {
        if (!head) { cout << "List is empty" << endl; return; }
        Node* p = head; Node* q = head; int ct = 1;
        while (ct <= n - 1) {
            if (q->next == NULL) { cout << "N is larger than length" << endl; return; }
            q = q->next; ct++;
        }
        while (q->next != NULL) { p = p->next; q = q->next; }
        cout << "Nth to last element is: " << p->data << endl;
    }
    void display(Node* head) {
        while (head) { cout << head->data << "  "; head = head->next; }
        cout << endl;
    }
}
void q17() {
    using namespace Q17;
    Node* head = new Node(10); head->next = new Node(50); head->next->next = new Node(90);
    head->next->next->next = new Node(40); head->next->next->next->next = new Node(15);
    display(head); int n; cout << "Enter N: "; cin >> n; findNthTerm(head, n);
}

    class Node {
    public:
        char data; Node* next;
        Node(char d) { data = d; next = NULL; }
    };
    void delete_at_middle(Node* n) {
        if (n == NULL || n->next == NULL) return;
        n->data = n->next->data; Node* temp = n->next; n->next = temp->next; delete temp;
    }
    void display(Node* head) {
        while (head != NULL) { cout << head->data << " "; head = head->next; }
        cout << endl;
    }
}
void q18() {
    using namespace Q18;
    Node* head = new Node('a'); head->next = new Node('b'); Node* nodeC = new Node('c');
    head->next->next = nodeC; nodeC->next = new Node('d'); cout << "actual list: ";
    display(head); delete_at_middle(nodeC); cout << "after: "; display(head);
}

namespace Q19 {
    class Node {
    public:
        int data; Node* next;
        Node(int d = 0) { data = d; next = NULL; }
    };
    Node* addLists(Node* l1, Node* l2) {
        Node* result = NULL; Node* tail = NULL; int carry = 0;
        while (l1 || l2 || carry) {
            int sum = carry;
            if (l1) { sum += l1->data; l1 = l1->next; }
            if (l2) { sum += l2->data; l2 = l2->next; }
            carry = sum / 10; Node* newNode = new Node(sum % 10);
            if (!result) result = tail = newNode;
            else { tail->next = newNode; tail = newNode; }
        }
        return result;
    }
    void printList(Node* head) {
        while (head) { cout << head->data << (head->next ? " -> " : ""); head = head->next; }
        cout << endl;
    }
}
void q19() {
    using namespace Q19;
    Node* num1 = new Node(3); num1->next = new Node(1); num1->next->next = new Node(9);
    Node* num2 = new Node(5); num2->next = new Node(9);
    printList(num1); printList(num2);
    Node* sum = addLists(num1, num2); cout << "Sum: "; printList(sum);
}

int main() {
    int choice;
    char confirm;

    do {

        cout << "=================================================" << endl;
        cout << "      DATA STRUCTURES PROJECT ASSIGNMENT         " << endl;
        cout << "=================================================" << endl;

        cout << "PART-1 (ARRAY & LINKED LIST):" << endl;
        cout << "1.  Rotate Array (Right K Positions)" << endl;
        cout << "2.  Rearrange Negatives First" << endl;
        cout << "3.  Priority Queue (Hospital)" << endl;
        cout << "4.  Detect Palindrome (Linked List)" << endl;
        cout << "5.  Merge Two Sorted Lists" << endl;
        cout << "6.  Detect Cycle Start (Floyd's)" << endl;
        cout << "7.  Remove Consecutive Absents" << endl;
        cout << "8.  Delete Node (Given Pointer Only)" << endl;
        cout << "9.  Double-Ended Queue (Deque)" << endl;
        cout << "10. Merge Sort Linked List" << endl << endl;

        cout << "PART-2 (STACK & QUEUE):" << endl;
        cout << "11. Sort Stack (Recursion)" << endl;
        cout << "12. Check Brackets Balance (Extended)" << endl;
        cout << "13. Stack Using Two Queues" << endl;
        cout << "14. Sort Queue Using Stack" << endl;
        cout << "15. Min Stack Implementation" << endl << endl;

        cout << "PART-3 (CRACKING THE CODE):" << endl;
        cout << "16. Remove Duplicates (Unsorted List)" << endl;
        cout << "17. Nth to Last Element" << endl;
        cout << "18. Delete Middle Node" << endl;
        cout << "19. Add Two Numbers (Lists)" << endl;
        cout << "20. Find Loop Beginning" << endl << endl;

        cout << "0.  Exit" << endl;
        cout << "=================================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:  q1(); break;
            case 2:  q2(); break;
            case 3:  q3(); break;
            case 4:  q4(); break;
            case 5:  q5(); break;
            case 6:  q6(); break;
            case 7:  q7(); break;
            case 8:  q8(); break;
            case 9:  q9(); break;
            case 10: q10(); break;
            case 11: q11(); break;
            case 12: q12(); break;
            case 13: q13(); break;
            case 14: q14(); break;
            case 15: q15(); break;
            case 16: q16(); break;
            case 17: q17(); break;
            case 18: q18(); break;
            case 19: q19(); break;
            case 20: q6(); break;
            case 0:  return 0;
            default: cout << "Invalid Selection!" << endl;
        }

        cout << "\nWould you like to run another function? (Y/N): ";
        cin >> confirm;
        cout << endl;

    } while (confirm == 'Y' || confirm == 'y');

    return 0;
}
