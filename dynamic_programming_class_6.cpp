#include<bits/stdc++.h>

using namespace std;

// guess number higher or lower - II
// recursive solution
int recursion(int start, int end) {
    // base case
    /*if [start] is greater than [end] that means it's out of range
    ans if[start] if equals to [end] that means it's the last number 
    you can guess so, it should be a correct no. so no penalty*/
    if(start >= end)
        return 0;

    // recursion
    /*calculating the min amount of money one would have to win the
    game, if one can choose any no. we've calculated all the ranges 
    where the picked no. lies and from those ranges we've acquires
    the max amount of money, and that max amount of money should be
    min among all the no. betweent [start] and [end], so the one can
    choose only that no. to minimize his spending on guessing*/
    int ans = INT_MAX;
    for(int i=start; i<=end; ++i)
        ans = min(ans, i + max(recursion(start, i-1), recursion(i+1, end)));
    return ans;
}

// memoization solution
int memoization(int start, int end, vector<vector<int>> &dp) {
    // base case
    if(start >= end)
        return 0;

    // if solutions is already present in [dp]
    if(dp[start][end] != -1)
        return dp[start][end];

    // solve the new occurring solutions
    int ans = INT_MAX;
    for(int i=start; i<=end; ++i)
        ans = min(ans, i + max(memoization(start, i-1, dp), memoization(i+1, end, dp)));
    dp[start][end] = ans;
    return dp[start][end];
}

// tabulation solution
int tabulation(int n) {
    // create a 2D vector and initialize it with [0]
    /*why [0]? => so that i'm not solving it for the base case 
    separately. if all the positions are [0], then there's no
    need for solving for base case in tabulaton*/
    vector<vector<int>> dp(n+2, vector<int>(n+1, 0));

    // after solving the base case solve the remaining solutions
    for(int start = n; start >= 1; --start) {
        for(int end = 1; end <= n; ++end) {
            /*we've to skip this condition as mentioned above this
            is a base case that gives [0] value but here we're just
            avoiding it so that it'll no affect our answer*/
            if(start >= end)
                continue;
            int ans = INT_MAX;
            for(int i=start; i<=end; ++i)
                /*why we're doing [n+2] above is related to here, so as
                we are performing (dp[i+1][end]), so when the value of
                [start] is (n) itself the statement will increment it's
                iterator so we need extra space for that iterator, that's
                why we've created a (n+2) row in a 2D vector, (n+1) can't
                fulfil the requirements to run this statement*/
                ans = min(ans, i + max(dp[start][i-1], dp[i+1][end]));
            dp[start][end] = ans;
        }
    }
    return dp[1][n];
}

int getMoneyAmount(int n) {
    int start=1, end=n;
    return recursion(start, end);

    vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
    return memoization(start, end, dp);

    return tabulation(n);
}

// minimum cost tree from leaf values
// recursive solution
int recursion(vector<int> &arr, map<pair<int, int>, int>& maxi, int s, int e) {
    // base case
    if(s >= e)
        return 0;

    // recursion
    int ans = INT_MAX;
    for(int i=s; i<e; ++i) {
        ans = min(ans, (maxi[{s, i}] * maxi[{i+1, e}]) 
                + recursion(arr, maxi, s, i) + recursion(arr, maxi, i+1, e));
    }
    return ans;
}
void print_2D(vector<vector<int>> &dp) {
    for(auto const row : dp) {
        cout << "[ ";
        for(auto col : row)
            cout << col << " ";
        cout << "]" << endl;
    }
    cout << endl;
}
// memoization solution
int memoization(vector<int> &arr, map<pair<int, int>, int>& maxi, vector<vector<int>> &dp, int s, int e) {
    // base case
    if(s >= e)
        return 0;

    // double check the solution if already presented in [dp]
    if(dp[s][e] != -1)
        return dp[s][e];

    // solve new occuring solutions in [dp]
    int ans = INT_MAX;
    for(int i=s; i<e; ++i) {
        ans = min(ans, (maxi[{s, i}] * maxi[{i+1, e}]) 
                + memoization(arr, maxi, dp, s, i) + memoization(arr, maxi, dp, i+1, e));
    }
    dp[s][e] = ans;
    // print_2D(dp);
    return dp[s][e];
}

// tabulation solution
int tabulation(vector<int> &arr, map<pair<int, int>, int>& maxi) {
    // create a 2D array
    int n = arr.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    // tabulation
    for(int s = n-1; s >= 0; --s) {
        for(int e = 0; e <= n-1; ++e) {
            if(s >= e)
                continue;
            int ans = INT_MAX;
            for(int i=s; i<e; ++i) {
                ans = min(ans, (maxi[{s, i}] * maxi[{i+1, e}]) 
                        + dp[s][i] + dp[i+1][e]);
            }
            dp[s][e] = ans;
        }
    }
    // print_2D(dp);
    return dp[0][n-1];
}

int minCostFromLeaves(vector<int> &arr) {
    map<pair<int, int>, int> maxi;
    for(int i=0; i<arr.size(); ++i) {
        maxi[{i, i}] = arr[i];
        for(int j=i+1; j<arr.size(); ++j)
            maxi[{i, j}] = max(arr[j], maxi[{i, j-1}]);
    }
    int start = 0, end = arr.size()-1;
    
    return recursion(arr, maxi, start, end);

    vector<vector<int>> dp(arr.size()+1, vector<int>(arr.size()+1, -1));
    return memoization(arr, maxi, dp, start, end);

    return tabulation(arr, maxi);
}

int main() {

    int n;
    cout << "enter [n] : ";
    cin >> n;
    cout << "min amount of money needed to win the game : " << getMoneyAmount(n) << endl;

    int n;
    cout << "enter the size of array : ";
    cin >> n;
    vector<int> arr(n);
    for(int i=0; i<n; ++i)
        cin >> arr[i];
    cout << "smallest possible sum of the values of each non-leaf node : " << minCostFromLeaves(arr) << endl;
     
    return 0;
}