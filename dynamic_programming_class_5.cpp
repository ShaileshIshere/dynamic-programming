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
    // create 2 1D vectors
    vector<int> nextRow(v.size()+1, 0);
    vector<int> currRow(v.size()+1, 0);

    // insert elements in [currRow] with the help of [nextRow]
    for(int curr = v.size()-1; curr >= 0; --curr) {
        for(int prev = curr-1; prev >= -1; --prev) {
            int include=0; 
            if(prev == -1 || v[curr] > v[prev])
                include = 1 + nextRow[curr+1];
            int exclude = nextRow[prev+1];
            currRow[prev+1] = max(include, exclude);
        }
        nextRow = currRow;
    }
    return nextRow[0];
}

// more space optimized
int moreSpaceOptimized(vector<int> &v) {
    // create a 1D vector
    vector<int> temp(v.size()+1, 0);

    // insert values in this vector
    for(int curr = v.size()-1; curr >= 0; --curr) {
        for(int prev = curr-1; prev >= -1; --prev) {
            int include=0; 
            if(prev == -1 || v[curr] > v[prev])
                include = 1 + temp[curr+1];
            int exclude = temp[prev+1];
            temp[prev+1] = max(include, exclude);
        }
    }
    return temp[0];
}

// optimal approach => using binary search
int binarySearch(vector<int> &v) {
    vector<int> ans;
    ans.push_back(v[0]);
    for(int i=1; i<v.size(); ++i) {
        if(v[i] > ans.back())
            ans.push_back(v[i]);
        else {
            int index = lower_bound(ans.begin(), ans.end(), v[i]) - ans.begin();
            ans[index] = v[i];
        }
    }
    return ans.size();
}

int longest_inc_subseq(vector<int> &v) {
    return recursion(v, -1, 0);

    vector<vector<int>> dp(v.size()+1, vector<int>(v.size()+1, -1));
    return topDown(v, -1, 0, dp);

    return bottomUp(v);

    return spaceOptimized(v);

    return moreSpaceOptimized(v);

    return binarySearch(v);
}

// maximum height by stacking cuboids
bool check(vector<int> &curr, vector<int> &prev) {
    if(prev[0] <= curr[0] && prev[1] <= curr[1] && prev[2] <= curr[2])
        return true;
    else
        return false;
}
int solveUsingTab(vector<vector<int>> &v) {
    // create a 1D vector
    vector<int> temp(v.size()+1, 0);

    // insert values in this vector
    for(int curr = v.size()-1; curr >= 0; --curr) {
        for(int prev = curr-1; prev >= -1; --prev) {
            int include=0; 
            if(prev == -1 || (check(v[curr], v[prev])))
                include = v[curr][2] + temp[curr+1];
            int exclude = temp[prev+1];
            temp[prev+1] = max(include, exclude);
        }
    }
    return temp[0];
}
int maxHeight(vector<vector<int>> &cuboids) {
    for(auto &cuboid : cuboids)
        sort(cuboid.begin(), cuboid.end());
    sort(cuboids.begin(), cuboids.end());
    return solveUsingTab(cuboids);
}

// russian doll envelopes
static bool comp(vector<int> &a, vector<int> &b) {
    if(a[0] == b[0])
        return a[1] > b[1];
    return a[0] < b[0];
}
int maxEnvelopes(vector<vector<int>> &envelopes) {
    sort(envelopes.begin(), envelopes.end(), comp);
    if(envelopes.size() == 0)
        return 0;
    vector<int> ans;
    ans.push_back(envelopes[0][1]);
    for(int i=1; i<envelopes.size(); ++i) {
        if(envelopes[i][1] > ans.back())
            ans.push_back(envelopes[i][1]);
        else {
            int index = lower_bound(ans.begin(), ans.end(), envelopes[i][1]) - ans.begin();
            // cout << "index : " << index << endl;
            ans[index] = envelopes[i][1];
        }
    }
    // for(auto a : ans)
    //     cout << a << " ";
    return ans.size();
}

int main() {

    int n;
    cout << "enter size : ";
    cin >> n;
    vector<int> nums(n);
    for(int i=0; i<n; ++i)
        cin >> nums[i];
    cout << "longest increasing subsequence : " << longest_inc_subseq(nums) << endl;

    int n, m=3;
    cout << "ener the no. of cuboids : ";
    cin >> n;
    vector<vector<int>> cuboids(n, vector<int>(m));
    for(int i=0; i<n; ++i) {
        cout << "enter " << i+1 << " cuboid's dimension :" << endl;
        for(int j=0; j<m; ++j)
            cin >> cuboids[i][j];
    }
    cout << "maximum height by stacking cuboids : " << maxHeight(cuboids) << endl;

    int n, m=2;
    cout << "enter the no. of envelopes : ";
    cin >> n;
    vector<vector<int>> envelopes(n, vector<int>(m));
    for(int i=0; i<n; ++i) {
        cout << "enter the " << i+1 << "th envelop :" << endl;
        for(int j=0; j<m; ++j)
            cin >> envelopes[i][j];
    }
    cout << "maximum no. of envelopes we can russian doll : " << maxEnvelopes(envelopes) << endl;
     
    return 0;
}