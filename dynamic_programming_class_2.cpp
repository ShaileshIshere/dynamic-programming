#include <bits/stdc++.h>

using namespace std;

// house robber
// recursion
int solve(vector<int> &v, int i) {
    // base case
    if(i >= v.size())
        return 0;
    // houses to be included
    int include = v[i] + solve(v, i+2);
    // houses to be excluded
    int exclude = 0 + solve(v, i+1);
    return max(include, exclude);
}

// top down approach
int topDown(vector<int> &v, int i, vector<int> &dp) {
    // base case
    if(i >= v.size())
        return 0;
    // step 3: if the element is already present in [dp]
    if(dp[i] != -1)
        return dp[i];
    // step 2: inserting the element that's occuring first time in [dp]
    int include = v[i] + topDown(v, i+2, dp);
    int exclude = 0 + topDown(v, i+1, dp);
    return dp[i] = max(include, exclude);
}

// bottom up approach
int bottomUp(vector<int> &v, int i) {
    int n = v.size();
    // step 1: create a [dp] array/vector
    vector<int> dp(n, -1);

    /*step 2: create first [and] by ourself then the rest
    of the [ans] will be calculated by further iterative approach*/
    dp[n-1] = v[n-1];

    /*step 3: solve the remaining solutions, here we're calculating 
    the max amount of money being stolen from different houses, also 
    here we're calculating from right to left in [dp] array/vector*/
    for(int index = n-2; index >= 0; --index) {
        int tempAns = 0;
        // edge case, if the house we're including is out of the given array
        if(index + 2 < n)
            tempAns = dp[index + 2];
        int include = v[index] + tempAns;
        int exclude = dp[index + 1];
        dp[index] = max(include, exclude);
    }
    // ans is at dp[0] coz we're calculating from right to left
    return dp[0];
}

// space optimized approach
int spaceOptimized(vector<int> &v) {
    int n = v.size();
    /*step 1: initialize important variables that will be useful
    in calculating the answers of further iterations*/
    int prev = v[n-1], next = 0, curr;

    /*step 2: sab kuch same h tabulation method ki trah, 
    bas dp[index + 2] => next or dp[index + 1] => prev likhna h*/
    for(int index = n-2; index >= 0; --index) {
        int include = v[index] + next;
        int exclude = prev;
        curr = max(include, exclude);
        /*step 3: update the values of prev or next variables*/
        next = prev;
        prev = curr;
    }
    return prev;
}
// calling function
int rob(vector<int>& nums) {
    return solve(nums, 0);
    
    // // step 1: create a [dp] array/vector
    vector<int> dp(nums.size(), -1);
    return topDown(nums, 0, dp);

    return bottomUp(nums, 0);
}

// coin change
// recursive approach
int recursion(vector<int> &v, int x) {
    // base case
    if(x == 0)
        return 0;
    // recursive relation
    int mini = INT_MAX;
    for(int i=0; i<v.size(); ++i) {
        if(x - v[i] >= 0) {
            int recAns = recursion(v, x - v[i]);
            if(recAns != INT_MAX) {
                int ans = 1 + recAns;
                mini = min(mini, ans);
            }
        }
    }
    return mini;
}

// top down approach
int topDown(vector<int> &v, int x, vector<int> &dp) {
    // base case
    if(x == 0)
        return 0;

    // step 3: check if any element is already present in [dp] array
    if(dp[x] != -1)
        return dp[x];
    
    // step 2: calculate new solutions and insert them in [dp] array
    int mini = INT_MAX;
    for(int i=0; i<v.size(); ++i) {
        if(x - v[i] >= 0) {
            int recAns = topDown(v, x - v[i], dp);
            if(recAns != INT_MAX) {
                int ans = 1 + recAns;
                mini = min(mini, ans);
            }
        }
    }
    // return the index that contains the final [ans]
    dp[x] = mini;
    return dp[x];
}

// bottom up approach
int bottomUp(vector<int> &v, int x) {
    // step 1: create a dp array
    vector<int> dp(x + 1, -1);

    // step 2: initialize our first solution manually
    dp[0] = 0;

    // step 3: calculate the remaining solutions iteratively
    for(int value = 1; value <= x; ++value) {
        int mini = INT_MAX;
        for(int i = 0; i < v.size(); ++i) {
            if(value - v[i] >= 0) {
                int recAns = dp[value - v[i]];
                if(recAns != INT_MAX) {
                    int ans = 1 + recAns;
                    mini = min(mini, ans);
                }
            }
        }
        dp[value] = mini;
    }
    return dp[x];
}
// calling function
int coinChange(vector<int> &coins, int amount) {
    int ans = recursion(coins, amount);

    // step 1: create a [dp] array
    vector<int> dp(amount+1, -1);
    int ans = topDown(coins, amount, dp);

    int ans = bottomUp(coins, amount);

    if(ans == INT_MAX)
        return -1;
    else 
        return ans;
}

int main() {

    int n;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; ++i)
        cin >> nums[i];
    cout << "the maximum amount of stolen money : " << rob(nums) << endl;

    int n, amount;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<int> coins(n);
    for(int i=0; i<n; ++i)
        cin >> coins[i];
    cout << "enter the amount you need from the given coins : ";
    cin >> amount;
    cout << "amount will be obtained after the usage of [" << coinChange(coins, amount) << "] coins " << endl;

    return 0;
}