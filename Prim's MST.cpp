//
//  Prim's MST.cpp
//  Hackerrank
//
//  Created by Mikael Arakelian on 6/11/17.
//  Copyright © 2017 Mikael Arakelian. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 3005;

int dsu[maxn];
int ranks[maxn];

void init() {
    for (int i = 0; i < maxn; ++i) {
        dsu[i] = i;
        ranks[i] = 1;
    }
}

int find (int node) {
    if (dsu[node] == node)
        return node;
    return dsu[node] = find(dsu[node]);
}

bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v)
        return false;
    if (ranks[u] > ranks[v]) {
        dsu[v] = u;
    }
    else if (ranks[v] > ranks[u]) {
        dsu[u] = v;
    }
    else {
        dsu[v] = u;
        ++ranks[u];
    }
    return true;
}

int main() {
    init();
    int n, m;
    cin >> n >> m;
    vector < pair <int, pair <int, int> > > edges(m);
    for (int i = 0; i < m; ++i)
        cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
    sort(edges.begin(), edges.end());
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int cost = edges[i].first;
        if (merge(u, v))
            ans += cost;
    }
    cout << ans << endl;
    return 0;
}


