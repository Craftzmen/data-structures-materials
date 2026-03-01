#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

// Linked list node
struct Node {
    int data;
    Node* next;
};

// Hospital patient node
struct PatientNode {
    string name;
    int level;
    PatientNode* next;
};

// Doubly linked node for deque
struct DNode {
    int data;
    DNode* next;
    DNode* prev;
};

// Create a new linked list node
Node* createNode(int val) {
    Node* n = new Node;
    n->data = val;
    n->next = nullptr;
    return n;
}

// Print linked list
void printList(Node* head) {
    while(head) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

// Print hospital queue
void printPatientList(PatientNode* head) {
    while(head) {
        cout << "[" << head->name << " Lvl:" << head->level << "] -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

// Insert patient based on priority
void insertPriority(PatientNode*& head, string name, int lvl) {
    PatientNode* n = new PatientNode{name, lvl, nullptr};
    if(!head || lvl < head->level) {
        n->next = head;
        head = n;
        return;
    }

    PatientNode* curr = head;
    while(curr->next && curr->next->level <= lvl)
        curr = curr->next;

    n->next = curr->next;
    curr->next = n;
}

// Rotate array by one
void rotateByOne(int arr[], int n) {
    int last = arr[n-1];
    for(int i=n-1; i>0; i--) arr[i] = arr[i-1];
    arr[0] = last;
}

// Rotate array k times
void rotateArrayRecursive(int arr[], int n, int k) {
    if(k==0) return;
    rotateByOne(arr,n);
    rotateArrayRecursive(arr,n,k-1);
}

// Rearrange negatives first, positives after
void rearrangeNegPos(vector<int>& arr) {
    vector<int> neg, pos;
    for(int x: arr) (x<0?neg:pos).push_back(x);

    int i=0;
    for(int x: neg) arr[i++] = x;
    for(int x: pos) arr[i++] = x;
}

// Check if linked list is palindrome
bool isPalindrome(Node* head) {
    if(!head || !head->next) return true;

    Node *slow=head, *fast=head;
    while(fast && fast->next) { slow=slow->next; fast=fast->next->next; }

    Node *prev=nullptr, *curr=slow, *next=nullptr;
    while(curr) { next=curr->next; curr->next=prev; prev=curr; curr=next; }

    Node *left=head, *right=prev;
    while(right) {
        if(left->data != right->data) return false;
        left=left->next; right=right->next;
    }
    return true;
}

// Merge two sorted linked lists
Node* mergeLists(Node* l1, Node* l2) {
    if(!l1) return l2;
    if(!l2) return l1;
    if(l1->data < l2->data) { l1->next = mergeLists(l1->next,l2); return l1; }
    else { l2->next = mergeLists(l1,l2->next); return l2; }
}

// Detect loop in linked list
Node* detectLoop(Node* head) {
    Node *slow=head, *fast=head;
    while(fast && fast->next) {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast) {
            slow=head;
            while(slow!=fast){ slow=slow->next; fast=fast->next; }
            return slow;
        }
    }
    return nullptr;
}

// Remove consecutive zeros >= k
void removeConsecutiveZeros(Node*& head, int k) {
    Node* dummy = createNode(-1);
    dummy->next = head;
    Node *prev=dummy, *curr=head;

    while(curr) {
        if(curr->data==0) {
            Node* temp=curr; int count=0;
            while(temp && temp->data==0){ count++; temp=temp->next; }

            if(count>=k) {
                while(curr!=temp){ Node* del=curr; curr=curr->next; delete del; }
                prev->next = temp;
            } else {
                while(curr!=temp){ prev=curr; curr=curr->next; }
            }
        } else { prev=curr; curr=curr->next; }
    }

    head = dummy->next;
    delete dummy;
}

// Delete a node by pointer
void deleteNodeByPointer(Node* node) {
    if(!node || !node->next){ cout<<"Cannot delete tail\n"; return; }
    Node* temp=node->next;
    node->data=temp->data;
    node->next=temp->next;
    delete temp;
}

// Merge sort linked list
void splitList(Node* src, Node** a, Node** b) {
    Node *slow=src, *fast=src->next;
    while(fast){ fast=fast->next; if(fast){ slow=slow->next; fast=fast->next; } }
    *a=src; *b=slow->next; slow->next=nullptr;
}

Node* sortedMerge(Node* a, Node* b) {
    if(!a) return b;
    if(!b) return a;
    if(a->data<=b->data){ a->next=sortedMerge(a->next,b); return a; }
    else{ b->next=sortedMerge(a,b->next); return b; }
}

void mergeSortList(Node** headRef) {
    Node* head=*headRef;
    if(!head || !head->next) return;
    Node *a,*b;
    splitList(head,&a,&b);
    mergeSortList(&a); mergeSortList(&b);
    *headRef = sortedMerge(a,b);
}

// Stack sort
void insertSortedStack(stack<int>& s,int x){
    if(s.empty() || x>s.top()){ s.push(x); return; }
    int temp = s.top(); s.pop();
    insertSortedStack(s,x);
    s.push(temp);
}

void sortStack(stack<int>& s){
    if(!s.empty()){
        int x=s.top(); s.pop();
        sortStack(s);
        insertSortedStack(s,x);
    }
}

// Check brackets
void checkBrackets(string expr){
    stack<char> s;
    for(char x:expr){
        if(x=='('||x=='{'||x=='[') s.push(x);
        else if(x==')'||x=='}'||x==']'){
            if(s.empty()){ cout<<"Extra closing "<<x<<"\n"; return; }
            char top=s.top();
            if((x==')' && top!='(') || (x==']' && top!='[') || (x=='}' && top!='{')){
                cout<<"Mismatch "<<top<<" found "<<x<<"\n"; return;
            }
            s.pop();
        }
    }
    if(!s.empty()) cout<<"Unclosed "<<s.top()<<"\n";
    else cout<<"Expression valid\n";
}

// Stack using two queues
struct StackTwoQueues{
    queue<int> q1,q2;
    void push(int x){
        q2.push(x);
        while(!q1.empty()){ q2.push(q1.front()); q1.pop(); }
        swap(q1,q2);
    }
    void pop(){ if(!q1.empty()) q1.pop(); }
    int top(){ return q1.empty()?-1:q1.front(); }
    bool empty(){ return q1.empty(); }
};

// Train bogies sorting
void trainSort(Node* head){
    stack<int> station;
    queue<int> output;
    int expected=1;
    Node* curr=head;

    while(curr || !station.empty()){
        if(!station.empty() && station.top()==expected){
            output.push(station.top()); station.pop(); expected++;
        }
        else if(curr){
            if(curr->data==expected){ output.push(curr->data); expected++; }
            else station.push(curr->data);
            curr=curr->next;
        }
        else break;
    }

    cout<<"Sorted train: ";
    while(!output.empty()){ cout<<output.front()<<" "; output.pop(); }
    cout<<"\n";
}

// Min stack
struct MinStack{
    stack<int> s,minS;
    void push(int x){ s.push(x); if(minS.empty()||x<=minS.top()) minS.push(x); }
    void pop(){ if(s.top()==minS.top()) minS.pop(); s.pop(); }
    int getMin(){ return minS.empty()?-1:minS.top(); }
};

// Remove duplicates
void removeDuplicates(Node* head){
    Node* ptr1=head;
    while(ptr1 && ptr1->next){
        Node* ptr2=ptr1;
        while(ptr2->next){
            if(ptr1->data==ptr2->next->data){ Node* del=ptr2->next; ptr2->next=ptr2->next->next; delete del; }
            else ptr2=ptr2->next;
        }
        ptr1=ptr1->next;
    }
}

// Nth to last element
void nthToLast(Node* head,int n){
    Node* main_ptr=head; Node* ref_ptr=head;
    for(int i=0;i<n;i++){ if(!ref_ptr){ cout<<"List too short\n"; return; } ref_ptr=ref_ptr->next; }
    while(ref_ptr){ main_ptr=main_ptr->next; ref_ptr=ref_ptr->next; }
    cout<<"Nth to last: "<<main_ptr->data<<"\n";
}

// Delete middle node
void deleteMiddle(Node* node){
    if(!node || !node->next){ cout<<"Cannot delete middle/tail node\n"; return; }
    Node* temp=node->next; node->data=temp->data; node->next=temp->next; delete temp;
}

// Add two linked lists
Node* addTwoLists(Node* first, Node* second){
    Node* res=nullptr; Node** nodePtr=&res; int carry=0;
    while(first || second || carry){
        int sum=carry+(first?first->data:0)+(second?second->data:0);
        carry=sum/10;
        *nodePtr=createNode(sum%10);
        nodePtr=&((*nodePtr)->next);
        if(first) first=first->next;
        if(second) second=second->next;
    }
    return res;
}

// Detect loop start
Node* loopStart(Node* head){
    Node *slow=head,*fast=head;
    while(fast && fast->next){
        slow=slow->next; fast=fast->next->next;
        if(slow==fast){ slow=head; while(slow!=fast){ slow=slow->next; fast=fast->next; } return slow; }
    }
    return nullptr;
}

// Deque
struct MyDeque{
    DNode *front=nullptr,*rear=nullptr;
    void insertFront(int val){ DNode* n=new DNode{val,front,nullptr}; if(front) front->prev=n; else rear=n; front=n; }
    void insertRear(int val){ DNode* n=new DNode{val,nullptr,rear}; if(rear) rear->next=n; else front=n; rear=n; }
    void display(){ for(DNode* t=front;t;t=t->next) cout<<t->data<<" "; cout<<"\n"; }
};

// MAIN MENU
int main(){
    int choice; char cont;

    do{
        cout<<"\n---PBL MENU 1-20---\n";
        cout<<"1 Array Rotation\n2 Rearrange Neg/Pos\n3 Hospital Queue\n4 Palindrome List\n5 Merge Lists\n";
        cout<<"6 Detect Loop\n7 Remove Consecutive Zeros\n8 Delete Node\n9 Deque\n10 MergeSort List\n";
        cout<<"11 Stack Sort\n12 Bracket Check\n13 Stack using Queues\n14 Train Bogies\n15 Min Stack\n";
        cout<<"16 Remove Duplicates\n17 Nth to Last\n18 Delete Middle Node\n19 Add Two Linked Lists\n20 Loop Start Node\n";
        cout<<"Enter choice: "; cin>>choice;

        switch(choice){
            case 1:{
                int arr[]={1,2,3,4,5,6};
                cout<<"Original: "; for(int i:arr) cout<<i<<" ";
                rotateArrayRecursive(arr,6,2);
                cout<<"\nRotated: "; for(int i:arr) cout<<i<<" "; cout<<"\n"; break;
            }
            case 2:{
                vector<int> v={-1,2,-3,4,5,-6};
                cout<<"Original: "; for(int x:v) cout<<x<<" ";
                rearrangeNegPos(v);
                cout<<"\nRearranged: "; for(int x:v) cout<<x<<" "; cout<<"\n"; break;
            }
            case 3:{
                PatientNode* p=nullptr;
                insertPriority(p,"Ali",5);
                insertPriority(p,"Zara",1);
                insertPriority(p,"Bilal",3);
                printPatientList(p); break;
            }
            case 4:{
                Node* h=createNode(1); h->next=createNode(2); h->next->next=createNode(1);
                printList(h);
                cout<<(isPalindrome(h)?"Palindrome":"Not Palindrome")<<"\n"; break;
            }
            case 5:{
                Node* l1=createNode(1); l1->next=createNode(3);
                Node* l2=createNode(2); l2->next=createNode(4);
                Node* merged=mergeLists(l1,l2);
                printList(merged); break;
            }
            case 6:{
                Node* h=createNode(1); h->next=createNode(2); h->next->next=createNode(3);
                h->next->next->next=h->next;
                Node* loop=detectLoop(h);
                cout<<(loop?"Loop at "+to_string(loop->data):"No loop")<<"\n"; break;
            }
            case 7:{
                Node* h=createNode(1); h->next=createNode(0); h->next->next=createNode(0); h->next->next->next=createNode(2);
                printList(h);
                removeConsecutiveZeros(h,2);
                printList(h); break;
            }
            case 8:{
                Node* h=createNode(1); h->next=createNode(2); h->next->next=createNode(3);
                printList(h);
                deleteNodeByPointer(h->next);
                printList(h); break;
            }
            case 9:{
                MyDeque dq; dq.insertFront(1); dq.insertRear(2); dq.insertFront(0);
                dq.display(); break;
            }
            case 10:{
                Node* h=createNode(4); h->next=createNode(2); h->next->next=createNode(5); h->next->next->next=createNode(1);
                printList(h);
                mergeSortList(&h);
                printList(h); break;
            }
            case 11:{
                stack<int> s; s.push(3); s.push(1); s.push(4); s.push(2);
                sortStack(s);
                cout<<"Sorted stack: "; while(!s.empty()){ cout<<s.top()<<" "; s.pop(); } cout<<"\n"; break;
            }
            case 12:{
                string expr="{[()]}";
                checkBrackets(expr); break;
            }
            case 13:{
                StackTwoQueues st; st.push(1); st.push(2); st.push(3);
                cout<<"Top element: "<<st.top()<<"\n";
                st.pop();
                cout<<"Top after pop: "<<st.top()<<"\n"; break;
            }
            case 14:{
                Node* h=createNode(3); h->next=createNode(1); h->next->next=createNode(2);
                trainSort(h); break;
            }
            case 15:{
                MinStack ms; ms.push(5); ms.push(2); ms.push(7); ms.push(1);
                cout<<"Min: "<<ms.getMin()<<"\n";
                ms.pop();
                cout<<"Min after pop: "<<ms.getMin()<<"\n"; break;
            }
            case 16:{
                Node* h=createNode(1); h->next=createNode(2); h->next->next=createNode(2); h->next->next->next=createNode(3);
                printList(h);
                removeDuplicates(h);
                printList(h); break;
            }
            case 17:{
                Node* h=createNode(1); h->next=createNode(2); h->next->next=createNode(3); h->next->next->next=createNode(4);
                nthToLast(h,2); break;
            }
            case 18:{
                Node* h=createNode(1); h->next=createNode(2); h->next->next=createNode(3);
                deleteMiddle(h->next);
                printList(h); break;
            }
            case 19:{
                Node* l1=createNode(3); l1->next=createNode(4);
                Node* l2=createNode(5); l2->next=createNode(6);
                Node* sum=addTwoLists(l1,l2);
                printList(sum); break;
            }
            case 20:{
                Node* h=createNode(1); h->next=createNode(2); h->next->next=createNode(3);
                h->next->next->next=h->next;
                Node* start=loopStart(h);
                cout<<(start?"Loop starts at "+to_string(start->data):"No loop")<<"\n"; break;
            }
            default: cout<<"Invalid choice\n";
        }

        cout<<"Continue? y/n: "; cin>>cont;

    } while(cont=='y'||cont=='Y');

    return 0;
}