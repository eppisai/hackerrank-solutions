//
//  Insertion Sort Advanced Analysis.cpp
//  Hackerrank
//
//  Created by Mikael Arakelian on 6/11/17.
//  Copyright © 2017 Mikael Arakelian. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 10000000;
int tree[4 * maxn];

void update(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        ++tree[v];
        return;
    }
    
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        update(v * 2, tl, tm, pos);
    else update(v * 2 + 1, tm + 1, tr, pos);
    
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

int get(int v, int l, int r, int tl, int tr) {
    if (l == tl && r == tr) {
        return tree[v];
    }
    
    int tm = (tl + tr) / 2;
    
    if (r <= tm)
        return get(2 * v, l, r, tl, tm);
    else if (l > tm)
        return get(2 * v + 1, l, r, tm + 1, tr);
    else
        return get(2 * v, l, tm, tl, tm) + get(2 * v + 1, tm + 1, r, tm + 1, tr);
}

void solve() {
    memset(tree, 0, sizeof(tree));
    int n, num;
    cin >> n;
    long long counter = 0;
    for (int i = 0; i < n; ++i) {
        cin >> num;
        counter += get(1, num + 1, maxn - 1, 0, maxn - 1);
        update(1, 0, maxn - 1, num);
    }
    cout << counter << endl;
}

int main() {
    
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
        solve();
    
    return 0;
}


