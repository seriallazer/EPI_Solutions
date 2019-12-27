//
//  main.cpp
//  EPI_16
//
//  Created by Mayank Gupta on 31/05/18.
//  Copyright © 2018 Mayank Gupta. All rights reserved.
//

#include <tuple>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

#define FF(i,a,b) for(int i = a; i < b; i++)

using namespace std;

bool isEq(const int& Sx, const int& Sy, const pair<int,int>& E) {
    return (Sx == E.first)&&(Sy == E.second);
}

//16.1
bool getMazePath(vector<string>& A, pair<int,int>& S, pair<int,int>& E) {
    if (A[S.first][S.second] == '0' || A[E.first][E.second] == '0') return false;
    queue<int> qx;
    queue<int> qy;
    vector<vector<int>> V;
    V.resize(A.size());
    FF(i,0,V.size()) {
        V[i].resize(A[i].length(), 0);
    }
    
    qx.push(S.first);
    qy.push(S.second);
    V[S.first][S.second] = 1;
    while (!qx.empty()) {
        //int id = qx.size()-1;
        int x = qx.front(); int y = qy.front();
        if (isEq(x,y,E)) return true;
        qx.pop(); qy.pop();
        if (x>0 && V[x-1][y] == 0 && A[x-1][y] == '1') {
            V[x-1][y] = 1;
            qx.push(x-1); qy.push(y);
        }
        if (x<A.size()-1 && V[x+1][y] == 0 && A[x+1][y] == '1') {
            V[x+1][y] = 1;
            qx.push(x+1); qy.push(y);
        }
        if (y>0 && V[x][y-1] == 0 && A[x][y-1] == '1') {
            V[x][y-1] = 1;
            qx.push(x); qy.push(y-1);
        }
        if (y<A[x].size()-1 && V[x][y+1] == 0 && A[x][y+1] == '1') {
            V[x][y+1] = 1;
            qx.push(x); qy.push(y+1);
        }
    }
    return false;
}

//16.2 7:24-7:42
bool tdiff1(const string& A, const string& B) {
    int c = 0;
    if (A.length() != B.length()) return false;
    FF(i, 0, A.length()) {
        if (A[i] != B[i]) c++;
        if (c>1) return false;
    }
    if (c != 1) return false;
    return true;
}

template <typename T>
void printL(vector<T>& A) {
    FF(i, 0, A.size()) {
        cout << A[i] << " ";
    }
    cout << endl;
}

bool checkWord(const string& A, const string& B, const vector<string>& dict) {
    unordered_map<string, int> cmap;
    vector<string> s;
    s.push_back(A);
    cmap[A] = 1;
    while(s.size() > 0) {
        string str = s[s.size()-1];
        s.pop_back();
        if (str == B) return true;
        if (tdiff1(str, B)) return true;
        FF(i, 0, dict.size()) {
            if (tdiff1(str, dict[i])) {
                if (cmap.find(dict[i]) == cmap.end()) cmap[dict[i]] = 1;
                else continue;
                s.push_back(dict[i]);
            }
        }
        //printL<string>(s);
    }
    return false;
}

//16.3 7:46-7:56
vector<vector<int>> circuitDivision(const vector<vector<int>>& A) {
    vector<vector<int>> res;
    unordered_map<int, int> cmap;
    FF(i, 0, A.size()) {
        if (cmap.find(i) != cmap.end()) continue;
        vector<int> s;
        s.push_back(i);
        cmap[i] = 0;
        while(s.size() > 0) {
            int pin = s[s.size()-1]; s.pop_back();
            int gnum = cmap[pin];
            FF(j, 0, A[pin].size()) {
                if (A[pin][j] == 0) continue;
                if (cmap.find(j) == cmap.end()) {
                    cmap[j] = 1 - gnum;
                    s.push_back(j);
                } else {
                    if (cmap[j] == gnum) return res;
                }
            }
        }
    }
    
    res.resize(2);
    FF(i, 0, A.size()) {
        res[cmap[i]].push_back(i);
    }
    return res;
}

//16.4 - 11:32
class GV {
public:
    int d, l;
    int state;
    vector<GV*> edges;
    
    GV(int _i) {d = l = -1; state = 0;}
};

bool check_2_for_every(vector<GV*>& G) {
    if (G.size() == 0) return true;
    int c = 0;
    vector<GV*> s;
    s.push_back(G[0]);
    G[0]->d = 0;
    c++;
    while (s.size() > 0) {
        GV* v = s[s.size()-1];
        if (v->state == 0) {
            v->state++;
            FF(i, 0, v->edges.size()) {
                if (v->edges[i]->d >= 0) continue;
                v->edges[i]->d = c;
                c++;
                s.push_back(v->edges[i]);
            }
        } else {
            v->l = v->d;
            FF(i, 0, v->edges.size()) {
                if (v->edges[i]->l < 0) continue;
                if (v->edges[i]->l < v->l) v->l = v->edges[i]->l;
            }
            
            if (v->l == v->d) return false;
        }
    }
    return true;
}

// 16.4(2)
// 16.4
//#include <iostream>
//#include <vector>
//#define FF(i,a,b) for(int i = a; i < b; i++)

//using namepace std;

class GraphVertex {
public:
    int d, l;
    vector<GraphVertex> edges;
    GraphVertex() {
        d = -1; l = INT_MAX;
    }
};

bool dfs_helper(GraphVertex* curr, GraphVertex* prev, int time) {
    curr->d = ++time;
    curr->l = INT_MAX;
    FF(i, 0, curr->edges.size()) {
        GraphVertex* next = &(curr->edges[i]);
        if (next == prev) continue;
        if (next->d >= 0) {
            //curr->d = next->l;
            curr->l = min(curr->l, next->d);
        } else {
            if (!dfs_helper(next, curr, time)) {
                return false;
            }
            curr->l = min(curr->l, next->l);
        }
    }
    return (prev == nullptr || curr->l < curr->d);
}
                
bool is_2_for_every_graph(vector<GraphVertex>& G) {
    if (G.size() == 0) return true;
    return dfs_helper(&G[0], nullptr, 0);
}

//16.8
bool isEmpty(vector<vector<bool>>& M) {
    FF(i, 0, M.size()) {
        FF(j, 0, M.size()) {
            if (M[i][j]) return false;
        }
    }
    return true;
}

vector<int> topologicalSort(vector<vector<bool>> M) {
    cout << "doing tsort" << endl;
    vector<int> res;
    queue<int> S;
    vector<int> inedges;
    inedges.resize(M.size(), 0);
    FF(j, 0, M.size()) {
        bool f = false;
        FF(i, 0, M.size()) {
            if (M[i][j]) {
                f = true;
                inedges[j]++;
            }
        }
        if (!f) {
            //cout << "queuepush: " << j << endl;
            S.push(j);
        }
    }
    //printL<int>(inedges);
    while (!S.empty() > 0) {
        int id = S.front(); S.pop();
        res.push_back(id);
        FF(i, 0, M[id].size()) {
            if (M[id][i]) {
                inedges[i]--;
                M[id][i] = 0;
                if (inedges[i] == 0) {
                    //cout << "dfspush: " << i << endl;
                    S.push(i);
                }
            }
        }
    }
    
    if (!isEmpty(M)) {
        cout << "Cycle exists in the Graph!" << endl;
    }
    return res;
}

int minTaskTime(vector<vector<bool>>& M, vector<int>& T) {
    vector<int> tsort = topologicalSort(M);
    printL<int>(tsort);
    vector<int> dtime;
    dtime.resize(M.size());
    int tasktime = 0;
    FF(i, 0, tsort.size()) {
        int id = tsort[i];
        int ttime = T[id];
        int maxtime = 0;
        FF(j, 0, M.size()) {
            if (M[j][id] && dtime[j] > maxtime) maxtime = dtime[j];
        }
        dtime[id] = ttime + maxtime;
        if (dtime[id] > tasktime) tasktime = dtime[id];
    }
    printL<int>(dtime);
    return tasktime;
}

// 16.9 - Shortest path with fewest edges
class gv {
public:
    vector<pair<gv*,int>> edges;
};

void swapNodes(tuple<int,int,int>& t1, tuple<int,int,int>& t2, unordered_map<gv*, int>& cmap,
               vector<gv*>& G) {
    int hid1 = cmap[G[get<0>(t1)]]; int hid2 = cmap[G[get<0>(t2)]];
    cmap[G[get<0>(t1)]] = hid2; cmap[G[get<0>(t2)]] = hid1;
    tuple<int,int,int> t = t1;
    t1 = t2; t2 = t;
}

tuple<int,int,int> extractMinSPLE(vector<tuple<int,int,int>>& h, unordered_map<gv*, int>& cmap,
                                  vector<gv*>& G) {
    tuple<int,int,int> val = h[0];
    swapNodes(h[0], h[h.size()-1], cmap, G);
    h.pop_back();
    int p = 0;
    int sm = p;
    while (p < h.size()) {
        int l = (p<<1)+1; int r = l+1;
        if (l < h.size() && get<1>(h[l]) >= 0) {
            if (get<1>(h[sm]) < 0 || (get<1>(h[l]) < get<1>(h[sm])
                                      || (get<1>(h[l]) == get<1>(h[sm]) && get<2>(h[l]) < get<2>(h[sm])))) {
                sm = l;
            }
        }
        if (r < h.size() && get<1>(h[r]) >= 0) {
            if (get<1>(h[sm]) < 0 || (get<1>(h[r]) < get<1>(h[sm])
                                      || (get<1>(h[r]) == get<1>(h[sm]) && get<2>(h[r]) < get<2>(h[sm])))) {
                sm = r;
            }
        }
        if (sm == p) break;
        swapNodes(h[sm], h[p], cmap, G);
        p = sm;
    }
    return val;
}

void editValSPLE(vector<tuple<int,int,int>>& h, unordered_map<gv*, int>& cmap,
                 vector<gv*>& G, int id, int wt, int ec) {
    get<1>(h[id]) = wt; get<2>(h[id]) = ec;
    int c = id;
    while (c > 0) {
        int p = (c-1)>>1;
        if (get<1>(h[p]) < 0
            || (get<1>(h[p]) > get<1>(h[c])
                || (get<1>(h[p]) == get<1>(h[c]) && get<2>(h[p]) > get<2>(h[c])) ) ) {
            swapNodes(h[c], h[p], cmap, G);
            c = p;
        } else {
            break;
        }
    }
}

vector<int> shortestPathLessEdges(vector<gv*>& G, int id, int eid) {
    vector<tuple<int,int,int>> h;
    unordered_map<gv*, int> cmap;
    vector<int> emap;
    vector<int> dmap;
    h.push_back(make_tuple(id, 0, 0));
    cmap[G[id]] = 0;
    emap[id] = -1;
    FF(i, 0, G.size()) {
        if (i == id) continue;
        h.push_back(make_tuple(i, -1, -1));
        cmap[G[i]] = h.size()-1;
    }
    while (h.size() > 0) {
        tuple<int,int,int> t = extractMinSPLE(h, cmap, G);
        int id = get<0>(t); int dist = get<1>(t); int ecount = get<2>(t);
        dmap[id] = dist;
        FF(i, 0, G[id]->edges.size()) {
            gv* v = G[id]->edges[i].first;
            int wt = dist + G[id]->edges[i].second;
            int ec = ecount+1;
            if (cmap.find(v) == cmap.end()) continue;
            tuple<int,int,int> it = h[cmap[v]];
            int oldwt = get<1>(it); int oldec = get<2>(t);
            if (oldwt < wt || (oldwt == wt && oldec <= ec)) continue;
            editValSPLE(h, cmap, G, cmap[v], wt, ec);
            emap[get<0>(it)] = id;
        }
    }
    
    vector<int> res;
    int k = eid;
    while (k >= 0) {
        res.insert(res.begin(), k);
        k = emap[k];
    }
    return res;
}

// 16.10 - Quickest Route with 60 min stopover
class Flight;
class City {
public:
    vector<Flight*> edges;
};

class Flight {
public:
    int stime; int etime;
    int dur;
    City* dest;
    City* source;
};

class Path {
public:
    vector<Flight*> path;
    int etime;
    int ttime;
    
    Path() {}
    Path(int _stime) {etime = _stime; ttime = 0;}
};

class cinfo {
public:
    int cid; int ttime; int rtime;
    cinfo(int _c, int _t, int _r) {cid = _c; ttime = _t; rtime = _r;}
};

cinfo* getCI(int c, int t, int r) {
    cinfo* ci = new cinfo(c,t,r);
    return ci;
}

void swapNodes(cinfo*& c1, cinfo*& c2, unordered_map<City*, int>& cmap, vector<City*>& G) {
    int hid1 = cmap[G[c1->cid]]; int hid2 = cmap[G[c2->cid]];
    cmap[G[c1->cid]] = hid2; cmap[G[c2->cid]] = hid1;
    cinfo* t = c1;
    c1 = c2; c2 = t;
}

cinfo* extractMinCity(vector<cinfo*>& h, unordered_map<City*, int>& cmap, vector<City*>& G) {
    cinfo* val = h[0];
    if (h.size() > 1) swapNodes(h[0], h[h.size()-1], cmap, G);
    h.pop_back();
    int p = 0;
    int sm = p;
    while (p < h.size()) {
        int l = (p<<1)+1; int r = l+1;
        if (l < h.size() && h[l]->ttime >=0 && h[l]->ttime < h[sm]->ttime) sm = l;
        if (r < h.size() && h[r]->ttime >=0 && h[r]->ttime < h[sm]->ttime) sm = r;
        if (sm == p) break;
        swapNodes(h[p], h[sm], cmap, G);
        p = sm;
    }
    return val;
}

void editHeapCity(vector<cinfo*>& h, unordered_map<City*, int>& cmap, vector<City*>& G,
                  int id, int ttime, int rtime) {
    h[id]->ttime = ttime; h[id]->rtime = rtime;
    int c = id;
    while (c > 0) {
        int p = (c-1)>>1;
        if (h[c]->ttime >= 0 && h[p]->ttime > h[c]->ttime) {
            swapNodes(h[p], h[c], cmap, G);
            c = p;
        } else {
            break;
        }
    }
}

int getTimeDiffHHMM(int rtime, int stime) {
    if (stime < rtime) {
        return getTimeDiffHHMM(rtime, 2400) + stime;
    }
    int rmin = rtime%100; int smin = stime%100;
    int rh = rtime/100; int sh = stime/100;
    if (smin >= rmin) return 100*(sh-rh) + (smin-rmin);
    int it1 = rh*100 + 60; int it2 = 100*sh;
    return getTimeDiffHHMM(rh, it1) + getTimeDiffHHMM(it2, stime);
}

int getTimeDiff(int rtime, int stime) {
    int hhmm = getTimeDiffHHMM(rtime, stime);
    return (hhmm/100)*60 + (hhmm%100);
}

Path* getQuickestRoute(vector<City*>& G, City* start, City* end, int stime) {
    if (start == end) {
        Path* p = new Path(stime);
        return p;
    }
    vector<cinfo*> h; // heap stores <City-id, total-time, etime>
    unordered_map<City*, int> cmap; // map from city to heap-id;
    vector<pair<Flight*,int>> emap; // reverse edge mapping for flights
    vector<pair<int,int>> dmap; // <ttime, rtime> pairs for each city-id
    int sid = -1; int eid = -1;

    FF(i, 0, G.size()) {
        if (G[i] == start) {
            sid = i;
            h.push_back(getCI(i, 0, stime));
            emap[i] = make_pair(nullptr, -1);
        } else {
            h.push_back(getCI(i, -1, -1));
        }
        cmap[G[i]] = h.size()-1;
    }
    
    while (h.size() > 0) {
        cinfo* ci = extractMinCity(h, cmap, G);
        dmap[ci->cid] = make_pair(ci->ttime, ci->rtime);
        int rtime = ci->rtime;
        int ttime = ci->ttime;
        FF(i, 0, G[ci->cid]->edges.size()) {
            Flight* f = G[ci->cid]->edges[i];
            if (cmap.find(f->dest) == cmap.end()) continue;
            if (f->stime < rtime) continue;
            int dtime = ttime + f->dur;
            dtime += getTimeDiff(rtime, f->stime);
            if (dtime >= h[cmap[f->dest]]->ttime) continue;
            editHeapCity(h, cmap, G, cmap[f->dest], dtime, f->etime);
            int fgid = h[cmap[f->dest]]->cid;
            emap[fgid] = make_pair(f, ci->cid);
        }
    }
    
    Path* pp = new Path();
    pp->etime = dmap[eid].second;
    pp->ttime = dmap[eid].first;
    
    int k = eid;
    while (k >= 0) {
        pp->path.insert(pp->path.begin(), emap[k].first);
        k = emap[k].second;
    }
    return pp;
}

// 16.11 - choose best proposal for the new road network that minimises a particular route
class Proposal {
public:
    gv* start;
    gv* end;
    int weight;
};

Proposal* getBestProposal(vector<gv*>& G, vector<Proposal*>& PP, gv* start, gv* end) {
    vector<vector<int>> D;
    vector<vector<int>> P;
    D.resize(G.size()); P.resize(D.size());
    unordered_map<gv*,int> cmap;
    FF(i, 0, D.size()) {
        D[i].resize(G.size(), -1);
        P[i].resize(G.size(), -1);
        cmap[G[i]] = i;
    }
    
    FF(i, 0, G.size()) {
        FF(j, 0, G[i]->edges.size()) {
            int jid = cmap[G[i]->edges[j].first];
            int wt = G[i]->edges[j].second;
            D[i][j] = wt;
            P[i][j] = i;
        }
    }
    
    FF(k, 0, G.size()) {
        FF(i, 0, G.size()) {
            FF(j, 0, G.size()) {
                if (k == i || k == j) continue;
                int v1 = D[i][k]; int v2 = D[k][j];
                if (v1 < 0 || v2 < 0) continue;
                if (D[i][j] < 0 || D[i][j] > v1+v2) {
                    D[i][j] = v1+v2;
                    P[i][j] = P[k][j];
                }
            }
        }
    }
    
    int minval = D[cmap[start]][cmap[end]];
    int pid = -1;
    FF(i, 0, PP.size()) {
        int sid = cmap[PP[i]->start];
        int eid = cmap[PP[i]->end];
        int wt = PP[i]->weight;
        int pcost = D[cmap[start]][sid] + wt + D[eid][cmap[end]];
        if (pcost < minval) {
            minval  = pcost;
            pid = i;
        }
    }
    if (pid < 0) return nullptr;
    return PP[pid];
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    //16.1
    /*vector<string> A = {"111111", "011110", "100000", "111111"};
    pair<int,int> s = make_pair(0,0);
    pair<int,int> e = make_pair(3,5);
    bool maze = getMazePath(A, s, e);
    cout << "maze: " << maze << endl;
     */
    
    // 16.2
    /*vector<string> D = {"log", "lig", "tog", "tig", "koi", "sdf"};
    bool cword = checkWord("kei", "tie", D);
    cout << "checkWord: " << cword << endl;
     */
    
    // 16.8
    vector<vector<bool>> M = {{0,1,1,0},{0,0,1,1},{0,0,0,0},{0,0,0,0}};
    vector<int> T = {10,20,5,25};
    int tasktime = minTaskTime(M, T);
    cout << "tasktime: " << tasktime << endl;
    return 0;
}
