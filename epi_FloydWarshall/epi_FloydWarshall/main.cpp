//
//  main.cpp
//  epi_FloydWarshall
//
//  Created by Mayank Gupta on 01/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//
// All pair shortest-path == Floyd- Warshall Algo (Directed or Undirected Graph)

#include <iostream>
#include <vector>
#include <unordered_map>
#define FF(i,a,b) for(int i =a; i < b; i++)

using namespace std;

class GV {
public:
    vector<pair<GV*,int>> edges;
};

void initPathAndDist(vector<GV*>& G, vector<vector<int>>& D, vector<vector<int>>& P) {
    unordered_map<GV*, int> cmap;
    FF(i, 0, G.size()) {
        cmap[G[i]] = i;
    }
    
    FF(i, 0, G.size()) {
        FF(j, 0, G[i]->edges.size()) {
            //GV* v = G[i]->edges[j].first;
            int weight = G[i]->edges[j].second;
            D[i][j] = weight;
            P[i][j] = i;
        }
    }
}

vector<vector<int>> getAllPairPaths(vector<GV*>& G) {
    vector<vector<int>> D;
    vector<vector<int>> P;
    int N = G.size();
    D.resize(N);
    P.resize(N);
    FF(i,0,N) {
        D[i].resize(N, -1);
        P[i].resize(N, N);
    }
    
    initPathAndDist(G, D, P);
    
    FF(k, 0, N) {
        FF(i, 0, N) {
            FF(j, 0, N) {
                int v1 = D[i][k]; int v2 = D[k][j];
                if (v1 < 0 || v2 < 0) continue;
                if (D[i][j] < 0 || D[i][j] > v1+v2) {
                    D[i][j] = v1+v2;
                    P[i][j] = P[k][j];
                }
            }
        }
    }
    return D;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
