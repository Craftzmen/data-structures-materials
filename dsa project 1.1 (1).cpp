#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};


Node* newNode(int x) {
    Node* n = new Node;
    n->data = x;
    n->next = NULL;
    return n;
}

void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}



// Q1 Rotate Array (Right K, Recursive)
void rotateOnce(int a[], int n) {
    int last = a[n-1];
    for (int i=n-1;i>0;i--) a[i]=a[i-1];
    a[0]=last;
}
void rotateArray(int a[], int n, int k) {
    if (k==0) return;
    rotateOnce(a,n);
    rotateArray(a,n,k-1);
}

// Q2 Rearrange Negatives First (Stable)
void rearrangeNegatives(int a[], int n) {
    for (int i=0;i<n;i++) {
        if (a[i]<0) {
            int j=i;
            while (j>0 && a[j-1]>=0) {
                int t=a[j]; a[j]=a[j-1]; a[j-1]=t;
                j--;
            }
        }
    }
}

// Q3 Priority Queue (Hospital)
struct Patient { string name; int emergencyLevel; Patient* next; };
Patient* newPatient(string name,int level){
    Patient* n=new Patient; n->name=name;n->emergencyLevel=level;n->next=NULL; return n;
}
void priorityInsert(Patient*& head,string name,int level){
    Patient* n=newPatient(name,level);
    if(!head||level<head->emergencyLevel){n->next=head;head=n;return;}
    Patient* cur=head;
    while(cur->next && cur->next->emergencyLevel<=level) cur=cur->next;
    n->next=cur->next; cur->next=n;
}

// Q4 Palindrome Linked List
Node* reverse(Node* h){
    Node* p=NULL;
    while(h){Node* n=h->next;h->next=p;p=h;h=n;}
    return p;
}
bool isPalindrome(Node* h){
    Node *s=h,*f=h;
    while(f&&f->next){s=s->next;f=f->next->next;}
    Node* r=reverse(s);
    Node* temp=r;
    while(r){ if(h->data!=r->data) return false; h=h->next; r=r->next;}
    reverse(temp); // restore
    return true;
}

// Q5 Merge Two Sorted Lists
Node* merge(Node* a,Node* b){
    if(!a) return b; if(!b) return a;
    if(a->data<b->data){a->next=merge(a->next,b);return a;}
    b->next=merge(a,b->next); return b;
}

// Q6 Detect Cycle Start
Node* detectCycle(Node* h){
    Node *s=h,*f=h;
    while(f&&f->next){s=s->next;f=f->next->next;if(s==f)break;}
    if(!f||!f->next) return NULL;
    s=h; while(s!=f){s=s->next;f=f->next;}
    return s;
}

// Q7 Remove Consecutive Absents (0s)
void removeKZeros(Node*& h,int k){
    Node d; d.next=h; Node* p=&d;
    while(p->next){
        Node* c=p->next; int cnt=0;
        while(c&&c->data==0){c=c->next;cnt++;}
        if(cnt>=k)p->next=c; else p=p->next;
    }
    h=d.next;
}

// Q8 Delete Node (Given Pointer, safe for tail)
void deleteGiven(Node*& head, Node* n){
    if(!n) return;
    if(n->next){ // normal case
        Node* t=n->next; n->data=t->data; n->next=t->next; delete t;
    }else{ // tail
        if(head==n){delete n; head=NULL;}
        else{
            Node* cur=head;
            while(cur->next!=n) cur=cur->next;
            cur->next=NULL; delete n;
        }
    }
}

// Q9 Deque
void pushFront(Node*& h,int x){Node* n=newNode(x);n->next=h;h=n;}
void pushBack(Node*& h,int x){
    Node* n=newNode(x); if(!h){h=n;return;}
    Node* c=h; while(c->next)c=c->next; c->next=n;
}
void popFront(Node*& h){if(!h)return;Node* t=h;h=h->next;delete t;}
void popBack(Node*& h){
    if(!h||!h->next){delete h;h=NULL;return;}
    Node* c=h; while(c->next->next)c=c->next;
    delete c->next; c->next=NULL;
}

// Q10 Merge Sort Linked List (with partial sort detection)
bool isSorted(Node* h){
    if(!h) return true;
    while(h->next){
        if(h->data > h->next->data) return false;
        h = h->next;
    }
    return true;
}

void split(Node* src,Node*& a,Node*& b){
    Node* s=src,*f=src->next;
    while(f&&f->next){s=s->next;f=f->next->next;}
    a=src; b=s->next; s->next=NULL;
}

Node* mergeSort(Node* h){
    if(!h || !h->next) return h;
    if(isSorted(h)) return h; // already sorted, skip merge
    Node *a,*b; split(h,a,b);
    return merge(mergeSort(a), mergeSort(b));
}


// Stack helpers
void push(Node*& t,int x){Node* n=newNode(x);n->next=t;t=n;}
int pop(Node*& t){int x=t->data;Node* d=t;t=t->next;delete d;return x;}

// Q11 Sort Stack (Recursion)
void insertSorted(Node*& t,int x){
    if(!t||x>t->data){push(t,x);return;}
    int v=pop(t); insertSorted(t,x); push(t,v);
}
void sortStack(Node*& t){
    if(!t)return; int v=pop(t); sortStack(t); insertSorted(t,v);
}

// Q12 Check Brackets Balance
bool checkBrackets(const char* s){
    Node* st=NULL;
    for(int i=0;s[i];i++){
        char c=s[i];
        if(c=='('||c=='{'||c=='['||c=='<') push(st,c);
        else{
            if(!st)return false;
            char t=pop(st);
            if((c==')'&&t!='(')||(c=='}'&&t!='{')||(c==']'&&t!='[')||(c=='>'&&t!='<'))
                return false;
        }
    }
    return st==NULL;
}

// Q13 Stack Using Two Queues
struct Queue{Node* f;Node* r;};
void qpush(Queue& q,int x){
    Node* n=newNode(x);
    if(!q.f){q.f=q.r=n;return;}
    q.r->next=n; q.r=n;
}
int qpop(Queue& q){
    int x=q.f->data; Node* t=q.f;
    q.f=q.f->next; if(!q.f)q.r=NULL; delete t; return x;
}

// Q14 Sort Queue Using Stack
void sortQueue(Node*& q){
    Node* st=NULL;
    while(q){
        int x=q->data; Node* t=q; q=q->next; delete t;
        while(st&&st->data>x){push(q,pop(st));}
        push(st,x);
    }
    while(st) push(q,pop(st));
}

// Q15 Min Stack
struct MinStack{Node* t; int mn;};
void minPush(MinStack& s,int x){
    if(!s.t){push(s.t,x);s.mn=x;}
    else if(x<s.mn){push(s.t,2*x-s.mn);s.mn=x;}
    else push(s.t,x);
}



// Q16 Remove Duplicates
void removeDup(Node* h){
    for(Node* i=h;i;i=i->next){
        Node* j=i;
        while(j->next){
            if(j->next->data==i->data){
                Node* d=j->next; j->next=d->next; delete d;
            }else j=j->next;
        }
    }
}

// Q17 Nth to Last
int nthFromLast(Node* h,int n){
    Node* f=h; while(n--)f=f->next;
    Node* s=h; while(f){s=s->next;f=f->next;}
    return s->data;
}

// Q18 Delete Middle
void deleteMiddle(Node*& h){
    Node *s=h,*f=h,*p=NULL;
    while(f&&f->next){p=s;s=s->next;f=f->next->next;}
    if(p) {p->next=s->next; delete s;}
}

// Q19 Add Two Numbers
Node* addNumbers(Node* a,Node* b){
    a=reverse(a); b=reverse(b);
    Node* r=NULL; int c=0;
    while(a||b||c){
        int s=c+(a?a->data:0)+(b?b->data:0);
        push(r,s%10); c=s/10;
        if(a)a=a->next; if(b)b=b->next;
    }
    return r;
}

int main() {
    int ch;

    do {
        cout << "\nDATA STRUCTURES PROJECT ASSIGNMENT\n";
        cout << "1  Rotate Array\n";
        cout << "2  Rearrange Negatives\n";
        cout << "3  Priority Queue\n";
        cout << "4  Palindrome\n";
        cout << "5  Merge Lists\n";
        cout << "6  Detect Cycle\n";
        cout << "7  Remove Absents\n";
        cout << "8  Delete Node\n";
        cout << "9  Deque\n";
        cout << "10 Merge Sort\n";
        cout << "11 Sort Stack\n";
        cout << "12 Brackets Balance\n";
        cout << "13 Stack Using Queues\n";
        cout << "14 Sort Queue\n";
        cout << "15 Min Stack\n";
        cout << "16 Remove Duplicates\n";
        cout << "17 Nth to Last\n";
        cout << "18 Delete Middle\n";
        cout << "19 Add Two Numbers\n";
        cout << "20 Find Loop Beginning\n";
        cout << "0  Exit\n";

        cout << "Choice: ";
        cin >> ch;

        switch (ch) {
            case 1: {
                int a[] = {1, 2, 3, 4, 5};
                rotateArray(a, 5, 5);
                for (int i = 0; i < 5; i++) cout << a[i] << " ";
                cout << endl;
            } break;

            case 2: {
                int a[] = {-3, -2, 1, 4};
                rearrangeNegatives(a, 4);
                for (int i = 0; i < 4; i++) cout << a[i] << " ";
                cout << endl;
            } break;

            case 3: {
                Patient* h = NULL;
                priorityInsert(h, "Ali", 5);
                priorityInsert(h, "zara", 1);
                priorityInsert(h, "Charlie", 3);
                for (Patient* p = h; p; p = p->next) cout << p->name << " ";
                cout << endl;
            } break;

            case 4: {
                Node* h = newNode(1);
                h->next = newNode(3);
                h->next->next = newNode(1);
                cout << (isPalindrome(h) ? "Palindrome" : "Not Palindrome") << endl;
            } break;

            case 5: {
                Node* a = newNode(1);
                a->next = newNode(3);
                Node* b = newNode(2);
                b->next = newNode(4);
                printList(merge(a, b));
            } break;

            case 6: {
                Node* h = newNode(1);
                h->next = newNode(2);
                h->next->next = newNode(3);
                h->next->next->next = h->next;  // create cycle
                cout << detectCycle(h)->data << endl;
            } break;

            case 7: {
                Node* h = newNode(1);
                h->next = newNode(0);
                h->next->next = newNode(0);
                removeKZeros(h, 2);
                printList(h);
            } break;

            case 8: {
                Node* h = newNode(1);
                h->next = newNode(2);
                deleteGiven(h, h->next);
                printList(h);
            } break;

            case 9: {
                Node* d = NULL;
                pushFront(d, 2);
                pushBack(d, 3);
                popFront(d);
                printList(d);
            } break;

            case 10: {
                Node* h = newNode(3);
                h->next = newNode(1);
                h->next->next = newNode(2);
                printList(mergeSort(h));
            } break;

            case 11: {
                Node* s = NULL;
                push(s, 3);
                push(s, 1);
                sortStack(s);
                printList(s);
            } break;

            case 12: {
                cout << (checkBrackets("{[()<>]}") ? "Balanced" : "Not Balanced") << endl;
            } break;

            case 13: {
                Queue q = {NULL, NULL};
                qpush(q, 5);
                qpush(q, 7);
                qpush(q, 1);
                qpush(q, 3);
                cout << qpop(q) << endl;
            } break;

            case 14: {
                Node* q = NULL;
                push(q, 3);
                push(q, 1);
                sortQueue(q);
                printList(q);
            } break;

            case 15: {
                MinStack s = {NULL, 0};
                minPush(s, 5);
                minPush(s, 2);
                minPush(s, 8);
                cout << s.mn << endl;
            } break;

            case 16: {
                Node* h = newNode(1);
                h->next = newNode(1);
                h->next->next = newNode(2);
                removeDup(h);
                printList(h);
            } break;

            case 17: {
                Node* h = newNode(1);
                h->next = newNode(2);
                h->next->next = newNode(3);
                cout << nthFromLast(h, 1) << endl;
            } break;

            case 18: {
                Node* h = newNode(1);
                h->next = newNode(2);
                h->next->next = newNode(3);
                deleteMiddle(h);
                printList(h);
            } break;

            case 19: {
                Node* a = newNode(3);
                a->next = newNode(1);
                a->next->next = newNode(9);
                a->next->next->next = newNode(9);
                Node* b = newNode(5);
                b->next = newNode(9);
                b->next->next = newNode(2);
                printList(addNumbers(a, b));
            } break;

            case 20: {
                Node* h = newNode(1);
                h->next = newNode(2);
                h->next->next = newNode(3);
                h->next->next->next = h->next;  // create loop
                cout << detectCycle(h)->data << endl;
            } break;
        }

    } while (ch != 0);

    return 0;
}

