//
//  main.cpp
//  epi_16_5
//
//  Created by Mayank Gupta on 01/06/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

class GV {
public:
    vector<pair<GV*,int>> edges;
};

void swapNodes(pair<int,int>& p1, pair<int,int>& p2,
               unordered_map<GV*,int>& cmap,  vector<GV*>& G) {
    pair<int,int> t = p1;
    p1.first = p2.first; p1.second = p2.second;
    p2.first = t.first; p2.second = t.second;
    cmap[G[p1.first]] = p1.first;
    cmap[G[p2.first]] = p2.first;
}

pair<int,int> extractMin(vector<pair<int,int>>& h, unordered_map<GV*,int>& cmap,
                         vector<GV*>& G) {
    pair<int,int> val = h[0];
    swapNodes(h[0], h[h.size()-1], cmap, G);
    h.pop_back();
    int p = 0;
    int sm = 0;
    while (p < h.size()) {
        int l = (p<<1)+1; int r = (p<<1)+2;
        if (l < h.size() && h[l].second >= 0 && (h[l].second < h[sm].second || h[sm].second < 0)) sm = l;
        if (r < h.size() && h[r].second >= 0 && (h[r].second < h[sm].second || h[sm].second < 0)) sm = r;
        if (sm == p) break;
        swapNodes(h[sm], h[p], cmap, G);
        p = sm;
    }
    return val;
}

void editHeap(vector<pair<int,int>>& h, unordered_map<GV*,int>& cmap,
              vector<GV*>& G, int id, int new_wt) {
    int oldwt = h[id].second;
    if (new_wt < 0 || (oldwt >= 0 && oldwt <= new_wt)) return;
    h[id].second = new_wt;
    int c = id;
    while(c > 0) {
        int p = (c-1)>>1;
        if (h[p].second < 0 || h[p].second > h[c].second) {
            swapNodes(h[p], h[c], cmap, G);
            c = p;
        } else {
            break;
        }
    }
}

vector<int> getSourceDist(vector<GV*>& G, int id) {
    vector<pair<int,int>> h;
    unordered_map<GV*, int> cmap;
    vector<int> dmap;
    h.push_back(make_pair(id, 0));
    cmap[G[id]] = 0;
    while(h.size() > 0) {
        pair<int,int> info = extractMin(h, cmap, G);
        dmap[info.first] = info.second;
        FF(i, 0, G[info.first]->edges.size()) {
            GV* v = G[info.first]->edges[i].first;
            int weight = dmap[info.first] + G[info.first]->edges[i].second;
            if (cmap.find(v) == cmap.end()) continue;
            editHeap(h, cmap, G, cmap[v], weight);
        }
    }
    return dmap;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
