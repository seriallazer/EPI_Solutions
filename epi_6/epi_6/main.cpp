//
//  main.cpp
//  epi_6
//
//  Created by Mayank Gupta on 02/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

void swap(int& a, int& b) {
    int t= a;
    a = b; b = t;
}

void quickSort(vector<int>& A, int sid, int eid) {
    if (sid >= eid) return;
    int pivot = sid;
    FF(i, sid+1, eid+1) {
        if (A[i] <= A[sid]) {
            pivot++;
            swap(A[pivot], A[i]);
        }
    }
    swap(A[sid], A[pivot]);
    quickSort(A, sid, pivot-1);
    quickSort(A, pivot+1, eid);
}


template<typename T>
void printL(vector<T>& A) {
    FF(i,0,A.size()) {
        cout << A[i] << " ";
    }
    cout << endl;
}

//6.1
void quickSort2(vector<int>& A, int sid, int eid) {
    if (sid >= eid) return;
    int pi = sid; int pj = eid;
    int val = A[sid];
    int ii = sid;
    while (pi < pj) {
        if (A[pi] < val) pi++;
        else if (A[pj] > val) pj--;
        else if (A[pi] >= val && A[pj] <= val && A[pi] != A[pj]) {
            swap(A[pi], A[pj]);
        }
        else {
            int i = max(pi, ii) + 1;
            while (i < pj && A[i] == val) i++;
            if (i >= pj) break;
            swap(A[pi], A[i]);
            ii = i;
        }
        //printL<int>(A); cout << pi << " " << pj << endl;
    }
    quickSort2(A, sid, pi-1);
    quickSort2(A, pj+1, eid);
}

//6.14 - Sudoku checker
bool checkRow(vector<vector<int>>& A, int rid) {
    vector<bool> M;
    M.resize(10, 0);
    FF(i, 0, A[rid].size()) {
        if (A[rid][i] == 0) continue;
        int val = A[rid][i];
        if (!M[val]) {
            M[val] = 1;
        } else {
            return false;
        }
    }
    return true;
}

bool checkCol(vector<vector<int>>& A, int cid) {
    vector<bool> M;
    M.resize(10, 0);
    FF(i, 0, A.size()) {
        if (A[i][cid] == 0) continue;
        int val = A[i][cid];
        if (!M[val]) {
            M[val] = 1;
        } else {
            return false;
        }
    }
    return true;
}

bool checkBlock(vector<vector<int>>& A, int bid) {
    vector<bool> M; M.resize(10, 0);
    int si = (bid/3)*3; int sj = 3*(bid%3);
    FF(i, si, si+3) {
        FF(j, sj, sj+3) {
            if (A[i][j] == 0) continue;
            int val  = A[i][j];
            if (!M[val]) {
                M[val] = 1;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool sudokuChecker(vector<vector<int>>& A) {
    FF(i, 0, 10) {
        if (!checkRow(A, i) || !checkCol(A, i) || !checkBlock(A, i)) return false;
    }
    return true;
}

// 6.22 - Phone mnemonic
vector<string> getMnemonic(int num) {
    vector<string> mapping = {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};
    vector<string> res;
    if (num < 10) {
        //cout << "num: " << num << " || ";
        FF(i, 0, mapping[num].length()) {
            string str(1, mapping[num][i]);
            res.push_back(str);
            //cout << str << "|" << mapping[num] << " " ;
        }
        //cout << endl;
        return res;
    }
    
    vector<string> temp = getMnemonic(num/10);
    int rem = num%10;
    FF(i, 0, mapping[rem].length()) {
        FF(j, 0, temp.size()) {
            string str = temp[j] + mapping[rem][i];
            res.push_back(str);
        }
    }
    return res;
}

// 6.3 - Robot car tank capacity - Max diff

int tankCap(vector<int>& C) {
    int minval = C[0];
    int maxcap = 0;
    FF(i, 0, C.size()) {
        if (C[i] < minval) minval = C[i];
        if (C[i] - minval > maxcap) maxcap = C[i] - minval;
    }
    return maxcap;
}

// 6.4 Generalizations of max-diff
int maxDiffK2(vector<int>& A) {
    vector<int> d1;
    vector<int> d2;
    d1.resize(A.size()); d2.resize(A.size());
    
    int minval = A[0];
    int maxp = 0;
    FF(i, 0, A.size()) {
        if (A[i] < minval) minval = A[i];
        if (A[i] - minval > maxp) maxp = A[i] - minval;
        d1[i] = maxp;
    }
    
    int maxval = A[A.size()-1];
    maxp = 0;
    for(int i = A.size()-1; i >=0; i--) {
        if (A[i] > maxval) maxval = A[i];
        if (maxval - A[i] > maxp) maxp = maxval - A[i];
        d2[i] = maxp;
    }
    
    maxp = 0;
    FF(i, 1, d1.size()-1) {
        if (d1[i] + d2[i+1] > maxp) maxp = d1[i]+d2[i+1];
    }
    return maxp;
}

int maxDiffK1(vector<int>& A, int sid, int eid) {
    int minval = A[sid];
    int maxp = 0;
    FF(i, sid, eid+1) {
        if (A[i] < minval) minval = A[i];
        if (A[i] - minval > maxp) maxp = A[i]-minval;
    }
    return maxp;
}

// K is small
int maxDiffGeneric(vector<int>& A, int K, int sid, int eid) {
    if (K == 1) return maxDiffK1(A, sid, eid);
    int maxp = 0;
    int minval = A[0];
    FF(i, sid+1, eid-1) {
        if (A[i] < minval) minval = A[0];
        if (A[i] - minval > maxp) maxp = A[i] - minval;
        int val = maxp + maxDiffGeneric(A, K-1, i+1, eid);
        if (val > maxp) maxp = val;
    }
    return maxp;
}

// better solution for K-fixed =>
int maxDiffKFixed(vector<int>& A, int K) {
    vector<vector<int>> V;
    V.resize(2);
    V[0].resize(K+1, 0);
    V[1].resize(K+1, INT_MIN);
    
    FF(i, 1, A.size()+1) {
        FF(j, 1, min(i+1, K)) {
            V[1][j] = max(V[1][j], V[0][j-1]-A[i-1]); // S(j, i) = A[i] + max_p<=i((B(j,p))
            V[0][j] = max(V[0][j], A[i-1] + V[1][j]); // B(j, i) = max_p<i(S(j-1,p)) - A[i]
        }
    }
    return V[0][K];
}

// 6.6 Longest increasing sub-ARRAY
pair<int,int> longestIncSA(vector<int>& A) {
    int sid = 0;
    int eid = 0;
    int msid = 0;
    int meid = 0;
    FF(i, 1, A.size()) {
        if (A[i] > A[i-1]) {
            eid = i;
        } else {
            if (eid - sid > meid - msid) {
                msid = sid; meid = eid;
            }
            sid = i;
        }
    }
    return make_pair(msid, meid);
}

// 6.7 Computing Equivalence classes
vector<vector<int>> eqRelation(vector<int>& A, vector<int>& B, int N) {
    vector<int> V;
    V.resize(N, -1);
    FF(i, 0, A.size()) {
        if (V[A[i]] < 0 && V[B[i]] < 0) {
            V[A[i]] = V[B[i]] = max(A[i], B[i]);
        } else {
            V[A[i]] = max(V[A[i]], V[B[i]]);
            V[B[i]] = V[A[i]];
        }
    }
    
    unordered_map<int,int> cmap;
    vector<vector<int>> res;
    FF(i, 0, V.size()) {
        int val = V[i];
        if (cmap.find(val) == cmap.end()) {
            res.push_back({i});
            cmap[val] = res.size()-1;
        } else {
            res[cmap[val]].push_back(i);
        }
    }
    
    FF(i, 0, res.size()) {
        printL<int>(res[i]);
    }
    return res;
}

//6.9 - BigInteger Multiply
string addNums(string A, string B) {
    if (A == "" || A == "0") return B;
    if (B == "" || B == "0") return A;
    
    int ai = A.length()-1; int bi = B.length()-1;
    string res = "";
    int carry = 0;
    while (ai >= 0 || bi >= 0 || carry > 0) {
        int aval = (ai >= 0) ? A[ai] - '0' : 0;
        int bval = (bi >= 0) ? B[bi] - '0' : 0;
        int val = aval + bval + carry;
        carry = val/10;
        val = val%10;
        char c = '0' + val;
        res.insert(res.begin(), 1, c);
        ai--; bi--;
    }
    
    return res;
}

string smallMult(string A, int n) {
    if (n == 0 || A == "") return "0";
    if (n == 1) return A;
    int i = A.length()-1;
    int carry = 0;
    string res = "";
    while (i >= 0 || carry > 0) {
        int aval = (i>=0) ? A[i]-'0' : 0;
        int val = aval*n + carry;
        carry = val/10;
        val = val%10;
        char c = '0' + val;
        res.insert(res.begin(), 1, c);
        i--;
    }
    
    return res;
}

string bigIntMult(string A, string B) {
    string res = "";
    string zeros = "";
    for(int i = B.length()-1; i >= 0; i--) {
        int val = B[i] - '0';
        string temp = smallMult(A, val);
        temp += zeros;
        res = addNums(res, temp);
        zeros += "0";
    }
    return res;
}

// 6.15 - Print array in Spiral
void printSpiral(vector<vector<int>>& A) {
    int xs = 0;
    int xe = A.size()-1;
    int ys = xs;
    int ye = xe;
    while (xs <= xe) {
        FF(i, ys, ye+1) {
            cout << A[xs][i] << " ";
        }
        xs++;
        FF(i, xs, xe+1) {
            cout << A[i][ye] << " ";
        }
        ye--;
        for(int i = ye; i >= ys; i--) {
            cout << A[xe][i] << " ";
        }
        xe--;
        for(int i = xe; i >= xe; i--) {
            cout << A[i][ys] << " ";
        }
        ys++;
    }
    cout << endl;
}

// 6.19
void swapC(char& c1, char& c2) {
    char c = c1;
    c1 = c2; c2 = c;
}

void reverse(string& A, int sid, int eid) {
    if (sid >= eid) return;
    int l = sid; int h = eid;
    while (l < h) {
        swapC(A[l], A[h]);
        l++; h--;
    }
}

void reverseWords(string& A) {
    reverse(A, 0, A.length()-1);
    int sid = 0;
    FF(i, 0, A.length()) {
        if (isspace(A[i])) {
            reverse(A, sid, i-1);
            sid = i+1;
        }
    }
    reverse(A, sid, A.length()-1);
    cout << A << endl;
}

// 6.21 remove and replace
void removeReplace(string A) {
    int wid = 0;
    int acount = 0;
    FF(i, 0, A.length()) {
        if (A[i] != 'b') {
            A[wid] = A[i];
            wid++;
        }
        if (A[i] == 'a') acount++;
    }
    cout << A << " " << acount << " " << wid << " " << A.length() << endl;
    int cid = wid-1;
    wid += acount-1;
    for(int i = cid; i >=0; i--) {
        if (A[i] != 'a') {
            A[wid] = A[i];
            wid--;
        } else {
            A[wid] = 'd';
            wid--;
            A[wid] = 'd';
            wid--;
        }
    }
    cout << A << endl;
}

// 6.1 Dutch National Flag
void dutchFlagPartition(vector<int>& A, int val) {
    int i = 0;
    int j = A.size()-1;
    int wi = i+1;
    while (i < j && wi < j) {
        if (A[i] < val) {
            i++; wi++;
        } else if (A[j] > val) {
            j--;
        } else if (A[i] >= val && A[j] < val) {
            swap(A[i], A[j]);
        } else if (A[i] > val && A[j] <= val) {
            swap(A[i], A[j]);
        } else {
            while (wi < j && A[wi] == val) wi++;
            swap(A[i], A[wi]);
        }
    }
}

// 6.2 Lazy Init
class LazyInit {
public:
    vector<bool> A;
    vector<int> P;
    vector<int> S;
    int count;
    
    LazyInit(int SZ) {
        A.resize(SZ); P.resize(SZ); S.resize(SZ);
        count = -1;
    }
    
    void write(bool val, int id) {
        int pid = P[id];
        if (pid >= 0 && pid <= count && S[pid] == id) {
            A[id] = val;
        } else {
            count++;
            A[id] = val;
            P[id] = count;
            S[count] = id;
        }
    }
    
    bool read(int id) {
        int pid = P[pid];
        if (pid >= 0 && pid <= count && S[pid] == id) return A[id];
        return false;
    }
};

// 6.4 MaxDiff Generalizations
int maxDiffGeneric(vector<int>& A, int K) {
    vector<int> S;
    vector<int> B;
    S.resize(K+1);
    B.resize(K+1);
    
    for(int j = 1; j <= K; j++) {
        B[j] = S[j-1] - A[j-1];
        S[j] = B[j] + A[j-1];
        for(int i = j; i < A.size(); i++) {
            B[j] = max(B[j], S[j-1] - A[i]);
            S[j] = max(S[j], B[j] + A[i]);
            
        }
    }
    return S[K];
}

// 6.20 First occurence of a substring
// Using Knutt-Morris-Pratt Algorithm (KMP)

vector<int> getPrefixArray(string& p) {
    vector<int> f;
    f.resize(p.length(), 0);
    int i = 1; int j = 0;
    while (i < p.length()) {
        if (p[i] == p[j]) {
            f[i] = j+1;
            i++; j++;
        } else if (j > 0) {
            j = f[j-1];
        } else {
            i++;
        }
    }
    return f;
}

bool findSubstring(string& t, string& p) {
    vector<int> f = getPrefixArray(p);
    int i = 0; int j = 0;
    while (i < t.length() && j < p.length()) {
        if (t[i] == p[j]) {
            i++; j++;
        } else if (j > 0) {
            j = f[j-1];
        } else {
            i++;
        }
    }
    if (j == p.length()) return true;
    return false;
}

void dutchFlag(vector<int>& A, int x) {
    int i = 0;
    int j = (int)A.size()-1;
    int ii = 0;
    printL(A);
    while (ii < j) {
        if (A[i] < x) {
            i++; ii++;
            continue;
        }
        if (A[j] > x) {
            j--;
            continue;
        }
        if (A[i] >= x && A[j] < x) {
            swap(A[i], A[j]); continue;
        }
        if (A[i] > x && A[j] <= x) {
            swap(A[i], A[j]);
            continue;
        }
        while (A[i] == A[ii]) {
            ii++;
            if (ii >= j) break;
        }
        if (ii < j) swap(A[i], A[ii]);
    }
}

void permutation(vector<int>& A, vector<int>& P) {
    for(int i = 0; i < P.size(); i++) {
        if (P[i] < 0) continue;
        int pid = P[i];
        P[i] -= P.size();
        int temp = A[i];
        int ii = i;
        while (pid != i && pid >= 0) {
            A[ii] = A[pid];
            ii = pid;
            pid = P[pid];
            P[pid] -= P.size();
        }
        A[ii] = temp;
    }
    
    for(int i = 0; i < P.size(); i++) {
        P[i] += P.size();
    }
}

typedef pair<int,int> PP;
void flipColor(vector<vector<bool>>& A, int x, int y) {
    queue<pair<int,int>> q;
    vector<vector<bool>> V;
    V.resize(A.size());
    for(int i = 0; i < A.size(); i++) {
        V[i].resize(A[i].size(), 0);
    }
    bool orgsign = A[x][y];
    q.push(make_pair(x,y));
    V[x][y] = 1;
    while (!q.empty()) {
        PP pp = q.front(); q.pop();
        A[pp.first][pp.second] = 1 - orgsign;
        int nx = pp.first; int ny = pp.second;
        if (nx > 0 && A[nx-1][ny] == orgsign && !V[nx-1][ny]) {
            q.push(make_pair(nx-1,ny));
            V[nx-1][ny] = 1;
        }
        if (nx < A.size()-1 && A[nx+1][ny] == orgsign && !V[nx+1][ny]) {
            q.push(make_pair(nx+1,ny));
            V[nx+1][ny] = 1;
        }
        if (ny > 0 && A[nx][ny-1] == orgsign && !V[nx][ny-1]) {
            q.push(make_pair(nx,ny-1));
            V[nx][ny-1] = 1;
        }
        if (ny < A[nx].size()-1 && A[nx][ny+1] == orgsign && !V[nx+1][ny]) {
            q.push(make_pair(nx+1,ny));
            V[nx+1][ny] = 1;
        }
    }
}

vector<int> getPrefixArray(string p) {
    vector<int> f;
    f.resize(p.length());
    int i = 0;
    int j = 1;
    while (j < p.length()) {
        if (p[j] == p[i]) {
            f[j] = i + 1;
            i++;
            j++;
        } else if (i > 0){
            i = f[i-1];
        } else {
            j++;
        }
    }
    return f;
}

int kmpAlgo(string s, string p) { // knutt morris pratt
    vector<int> f = getPrefixArray(p);
    int i = 0; int j = 0;
    while (i < s.length()){
        if (s[i] == p[j]) {
            i++;
            j++;
            if (j == p.length()) return i;
        } else if (j > 0) {
            j = f[j-1];
        } else {
            i++;
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> A = { 3, 3, 3, 5, 6, 2, 9, 1, 3, 3, 3, 3, 3};
    //dutchFlagPartition(A, 3);
    dutchFlag(A, 3);
    printL(A);
    //quickSort2(A, 0, A.size()-1);
    //printL(A);
    //pair<int,int> pp = longestIncSA(A);
    //cout << pp.first << "/" << pp.second << endl;
    
    //vector<int> S1 = {1,5,3,6};
    //vector<int> S2 = {2,1,0,5};
    //vector<vector<int>> R = eqRelation(S1, S2, 7);
    //vector<string> A = getMnemonic(2276696);
    //printL<string>(A);
    
    
    //cout << "bigmult: " << bigIntMult("123456789123456789", "200000000") << endl;
    string str = "Alice likes Bob ";
    reverseWords(str);
    
    removeReplace("bxybxxakjsakdayyabuuaibiijbkk");
    return 0;
}
