//
//  Maximum Subarray.cpp
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


int main() {
    int t;
    cin >> t;
    while (t--> 0) {
        int n;
        cin >> n;
        vector <int> v(n);
        int max_sum_non_cont = 0;
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
            max_sum_non_cont += max(0, v[i]);
        }
        int curr_sum = 0;
        int max_sum_cont = 0;
        for (int i = 0; i < n; ++i) {
            curr_sum += v[i];
            curr_sum = max(curr_sum, 0);
            max_sum_cont = max(max_sum_cont, curr_sum);
        }
        if (max_sum_cont > 0 || max_sum_non_cont > 0) {
            cout << max_sum_cont << ' ' << max_sum_non_cont << endl;
        }
        else {
            cout << v[0] << ' ' << v[0] << endl;
        }
    }
    return 0;
}

