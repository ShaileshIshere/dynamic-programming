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
    // return recursion(s1, s2, s3, 0, 0, 0);

    // vector<vector<vector<int>>> dp(s1.size()+1, vector<vector<int>>(s2.size()+1, vector<int>(s3.size()+1, -1)));
    // return memoization(s1, s2, s3, 0, 0, 0, dp);

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
    // return recursion(prices, 0, 1);

    // vector<vector<int>> dp(prices.size(), vector<int>(2, -1));
    // return memoization(prices, 0, 1, dp);

    // return tabulation(prices);

    return spaceOptimized(prices);
}

int main() {

    // int n;
    // cout << "enter the size of vector : ";
    // cin >> n;
    // vector<int> nums(n);
    // for(int i=0; i<n; ++i)
    //     cin >> nums[i];
    // cout << "maximum coins you can collect by bursting the balloons : " << maxCoins(nums) << endl;

    // string s1, s2, s3;
    // cout << "enter s1 s2 s3 : ";
    // cin >> s1 >> s2 >> s3;
    // if(isInterleave(s1, s2, s3))
    //     cout << "true" << endl;
    // else 
    //     cout << "false" << endl;

    // int n;
    // cout << "enter the size of vector : ";
    // cin >> n;
    // vector<int> nums(n);
    // for(int i=0; i<n; ++i)
    //     cin >> nums[i];
    // cout << "minimum number of elements to remove : " << minimumMountainRemovals(nums) << endl;

    // int n, m;
    // cout << "enter the size of [arr1] or [arr2] : ";
    // cin >> n >> m;
    // vector<int> arr1(n), arr2(m);
    // for(int i=0; i<n; ++i)
    //     cin >> arr1[i];
    // for(int i=0; i<m; ++i)
    //     cin >> arr2[i];
    // cout << "minimum number of operations : " << makeArrayIncreasing(arr1, arr2) << endl;

    int n;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<int> prices(n);
    for(int i=0; i<n; ++i)
        cin >> prices[i];
    cout << " the maximum profit you can achieve : " << maxProfit(prices) << endl;
     
    return 0;
}