//
//  main.cpp
//  epi_9
//
//  Created by Mayank Gupta on 02/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;
template<typename T>
void printL(vector<T>& A) {
    FF(i, 0, A.size()) {
        cout << A[i] << " ";
    }
    cout << endl;
}

class Node {
public:
    Node* left;
    Node* right;
    int val;
    Node(int _v, Node* l = nullptr, Node* r = nullptr) {val = _v; left = l; right = r;}
};

// 9.5 Morris Traversal
Node* getPred(Node* root) {
    Node* pp = root->left;
    while (pp->right != nullptr && pp->right != root) {
        pp = pp->right;
    }
    return pp;
}

void morrisTraversal(Node* root) {
    Node* curr = root;
    vector<int> res;
    while (curr != nullptr) {
        if (curr->left == nullptr) {
            res.push_back(curr->val);
            curr = curr->right;
        } else {
            Node* pred = getPred(curr);
            if (pred->right != nullptr) {
                pred->right = nullptr;
                res.push_back(curr->val);
                curr = curr->right;
            } else {
                pred->right = curr;
                curr = curr->left;
            }
        }
    }
    printL<int>(res);
}

// 9.7 - Reconstruct tree from Inorder & Preorder Data
Node* getTree(vector<int>& A, vector<int>& B, int as, int ae, int bs, int be) {
    if (as > ae || bs > be) return nullptr;
    Node* r = new Node(B[bs]);
    int amid = as;
    FF(i, as, ae+1) {
        if (A[i] == B[bs]) {
            amid = i;
            break;
        }
    }
    int alen = amid-as;
    r->left = getTree(A, B, as, amid-1, bs+1, bs+alen);
    r->right = getTree(A, B, amid+1, ae, bs+alen+1, be);
    return r;
}

// 9.13 - LCA without parent
vector<Node*> getPath(Node* root, Node* a) {
    vector<Node*> p;
    vector<int> state;
    p.push_back(root);
    state.push_back(0);
    while (p.size() > 0) {
        int id = p.size()-1;
        Node* n = p[id];
        if (n == a) return p;
        if (state[id] == 0) {
            state[id]++;
            if (n->left) {
                p.push_back(n->left);
                state.push_back(0);
            }
        } else if (state[id] == 1) {
            state[id]++;
            if (n->right) {
                p.push_back(n->right);
                state.push_back(0);
            }
        } else {
            p.pop_back(); state.pop_back();
        }
    }
    return p;
}

Node* getLCA(Node* root, Node* a, Node* b) {
    vector<Node*> apath = getPath(root, a);
    vector<Node*> bpath = getPath(root, b);
    
    Node* lca = nullptr;
    int ai = 0; int bi = 0;
    while (ai < apath.size() && bi < bpath.size() && apath[ai] == bpath[bi]) {
        lca = apath[ai];
        ai++; bi++;
    }
    return lca;
}

// 9.2 - k-balanced
class info {
public:
    Node* n;
    int lc;
    int rc;
    int tc;
    info(Node* _n, int _lc = 0, int _rc = 0) {n = _n; lc = _lc; rc = _rc; tc = lc+rc;}
};

info* kBalanced(Node* root, int K) {
    if (root == nullptr) {
        info* ii = new info(nullptr);
        return ii;
    }
    info* li = kBalanced(root->left, K);
    info* ri = kBalanced(root->right, K);
    if (li->n != nullptr) {
        return li;
    }
    if (ri->n != nullptr) {
        return ri;
    }
    info* ii = new info(nullptr);
    ii->lc = li->tc; ii->rc = ri->tc;
    ii->tc = ii->lc + ii->rc + 1;
    if (abs(li->tc - ri->tc) > K) {
        ii->n = root;
    }
    return ii;
}

// 9.8 - Contruct tree using pre-order and null-markers

Node* getMarkerTree(vector<int>& A) {
    vector<Node*> s;
    vector<int> state;
    Node* n = new Node(A[0]);
    Node* head = n;
    s.push_back(n);
    state.push_back(0);
    FF(i, 1, A.size()) {
        int id = s.size()-1;
        n = s[id];
        if (state[id] == 0) {
            state[id]++;
            if (A[i] != -1) {
                Node* t = new Node(A[i]);
                n->left = t;
                s.push_back(t);
                state.push_back(0);
            }
        } else if (state[id] == 1) {
            state[id]++;
            if (A[i] != -1) {
                Node* t = new Node(A[i]);
                n->right = t;
                s.push_back(t);
                state.push_back(0);
            }
        } else {
            s.pop_back();
            state.pop_back();
        }
    }
    return head;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Node* n3 = new Node(3);
    Node* n4 = new Node(4, n3, nullptr);
    Node* n1 = new Node(1);
    Node* n2 = new Node(2, n1, n4);
    Node* n9 = new Node(9);
    Node* n10 = new Node(10, n9, nullptr);
    Node* n8 = new Node(8, nullptr, n10);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7, n6, n8);
    Node* n5 = new Node(5, n2, n7);
    
    morrisTraversal(n5);
    Node* r = getLCA(n5, n6, n10);
    cout << "lca: " << r->val << endl;
    return 0;
}
