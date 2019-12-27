//
//  main.cpp
//  epi_11
//
//  Created by Mayank Gupta on 03/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

int searchLarger(vector<int>& A, int B) {
    int l = 0; int h = A.size()-1;
    while (l < h) {
        int mid = (l+h)>>1;
        if (A[mid] <= B) {
            if (l == mid) mid++;
            l = mid;
        } else {
            h = mid;
        }
    }
    if (A[l] > B) return l;
    return -1;
}

// 11.3
int searchIdEl(vector<int>& A) {
    int l = 0; int h = A.size()-1;
    while (l < h) {
        int mid = (l+h)>>1;
        if (A[mid] < mid) {
            if (l == mid) mid++;
            l = mid;
        } else if (A[mid] > mid){
            h = mid;
        } else {
            return mid;
        }
    }
    return -1;
}

// 11.8
int findKthElement(vector<int>& A, vector<int>& B, int as, int ae, int bs, int be, int K) {
    int alen = ae-as+1;
    int blen = be-bs+1;
    if (alen <= 0) return B[bs+K-1];
    if (blen <= 0) return A[as+K-1];
    if (K == 1) return min(A[as], B[bs]);
    
    int aval = K/2;
    if (aval > alen) aval = alen;
    int bval = K - aval;
    if (bval > blen) {
        bval = blen;
        aval = K - bval;
    }
    int amid = as + aval - 1;
    int bmid = bs + bval - 1;
    if (A[amid] > B[bmid]) {
        K -= bmid - bs + 1;
        bs = bmid+1;
        ae = amid;
    } else {
        K -= amid - as + 1;
        as = amid+1;
        be = bmid;
    }
    return findKthElement(A, B, as, ae, bs, be, K);
}

// 11.13 - find Kth smallest element in O(n) expected time
int partition(vector<int>& A, int as, int ae, int id) {
    int pivot = as;
    int val = A[id];
    if (id != as) swap(A[as], A[id]);
    FF(i, as+1, ae+1) {
        if (A[i] < val) {
            pivot++;
            if (pivot != i) swap(A[pivot], A[i]);
        }
    }
    if (pivot != as) swap(A[pivot], A[as]);
    return pivot;
}

int qsFind(vector<int>& A, int as, int ae, int K) {
    int B = K - 1;
    while (as < ae) {
        int pid = partition(A, as, ae, as);
        //cout << as << "/" << ae << "/" << pid << endl;
        if (pid == B) return A[pid];
        else if (pid < B) {
            as = pid+1;
        } else {
            ae = pid-1;
        }
    }
    return -1;
}

// 11.1 - First occurence in sorted array
int getFirstId(vector<int>& A, int B) {
    int l = 0; int h = A.size()-1;
    while (l < h) {
        int mid = (l+h)>>1;
        if (A[mid] < B) {
            if (l == mid) mid++;
            l = mid;
        } else {
            h = mid;
        }
    }
    if (A[l] == B) return l;
    return -1;
}

// 11.9 - Square root
double sqrt(double x) {
    if (x == 1 || x == 0) return x;
    double ratio = 1;
    if (x < 1) {
        x *= 100;
        ratio = 10;
    }
    double l = 1; double h = x;
    while (h-l > 0.001) {
        double mid = (l+h)/2.0;
        double sq = mid*mid;
        if (sq < x) {
            l = mid;
        } else if (sq > x) {
            h = mid;
        } else {
            break;
        }
    }
    double val = (l+h)/2.0;
    val /= ratio;
    return val;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //vector<int> A = {-3,-1,1,2,3,4,6,8,10,12,15,20,25,30,35,40,45};
    /*int id = searchLarger(A, 50);
    cout << "id = 50: " << id << endl;
    id = searchLarger(A, 6);
    cout << "id = 6: " << id << endl;*/
    //int id = searchIdEl(A);
    //cout << "id = " << id << endl;
    
    vector<int> A = {1,3,5,5,6,8,9,9,11,13,13,15};
    vector<int> B = {1,2,2,2,4,6,9,20};
    cout << getFirstId(A, 5) << endl;
    /*FF(i, 1, 21) {
        int val = findKthElement(A, B, 0, A.size()-1, 0, B.size()-1, i);
        cout << "i:" << i << " => "<< val << endl;
    }*/
    //int v3 = qsFind(A, 0, A.size()-1, 3);
    //cout << "v3: " << v3 << endl;
    
    cout << sqrt(15) << endl;

    return 0;
}
