#include<bits/stdc++.h>

using namespace std;

// fibonacci number
// top down method => (recursion + memoization)
int topDown(int n, vector<int> &dp) {
    if(n == 1 || n == 0)
        return n;

    /*step 3: if a solution is already present
    in the dp array then return it from here no further processing*/ 
    if(dp[n] != -1)
        return dp[n];
    
    /*step 2: if a solution occurs first time then
    store that solution in the dp array*/
    dp[n] = topDown(n-1, dp) + topDown(n-2, dp);
    return dp[n];
}
// bottom up method => (iterative), tabulation approach
int bottomUp(int n) {
    // step 1: create a dp array/vector
    vector<int> dp(n+1, -1);
    
    /*step 2: analyse the base cases and fill them
    accordingly and manually also check the edge cases*/
    // 1st base case
    dp[0] = 0;
    /*edge case => if (n == 0) then there's only one sized vector
    so we can't insert another element in the same vector so return from here*/
    if(n == 0)
        return dp[n];
    // 2nd base case
    dp[1] = 1;

    /*step 3: fill up the remaining elements in the dp array/vector
    ab humne dp[0] or dp[1] to pehle hi fill karliya h, to hume dp[2]
    se fill kerna padega iterative way mai*/
    for(int index = 2; index <= n; ++index) 
        dp[index] = dp[index - 1] + dp[index - 2];
    return dp[n];
}
// space optimized method
int spaceOptimized(int n) {
    // not a base case, but an edge case
    if(n == 0 || n == 1)
        return n;
    /*declaration of important variables that stores the
    values of previous [2] elements which are the sum of the
    next fibonacci number, [ans] => it's a variable to store
    the answer that forms after adding [prev] and [curr] variables*/
    int prev = 0, curr = 1, ans;
    for(int index = 2; index <= n; ++index) {
        // adding [prev] and [curr] to form a fibonacci number
        ans = prev + curr;
        // update the values of [prev] and [curr]
        prev = curr;
        curr = ans;
    }
    return ans;
}
int fib(int n) {
    /*step 1: create a array/vector to store answers
    that are going to repeat in the future*/
    vector<int> dp(n+1, -1); 
    return topDown(n, dp);

    return bottomUp(n);

    return spaceOptimized(n);
}

int main() {

    int n;
    cout << "how many fibonacci number you need : ";
    cin >> n;
    cout << "here is your fibonacci series : " << "[ ";
    for(int i=0; i<n; ++i)
        cout << fib(i) << " ";
    cout << "]" << endl;

    return 0;
}