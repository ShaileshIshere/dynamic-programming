#include<bits/stdc++.h>

using namespace std;

// partition equal subset sum
// recursive solution
bool recursion(vector<int> &v, int index, int sum, int target) {
    // base case
    if(index >= v.size())
        return false;
    else if(sum > target)
        return false;
    else if(sum == target)
        return true;

    // recursion
    bool include = recursion(v, index+1, sum+v[index], target);
    bool exclude = recursion(v, index+1, sum, target);
    return include || exclude;
}

// memoization solution
bool memoization(vector<int> &v, int index, int sum, int target, vector<vector<int>> &dp) {
    // base case
    if(index >= v.size())
        return false;
    else if(sum > target)
        return false;
    else if(sum == target)
        return true;

    // memoization
    if(dp[index][sum] != -1)
        return dp[index][sum];

    // recursion
    bool include = memoization(v, index+1, sum+v[index], target, dp);
    bool exclude = memoization(v, index+1, sum, target, dp);
    dp[index][sum] = include || exclude;
    return dp[index][sum];
}

// tabulation solution
bool tabulation(vector<int> &v, int target) {
    // create a 2D vector
    vector<vector<int>> dp(v.size()+1, vector<int>(target+1, 0));

    // solve first base case/solution
    for(int row=0; row<=v.size(); ++row)
        dp[row][target] = 1;

    // tabulation
    for(int index = v.size()-1; index >= 0; --index) {
        for(int sum = target-1; sum >= 0; --sum) {
            bool include = 0;
            if(sum + v[index] <= target)
                include = dp[index+1][sum+v[index]];
            bool exclude = dp[index+1][sum];
            dp[index][sum] = include || exclude;
        }
    }
    return dp[0][0];
}

// space optimization
bool spaceOptimized(vector<int> &v, int target) {
    // create 2 1D vectors
    vector<int> next(target+1, 0);
    vector<int> curr(target+1, 0);

    // solving a base case manually
    next[target] = true;

    // solving through tabulation approach but only using above 2 vectors
    for(int index = v.size()-1; index >= 0; --index) {
        for(int sum = target; sum >= 0; --sum) {
            /*if you don't want to solve a base case just like we did above
            then you should add this condition inside the nested loops*/
            if(sum == target)
                next[sum] = true;
            bool include = 0;
            if(sum + v[index] <= target)
                include = next[sum+v[index]];
            bool exclude = next[sum];
            curr[sum] = include || exclude;
        }
        // update the vectors
        next = curr;
    }
    return next[0];
}

bool partition(vector<int> &nums) {
    int sum = 0, currSum = 0, index = 0;
    for(int i=0; i<nums.size(); ++i)
        sum += nums[i];
    if(sum & 1)
        return false;
    int target = sum >> 1;

    return recursion(nums, index, currSum, target);

    vector<vector<int>> dp(sum+1, vector<int>(sum+1, -1));
    return memoization(nums, index, currSum, target, dp);

    return tabulation(nums, target);

    return spaceOptimized(nums, target);
}

// number of dice rolls with target sum
/*as the question says that the final answer would be very long
so it's beneficial to return the answer in [modulo]*/
long long int MOD = 1000000007;
// recursive solution
int recursion(int n, int k, int target) {
    // base cases
    if(n == 0 && target == 0) 
        return 1;
    if((n != 0 && target == 0) || (n == 0 && target != 0))
        return 0;

    // recursion
    int ans = 0;
    for(int i=1; i<=k; ++i)
        ans += recursion(n-1, k, target-i);
    return ans;
}

// memoization solution
int memoization(int n, int k, int target, vector<vector<int>> &dp) {
    // base cases
    if(n == 0 && target == 0) 
        return 1;
    if((n != 0 && target == 0) || (n == 0 && target != 0))
        return 0;

    // memoization
    if(dp[n][target] != -1)
        return dp[n][target];

    // recursion
    int ans = 0;
    for(int i=1; i<=k; ++i) {
        int finalAns = 0;
        if(target - i >= 0)
            finalAns = memoization(n-1, k, target-i, dp) % MOD;
        ans = (ans + finalAns) % MOD;
    }
    dp[n][target] = ans;
    return dp[n][target];
} 

// tabulation solution
int tabulation(int N, int k, int target) {
    // create a 2D vector, also solved a base case by initializing whole array with [0]
    vector<vector<int>> dp(N+1, vector<int>(target+1, 0));

    // solve another base case
    dp[0][0] = 1;

    // tabulation
    for(int n=1; n<=N; ++n) {
        for(int t=1; t<=target; ++t) {
            int ans = 0;
            for(int i=1; i<=k; ++i) {
                int finalAns = 0;
                if(t - i >= 0)
                    finalAns = (dp[n-1][t-i]) % MOD;
                ans = (ans + finalAns) % MOD;
            }
            dp[n][t] = ans;
        }
    }
    return dp[N][target];
}

// space optimized
int spaceOptimized(int N, int k, int target) {
    vector<int> curr(target+1, 0);
    vector<int> next(target+1, 0);

    curr[0] = 1;

    for(int n=1; n<=N; ++n) {
        for(int t=1; t<=target; ++t) {
            int ans = 0;
            for(int i=1; i<=k; ++i) {
                int finalAns = 0;
                if(t - i >= 0)
                    finalAns = curr[t-i];
                ans = (ans + finalAns) % MOD;
            }
            next[t] = ans;
        }
        curr = next;
    }
    return curr[target];
}

int numRolls(int n, int k, int target) {
    return recursion(n, k, target);

    vector<vector<int>> dp(n+1, vector<int>(target+1, -1));
    return memoization(n, k, target, dp);

    return tabulation(n, k, target);

    return spaceOptimized(n, k, target);
}

int main() {

    int n;
    cout << "ente the size of vector : ";
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; ++i)
        cin >> nums[i];
    if(partition(nums))
        cout << "true" << endl;
    else 
        cout << "false" << endl;

    int n, k, target;
    cout << "enter : how many dices?, how many sides of each dice?, target" << endl;
    cin >> n >> k >> target;
    cout << "total no. of ways that all dice matches up to target : " << numRolls(n, k, target) << endl;
     
    return 0;
}