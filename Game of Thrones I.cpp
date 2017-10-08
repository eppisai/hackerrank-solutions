//
//  Game of Thrones I.cpp
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
    
    string s;
    cin >> s;
    int flag = 0;
    
    vector <int> bucket(26);
    for (int i = 0; i < s.size(); ++i)
        ++bucket[s[i] - 'a'];
    
    for (int i = 0; i < 26; ++i)
        flag += bucket[i] & 1;
    
    // Assign Flag a value of 0 or 1 depending on whether or not you find what you are looking for, in the given string
    if(flag <= 1)
        cout<<"YES";
    else
        cout<<"NO";
    return 0;
}


