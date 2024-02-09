#include<bits/stdc++.h>

using namespace std;

// longest common subsequence
// recursive approach
int recursion(string &a, int i, string &b, int j) {
    // base case
    if(i == a.length() || j == b.length())
        return 0;
    // recursion
    int ans=0;
    if(a[i] == b[j])
        ans = 1 + recursion(a, i+1, b, j+1);
    else 
        ans = max(recursion(a, i+1, b, j), recursion(a, i, b, j+1));
    return ans;
}

// experiment purpose
void print_2D_dp(vector<vector<int>> &dp) {
    cout << "recursive soln : " << endl;
    for(auto row : dp) {
        cout << "[ ";
        for(int col : row)
            cout << col << " ";
        cout << "]" << endl;
    }
}

// top down approach
int topDown(string &a, int i, string &b, int j, vector<vector<int>> &dp) {
    // base case
    if(i == a.length() || j == b.length())
        return 0;

    // check if any solution is already present in [dp]
    if(dp[i][j] != -1)
        return dp[i][j];
    // recursion
    if(a[i] == b[j])
        dp[i][j] = 1 + topDown(a, i+1, b, j+1, dp);
    else 
        dp[i][j] = max(topDown(a, i+1, b, j, dp), topDown(a, i, b, j+1, dp));
    // print_2D_dp(dp);
    return dp[i][j];
}

// bottom up approach
int bottomUp(string &a, string &b) {
    int n=a.length(), m=b.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

    // manually solved the base solution/base case
    for(int i=0; i<=m; ++i)
        dp[n][i] = 0;
    for(int i=0; i<=n; ++i)
        dp[i][m] = 0;

    // solving the remaining solutions
    for(int i=n-1; i>=0; --i) {
        for(int j=m-1; j>=0; --j) {
            int ans=0;
            if(a[i] == b[j])
                ans = 1 + dp[i+1][j+1];
            else 
                ans = max(dp[i+1][j], dp[i][j+1]);
            dp[i][j] = ans;
        }
    }
    // print_2D_dp(dp);
    return dp[0][0];
}

// space optimized
int spaceOptimized(string &a, string &b) {
    // create two vectors on the base of which we've to calculate final ans
    vector<int> curr(a.length()+1, 0);
    vector<int> next(a.length()+1, 0);

    // we're calculating ans col wise that's why we've swaped variables
    for(int j=b.length()-1; j>=0; --j) { 
        for(int i=a.length()-1; i>=0; --i) {
            int ans=0;
            if(a[i] == b[j])
                ans = 1 + next[i+1];
            else 
                ans = max(next[i], curr[i+1]);
            curr[i] = ans;
        }
        // update the next vector
        next = curr;
    }
    return next[0];
}

int longestSubsequence(string &text1, string &text2) {
    return recursion(text1, 0, text2, 0);

    vector<vector<int>> dp(text1.length(), vector<int>(text2.length(), -1));
    return topDown(text1, 0, text2, 0, dp);

    return bottomUp(text1, text2);

    return spaceOptimized(text1, text2);
}

// longest palindromic subsequence
/*the solution of this problem is entirely based on above problem
the extra work we've done here is [reversed] the given string so 
that we can obtain the longest subsequence also that string should
be a palindrome, apply by yourself*/
int longest_palindromic_subsequence(string &s) {
    string s1 = s;
    reverse(s.begin(), s.end());
    string s2 = s;
    return spaceOptimized(s1, s2);
}

// edit distance
// recursion solution
int recursion(string &a, int i, string &b, int j) {
    if(i == a.length())
        return b.length()-j;
    if(j == b.length())
        return a.length()-i;
    int ans=0;
    if(a[i] == b[j])
        ans = recursion(a, i+1, b, j+1);
    else {
        int replace = 1 + recursion(a, i+1, b, j+1);
        int insert = 1 + recursion(a, i, b, j+1);
        int remove = 1 + recursion(a, i+1, b, j);
        ans = min(replace, min(insert, remove));
    }
    return ans;
}

int edit_distance(string &word1, string &word2) {
    return recursion(word1, 0, word2, 0);
}

int main() {

    // string text1, text2;
    // cout << "enter two distinct strings : ";
    // cin >> text1 >> text2;
    // cout << "length of longest common subsequence : " << longestSubsequence(text1, text2) << endl;

    // string s;
    // cout << "enter string : ";
    // cin >> s;
    // cout << "length of longest palindromic subsequence : " << longest_palindromic_subsequence(s) << endl;
     
    return 0;
}