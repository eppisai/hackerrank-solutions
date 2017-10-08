//
//  Fibonacci Modified.cpp
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

typedef vector <int> bigint;

const int base = 1000 * 1000 * 1000;

bigint mul(const bigint& a, const bigint& b)
{
    bigint c(a.size() + b.size());
    
    for (int i = 0; i < a.size(); ++i)
    {
        int carry = 0;
        for (int j = 0; j < b.size() || carry; ++j)
        {
            long long curr = c[i + j] + carry;
            if (j < b.size())
                curr += a[i] * 1ll * b[j];
            c[i + j] = curr % base;
            carry = curr / base;
        }
    }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

bigint sum(const bigint& c, const bigint& b){
    bigint a(c);
    int carry = 0;
    for (int i = 0; i < max(a.size(), b.size()) || carry; ++i){
        if (i == a.size())
            a.push_back(0);
        a[i] += carry;
        if (i < b.size())
            a[i] += b[i];
        carry = a[i] >= base;
        if (carry)
            a[i] -= base;
    }
    return a;
}

void print(bigint& a){
    cout << a.back();
    for (int i = (int) a.size() - 2; i >= 0; --i)
        printf("%09d", a[i]);
    cout << endl;
}

int main() {
    int n, a, b;
    cin >> a >> b >> n;
    vector <bigint> v(n);
    v[0] = vector <int>(1, a);
    v[1] = vector <int>(1, b);
    for (int i = 2; i < n; ++i){
        v[i] = sum(mul(v[i - 1], v[i - 1]), v[i - 2]);
    }
    print(v[n - 1]);
    return 0;
}


