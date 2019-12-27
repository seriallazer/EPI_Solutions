//
//  main.cpp
//  epi_15
//
//  Created by Mayank Gupta on 04/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

template <typename T>
void printL(vector<T>& A) {
    FF(i, 0, A.size()) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// 15.11
int editDistance(const string& A, const string& B) {
    vector<vector<int>> D;
    D.resize(A.length()+1);
    FF(i, 0, D.size()) {
        D[i].resize(B.length()+1);
        D[i][0] = i;
    }
    FF(j, 0, D[0].size()) {
        D[0][j] = j;
    }
    
    FF(i, 1, D.size()) {
        FF(j, 1, D[i].size()) {
            if (A[i-1] == B[j-1]) D[i][i] = D[i-1][j-1];
            else {
                D[i][j] = min(D[i-1][j], D[i][j-1]);
            }
        }
    }
    return D[A.length()][B.length()];
}

// 15.4 - Diameter of the tree
class Tree {
public:
    vector<pair<Tree*, int>> edges;
};

pair<int,int> treeDia(Tree* root) {
    pair<int,int> pp = make_pair(0,0);
    int mp1 = 0; int mp2 = 0;
    FF(i, 0, root->edges.size()) {
        pair<int,int> t = treeDia(root->edges[i].first);
        int wt = root->edges[i].second;
        pp.second = max(pp.second, t.second);
        if (t.first + wt > mp1) {
            mp2 = mp1;
            mp1 = t.first + wt;
        } else if (t.first + wt > mp2) {
            mp2 = t.first + wt;
        }
        pp.second = max(pp.second, mp1+mp2);
    }
    pp.first = mp1;
    return pp;
}

// 15.22 - Scheduling tutors
int minTutors(vector<int>& A) { // each val = start-time in mins (0-450 mins - 9AM-5PM); endtime = starttime+30 mins
    sort(A.begin(), A.end());
    int count = 0;
    int used = 0;
    queue<pair<int,int>> qq;
    FF(i, 0, A.size()) {
        if (qq.empty()) {
            qq.push(make_pair(A[i]+30, A[i]+90));
        } else {
            pair<int,int> pp = qq.front();
            if (A[i] >= pp.first && A[i] <= pp.second) {
                qq.pop();
            } else if (A[i] > pp.second) {
                qq.pop();
                used++;
            }
            qq.push(make_pair(A[i]+30, A[i]+90));
        }
        if (qq.size() + used > count) count = qq.size() + used;
    }
    return count;
}

// 15.2 - Counting inversions
int numInver(vector<int>& A, int sid, int eid) {
    if (sid >= eid) return 0;
    int count = 0;
    int mid = (sid+eid)>>1;
    count += numInver(A, sid, mid);
    //cout << sid << "/" << mid << "=> " << count << endl;
    int rc = numInver(A, mid+1, eid);
    count += rc;
    //cout << mid+1 << "/" << eid << "=> " << rc << endl;
    
    int as = sid; int ae = mid;
    int bs = mid+1; int be = eid;
    int ai = as; int bi = bs;
    int alen = ae-as+1; int blen = be-bs+1;
    vector<int> temp;
    int lc = 0;
    while (ai <= ae && bi <= be) {
        int aval = (ai <= ae) ? A[ai] : A[ae];
        int bval = (bi <= be) ? A[bi] : A[be];
        if (bval < aval) {
            lc += ae - ai + 1;
            //cout << "-->>" << A[ai] << "/" << A[bi] << "=> " << lc << "||" << ai << "/" << bi << endl;
            temp.push_back(bval);
            //cout << "<<<->>> push: " << bval << endl;
            bi++;
        } else {
            temp.push_back(aval);
            //cout << "<<<->>> push: " << aval << endl;
            ai++;
        }
    }
    while (ai <= ae) {
        //cout << "<<<->>> push: " << A[ai] << endl;
        temp.push_back(A[ai]); ai++;
    }
    while (bi <= be) {
        //cout << "<<<->>> push: " << A[bi] << endl;
        temp.push_back(A[bi]); bi++;
    }
    count += lc;
    
    FF(i, sid, eid+1) {
        A[i] = temp[i-as];
    }
    return count;
}

int numInverN2(vector<int> A) {
    int count = 0;
    FF(i, 0, A.size()) {
        FF(j, i+1, A.size()) {
            count += (A[j] < A[i]) ? 1 : 0;
            //cout << A[i] << "/" << A[j] << " " << count << endl;
        }
    }
    return count;
}

// word-breaking
string wordBreak(vector<string>& A, string S) {
    vector<int> D;
    D.resize(S.length()+1, -1);
    D[0] = 0;
    unordered_map<string,bool> cmap;
    FF(i, 0, A.size()) {
        cmap[A[i]] = true;
    }
    
    FF(i, 1, D.size()) {
        for(int j = i-1; j >= 0; j--) {
            if (D[j] >= 0) {
                string str = S.substr(j, i-j);
                if (cmap.find(str) != cmap.end()) {
                    D[i] = j;
                    break;
                }
            }
        }
    }
    
    if (D[S.length()] < 0) return "";
    string res = "";
    int prev = S.length();
    while (prev > 0) {
        int id = D[prev];
        res = S.substr(id, prev-id) + " " + res;
        prev = id;
    }
    return res;
}

// 15.26 - Huffman Coding
class Node {
public:
    int c; // leaf-char
    int code;
    double f; // freq
    Node* left;
    Node* right;
    
    Node(int _c, double _f, Node* l = nullptr, Node* r = nullptr) {
        c = _c; f = _f; left = l; right = r;
        code = -1;
    }
};

bool compare(Node*& a, Node*& b) {
    return a->f < b->f;
}

template <typename T>
void swapNodes(T& v1, T& v2) {
    T t = v1;
    v1 = v2;
    v2 = t;
}

template <typename T>
void insertVal(vector<T>& h, T& val, bool (*compareVal)(T& v1, T& v2)) {
    h.push_back(val);
    int c = h.size()-1;
    while (c > 0) {
        int p = (c-1)>>1;
        if (compareVal(h[c], h[p])) {
            swapNodes(h[c], h[p]);
            c = p;
        } else {
            break;
        }
    }
}

template <typename T>
void editVal(vector<T>& h, int id, T& val, bool (*compareVal)(T& v1, T& v2)) {
    h[id] = val;
    int p = id;
    int sm = p;
    while (p < h.size()) {
        int l = (p<<1)+1; int r = l+1;
        if (l < h.size() && compareVal(h[l], h[sm])) sm = l;
        if (r < h.size() && compareVal(h[r], h[sm])) sm = r;
        if (sm == p) break;
        swapNodes(h[p], h[sm]);
        p = sm;
    }
}

template <typename T>
T extractMin(vector<T>& h, bool (*compareVal)(T& v1, T& v2)) {
    T val = h[0];
    if (h.size() > 1) swapNodes(h[0], h[h.size()-1]);
    h.pop_back();
    editVal(h, 0, h[0], compareVal);
    return val;
}

vector<string> huffmanCoding(vector<double> F) {
    vector<Node*> h;
    FF(i, 0, F.size()) {
        Node* n = new Node(i, F[i]);
        insertVal<Node*>(h, n, compare);
    }
    
    while (h.size() > 1) {
        Node* n1 = extractMin<Node*>(h, compare);
        Node* n2 = extractMin<Node*>(h, compare);
        n1->code = 0; n2->code = 1;
        Node* n = new Node(-1, n1->f+n2->f, n1, n2);
        insertVal<Node*>(h, n, compare);
    }
    
    Node* root = h[0];
    vector<string> R; R.resize(F.size());
    
    vector<Node*> s;
    s.push_back(root);
    string code = "2";
    while (s.size() > 0) {
        int id = s.size()-1;
        Node* n = s[id];
        if (code[id] == '2') {
            code[id] = '0';
            if (n->left) {
                s.push_back(n->left);
                code.push_back('2');
            }
        } else if (code[id] == '0') {
            code[id]++;
            if (n->right) {
                s.push_back(n->right);
                code.push_back('2');
            }
        } else {
            code.pop_back();
            s.pop_back();
            if (n->c < 0) continue;
            R[n->c] = code;
        }
    }
    //printL<string>(R);
    return R;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    //               0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
    vector<int> A = {3,6,2,6,4,8,1,9,0,-1,4,11,10,19,2,21};
    //  {2,3,6,6}{1,4,8,9}//{-1,0,4,11}{2,10,19,21}
    //vector<int> A = {6,2,1};
    //cout << "inver: " << numInver(A, 0, A.size()-1) << endl;
    //A = {3,6,2,6,4,8,1,9,0,-1,4,11,10,19,2,21};
    //cout << "inver2: " << numInverN2(A) << endl;
    
    vector<double> F = {8.17, 1.49, 2.78, 4.25, 12.7, 2.23, 2.02, 6.09, 6.97, 0.15, 0.77, 4.03, 2.41, 6.75, 7.51, 1.93,
        0.1, 5.99, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15, 1.97, 0.07};
    vector<string> R = huffmanCoding(F);
    FF(i, 0, R.size()) {
        char c = 'A' + i;
        cout << c << " => " << R[i] << endl;
    }
    return 0;
}
