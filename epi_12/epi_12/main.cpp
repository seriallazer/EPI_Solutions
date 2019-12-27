//
//  main.cpp
//  epi_12
//
//  Created by Mayank Gupta on 03/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

#define FF(i, a, b) for(int i = a; i < b; i++)

using namespace std;

//12.9
bool checkLetter(const string& L, const string& M) {
    unordered_map<char, int> cmap;
    FF(i, 0, L.length()) {
        if (cmap.find(L[i]) == cmap.end()) cmap[L[i]] = 0;
        cmap[L[i]]++;
    }
    FF(i, 0, M.length()) {
        if (cmap.find(M[i]) == cmap.end()) continue;
        cmap[M[i]]--;
    }
    
    for(auto it = cmap.begin(); it != cmap.end(); it++) {
        if (it->second > 0) return false;
    }
    return true;
}

//12.2 Chess-board hash function
int64_t getHash(int64_t oldhash, string move) {
    int M[4];
    M[0] = move[0]-'a'; M[2] = move[2]-'a';
    M[1] = move[1]-'1'; M[3] = move[3]-'1';
    
    int oldpos = 4*(8*M[0] + M[1]);
    int newpos = 4*(8*M[2] + M[3]);
    
    int64_t temp = oldhash;
    int suffix = temp & ((1<<(oldpos+1)) - 1);
    temp >>= oldpos;
    int moveval = temp & 15;
    temp >>= 4; temp <<= 4 + oldpos;
    temp |= suffix;
    
    // add moveval to new pos
    suffix = temp & ((1<<(newpos+1))-1);
    temp >>= newpos+4;
    temp <<= 4;
    temp |= moveval;
    temp <<= newpos;
    temp |= suffix;
    return temp;
}

// 12.7 - Anagrams subsets
string getWordHash(const string& A) {
    unordered_map<char, int> cmap;
    FF(i, 0, A.length()) {
        if (cmap.find(A[i]) == cmap.end()) cmap[A[i]] = 0;
        cmap[A[i]]++;
    }
    
    string hash;
    stringstream ss;
    FF(i, 0, 26) {
        char c = 'a' + i;
        if (cmap.find(c) == cmap.end()) continue;
        ss << c << cmap[c];
    }
    hash = ss.str();
    return hash;
}

void printL(vector<vector<string>>& A) {
    FF(i, 0, A.size()) {
        FF(j, 0, A[i].size()) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<string>> getAnagramList(vector<string>& A) {
    unordered_map<string,int> cmap;
    vector<vector<string>> res;
    FF(i, 0, A.size()) {
        string hash = getWordHash(A[i]);
        if (cmap.find(hash) == cmap.end()) {
            res.push_back({A[i]});
            cmap[hash] = res.size()-1;
        } else {
            int id = cmap[hash];
            res[id].push_back(A[i]);
        }
    }
    return res;
}

// 12.8
bool permutePalindrome(string A) {
    unordered_map<char,int> cmap;
    FF(i, 0, A.length()) {
        if (cmap.find(A[i]) == cmap.end()) cmap[A[i]] == 0;
        cmap[A[i]]++;
    }
    int ocount = 0;
    for(auto it = cmap.begin(); it != cmap.end(); ++it) {
        if (it->second % 2 == 1) ocount++;
        if (ocount > 1) return false;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string A = "aabbccddz";
    string B = "sdfjhkaasdsdfwcahee";
    //bool c = checkLetter(A,B);
    //cout << c << endl;
    
    vector<string> D = { "motherinlaw", "womanhitler",
        "theearthquakes",    "thatqueershake",
        "debitcard",    "badcredit",
        "slotmachines",    "cashlostinem",
        "schoolmaster",    "theclassroom",
        "elevenplustwo",    "twelveplusone",
        "dormitory",   "dirtyroom",
        "punishment",    "ninethumps",
        "desperation",    "aropeendsit",
        "themorsecode",   "herecomedots"};
    //vector<vector<string>> S = getAnagramList(D);
    //printL(S);
    cout << permutePalindrome("edifdied") << endl;
    return 0;
}
