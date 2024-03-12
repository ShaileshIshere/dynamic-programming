#include<bits/stdc++.h>

using namespace std;

// burst balloons - LC(312)
// recursive solution
int recursion(vector<int> &nums, int start, int end) {
    // base case
    if(start > end)
        return 0;
    
    // recursion
    int coins = INT_MIN;
    for(int i=start; i<=end; ++i) {
        coins = max(coins, 
                    nums[start-1]*nums[i]*nums[end+1]
                    + recursion(nums, start, i-1)
                    + recursion(nums, i+1, end)
                );
    }
    return coins;
}

// memoization solution
int memoization(vector<int> &nums, int start, int end, vector<vector<int>> &dp) {
    // base case
    if(start > end)
        return 0;

    // meoization
    if(dp[start][end] != -1)
        return dp[start][end];
    
    // recursion
    int coins = INT_MIN;
    for(int i=start; i<=end; ++i) {
        coins = max(coins, 
                    nums[start-1]*nums[i]*nums[end+1]
                    + memoization(nums, start, i-1, dp)
                    + memoization(nums, i+1, end, dp)
                );
    }
    return dp[start][end] = coins;
}

// tabulation solution
int tabulation(vector<int> &nums) {
    vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), 0));

    // tabulation
    for(int start = nums.size()-1; start >= 1; --start) {
        for(int end = 1; end <= nums.size()-2; ++end) {
            if(start > end)
                continue;
            int coins = INT_MIN;
            for(int i=start; i<=end; ++i) {
                coins = max(coins, 
                            nums[start-1]*nums[i]*nums[end+1]
                            + dp[start][i-1]
                            + dp[i+1][end]
                        );
            }
            dp[start][end] = coins;
        }
    }
    return dp[1][nums.size()-2];
}
int maxCoins(vector<int>& nums) {
    nums.insert(nums.begin(), 1);
    nums.insert(nums.end(), 1);

    return recursion(nums, 1, nums.size()-2);

    vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), -1));
    return memoization(nums, 1, nums.size()-2, dp);

    return tabulation(nums);
}

// interleaving string - LC(97)
// recursive solution
bool recursion(string &s1, string &s2, string &s3, int i, int j, int k) {
    // base case
    if(i == s1.size() && j == s2.size() && k == s3.size())
        return true;

    // recursion
    bool flag = false;
    if(i < s1.size() && s1[i] == s3[k])
        flag = flag || recursion(s1, s2, s3, i+1, j, k+1);
    if(j < s2.size() && s2[j] == s3[k])
        flag = flag || recursion(s1, s2, s3, i, j+1, k+1);
    return flag;
}

// memoization solution
bool memoization(string &s1, string &s2, string &s3, int i, int j, int k, vector<vector<vector<int>>> &dp) {
    // base case
    if(i == s1.size() && j == s2.size() && k == s3.size())
        return true;

    // memoization
    if(dp[i][j][k] != -1)
        return dp[i][j][k];

    // recursion
    bool flag = false;
    if(i < s1.size() && s1[i] == s3[k])
        flag = flag || memoization(s1, s2, s3, i+1, j, k+1, dp);
    if(j < s2.size() && s2[j] == s3[k])
        flag = flag || memoization(s1, s2, s3, i, j+1, k+1, dp);
    return dp[i][j][k] = flag;
}

// tabulation solution
int tabulation(string &s1, string &s2, string &s3) {
    vector<vector<vector<int>>> dp(s1.size()+1, vector<vector<int>>(s2.size()+1, vector<int>(s3.size()+1, 0)));
    // base case or first case
    dp[s1.size()][s2.size()][s3.size()] = 1;

    // tabulation
    for(int i=s1.size(); i>=0; --i) {
        for(int j=s2.size(); j>=0; --j) {
            for(int k=s3.size(); k>=0; --k) {
                if(i == s1.size() && j == s2.size() && k == s3.size())
                    continue;
                bool flag = false;
                if(i < s1.size() && s1[i] == s3[k])
                    flag = flag || dp[i+1][j][k+1];
                if(j < s2.size() && s2[j] == s3[k])
                    flag = flag || dp[i][j+1][k+1];
                dp[i][j][k] = flag;
            }
        }
    }
    return dp[0][0][0]; 
}
bool isInterleave(string s1, string s2, string s3) {
    return recursion(s1, s2, s3, 0, 0, 0);

    vector<vector<vector<int>>> dp(s1.size()+1, vector<vector<int>>(s2.size()+1, vector<int>(s3.size()+1, -1)));
    return memoization(s1, s2, s3, 0, 0, 0, dp);

    return tabulation(s1, s2, s3);
}

// Minimum Number of Removals to Make Mountain Array - LC(1671)
int binarySearch(vector<int> &v, vector<int> &arr) {
    vector<int> ans;
    arr.push_back(1);
    ans.push_back(v[0]);
    for(int i=1; i<v.size(); ++i) {
        if(v[i] > ans.back()) {
            ans.push_back(v[i]);
            arr.push_back(ans.size());
        }
        else {
            int index = lower_bound(ans.begin(), ans.end(), v[i]) - ans.begin();
            ans[index] = v[i];
            arr.push_back(index + 1);
        }
    }
    return ans.size();
}
int minimumMountainRemovals(vector<int>& nums) {
    vector<int> lis, lds;
    binarySearch(nums, lis);
    reverse(nums.begin(), nums.end());
    binarySearch(nums, lds);
    int largestMountain = INT_MIN;
    for(int i=0; i<nums.size(); ++i) {
        if(lis[i] == 1 || lds[nums.size()-i-1] == 1)
            continue;
        largestMountain = max(largestMountain, lis[i] + lds[nums.size()-i-1] - 1);
    }
    return nums.size() - largestMountain;
}

// Make Array Strictly Increasing - LC(1187)
#define INF (1e9 + 1)
// recursive solution
int recursion(vector<int>& arr1, vector<int>& arr2, int prev, int i) {
    // base case
    if(i == arr1.size())
        return 0;

    // recursion
    int op1 = INF;
    if(prev < arr1[i])
        op1 = recursion(arr1, arr2, arr1[i], i+1);
    int op2 = INF;
    auto it = upper_bound(arr2.begin(), arr2.end(), prev);
    if(it != arr2.end()) {
        int index = it - arr2.begin();
        op2 = 1 + recursion(arr1, arr2, arr2[index], i+1);
    }
    return min(op1, op2);
}

// memoization solution
int memoization(vector<int>& arr1, vector<int>& arr2, int prev, int i, map<pair<int, int>, int> &dp) {
    // base case
    if(i == arr1.size())
        return 0;

    // memoization
    if(dp.find({prev, i}) != dp.end())
        return dp[{prev, i}];
    // recursion
    int op1 = INF;
    if(prev < arr1[i])
        op1 = memoization(arr1, arr2, arr1[i], i+1, dp);
    int op2 = INF;
    auto it = upper_bound(arr2.begin(), arr2.end(), prev);
    if(it != arr2.end()) {
        int index = it - arr2.begin();
        op2 = 1 + memoization(arr1, arr2, arr2[index], i+1, dp);
    }
    return dp[{prev,i}] = min(op1, op2);
}
int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
    sort(arr2.begin(), arr2.end());
    // int ans = recursion(arr1, arr2, -1, 0);
    map<pair<int,int>, int> dp;
    int ans = memoization(arr1, arr2, -1, 0, dp);
    return ans == INF ? -1 : ans;
}

// Best Time to Buy and Sell Stock II - LC(122)
// recursive solution
int recursion(vector<int> &prices, int i, int buy) {
    // base case
    if(i >= prices.size())
        return 0;
    
    // recursion
    int profit = 0;
    if(buy) {
        int buyProfit = -prices[i] + recursion(prices, i+1, 0);
        int skipProfit = recursion(prices, i+1, 1);
        profit = max(buyProfit, skipProfit);
    }
    else {
        int sellProfit = prices[i] + recursion(prices, i+1, 1);
        int skipProfit = recursion(prices, i+1, 0);
        profit = max(sellProfit, skipProfit);
    }
    return profit;
}

// memoization solution
int memoization(vector<int> &prices, int i, int buy, vector<vector<int>> &dp) {
    // base case
    if(i >= prices.size())
        return 0;

    // memoization
    if(dp[i][buy] != -1)
        return dp[i][buy];
    
    // recursion
    int profit = 0;
    if(buy) {
        int buyProfit = -prices[i] + memoization(prices, i+1, 0, dp);
        int skipProfit = memoization(prices, i+1, 1, dp);
        profit = max(buyProfit, skipProfit);
    }
    else {
        int sellProfit = prices[i] + memoization(prices, i+1, 1, dp);
        int skipProfit = memoization(prices, i+1, 0, dp);
        profit = max(sellProfit, skipProfit);
    }
    return dp[i][buy] = profit;
}

// tabulation solution
int tabulation(vector<int> &prices) {
    vector<vector<int>> dp(prices.size()+1, vector<int>(2, 0));
    for(int i=prices.size()-1; i>=0; --i) {
        for(int buy=0; buy<=1; ++buy) {
            int profit = 0;
            if(buy) {
                int buyProfit = -prices[i] + dp[i+1][0];
                int skipProfit = dp[i+1][1];
                profit = max(buyProfit, skipProfit);
            }
            else {
                int sellProfit = prices[i] + dp[i+1][1];
                int skipProfit = dp[i+1][0];
                profit = max(sellProfit, skipProfit);
            }
            dp[i][buy] = profit;
        }
    }
    return dp[0][1];
}

// space optimized
int spaceOptimized(vector<int> &prices) {
    vector<vector<int>> dp(2, vector<int>(2, 0));
    for(int i=prices.size()-1; i>=0; --i) {
        for(int buy=0; buy<=1; ++buy) {
            int profit = 0;
            if(buy) {
                int buyProfit = -prices[i] + dp[1][0];
                int skipProfit = dp[1][1];
                profit = max(buyProfit, skipProfit);
            }
            else {
                int sellProfit = prices[i] + dp[1][1];
                int skipProfit = dp[1][0];
                profit = max(sellProfit, skipProfit);
            }
            dp[0][buy] = profit;
        }
        dp[1] = dp[0];
    }
    return dp[0][1];
}
int maxProfit(vector<int>& prices) {
    return recursion(prices, 0, 1);

    vector<vector<int>> dp(prices.size(), vector<int>(2, -1));
    return memoization(prices, 0, 1, dp);

    return tabulation(prices);

    return spaceOptimized(prices);
}

// Best Time to Buy and Sell Stock III - LC(123)
// recursive solution
int recursion(vector<int> &prices, int i, int buy, int limit) {
    // base case
    if(i >= prices.size() || limit == 0)
        return 0;
    
    // recursion
    int profit = 0;
    if(buy) {
        int buyProfit = -prices[i] + recursion(prices, i+1, 0, limit);
        int skipProfit = recursion(prices, i+1, 1, limit);
        profit = max(buyProfit, skipProfit);
    }
    else {
        int sellProfit = prices[i] + recursion(prices, i+1, 1, limit-1);
        int skipProfit = recursion(prices, i+1, 0, limit);
        profit = max(sellProfit, skipProfit);
    }
    return profit;
}

// memoization solution
int memoization(vector<int> &prices, int i, int buy, int limit, vector<vector<vector<int>>> &dp) {
    // base case
    if(i >= prices.size() || limit == 0)
        return 0;

    // memoization
    if(dp[i][buy][limit] != -1)
        return dp[i][buy][limit];
    
    // recursion
    int profit = 0;
    if(buy) {
        int buyProfit = -prices[i] + memoization(prices, i+1, 0, limit, dp);
        int skipProfit = memoization(prices, i+1, 1, limit, dp);
        profit = max(buyProfit, skipProfit);
    }
    else {
        int sellProfit = prices[i] + memoization(prices, i+1, 1, limit-1, dp);
        int skipProfit = memoization(prices, i+1, 0, limit, dp);
        profit = max(sellProfit, skipProfit);
    }
    return dp[i][buy][limit] = profit;
}

// tabulation solution
int tabulation(vector<int> &prices) {
    vector<vector<vector<int>>> dp(prices.size()+1, vector<vector<int>>(2, vector<int>(3, 0)));

    // tabulation
    for(int i=prices.size()-1; i>=0; --i) {
        for(int buy=0; buy<=1; ++buy) {
            for(int limit=0; limit<=2; ++limit) {
                if(limit == 0)
                    continue;
                int profit = 0;
                if(buy) {
                    int buyProfit = -prices[i] + dp[i+1][0][limit];
                    int skipProfit = dp[i+1][1][limit];
                    profit = max(buyProfit, skipProfit);
                }
                else {
                    int sellProfit = prices[i] + dp[i+1][1][limit-1];
                    int skipProfit = dp[i+1][0][limit];
                    profit = max(sellProfit, skipProfit);
                }
                dp[i][buy][limit] = profit;
            }
        }
    }
    return dp[0][1][2];
}

// space optimized solution
int spaceOptimized(vector<int> &prices) {
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(2, vector<int>(3, 0)));

    // tabulation
    for(int i=prices.size()-1; i>=0; --i) {
        for(int buy=0; buy<=1; ++buy) {
            for(int limit=0; limit<=2; ++limit) {
                if(limit == 0)
                    continue;
                int profit = 0;
                if(buy) {
                    int buyProfit = -prices[i] + dp[1][0][limit];
                    int skipProfit = dp[1][1][limit];
                    profit = max(buyProfit, skipProfit);
                }
                else {
                    int sellProfit = prices[i] + dp[1][1][limit-1];
                    int skipProfit = dp[1][0][limit];
                    profit = max(sellProfit, skipProfit);
                }
                dp[0][buy][limit] = profit;
            }
        }
        dp[1] = dp[0];
    }
    return dp[0][1][2];
}
int maxProfit(vector<int>& prices) {
    return recursion(prices, 0, 1, 2);

    vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(2, vector<int>(3, -1)));
    return memoization(prices, 0, 1, 2, dp);

    return tabulation(prices);

    return spaceOptimized(prices);
}

// target sum - LC(494)
// recursive solution
int recursion(vector<int> &nums, int target, int i) {
    // base case
    if(i == nums.size())
        return target == 0 ? 1 : 0;
    
    // recursion
    int plus = recursion(nums, target - nums[i], i+1);
    int minus = recursion(nums, target + nums[i], i+1);
    return plus + minus;
}

// memoization solution
int memoization(vector<int> &nums, int target, int i, map<pair<int, int>, int> &dp) {
    // base case
    if(i == nums.size())
        return target == 0 ? 1 : 0;

    // memoization
    if(dp.find({target, i}) != dp.end())
        return dp[{target, i}];
    
    // recursion
    int plus = memoization(nums, target - nums[i], i+1, dp);
    int minus = memoization(nums, target + nums[i], i+1, dp);
    return dp[{target, i}] = plus + minus;
}

// tabulation solution
int tabulation(vector<int> &nums, int target) {
    map<pair<int, int>, int> dp;
    dp[{nums.size(), 0}] = 1;
    int total=0;
    for(auto num : nums)
        total += num;
    
    // tabulation
    for(int i=nums.size()-1; i>=0; --i) {
        for(int sum = -total; sum <= total; ++sum) {
            int plus = dp.find({i+1, sum-nums[i]}) != dp.end() ? dp[{i+1, sum-nums[i]}] : 0;
            int minus = dp.find({i+1, sum+nums[i]}) != dp.end() ? dp[{i+1, sum+nums[i]}] : 0;
            dp[{i, sum}] = plus + minus;
        }
    }
    return dp[{0, target}];
}
int findTargetSumWays(vector<int>& nums, int target) {
    return recursion(nums, target, 0);

    map<pair<int, int>, int> dp;
    return memoization(nums, target, 0, dp);

    return tabulation(nums, target);
}

// ones and zeros - LC(474)
void convert(vector<string> &strs, vector<pair<int, int>> &numStrs) {
    for(auto str : strs) {
        int ones=0, zeros=0;
        for(auto ch : str) {
            if(ch == '1')
                ones++;
            else
                zeros++;
        }
        numStrs.push_back({zeros, ones});
    }
}

// recursive solution
int recursion(vector<pair<int, int>> &numStrs, int i, int m, int n) {
    // base case
    if(i == numStrs.size())
        return 0;

    // recursion
    int zeros = numStrs[i].first;
    int ones = numStrs[i].second;
    int include=0;
    if(m - zeros >= 0 && n - ones >= 0)
        include = 1 + recursion(numStrs, i+1, m-zeros, n-ones);
    int exclude = recursion(numStrs, i+1, m, n);
    return max(include, exclude);
}

// memoization solution
int memoization(vector<pair<int, int>> &numStrs, int i, int m, int n, vector<vector<vector<int>>> &dp) {
    // base case
    if(i == numStrs.size())
        return 0;

    if(dp[i][m][n] != -1)
        return dp[i][m][n];

    // recursion
    int zeros = numStrs[i].first;
    int ones = numStrs[i].second;
    int include=0;
    if(m - zeros >= 0 && n - ones >= 0)
        include = 1 + memoization(numStrs, i+1, m-zeros, n-ones, dp);
    int exclude = memoization(numStrs, i+1, m, n, dp);
    return dp[i][m][n] = max(include, exclude);
}

// tabulation solution
int tabulation(vector<pair<int, int>> &numStrs, int M, int N) {
    vector<vector<vector<int>>> dp(numStrs.size()+1, vector<vector<int>>(M+1, vector<int>(N+1, 0)));

    // tabulation
    for(int i=numStrs.size()-1; i>=0; --i) {
        for(int m=0; m<=M; ++m) {
            for(int n=0; n<=N; ++n) {
                int zeros = numStrs[i].first;
                int ones = numStrs[i].second;
                int include=0;
                if(m - zeros >= 0 && n - ones >= 0)
                    include = 1 + dp[i+1][m-zeros][n-ones];
                int exclude = dp[i+1][m][n];
                dp[i][m][n] = max(include, exclude);
            }
        }
    } 
    return dp[0][M][N];
}
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<pair<int, int>> numStrs;
    convert(strs, numStrs);

    return recursion(numStrs, 0, m, n);

    vector<vector<vector<int>>> dp(strs.size(), vector<vector<int>>(m+1, vector<int>(n+1, -1)));
    return memoization(numStrs, 0, m, n, dp);

    return tabulation(numStrs, m, n);
}

// Minimum Swaps To Make Sequences Increasing - LC(801)
// recursion solution
int recursion(vector<int> &nums1, vector<int> &nums2, int i, int p1, int p2) {
    // base case
    if(i == nums1.size())
        return 0;

    // recursion
    int swap = INT_MAX, noswap = INT_MAX;
    if(p1 < nums2[i] && p2 < nums1[i])
        swap = 1 + recursion(nums1, nums2, i+1, nums2[i], nums1[i]);
    if(p1 < nums1[i] && p2 < nums2[i])
        noswap = recursion(nums1, nums2, i+1, nums1[i], nums2[i]);
    return min(swap, noswap);
}

// memoization solution
int memoization(vector<int> &nums1, vector<int> &nums2, int i, int p1, int p2, vector<vector<int>> &dp, int isswap) {
    // base case
    if(i == nums1.size())
        return 0;

    // memoization
    if(dp[i][isswap] != -1)
        return dp[i][isswap];

    // recursion
    int swap = INT_MAX, noswap = INT_MAX;
    if(p1 < nums2[i] && p2 < nums1[i])
        swap = 1 + memoization(nums1, nums2, i+1, nums2[i], nums1[i], dp, 1);
    if(p1 < nums1[i] && p2 < nums2[i])
        noswap = memoization(nums1, nums2, i+1, nums1[i], nums2[i], dp, 0);
    return dp[i][isswap] = min(swap, noswap);
}

// tabulation solution
int tabulation(vector<int> &nums1, vector<int> &nums2) {
    vector<vector<int>> dp(nums1.size()+1, vector<int>(2, 0));

    // tabulation
    for(int i=nums1.size()-1; i>=1; --i) {
        for(int isswap=1; isswap>=0; --isswap) {
            int p1 = nums1[i-1];
            int p2 = nums2[i-1];
            if(isswap)
                swap(p1, p2);
            int swap = INT_MAX, noswap = INT_MAX;
            if(p1 < nums2[i] && p2 < nums1[i])
                swap = 1 + dp[i+1][1];
            if(p1 < nums1[i] && p2 < nums2[i])
                noswap = dp[i+1][0];
            dp[i][isswap] = min(swap, noswap);
        }
    }
    return dp[1][0];
}
int minSwap(vector<int>& nums1, vector<int>& nums2) {
    return recursion(nums1, nums2, 0, -1, -1);

    vector<vector<int>> dp(nums1.size(), vector<int>(2, -1));
    return memoization(nums1, nums2, 0, -1, -1, dp, 0);

    nums1.insert(nums1.begin(), -1);
    nums2.insert(nums2.begin(), -1);
    return tabulation(nums1, nums2);
}

// reducing dishes - LC(1402)
// recursive solution
int recursion(vector<int> &sat, int i, int time) {
    // base case
    if(i == sat.size())
        return 0;

    // recursion
    int include = sat[i] * time + recursion(sat, i+1, time+1);
    int exclude = recursion(sat, i+1, time);
    return max(include, exclude);
}

// memoization solution
int memoization(vector<int> &sat, int i, int time, vector<vector<int>> &dp) {
    // base case
    if(i == sat.size())
        return 0;

    // memoization
    if(dp[i][time] != -1)
        return dp[i][time];

    // recursion
    int include = sat[i] * time + memoization(sat, i+1, time+1, dp);
    int exclude = memoization(sat, i+1, time, dp);
    return dp[i][time] = max(include, exclude);
}

// tabulation solution
int tabulation(vector<int> &sat) {
    vector<vector<int>> dp(sat.size()+1, vector<int>(sat.size()+2, 0));

    // tabulation
    for(int i=sat.size()-1; i>=0; --i) {
        for(int time=sat.size(); time>=1; --time) {
            int include = sat[i] * time + dp[i+1][time+1];
            int exclude = dp[i+1][time];
            dp[i][time] = max(include, exclude);
        }
    }
    return dp[0][1];
}
int maxSatisfaction(vector<int>& satisfaction) {
    sort(satisfaction.begin(), satisfaction.end());

    return recursion(satisfaction, 0, 1);

    vector<vector<int>> dp(satisfaction.size()+1, vector<int>(satisfaction.size()+1, -1));
    return memoization(satisfaction, 0, 1, dp);

    return tabulation(satisfaction);
}

// predict the winner - LC(486)
// recursive solution
int recursion(vector<int> &nums, int start, int end) {
    // base case
    if(start == end)
        return nums[start];

    // recursion
    int pickStart = nums[start] - recursion(nums, start+1, end);
    int pickEnd = nums[end] - recursion(nums, start, end-1);
    return max(pickStart, pickEnd);
}

// memoization solution
int memoization(vector<int> &nums, int start, int end, vector<vector<int>> &dp) {
    // base case
    if(start == end)
        return nums[start];

    // memoization
    if(dp[start][end] != -1)
        return dp[start][end];

    // recursion
    int pickStart = nums[start] - memoization(nums, start+1, end, dp);
    int pickEnd = nums[end] - memoization(nums, start, end-1, dp);
    return dp[start][end] = max(pickStart, pickEnd);
}

// tabulation solution
int tabulation(vector<int> &nums) {
    vector<vector<int>> dp(nums.size(), vector<int>(nums.size()+1, -1));

    // solve first base case
    for(int i=0; i<nums.size(); ++i)
        dp[i][i] = nums[i];

    // tabulation
    int i = nums.size();
    for(int start = nums.size()-1; start >= 0; --start) {
        for(int end = i; end < nums.size(); ++end) {
            int pickStart = nums[start] - dp[start+1][end];
            int pickEnd = nums[end] - dp[start][end-1];
            dp[start][end] = max(pickStart, pickEnd);
        }
        --i;
    }
    return dp[0][nums.size()-1];
}
bool predictTheWinner(vector<int>& nums) {
    return recursion(nums, 0, nums.size()-1) >= 0;

    vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), -1));
    return memoization(nums, 0, nums.size()-1, dp) >= 0;

    return tabulation(nums) >= 0;
}

int main() {

    int n;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; ++i)
        cin >> nums[i];
    cout << "maximum coins you can collect by bursting the balloons : " << maxCoins(nums) << endl;

    string s1, s2, s3;
    cout << "enter s1 s2 s3 : ";
    cin >> s1 >> s2 >> s3;
    if(isInterleave(s1, s2, s3))
        cout << "true" << endl;
    else 
        cout << "false" << endl;

    int n;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; ++i)
        cin >> nums[i];
    cout << "minimum number of elements to remove : " << minimumMountainRemovals(nums) << endl;

    int n, m;
    cout << "enter the size of [arr1] or [arr2] : ";
    cin >> n >> m;
    vector<int> arr1(n), arr2(m);
    for(int i=0; i<n; ++i)
        cin >> arr1[i];
    for(int i=0; i<m; ++i)
        cin >> arr2[i];
    cout << "minimum number of operations : " << makeArrayIncreasing(arr1, arr2) << endl;

    int n;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<int> prices(n);
    for(int i=0; i<n; ++i)
        cin >> prices[i];
    cout << " the maximum profit you can achieve : " << maxProfit(prices) << endl;

    int n, target;
    cout << "enter the size of vector : ";
    cin >> n;
    cout << "enter target : ";
    cin >> target; 
    vector<int> nums(n);
    for(int i=0; i<n; ++i)
        cin >> nums[i];
    cout << "total no. of expressions we can build : " << findTargetSumWays(nums, target) << endl;

    int x, m, n;
    cout << "enter size of vector : ";
    cin >> x;
    vector<string> strs(x);
    for(char ch=0; ch<x; ++ch)
        cin >> strs[ch];
    cout << "enter [m] and [n] : ";
    cin >> m >> n;
    cout << "the largest subset with max no. of 0's and 1's : " << findMaxForm(strs, m, n) << endl;

    int n;
    cout << "enter the size of both vectors : ";
    vector<int> nums1(n);
    for(int i=0; i<n; ++i)
        cin >> nums1[i];
    vector<int> nums2(n);
    for(int i=0; i<n; ++i)
        cin >> nums2[i];
    cout << "minimum number of needed operations : " << minSwap(nums1, nums2) << endl;

    int n;
    cout << "enter the size of vector : ";
    vector<int> satisfaction(n);
    for(int i=0; i<n; ++i)
        cin >> satisfaction[i];
    cout << "max satisfaction level : " << maxSatisfaction(satisfaction) << endl;

    int n;
    cout << "enter the size of vector : ";
    vector<int> nums(n);
    for(int i=0; i<n; ++i)
        cin >> nums[i];
    if(predictTheWinner(nums))
        cout << "player 1 wins" << endl;
    else 
        cout << "player 2 wins" << endl;
     
    return 0;
}