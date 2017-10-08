//
//  Little Panda Power.cpp
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

int bin_pow(int a, int n, int mod) {
    if (n == 0)
        return 1;
    if (n == 1)
        return a % mod;
    if (n & 1)
        return ((a % mod) * 1ll * (bin_pow(a, n - 1, mod))) % mod;
    int temp = bin_pow(a, n / 2, mod);
    return (temp * 1ll * temp) % mod;
}

int phi(int n) {
    long long ans = 1;
    for (int i = 2; i * 1ll * i <= n; ++i) {
        bool flag = false;
        while (n % i == 0) {
            flag = true;
            n /= i;
            ans *= i;
        }
        if (flag) {
            ans /= i;
            ans *= (i - 1);
        }
    }
    if (n > 1)
        ans *= (n - 1);
    return ans;
}

inline int solve() {
    int a, n, mod;
    cin >> a >> n >> mod;
    int a_inverse = bin_pow(a, phi(mod) - 1, mod);
    //cout << a_inverse << ' ';
    if (n < 0)
        return bin_pow(a_inverse, -n, mod);
    return bin_pow(a, n, mod);
}

int main() {
    int t;
    cin >> t;
    for (int i= 0; i < t; ++i)
        cout << solve() << endl;;
    return 0;
}


