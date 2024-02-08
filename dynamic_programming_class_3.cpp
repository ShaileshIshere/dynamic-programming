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

    return recursion(n, k);

    vector<int> dp(n+1, -1);
    return topDown(n, k, dp);

    return bottomUp(n, k);

    return spaceOptimized(n, k);
}

// 0/1 knapsack problem => 2D [dp]
// recursion
int recursion(int w, int n, int index, vector<int> &val, vector<int> &wt) {
    // base case 1:
    if(index >= n)
        return 0;
// the code is working with any of the mentioned base cases
    // base case 2:
    // it means we're currently on the last index of [wt]
    if(index == n-1) {
        if(wt[index] <= w)
            return val[index];
        else 
            return 0;
    }

    // include / exclude
    int include = 0;
    if(wt[index] <= w)
        include = val[index] + recursion(w - wt[index], n, index + 1, val, wt);
    int exclude = recursion(w, n, index + 1, val, wt);
    return max(include, exclude);
}

// just for experiment
void print_dp(vector<vector<int>> &dp) {
    cout << "recursive case :- " << endl;
    for(auto row : dp) {
        cout << "[ ";
        for(int col : row)
            cout << col << " ";
        cout << "]" << endl;
    }
}

// top down approach
int topDown(int w, int n, int index, vector<int> &val, vector<int> &wt, vector<vector<int>> &dp) {
    // base case same thing diff fun
    if(index >= n)
        return 0;

    // check if any element already present in [dp]
    if(dp[w][index] != -1)
        return dp[w][index];

    // include / exclude
    // calculate new solutions and insert them in [dp]
    int include = 0;
    if(wt[index] <= w)
        include = val[index] + topDown(w - wt[index], n, index + 1, val, wt, dp);
    int exclude = topDown(w, n, index + 1, val, wt, dp);
    // insertion of elements in [dp] 
    dp[w][index] = max(include, exclude);
    print_dp(dp);
    return dp[w][index];
}
 
// bottom up approach
int bottomUp(int w, int n, vector<int> &val, vector<int> &wt) {
    // create a 2D vector/array 
    vector<vector<int>> dp(w+1, vector<int>(n+1, -1));

    // initialize starting varable manually
    for(int row = 0; row <= w; ++row)
        dp[row][n] = 0;

    // solve for upcomming varables
    for(int i = 0; i <= w; ++i) {
        for(int j = n-1; j >= 0; --j) {
            int include = 0;
            if(wt[j] <= i)
                include = val[j] + dp[i - wt[j]][j + 1];
            int exclude = dp[i][j + 1]; 
            // insertion of elements in [dp] 
            dp[i][j] = max(include, exclude);
        }
    }
    print_dp(dp);
    return dp[w][0];
}

// space optimized
int spaceOptimized(int w, int n, vector<int> &val, vector<int> &wt) {
    /*create two 1D vectors and from the combinations of
    these two vectors we can form the ans of upcomming answers*/
    vector<int> curr(w+1, -1);
    vector<int> next(w+1, -1);

    // set the [next] values to [0] so that we can form answers of [curr] vector
    for(int row = 0; row <= w; ++row)
        next[row] = 0;
    
    // form the remaining answers
    for(int j=n-1; j>=0; --j) {
        for(int i=0; i<=w; ++i) {
            int include = 0;
            if(wt[j] <= i)
                include = val[j] + next[i - wt[j]];
            int exclude = next[i];
            curr[i] = max(include, exclude);
        }
        // update values
        next = curr;
    }
    return curr[w];
}

// more space optimized
int moreSpaceOptimized(int w, int n, vector<int> &val, vector<int> &wt) {
    // create only a single 1D vector
    vector<int> next(w+1, 0);

    // calculate solutions and store them in previously created vector
    for(int j=n-1; j>=0; --j) {
        for(int i=w; i>=0; --i) {
            int include = 0;
            if(wt[j] <= i)
                include = val[j] + next[i - wt[j]];
            int exclude = next[i];
            next[i] = max(include, exclude);
        }
    }
    return next[w];
}

int knap_sack(int w, int n, vector<int> &values, vector<int> &weights) {
    return recursion(w, n, 0, values, weights);

    vector<vector<int>> dp(w+1, vector<int>(n+1, -1));
    return topDown(w, n, 0, values, weights, dp);

    return bottomUp(w, n, values, weights);

    return spaceOptimized(w, n, values, weights);

    return moreSpaceOptimized(w, n, values, weights);
}

int main() {

    int posts, colors;
    cout << "enter the number of [posts] and [colors] : ";
    cin >> posts >> colors;
    cout << "total no. of ways to color posts are : " << painting_fence(posts, colors) << endl;

    int w, n;
    cout << "enter the size of capacity of knapsack and size of vectors : ";
    cin >> w >> n;
    vector<int> values(n);
    for(int i=0; i<n; ++i)
        cin >> values[i];
    vector<int> weights(n);
    for(int i=0; i<n; ++i)
        cin >> weights[i];
    cout << "the maximum values that can be stored in " << w << " sized knapsack is : " << knap_sack(w, n, values, weights) << endl;


    return 0;
}