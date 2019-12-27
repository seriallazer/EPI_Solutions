//
//  main.cpp
//  epi_primAlgo
//
//  Created by Mayank Gupta on 01/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

// Prim’s Algo - Undirected weighted-graphs - Minimum Spanning Tree

#include <iostream>
#include <vector>
#include <unordered_map>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

class GV {
public:
    vector<pair<GV*, int>> edges;
};

class Edge {
public:
    GV* a;
    GV* b;
    int weight;
    Edge(GV* _a, GV* _b, int wt) { a = _a; b = _b; weight = wt; }
};

void swapNodes(pair<int,int>& p1, pair<int,int>& p2, unordered_map<GV*, int>& cmap,
               vector<GV*>& G) {
    pair<int,int> t = p1;
    p1 = p2; p2 = t;
    int temp = cmap[G[p1.first]];
    cmap[G[p1.first]] = cmap[G[p2.first]];
    cmap[G[p2.first]] = temp;
}

pair<int,int> extractMin(vector<pair<int,int>>& h, unordered_map<GV*, int>& cmap,
                         vector<GV*>& G) {
    pair<int,int> val = h[0];
    swapNodes(h[0], h[h.size()-1], cmap, G);
    int p = 0;
    int sm = p;
    while (p < h.size()) {
        int l = (p<<1)+1; int r = l+1;
        if (l < h.size() && h[l].second >= 0 && (h[l].second < h[sm].second || h[sm].second < 0)) sm = l;
        if (r < h.size() && h[r].second >= 0 && (h[r].second < h[sm].second || h[sm].second < 0)) sm = r;
        if (sm == p) break;
        swapNodes(h[p], h[sm], cmap, G);
        p = sm;
    }
    return val;
}

void editHeap(vector<pair<int,int>>& h, unordered_map<GV*, int>& cmap,
              vector<GV*>& G, int id, int wt) {
    h[id].second = wt;
    int c = id;
    while (c > 0) {
        int p = (c-1)>>1;
        if (h[p].second < 0 || h[p].second > h[c].second) {
            swapNodes(h[p], h[c], cmap, G);
            c = p;
        } else {
            break;
        }
    }
}

vector<Edge*> MST(vector<GV*>& G) {
    vector<pair<int,int>> h;
    unordered_map<GV*, int> cmap;
    vector<int> emap;
    emap.resize(G.size());
    h.push_back(make_pair(0,0));
    cmap[G[0]] = 0;
    emap[0] = -1;
    
    vector<Edge*> res;
    while (h.size() > 0) {
        pair<int,int> pp = extractMin(h, cmap, G);
        if (emap[pp.first] >= 0) {
            Edge* e = new Edge(G[pp.first], G[emap[pp.first]], pp.second);
            res.push_back(e);
        }
        FF(i, 0, G[pp.first]->edges.size()) {
            GV* v = G[pp.first]->edges[i].first;
            int weight = G[pp.first]->edges[i].second;
            if (cmap.find(v) == cmap.end()) continue;
            if (h[cmap[v]].second <= weight) continue;
            editHeap(h, cmap, G, cmap[v], weight);
            int gid = h[cmap[v]].first;
            emap[gid] = pp.first;
        }
    }
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
