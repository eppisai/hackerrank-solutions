//
//  Manasa loves Math.cpp
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
#include <string>
using namespace std;


int main() {
    int t;
    cin >> t;
    while (t-->0) {
        vector <int> bucket(10, 0);
        string s;
        cin >> s;
        for (int i = 0; i < s.size(); ++i) {
            ++bucket[s[i] - '0'];
        }
        bool ok = false;
        if (s.size() == 1) {
            ok = (s[0] - '0') % 8 == 0;
        }
        else if (s.size() == 2) {
            ok = ((s[1] - '0') + (s[0] - '0') * 10) % 8 == 0;
            ok = ok || (((s[0] - '0') + (s[1] - '0') * 10) % 8 == 0);
        }
        else {
            for (int i = 0; i < 1000 && !ok; i += 8) {
                //if (i % 8 != 0) continue;
                // if (i == 16) cout << i << endl;
                vector <int> curr_bucket(10, 0);
                int a = i % 10,
                b = (i / 10) % 10,
                c = (i / 100) % 10;
                ++curr_bucket[a]; ++curr_bucket[b]; ++curr_bucket[c];
                ok = true;
                for (int j = 0; j < 10; ++j) {
                    if (bucket[j] < curr_bucket[j]) {
                        ok = false;
                        break;
                    }
                }
            }
        }
        if (ok) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}


