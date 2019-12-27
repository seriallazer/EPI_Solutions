//
//  main.cpp
//  epi_8
//
//  Created by Mayank Gupta on 02/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

//8.1
template <typename T>
class MaxStack {
public:
    vector<T> s;
    vector<T> maxs;
    
    MaxStack() {}
    
    bool isEmpty() { return s.size() == 0; }
    
    void push(T val) {
        if (isEmpty()) {
            s.push_back(val);
            maxs.push_back(val);
        } else {
            T topmax = maxs[maxs.size()-1];
            if (val > topmax) topmax = val;
            maxs.push_back(topmax);
            s.push_back(val);
        }
    }
    
    void pop() {
        s.pop_back();
        maxs.pop_back();
    }
    
    T front() {
        return s[s.size()-1];
    }
    
    T getMax() {
        return maxs[maxs.size()-1];
    }
};

template<typename T>
void printL(vector<T>& A) {
    FF(i, 0, A.size()) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// 8.5 Tower of hanoi
void hanoiTower(vector<int>& F, vector<int>& T, vector<int>& V, int N, int fnum, int tnum, int vnum) {
    if (N==0) return;
    hanoiTower(F, V, T, N-1, fnum, vnum, tnum);
    //printL<int>(F);
    cout << "tranfer " << F.back() << " from T" << fnum << " to T" << tnum << endl;
    int val = F.back(); F.pop_back();
    T.push_back(val);
    hanoiTower(V, T, F, N-1, vnum, tnum, fnum);
}

// 8.9 - print BST in level order
class Node {
public:
    Node* left;
    Node* right;
    int val;
};

void printLevelOrder(Node* root) {
    queue<Node*> qq;
    qq.push(root);
    vector<int> res;
    while (!qq.empty()) {
        Node* t = qq.front();
        qq.pop();
        res.push_back(t->val);
        if (t->left) qq.push(t->left);
        if (t->right) qq.push(t->right);
    }
}

// 8.10 - Circular Queue
class CQueue {
public:
    vector<int> v;
    int CAP;
    int sid;
    int eid;
    int count;
    
    CQueue(int cap) {
        CAP = cap;
        v.resize(CAP);
        count = 0;
    }
    
    void enqueue(int val) {
        if (eid == sid && count == CAP) {
            sid++;
            sid %= CAP;
        }
        v[eid] = val;
        eid++;
        eid %= CAP;
        count++;
        count = max(count, CAP);
    }
    
    int dequeue() {
        if (count == 0) return -1;
        int val = v[sid];
        sid++;
        sid %= CAP;
        count--;
        return val;
    }
    
    void resize(int cap) {
        int oldcap = CAP;
        CAP = cap;
        vector<int> temp;
        temp.resize(CAP);
        int tc = count;
        int oldsid = sid;
        sid = 0;
        eid = 0;
        while (tc > cap) {
            oldsid++;
            oldsid %= oldcap;
        }
        tc = min(tc, cap);
        while (tc > 0) {
            temp[eid] = v[oldsid];
            oldsid++; oldsid %= oldcap;
            tc--;
            eid++;
        }
        count = min(count, CAP);
    }
};

// 8.12 Queue from 2 stacks
class Queue {
public:
    vector<int> vtop;
    vector<int> vbottom;
    
    bool isEmpty() {
        return vtop.size() == 0 & vbottom.size() == 0;
    }
    
    void enqueue(int val) {
        vbottom.push_back(val);
    }
    
    int dequeue() {
        if (isEmpty()) return -1;
        if (vtop.size() == 0) {
            while (vbottom.size() > 0) {
                int val = vbottom[vbottom.size()-1];
                vbottom.pop_back();
                vtop.push_back(val);
            }
        }
        int val = vtop[vtop.size()-1];
        vtop.pop_back();
        return val;
    }
};

// 8.4 - Postings jump order
class Node {
public:
    Node* next;
    Node* jump;
    int val;
    int order;
};

vector<int> jumpOrder(Node* root) {
    Node* temp = root;
    int order = 0;
    vector<int> res;
    vector<Node*> s;
    s.push_back(root);
    while (s.size() > 0) {
        Node* top = s[s.size()-1];
        s.pop_back();
        if (top && top->order < 0) {
            top->order = order;
            order++;
            res.push_back(top->val);
            s.push_back(top->next);
            s.push_back(top->jump);
        }
    }
    return res;
}

// 8.7
class Stack {
public:
    vector<int> s;
    
    Stack() {
        s.clear();
    }
    
    void push(int val) {
        s.push_back(val);
    }
    
    void pop() {
        if (s.size() > 0) s.pop_back();
    }
    
    int top() {
        if (s.size() > 0) return s.back();
        return -1;
    }
    
    bool empty() {
        return s.size() == 0;
    }
};

void StackSorting(Stack*& s) {
    Stack* t = new Stack();
    while (!s->empty()) {
        int top = s->top(); s->pop();
        while (!t->empty() && top > t->top()) {
            int ttop = t->top(); t->pop();
            s->push(ttop);
        }
        t->push(top);
    }
    
    while (!t->empty()) {
        s->push(t->top()); t->pop();
    }
    delete t;
}

void insertRecursion(Stack*& s, int e) {
    if (s->empty() || e >= s->top()) {
        s->push(e);
    } else {
        int top = s->top(); s->pop();
        insertRecursion(s, e);
        s->push(top);
    }
}

void StackSortingRecursion(Stack*& s) {
    if (s->empty()) return;
    int top = s->top(); s->pop();
    StackSortingRecursion(s);
    insertRecursion(s, top);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> F = {3, 2, 1};
    vector<int> T = {};
    vector<int> V = {};
    hanoiTower(F, T, V, F.size(), 1, 2, 3);
    return 0;
}



