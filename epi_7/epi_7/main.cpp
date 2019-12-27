//
//  main.cpp
//  epi_7
//
//  Created by Mayank Gupta on 02/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

class LL {
public:
    LL* next;
    int val;
    LL(int _val) {val = _val; next = nullptr; }
};

LL* createLL(vector<int>& A, int cycle = -1) {
    LL* head = nullptr;
    LL* curr = nullptr;
    LL* chead = nullptr;
    FF(i, 0, A.size()) {
        LL* l = new LL(A[i]);
        if (i == cycle) chead = l;
        if (head == nullptr) head = l;
        if (curr != nullptr) curr->next = l;
        curr = l;
    }
    curr->next = chead;
    return head;
}

void printLL(LL* A) {
    while (A != nullptr) {
        cout << A->val << " ";
        A = A->next;
    }
    cout << endl;
}

// 7.1 - Merge Two LL
LL* mergeTwoLL(LL* A, LL* B) {
    LL* head = nullptr;
    LL* curr = nullptr;
    while (A != nullptr && B != nullptr) {
        if (A->val <= B->val) {
            if (head == nullptr) head = A;
            if (curr != nullptr) {
                curr->next = A;
            }
            curr = A;
            A = A->next;
        } else {
            if (head == nullptr) head = B;
            if (curr != nullptr) {
                curr->next = B;
            }
            curr = B;
            B = B->next;
        }
    }
    
    if (A != nullptr) curr->next = A;
    else curr->next = B;
    return head;
}

// 7.2 - Cycle in LL
LL* checkCycle(LL* A) {
    LL* s = A;
    LL* f = A;
    s = A->next;
    if (A->next == nullptr) return nullptr;
    f = A->next->next;
    while (s != f) {
        s = s->next;
        if (f == nullptr || f->next == nullptr) return nullptr;
        f = f->next->next;
    }
    
    int count = 1;
    LL* ss = s->next;
    while (ss != s) {
        ss = ss->next;
        count++;
    }
    
    s = A;
    f = A;
    FF(i, 0, count) {
        f = f->next;
    }
    while (s != f) {
        s = s->next;
        f = f->next;
    }
    return s;
}

// 7.5
class LLI {
public:
    LL* first;
    int second;
    
    LLI(LL* n, int v) {first = n; second = v;}
};

LLI* getCycleHead(LL* A) {
    LL* s = A;
    LL* f = A;
    while (f != nullptr && f->next != nullptr) {
        s = s->next;
        f = f->next->next;
        if (s == f) break;
    }
    if (f == nullptr) {
        LLI* ll = new LLI(nullptr, -1);
        return ll;
    }
    int count = 0;
    f = f->next; count++;
    while (f != s) {
        f = f->next;
        count++;
    }
    s = A;
    f = A;
    while (count > 0) f = f->next;
    
    int branchlen = 0;
    while (s != f) {
        s = s->next;
        f = f->next;
        branchlen++;
    }
    LLI* ll = new LLI(s, branchlen);
    return ll;
}

LL* getOverlapWithCycle(LL* A, LL* B) {
    LLI* pp1 = getCycleHead(A);
    LLI* pp2 = getCycleHead(B);
    
    if (pp1->first == nullptr || pp2->first == nullptr) return nullptr;
    if (pp1->first == pp2->first) {
        while (pp1->second > pp2->second) {
            A = A->next;
            pp1->second--;
        }
        while (pp2->second > pp1->second) {
            B = B->next;
            pp2->second--;
        }
        while (A != B) {
            A = A->next; B = B->next;
        }
        return A;
    }
    
    if (pp1->second < pp2->second) {
        return pp1->first;
    }
    return pp2->first;
}

// 7.6 Even-odd merge
LL* evenOddMerge(LL* A) {
    LL* ecurr = nullptr;
    LL* ocurr = nullptr;
    LL* ehead = nullptr;
    LL* ohead = nullptr;
    int count = 0;
    while (A != nullptr) {
        if (count%2 == 0) {
            if (ehead == nullptr) ehead = A;
            if (ecurr != nullptr) ecurr->next = A;
            ecurr = A;
        } else {
            if (ohead == nullptr) ohead = A;
            if (ocurr != nullptr) ocurr->next = A;
            ocurr = A;
        }
        A = A->next;
        count++;
    }
    ocurr->next = nullptr;
    ecurr->next = ohead;
    return ehead;
}

// 7.9 Reversing LL
LL* reverseLL(LL* A) {
    LL* prev = nullptr;
    LL* curr = A;
    while (curr != nullptr) {
        LL* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}

// 7.12 Posting list
class Node {
public:
    Node* next;
    Node* jump;
    int val;
    Node(int _v, Node* n = nullptr, Node* j = nullptr) { val = _v; next = n; jump = j;}
};

Node* getPostingsListCopy(Node* root) {
    //Node* prev = nullptr;
    Node* curr = nullptr;
    Node* head = nullptr;
    Node* old = root;
    while (old != nullptr) {
        Node* n = new Node(old->val, old->next);
        if (head == nullptr) head = n;
        old->next = n;
        old = n->next;
    }
    
    curr = root;
    while (curr != nullptr) {
        Node* newjump = curr->jump->next;
        curr = curr->next;
        curr->jump = newjump;
        curr = curr->next;
    }
    
    curr = root;
    while (curr->next != nullptr) {
        curr->next = curr->next->next;
        curr = curr->next;
    }
    
    return head;
}

Node* reverseLL(Node* root) {
    Node* curr = root;
    Node* prev = nullptr;
    Node* temp = nullptr;
    while (curr->next != nullptr) {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return curr;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> v1 = {1,3,5,7,8,20};
    vector<int> v2 = {2,4,5,5,6,9,11,14,19};
    LL* A = createLL(v1);
    LL* B = createLL(v2);
    //LL* M = mergeTwoLL(A,B);
    //printLL(A);
    LL* M = reverseLL(A);
    
    printLL(M);
    
    LL* C = createLL(v2, 4);
    cout << checkCycle(C)->val << endl;
    return 0;
}
