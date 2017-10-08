//
//  Permuting Two Arrays.cpp
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


inline void solve()
{
    int n, k;
    cin >> n >> k;
    vector <int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());
    int ok = true;
    for (int i = 0; i < n ;++i)
        ok = ok && (a[i] + b[i] >= k);
    if (ok)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}


int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
        solve();
    return 0;
}


