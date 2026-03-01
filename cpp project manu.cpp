#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

// ==========================================
// DATA STRUCTURES (Sab questions ke liye)
// ==========================================

// 1. Standard Node (Zyada tar questions ke liye)
struct Node {
    int data;
    Node* next;
    Node(int val = 0) {
        data = val;
        next = NULL;
    }
};

// 2. Priority Node (Question 3 ke liye)
struct NodePri {
    string name;
    int level;
    NodePri* next;
    NodePri(string n, int l) {
        name = n;
        level = l;
        next = NULL;
    }
};

// 3. Price Node (Question 5 ke liye)
struct NodePrice {
    int price;
    NodePrice* next;
    NodePrice(int val) {
        price = val;
        next = NULL;
    }
};

// 4. Doubly Linked Node (Question 9 ke liye)
struct NodeDLL {
    int data;
    NodeDLL* next;
    NodeDLL* prev;
    NodeDLL(int val) {
        data = val;
        next = NULL;
        prev = NULL;
    }
};

// ==========================================
// FUNCTIONS (LOGIC)
// ==========================================

// Q1: Rotate Array
void rotateRight(int arr[], int n, int k) {
    if (k == 0) return;
    int last = arr[n - 1];
    for (int i = n - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = last;
    rotateRight(arr, n, k - 1);
}

// Q2: Insertion Sort Rearrange
void rearrangeInsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        if (key < 0) {
            int j = i - 1;
            while (j >= 0 && arr[j] >= 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

// Q3: Hospital Priority Queue
class HospitalQueue {
private:
    NodePri *front, *tail;
public:
    HospitalQueue() { front = tail = NULL; }
    void InsertPriority(string name, int emergencyLevel) {
        NodePri* newNode = new NodePri(name, emergencyLevel);
        if (front == NULL) { 
            front = tail = newNode;
             return; 
            }
        if (emergencyLevel < front->level)
         { 
            newNode->next = front;
             front = newNode; 
             return;
             }
        NodePri* curr = front;
        while (curr->next != NULL && curr->next->level <= emergencyLevel) {
             curr = curr->next; 
            }
        newNode->next = curr->next;
        curr->next = newNode;
        if (newNode->next == NULL)
         tail = newNode;
    }
    void display() {
        if (front == NULL) { cout << "Queue Empty" << endl; return; }
        NodePri* temp = front;
        cout << "Priority Queue: ";
        while (temp != NULL) {
            cout << "[" << temp->name << ", Lvl:" << temp->level << "]  ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

// Q4: Palindrome
class SolutionQ4 {
public:
    Node* getmid(Node* head) {
        Node* slow = head;
        Node* fast = head->next; 
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;       
            fast = fast->next->next; 
        }
        return slow; 
    }
    Node* reverse(Node* head) {
        Node* curr = head;
        Node* prev = NULL;
        Node* next = NULL;
        while (curr != NULL) {
            next = curr->next; 
            curr->next = prev; 
            prev = curr;       
            curr = next;       
        }
        return prev; 
    }
    bool isPalindrome(Node* head) {
        if (head == NULL || head->next == NULL) return true; 
        Node* middle = getmid(head);
        Node* temp = middle->next;
        middle->next = reverse(temp);
        Node* head1 = head;        
        Node* head2 = middle->next; 
        while (head2 != NULL) {
            if (head1->data != head2->data) return false; 
            head1 = head1->next;
            head2 = head2->next;
        }      
        return true; 
    }
};

// Q5: Merge Sort Linked List (Price)
NodePrice* MergeLists(NodePrice* headA, NodePrice* headB) {
    if (headA == NULL) return headB;
    if (headB == NULL) return headA;
    NodePrice* resultHead = NULL;
    if (headA->price <= headB->price) {
         resultHead = headA;
          headA = headA->next;
         } 
    else { 
        resultHead = headB;
         headB = headB->next;
         }
    NodePrice* curr = resultHead;
    while (headA != NULL && headB != NULL) {
        if (headA->price <= headB->price) {
             curr->next = headA;
              headA = headA->next;
             } 
        else { 
            curr->next = headB;
             headB = headB->next;
             }
        curr = curr->next;
    }
    if (headA != NULL) curr->next = headA;
    else if (headB != NULL) curr->next = headB;
    return resultHead;
}
void printListPrice(NodePrice* head) {
    while (head) {
         cout << head->price << " -> ";
          head = head->next;
         }
    cout << "NULL" << endl;
}

// Q6: Cycle Detection
class SolutionQ6 {
public:
    Node* detectCycle(Node* head) {
        if (head == NULL || head->next == NULL) 
        return NULL;
        Node* slow = head;
        Node* fast = head;
        bool hasCycle = false;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;          
            fast = fast->next->next;   
            if (slow == fast) { 
                hasCycle = true;
                 break; 
                }
        }
        if (!hasCycle) return NULL;
        slow = head; 
        while (slow != fast) { 
            slow = slow->next; 
            fast = fast->next; 
        }
        return slow; 
    }
};

// Q7: Remove Consecutive Absents
void RemoveConsecutiveAbsents(Node*& head, int k) {
    Node* curr = head;
    Node* prev = NULL; 
    while (curr != NULL) {
        if (curr->data == 1) {
            prev = curr;       
            curr = curr->next; 
        } else {
            Node* temp = curr;
            int count = 0;
            while (temp != NULL && temp->data == 0) {
                count++;
                temp = temp->next;
            }
            if (count >= k) {

                if (prev != NULL) 
                prev->next = temp; 
                else head = temp;      
                curr = temp; 
            } else {
                prev = curr;     
                curr = curr->next;
            }
        }
    }
}

// Q8: Delete Node without Head
class SolutionQ8 {
public:
    void deleteNode(Node* node) {
        if (node == NULL) 
        return;
        if (node->next == NULL) { 
            cout << "Cannot delete Tail" << endl;
             return;
             }
        Node* temp = node->next;
        node->data = temp->data; 
        node->next = temp->next; 
        delete temp;            
    }
};

// Q9: Deque with DLL
class Deque {
private:
    NodeDLL* front;
    NodeDLL* rear;
public:
    Deque() { front = rear = NULL; }
    void insertFront(int val) {
        NodeDLL* newNode = new NodeDLL(val);
        if (front == NULL) {
             front = rear = newNode;
             } 
        else { 
            newNode->next = front;
             front->prev = newNode; 
             front = newNode;
             }
        cout << "Inserted Front: " << val << endl;
    }
    void insertRear(int val) {
        NodeDLL* newNode = new NodeDLL(val);
        if (rear == NULL) {
             front = rear = newNode;
             } 
        else {
             rear->next = newNode; 
             newNode->prev = rear; 
             rear = newNode; 
            }
        cout << "Inserted Rear: " << val << endl;
    }
    void removeFront() {
        if (front == NULL) { 
            cout << "Underflow!" << endl; return;
         }
        NodeDLL* temp = front;
        if (front == rear) { 
            front = rear = NULL; 
        } 
        else { 
            front = front->next; front->prev = NULL;
         }
        cout << "Removed Front: " << temp->data << endl;
        delete temp;
    }
    void removeRear() {
        if (rear == NULL) {
             cout << "Underflow!" << endl;
              return; 
            }
        NodeDLL* temp = rear;
        if (front == rear) {
             front = rear = NULL;
             } 
        else 
        {
             rear = rear->prev;
              rear->next = NULL;
             }
        cout << "Removed Rear: " << temp->data << endl;
        delete temp;
    }
    void display() {
        if (!front) { cout << "Empty" << endl; return; }
        NodeDLL* temp = front;
        while (temp) { cout << temp->data << " <-> ";
             temp = temp->next; 
            }
        cout << "NULL" << endl;
    }
};

// Q10: Optimized Merge Sort
Node* getMiddle(Node* head) {
    if (!head) return head;
    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
         slow = slow->next;
          fast = fast->next->next;
         }
    return slow;
}
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    Node* result = NULL;
    if (left->data <= right->data)
     { result = left;
         result->next = merge(left->next, right);
         } 
    else {
         result = right;
          result->next = merge(left, right->next);
         }
    return result;
}
Node* mergeSort(Node* head) {
    if (!head || !head->next) 
    return head;
    Node* middle = getMiddle(head);
    Node* leftHead = head;
    Node* rightHead = middle->next;
    middle->next = NULL;
    Node* leftSorted = mergeSort(leftHead);
    Node* rightSorted = mergeSort(rightHead); 
    Node* leftTail = leftSorted;
    while (leftTail->next != NULL) 
    { 
        leftTail = leftTail->next; 
    }//checking if last of left <= first of right
    if (leftTail->data <= rightSorted->data)
     { 
        leftTail->next = rightSorted;
         return leftSorted; }
    return merge(leftSorted, rightSorted);
}

// Q11: Stack Recursion
void insertSorted(stack<int>& s, int x) {
    if (s.empty() || s.top() <= x)
     {
         s.push(x); return;
     }
    int temp = s.top(); s.pop();
    insertSorted(s, x);
    s.push(temp);
}
void sortStack(stack<int>& s) {
    if (s.empty())
     return;
    int x = s.top(); 
    s.pop();
    sortStack(s);
    insertSorted(s, x);
}

// Q12: Balanced Brackets
bool isMatching(char open, char close) {
    return (open == '(' && close == ')') || (open == '{' && close == '}') ||
           (open == '[' && close == ']') || (open == '<' && close == '>');
}
void checkBrackets(string exp) {
    stack<char> s;
    for (char ch : exp) {
        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') s.push(ch);
        else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
            if (s.empty()) { cout << "Extra closing bracket: " << ch << endl; return; }
            char top = s.top(); s.pop();
            if (!isMatching(top, ch)) {
                cout << "Mismatch: expected matching for " << top << " but found " << ch << endl;
                return;
            }
        }
    }
    if (!s.empty())
     cout << "Unclosed bracket at end" << endl;
    else 
    cout << "Balanced Expression" << endl;
}

// Q13: Stack Using Queues
class StackUsingQueues {
    queue<int> q1, q2;
public:
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) 
        { 
            q2.push(q1.front());
             q1.pop(); 
            }
        swap(q1, q2);
    }
    void pop() {
        if (q1.empty()) 
        { 
            cout << "Stack Empty\n"; return; 
        }
        q1.pop();
    }
    int top() {
         return q1.front();
         }
};

// Q14: Train Sorting
void sortTrain(queue<int>& q) {
    stack<int> s;
    while (!q.empty()) {
        int x = q.front(); 
        q.pop();
        while (!s.empty() && s.top() > x)
         { 
            q.push(s.top());
             s.pop(); 
            }
        s.push(x);
    }
    while (!s.empty()) { 
        q.push(s.top());
         s.pop(); 
        }
}

// Q15: Min Stack
class MinStack {
    stack<int> s;
    int minVal;
public:
    void push(int x) {
        if (s.empty()) { 
            s.push(x);
             minVal = x; 
            } 
        else if (x >= minVal) {
             s.push(x); 
            } 
        else {
             s.push(2*x - minVal);
              minVal = x; 
            }
    }
    void pop() {
        if (s.empty()) return;
        int top = s.top();
         s.pop();
        if (top < minVal)
         minVal = 2*minVal - top;
    }
    int getMin() {
         return minVal;
         }
};

// Q16: Remove Duplicates
void removeDuplicates(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        Node* temp = curr;
        while (temp->next != NULL) {
            if (temp->next->data == curr->data) {
                Node* dup = temp->next;
                temp->next = temp->next->next;
                delete dup;
            } else temp = temp->next;
        }
        curr = curr->next;
    }
}

// Q17: Nth from End
int nthFromEnd(Node* head, int n) {
    Node* fast = head;
    Node* slow = head;
    for (int i = 0; i < n; i++) {
        if (fast == NULL) 
        return -1;
        fast = fast->next;
    }
    while (fast != NULL) {
         fast = fast->next;
          slow = slow->next; 
        }
    return slow->data;
}

// Q18: Delete Middle Node (Access Only)
void deleteMiddle(Node* node) {
    if (node == NULL || node->next == NULL) 
    return;
    Node* temp = node->next;
    node->data = temp->data;
    node->next = temp->next;
    delete temp;
}

// Q19: Add Two Lists
Node* addLists(Node* l1, Node* l2) {
    Node* result = NULL;
    Node* tail = NULL;
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
        Node* newNode = new Node();
        newNode->data = sum % 10;
        newNode->next = NULL;
        if (!result)
         result = tail = newNode;
        else { 
            tail->next = newNode; 
            tail = newNode; 
        }
    }
    return result;
}

// Q20: Detect Loop Start
Node* detectLoopStart(Node* head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
         break;
    }
    if (!fast || !fast->next)
     return NULL;
    slow = head;
    while (slow != fast)
     { 
        slow = slow->next; 
        fast = fast->next;
     }
    return slow;
}

// Helper to print standard list
void printList(Node* head) {
    while (head) { 
        cout << head->data << " -> "; 
        head = head->next; }
    cout << "NULL" << endl;
}

// ==========================================
// SIMPLIFIED MAIN FUNCTION
// ==========================================
int main() {
    int choice;
    char cont;

    do {
        // Menu Display
        cout << "\n========================================\n";
        cout << "      DSA FINAL PROJECT MENU            \n";
        cout << "========================================\n";
        cout << "1. Rotate Array\n2. Insertion Sort\n3. Hospital Priority Queue\n4. Palindrome List\n";
        cout << "5. Merge Two Lists\n6. Detect Cycle\n7. Remove Consecutive Absents\n8. Delete Node (No Head)\n";
        cout << "9. Deque (DLL)\n10. Optimized Merge Sort\n11. Sort Stack (Recursion)\n12. Balanced Brackets\n";
        cout << "13. Stack via Queues\n14. Train Sort\n15. Min Stack\n16. Remove Duplicates\n";
        cout << "17. Nth from End\n18. Delete Middle (Access Only)\n19. Add Linked Lists\n20. Detect Loop Start\n";
        cout << "0. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice (0-20): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "--- Q1: Rotate Array ---" << endl;
                int arr[] = {1, 2, 3, 4, 5};
                cout << "Original: "; printArray(arr, 5);
                rotateRight(arr, 5, 2);
                cout << "Rotated:  "; printArray(arr, 5);
                break;
            }
            case 2: {
                cout << "--- Q2: Rearrange Array ---" << endl;
                int arr[] = {1, -2, 3, -4, 5, -6};
                cout << "Original: "; printArray(arr, 6);
                rearrangeInsertionSort(arr, 6);
                cout << "Sorted:   "; printArray(arr, 6);
                break;
            }
            case 3: {
                cout << "--- Q3: Hospital Priority Queue ---" << endl;
                HospitalQueue hq;
                hq.InsertPriority("Alice", 5);
                hq.InsertPriority("Bob", 1);
                hq.display();
                break;
            }
            case 4: {
                cout << "--- Q4: Palindrome ---" << endl;
                Node* head = new Node(1);
                head->next = new Node(2);
                head->next->next = new Node(1);
                SolutionQ4 sol4;
                if(sol4.isPalindrome(head)) cout << "Palindrome" << endl;
                else cout << "Not Palindrome" << endl;
                break;
            }
            case 5: {
                cout << "--- Q5: Merge Lists (Price) ---" << endl;
                NodePrice* hp1 = new NodePrice(1); hp1->next = new NodePrice(3);
                NodePrice* hp2 = new NodePrice(2); hp2->next = new NodePrice(4);
                NodePrice* hpRes = MergeLists(hp1, hp2);
                printListPrice(hpRes);
                break;
            }
            case 6: {
                cout << "--- Q6: Detect Cycle ---" << endl;
                Node* head = new Node(1);
                head->next = new Node(2);
                head->next->next = head; // cycle
                SolutionQ6 sol6;
                if(sol6.detectCycle(head)) cout << "Cycle Detected" << endl;
                else cout << "No Cycle" << endl;
                break;
            }
            case 7: {
                cout << "--- Q7: Remove Absents ---" << endl;
                Node* head = new Node(1);
                head->next = new Node(0);
                head->next->next = new Node(0);
                head->next->next->next = new Node(0);
                head->next->next->next->next = new Node(1);
                RemoveConsecutiveAbsents(head, 3);
                printList(head);
                break;
            }
            case 8: {
                cout << "--- Q8: Delete without Head ---" << endl;
                Node* head = new Node(10);
                head->next = new Node(20);
                head->next->next = new Node(30);
                cout << "Deleting 20..." << endl;
                SolutionQ8 sol8;
                sol8.deleteNode(head->next);
                printList(head);
                break;
            }
            case 9: {
                cout << "--- Q9: Deque (DLL) ---" << endl;
                Deque dq;
                dq.insertFront(10); dq.insertRear(20); dq.display();
                dq.removeFront(); dq.display();
                break;
            }
            case 10: {
                cout << "--- Q10: Optimized Merge Sort ---" << endl;
                Node* head = new Node(4);
                head->next = new Node(2);
                head->next->next = new Node(1);
                head = mergeSort(head);
                printList(head);
                break;
            }
            case 11: {
                cout << "--- Q11: Sort Stack ---" << endl;
                stack<int> s;
                s.push(30); s.push(10); s.push(20);
                sortStack(s);
                cout << "Stack sorted (Top is max): " << s.top() << endl;
                break;
            }
            case 12: {
                cout << "--- Q12: Brackets ---" << endl;
                string expr = "{[]}";
                checkBrackets(expr);
                break;
            }
            case 13: {
                cout << "--- Q13: Stack via Queue ---" << endl;
                StackUsingQueues suq;
                suq.push(10); suq.push(20);
                cout << "Top: " << suq.top() << endl;
                break;
            }
            case 14: {
                cout << "--- Q14: Train Sort ---" << endl;
                queue<int> q;
                q.push(3); q.push(1); q.push(2);
                sortTrain(q);
                cout << "Sorted Queue Front: " << q.front() << endl;
                break;
            }
            case 15: {
                cout << "--- Q15: Min Stack ---" << endl;
                MinStack ms;
                ms.push(5); ms.push(2); ms.push(10);
                cout << "Min: " << ms.getMin() << endl;
                break;
            }
            case 16: {
                cout << "--- Q16: Remove Duplicates ---" << endl;
                Node* head = new Node(1);
                head->next = new Node(1);
                head->next->next = new Node(2);
                removeDuplicates(head);
                printList(head);
                break;
            }
            case 17: {
                cout << "--- Q17: Nth from End ---" << endl;
                Node* head = new Node(10);
                head->next = new Node(20);
                head->next->next = new Node(30);
                cout << "2nd from last: " << nthFromEnd(head, 2) << endl;
                break;
            }
            case 18: {
                cout << "--- Q18: Delete Middle ---" << endl;
                Node* head = new Node(1);
                head->next = new Node(2);
                head->next->next = new Node(3);
                deleteMiddle(head->next);
                printList(head);
                break;
            }
            case 19: {
                cout << "--- Q19: Add Lists ---" << endl;
                Node* l1 = new Node(2); l1->next = new Node(4);
                Node* l2 = new Node(5); l2->next = new Node(6);
                Node* res = addLists(l1, l2);
                printList(res);
                break;
            }
            case 20: {
                cout << "--- Q20: Detect Loop Start ---" << endl;
                Node* head = new Node(1);
                head->next = new Node(2);
                head->next->next = head;
                Node* start = detectLoopStart(head);
                if(start) cout << "Loop start: " << start->data << endl;
                break;
            }
            case 0: 
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default: cout << "Invalid choice!" << endl;
        }

        cout << "Do you want to run another function? (y/n): ";
        cin >> cont;

    } while (cont == 'y' || cont == 'Y');

    return 0;
}