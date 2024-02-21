#include<bits/stdc++.h>

using namespace std;

// perfect squares - LC(279)
// recursive solution
int recursion(int n) {
    // base case
    if(n <= 0)
        return 0;

    // recursion
    int it = 1, ans = INT_MAX, end = sqrt(n);
    while(it <= end) {
        int perfectSq = it * it;
        int numOfPerfectSq = 1 + recursion(n - perfectSq);
        if(numOfPerfectSq < ans)
            ans = numOfPerfectSq;
        ++it;
    }
    return ans;
}
// memoization solution
int memoization(int n, vector<int> &dp) {
    // base case
    if(n <= 0)
        return 0;

    // memoization
    if(dp[n] != -1)
        return dp[n];

    // recursion
    int it = 1, ans = INT_MAX, end = sqrt(n);
    while(it <= end) {
        int perfectSq = it * it;
        int numOfPerfectSq = 1 + memoization(n - perfectSq, dp);
        if(numOfPerfectSq < ans)
            ans = numOfPerfectSq;
        ++it;
    }
    dp[n] = ans;
    return dp[n];
}
// tabulation
int tabulation(int N) {
    vector<int> dp(N+1, 0);

    // tabulation
    for(int n=1; n<=N; ++n) {
        int it = 1, ans = INT_MAX, end = sqrt(n);
        while(it <= end) {
            int perfectSq = it * it;
            int numOfPerfectSq = 1 + dp[n - perfectSq];
            if(numOfPerfectSq < ans)
                ans = numOfPerfectSq;
            ++it;
        }
        dp[n] = ans;
    }
    return dp[N];
}
int numSquares(int n) {
    return recursion(n);

    vector<int> dp(n+1, -1);
    return memoization(n, dp);

    return tabulation(n);
}

// minimum cost for tickets - LC(983)
// recursive solution
int recursion(vector<int>& days, vector<int>& costs, int i) {
    // base case
    if(i >= days.size()) 
        return 0;

    // recursion
    // here we're buying ticket for [1] day
    int cost_1 = costs[0] + recursion(days, costs, i+1);
    // here we're buying ticket for [7] days
    int PED = days[i] + 7;
    int j = i;
    while(j < days.size() && days[j] < PED) 
        j++;
    int cost_7 = costs[1] + recursion(days, costs, j);
    // here we're buying ticket for [15] days
    PED = days[i] + 30;
    j = i;
    while(j < days.size() && days[j] < PED)
        j++;
    int cost_30 = costs[2] + recursion(days, costs, j);

    return min(cost_1, min(cost_7, cost_30));
}
// memoization solution
int memoization(vector<int>& days, vector<int>& costs, int i, vector<int> &dp) {
    // base case
    if(i >= days.size()) 
        return 0;

    // memoization
    if(dp[i] != -1)
        return dp[i];

    // recursion
    int cost_1 = costs[0] + memoization(days, costs, i+1, dp);
    int PED = days[i] + 7;
    int j = i;
    while(j < days.size() && days[j] < PED) 
        j++;
    int cost_7 = costs[1] + memoization(days, costs, j, dp);
    PED = days[i] + 30;
    j = i;
    while(j < days.size() && days[j] < PED)
        j++;
    int cost_30 = costs[2] + memoization(days, costs, j, dp);

    dp[i] = min(cost_1, min(cost_7, cost_30));
    return dp[i];
}
// tabulation solution
int tabulation(vector<int> &days, vector<int> &costs) {
    // created a 1D vector, also solved the first base case
    vector<int> dp(days.size()+1, 0);

    // tabulation
    for(int i = days.size()-1; i>=0; --i) {
        int cost_1 = costs[0] + dp[i+1];
        int PED = days[i] + 7;
        int j = i;
        while(j < days.size() && days[j] < PED) 
            j++;
        int cost_7 = costs[1] + dp[j];
        PED = days[i] + 30;
        j = i;
        while(j < days.size() && days[j] < PED)
            j++;
        int cost_30 = costs[2] + dp[j];
        dp[i] = min(cost_1, min(cost_7, cost_30));
    }
    return dp[0];
}
int minCostTickets(vector<int> &days, vector<int> &costs) {
    return recursion(days, costs, 0);

    vector<int> dp(days.size()+1, -1);
    return memoization(days, costs, 0, dp);

    return tabulation(days, costs);
}

int main() {

    int n;
    cout << "enter the value of [n] : ";
    cin >> n;
    cout << "least no. to make [n] : " << numSquares(n) << endl;

    int n;
    cout << "enter the size for [days] : ";
    cin >> n;
    vector<int> days(n);
    cout << "enter days : ";
    for(int i=0; i<n; ++i)
        cin >> days[i];
    vector<int> costs(3);
    cout << "enter costs : ";
    for(int i=0; i<3; ++i)
        cin >> costs[i];
    cout << "min cost of ticket to travel on given days : " << minCostTickets(days, costs) << endl;
     
    return 0;
}