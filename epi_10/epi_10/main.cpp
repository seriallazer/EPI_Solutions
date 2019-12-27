//
//  main.cpp
//  epi_10
//
//  Created by Mayank Gupta on 02/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>

#define FF(i, a,b) for(int i = a; i < b; i++)

using namespace std;

template <typename T>
void printL(vector<T>& A) {
    FF(i,0,A.size()) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// 10.1 - Merge sorted files
void swapNodes(pair<int,int>& p1, pair<int,int>& p2) {
    pair<int,int> t = p1;
    p1 = p2;
    p2 = t;
}

void editVal(vector<pair<int,int>>& h, int id) {
    int p = id;
    int sm = p;
    while (p < h.size()) {
        int l = (p<<1)+1; int r = l+1;
        if (l < h.size() && h[l].first < h[sm].first) sm = l;
        if (r < h.size() && h[r].first < h[sm].first) sm = r;
        if (sm == p) break;
        swapNodes(h[p], h[sm]);
        p = sm;
    }
}

pair<int,int> extractMin(vector<pair<int,int>>& h) {
    pair<int,int> val = h[0];
    if (h.size() > 1) swapNodes(h[0], h[h.size()-1]);
    h.pop_back();
    editVal(h, 0);
    return val;
}

void insertVal(vector<pair<int,int>>& h, pair<int,int>& pp) {
    h.push_back(pp);
    int c = h.size()-1;
    while (c > 0) {
        int p = (c-1)>>1;
        if (h[p].first <= h[c].first) break;
        swapNodes(h[p], h[c]);
        c = p;
    }
}

vector<int> mergeFiles(vector<vector<int>>& A) {
    vector<pair<int,int>> h;
    vector<int> fid;
    vector<int> res;
    fid.resize(A.size(), 0);
    FF(i, 0, A.size()) {
        pair<int,int> pp = make_pair(A[i][0], i);
        insertVal(h, pp);
        fid[i]++;
    }
    
    while (h.size() > 0) {
        int tid = h[0].second;
        res.push_back(h[0].first);
        if (fid[tid] >= A[tid].size()) {
            extractMin(h);
        } else {
            int ii = fid[tid];
            h[0].first = A[tid][ii];
            fid[tid]++;
            editVal(h, 0);
        }
    }
    return res;
}

// 10.2 - Sort k-inc/dec array
vector<int> sortKArray(vector<int>& A) {
    vector<vector<int>> S;
    int is_inc = true;
    int sid = 0;
    FF(i, 1, A.size()) {
        if ((A[i-1] > A[i] && is_inc)
            || (A[i-1] < A[i] && !is_inc)) {
            vector<int> temp;
            if (is_inc) {
                S.emplace_back(A.cbegin()+sid, A.cbegin()+i-1);
                //S.push_back(temp);
            } else {
                S.emplace_back(A.crbegin()+A.size()-i, A.crbegin()+A.size()-sid+1);
                //S.push_back(temp);
            }
            sid = i;
            is_inc = !is_inc;
        }
    }
    if (sid < A.size()-1) {
        if (is_inc) {
            S.emplace_back(A.cbegin()+sid, A.end()-1);
        } else {
            S.emplace_back(A.crbegin(), A.crbegin()+A.size()-sid+1);
        }
    }
    
    return mergeFiles(S);
}

// 10.6 Approximate Sort

bool compare(int& a, int& b) {
    return a < b;
}

template <typename T>
void swapNodes(T& t1, T& t2) {
    T tt = t1;
    t1 = t2;
    t2 = tt;
}

template <typename T>
void editVal(vector<T>& h, int id, T val, bool (*compareVal)(T& v1, T& v2)) {
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
    editVal<T>(h, 0, h[0], compareVal);
    return val;
}

template <typename T>
void insertVal(vector<T>& h, const T& val, bool (*compareVal)(T& v1, T& v2)) {
    h.push_back(val);
    int c = (int)(h.size()-1);
    while (c > 0) {
        int p = (c-1)>>1;
        if (compareVal(h[c], h[p])) {
            swapNodes(h[p], h[c]);
            c = p;
        } else {
            break;
        }
    }
}

vector<int> approxSort(const vector<int>& A, int K) {
    vector<int> h;
    vector<int> res;
    FF(i, 0, A.size()) {
        if (i < K) {
            insertVal<int>(h, A[i], compare);
        } else {
            int val = h[0];
            res.push_back(val);
            editVal<int>(h, 0, A[i], compare);
        }
    }
    
    while (h.size() > 0) {
        int val = extractMin<int>(h, compare);
        res.push_back(val);
    }
    return res;
}

// 10.8
bool compareMin(int& a, int& b) { return a < b; }
bool compareMax(int& a, int& b) { return a > b; }

vector<double> onlineMedian(vector<int>& A) {
    vector<int> minh;   // maintains the latter half
    vector<int> maxh;   // maintains the first half
    vector<double> res;
    FF(i, 0, A.size()) {
        int minhval = (maxh.size() > 0) ? max(maxh[0], A[i]) : A[i];
        int maxhval = (minh.size() > 0) ? min(minh[0], A[i]) : A[i];
        insertVal<int>(minh, minhval, compareMin);
        insertVal<int>(maxh, maxhval, compareMax);
        if (minh.size() > (i+2)/2) {
            //cout << "extractingMin: " << endl;
            extractMin<int>(minh, compareMin);
            //cout << "extractingMax: " << endl;
            extractMin<int>(maxh, compareMax);
        }
        int minval = minh[0];
        int maxval = maxh[0];
        double median = (minval + maxval)/2.0;
        res.push_back(median);
        //cout << " i = " << i << endl;
        //printL<int>(minh);
        //printL<int>(maxh);
    }
    return res;
}

// 10.5 - kth largest - streaming case
vector<int> kthStreaming(vector<int>& A, int K) {
    vector<int> h;
    vector<int> res;
    FF(i, 0, A.size()) {
        if (i < K) {
            insertVal<int>(h, A[i], compare);
            if (i == K-1) res.push_back(h[0]);
        } else {
            int topval = h[0];
            if (A[i] > topval) editVal<int>(h, 0, A[i], compare);
            res.push_back(h[0]);
        }
    }
    return res;
}

// 10.7 - k closest numbers to median

int getKthVal(vector<int>& A, int k, int sid, int eid) {
    int val = A[sid];
    int pivot = sid;
    FF(i, sid+1, eid+1) {
        if (A[i] <= val) {
            pivot++;
            swap(A[pivot], A[i]);
        }
    }
    swap(A[sid], A[pivot]);
    
    if (pivot < k) return getKthVal(A, k, pivot+1, eid);
    else if (pivot > k) return getKthVal(A, k, sid, pivot-1);
    return A[pivot];
}

vector<int> kClosestMedian(vector<int>& A, int K) {
    int midval = A.size()/2;
    int median = getKthVal(A, midval, 0, A.size()-1);
    if (A.size() % 2 == 0) {
        median += getKthVal(A, midval-1, 0, A.size()-1);
        median /= 2;
    }
    
    vector<int> S;
    FF(i, 0, A.size()) {
        S.push_back(abs(A[i]-median));
    }
    
    int maxdiff = getKthVal(S, K, 0, S.size()-1);
    vector<int> res;
    FF(i, 0, A.size()) {
        if (abs(A[i]-median) < maxdiff) res.push_back(A[i]);
    }
    FF(i, 0, A.size()) {
        if (res.size() == K) break;
        if (abs(A[i]-median) == maxdiff) res.push_back(A[i]);
    }
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //vector<vector<int>> A = {{1,4,5,9,10},{-1,2,3,8,29,100,150},{0,20,30,31,35,149,199}};
    //vector<int> S = mergeFiles(A);
    //printL<int>(S);
    
    vector<int> A = {57, 131, 493, 294, 221, 339, 418, 452, 442, 190};
    //vector<int> S = approxSort(A, 8);
    //vector<double> S = onlineMedian(A);
    vector<int> S = kthStreaming(A, 3);
    printL<int>(S);
    return 0;
}
