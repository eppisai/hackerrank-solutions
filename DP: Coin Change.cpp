//
//  DP: Coin Change.cpp
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
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

long long make_change(const std::vector<int>& coins, int money) {
    const int n = (int)coins.size();
    std::vector < std::vector <long long> > dp(money + 1, std::vector<long long>(n + 1));
    
    for (int i = 0; i <= n; ++i)
        dp[0][i] = 1;
    
    for (int i = 1; i <= money; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int k = 0; k * coins[j - 1] <= i; ++k)
            {
                dp[i][j] += dp[i - k * coins[j - 1]][j - 1];
            }
        }
    }
    
    return dp[money][n];
}

int main(){
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<int> coins(m);
    for(int coins_i = 0;coins_i < m;coins_i++){
        std::cin >> coins[coins_i];
    }
    std::cout << make_change(coins, n) << std::endl;
    return 0;
}


