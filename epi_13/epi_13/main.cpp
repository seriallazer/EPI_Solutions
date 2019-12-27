//
//  main.cpp
//  epi_13
//
//  Created by Mayank Gupta on 04/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

template <typename T>
void printL(vector<T>& A) {
    FF(i, 0, A.size()) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// 13.5 - Intersection of sorted arrays

vector<int> getInter(vector<int>& A, vector<int>& B) {
    int ai = 0; int bi = 0;
    vector<int> res;
    while (ai < A.size() && bi < B.size()) {
        if (A[ai] < B[bi]) ai++;
        else if (A[ai] > B[bi]) bi++;
        else {
            int val = A[ai];
            ai++; bi++;
            if (res.size() > 0 && val == res[res.size()-1]) {
                continue;
            }
            res.push_back(val);
        }
    }
    return res;
}

// 13.12 - Points covering intervals
struct iv {
    int start; int end;
};

bool compareIv(const iv* a, const iv* b) {
    return a->end < b->end;
}

int getMinChecks(vector<iv*>& A) {
    if (A.size() == 0) return 0;
    sort(A.begin(), A.end(), compareIv);
    
    int count = 1;
    int ptime = A[0]->end;
    FF(i, 1, A.size()) {
        if (A[i]->start > ptime) {
            count ++;
            ptime = A[i]->end;
        }
    }
    return count;
}

// 13.10 Rendering a calendar

class Time {
public:
    int type;
    int time;
    Time(int _t, int _time) { type = _t; time = _time;}
};

bool compareTime(Time*& t1, Time*& t2) {
    return t1->time < t2->time;
}

int getMaxConcurrentEvents(vector<Time*>& S, vector<Time*>& E) {
    S.insert(S.end(), E.begin(), E.end());
    sort(S.begin(), S.end(), compareTime);
    int count = 0;
    int maxp = 1;
    FF(i, 0, S.size()) {
        if (S[i]->type > 0) count++;
        else count--;
        if (count > maxp) maxp = count;
    }
    return maxp;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> A = {1,2,4,5,5,5,5,6,9,10};
    vector<int> B = {-1,2,5,5,5,9,11,23,31,99};
    vector<int> I = getInter(A,B);
    printL<int>(I);
    return 0;
}
