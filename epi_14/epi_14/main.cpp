//
//  main.cpp
//  epi_14
//
//  Created by Mayank Gupta on 04/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    int val;
    Node(int _v, Node* l = nullptr, Node* r = nullptr) { val = _v; left = l; right = r; }
};

pair<int,int> isBST(Node* root) {
    int val = root->val;
    pair<int,int> rp = make_pair(val,val);
    if (root->left) {
        pair<int,int> pp = isBST(root->left);
        if (pp.second < pp.first || pp.second > val) return make_pair(1,0);
        rp.first = pp.first;
    }
    if (root->right) {
        pair<int,int> pp = isBST(root->right);
        if (pp.second < pp.first || pp.first < val) return make_pair(1,0);
        rp.second = pp.second;
    }
    return rp;
}

bool checkBST(Node* root) {
    if (root == nullptr) return true;
    pair<int,int> pp = isBST(root);
    return pp.first <= pp.second;
}

// 14.5 - Search element greater than key k
int getValK(Node* root, int K) {
    Node* curr = root;
    Node* par = nullptr;
    while (curr != nullptr) {
        if (curr->val > K) {
            par = curr;
            curr = curr->left;
        } else if (curr->val < K) {
            curr = curr->right;
            if (curr == nullptr && par != nullptr) {
                curr = par->right;
                par = nullptr;
            }
        } else {
            if (curr->right) {
                curr = curr->right;
                while (curr->left != nullptr) curr = curr->left;
                return curr->val;
            } else if (par != nullptr) {
                return par->val;
            } else {
                break;
            }
        }
    }
    return -1;
}

// 14.4 - First occurence of K in BST
// recursive
Node* getFirstOccur(Node* root, int K) {
    if (root == nullptr) return nullptr;
    Node* lr = getFirstOccur(root->left, K);
    if (lr != nullptr) return lr;
    if (root->val == K) return root;
    return getFirstOccur(root->right, K);
}

//iterative
Node* getFirstOccurIter(Node* root, int K) {
    Node* p = nullptr; Node* c = root;
    while (c != nullptr) {
        if (c->val < K) {
            c = c->right;
        } else if (c->val >= K) {
            if (c->val == K) p = c;
            c = c->left;
        }
    }
    return p;
}

int main(int argc, const char * argv[]) {
    // insert code here...
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
    
    pair<int,int> pp = isBST(n5);
    //cout << pp.first <<"/" << pp.second << endl;
    
    cout << getValK(n5, 10) << endl;
    return 0;
}
