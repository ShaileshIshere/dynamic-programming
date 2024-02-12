#include<bits/stdc++.h>

using namespace std;

// longest increasing subsequence
// recursive solution
int recursion(vector<int> &v, int prev, int curr) {
    // base case
    if(curr == v.size())
        return 0;
    
    // include/exclude => recursion
    int include = 0;
    if(prev == -1 || v[curr] > v[prev])
        include = 1 + recursion(v, curr, curr+1);
    int exclude = recursion(v, prev, curr+1);
    return max(include, exclude);
}

// experiment purpose
void print_2D(vector<vector<int>> &v) {
    for(auto const row : v) {
        cout << "[ ";
        for(int col : row)
            cout << col << " ";
        cout << "]" << endl;
    }
}

// top down
int topDown(vector<int> &v, int prev, int curr, vector<vector<int>> &dp) {
    // base case
    if(curr == v.size())
        return 0;

    // check if any solution occurs twice
    if(dp[prev+1][curr] != -1)
        return dp[prev+1][curr];
    
    // solve the new ones
    int include = 0;
    if(prev == -1 || v[curr] > v[prev])
        include = 1 + topDown(v, curr, curr+1, dp);
    int exclude = topDown(v, prev, curr+1, dp);
    dp[prev+1][curr] = max(include, exclude);
    return dp[prev+1][curr];
}

// tabulation solution
int bottomUp(vector<int> &v) {
    // create a 2D array
    vector<vector<int>> dp(v.size()+1, vector<int>(v.size()+1, 0));

    // solve remaining solutions
    for(int curr=v.size()-1; curr>=0; --curr) {
        for(int prev=curr-1; prev>=-1; --prev) {
            int include = 0;
            if(prev == -1 || v[curr] > v[prev])
                include = 1 + dp[curr+1][curr+1];
            int exclude = dp[prev+1][curr+1];
            dp[prev+1][curr] = max(include, exclude);
        }
    }
    print_2D(dp);
    return dp[0][0];
}

// space optimized
int spaceOptimized(vector<int> &v) {
    // create 2 1D arrays
    vector<int> prev(v.size()+1, 0);
    vector<int> curr(v.size()+1, 0);

    // inserting in [curr] with the help of [prev]
    for(int prev = curr-1; prev >= -1; --prev) {
        for(int curr = v.size()-1; curr >= 0; --curr) {
            int include = 0;
            if(prev == -1 || v[curr] > v[prev])
                include = 1 + curr[curr+1];
            int exclude = curr[prev+1];
            prev[curr] = max(include, exclude);
        }
        curr = prev;
    }
    return curr[0];
}

int longest_inc_subseq(vector<int> &v) {
    // return recursion(v, -1, 0);

    // vector<vector<int>> dp(v.size()+1, vector<int>(v.size()+1, -1));
    // return topDown(v, -1, 0, dp);

    // return bottomUp(v);

    return spaceOptimized(v);
}

int main() {

    int n;
    cout << "enter size : ";
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; ++i)
        cin >> nums[i];
    cout << "longest increasing subsequence : " << longest_inc_subseq(nums) << endl;
     
    return 0;
}