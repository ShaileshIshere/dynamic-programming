#include<bits/stdc++.h>

using namespace std;

// painting fence algorithm
// recursive approach
int recursion(int n, int k) {
    if(n == 1)
        return k;
    if(n == 2)
        return k + (k*(k - 1));
    return (k - 1) * (recursion(n - 1, k) + recursion(n - 2, k));
}

// top down approach
int topDown(int n, int k, vector<int> &dp) {
    if(n == 1)
        return k;
    if(n == 2)
        return k + (k*(k - 1));
    // if solution already exists then return from here
    if(dp[n] != -1)
        return dp[n];
    // if not then solve it here and insert in [dp]
    dp[n] = (k - 1) * (topDown(n - 1, k, dp) + topDown(n - 2, k, dp));
    return dp[n];
}

// bottom up approach
int bottomUp(int n, int k) {
    vector<int> dp(n+1, -1);
    // initialize the base variables manually
    dp[1] = k;
    dp[2] = k + k*(k-1);
    // calculate the rest of the variables
    for(int i=3; i<=n; ++i) 
        dp[i] = (k - 1) * (dp[i - 1] + dp[i - 2]);
    return dp[n];
}

// space optimized
int spaceOptimized(int n, int k) {
    int prev = k;
    // edge case
    if(n == 1)
        return prev;
    int curr = k + k*(k-1);
    int next;
    for(int i=3; i<=n; ++i) {
        next = (k-1 ) * (prev + curr);
        // update values of both pointers
        prev = curr;
        curr = next;
    }
    return curr;
}
int painting_fence(int posts, int colors) {
    int n = posts, k = colors;

    // return recursion(n, k);

    // vector<int> dp(n+1, -1);
    // return topDown(n, k, dp);

    // return bottomUp(n, k);

    return spaceOptimized(n, k);
}

int main() {

    int posts, colors;
    cout << "enter the number of [posts] and [colors] : ";
    cin >> posts >> colors;
    cout << "total no. of ways to color posts are : " << painting_fence(posts, colors) << endl;

    return 0;
}