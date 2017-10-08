//
//  String Similarity.cpp
//  Hackerrank
//
//  Created by Mikael Arakelian on 6/11/17.
//  Copyright © 2017 Mikael Arakelian. All rights reserved.
//

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
/* Head ends here */


int n;
vector <int> z_function(char a[]) {
    vector <int> z(n, 0);
    z[0] = n;
    int r = 0, l = 0;
    for (int i = 1; i < n; ++i) {
        z[i] = min(max(0, r - i + 1), z[i - l]);
        while (i + z[i] < n && a[z[i]] == a[i + z[i]])
            ++z[i];
        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

long long int stringSimilarity(char a[]) {
    vector <int> z = z_function(a);
    long long ans = 0;
    for (int i = 0; i < z.size(); ++i)
        ans += z[i];
    return ans;
}
int main() {
    int t, i;
    scanf("%d",&t);
    char a[100001];
    for (i=0;i<t;i++) {
        scanf("%s",a);
        n = strlen(a);
        long long int res=stringSimilarity(a);
        printf("%lld\n",res);
    }
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}


