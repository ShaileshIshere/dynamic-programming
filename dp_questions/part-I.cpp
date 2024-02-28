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

// Minimum ASCII Delete Sum for Two Strings - LC(712)
// recursive solution
int recursion(string &s1, string &s2, int i, int j) {
    int cost = 0;
    // base case 
    if(i == s1.size() || j == s2.size()){
        for(int x=i; x<s1.size(); ++x)
            cost += s1[x];
        for(int x=j; x<s2.size(); ++x)
            cost += s2[x];
    }
    
    // recursion
    else if(s1[i] == s2[j])
        cost += recursion(s1, s2, i+1, j+1);
    else {
        int cost_1 = s1[i] + recursion(s1, s2, i+1, j);
        int cost_2 = s2[j] + recursion(s1, s2, i, j+1);
        cost = min(cost_1, cost_2);
    }
    return cost;
}
// memoization solution
int memoization(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
    int cost = 0;
    // base case 
    if(i == s1.size() || j == s2.size()){
        for(int x=i; x<s1.size(); ++x)
            cost += s1[x];
        for(int x=j; x<s2.size(); ++x)
            cost += s2[x];
    }

    // memoization
    else if(dp[i][j] != -1)
        return dp[i][j];
    
    // recursion
    else if(s1[i] == s2[j])
        cost += memoization(s1, s2, i+1, j+1, dp);
    else {
        int cost_1 = s1[i] + memoization(s1, s2, i+1, j, dp);
        int cost_2 = s2[j] + memoization(s1, s2, i, j+1, dp);
        cost = min(cost_1, cost_2);
    }
    dp[i][j] = cost;
    return dp[i][j];
}
// tabulation solution
int tabulation(string &s1, string &s2) {
    vector<vector<int>> dp(s1.size()+1, vector<int>(s2.size()+1, 0));

    // solving first base case 
    for(int row = s1.size()-1; row >= 0; --row)
        dp[row][s2.size()] = s1[row] + dp[row+1][s2.size()];
    for(int col = s2.size()-1; col >= 0; --col)
        dp[s1.size()][col] = s2[col] + dp[s1.size()][col+1];

    // tabulation
    for(int i=s1.size()-1; i>=0; --i) {
        for(int j=s2.size()-1; j>=0; --j) {
            int cost = 0;
            if(s1[i] == s2[j])
                cost += dp[i+1][j+1];
            else {
                int cost_1 = s1[i] + dp[i+1][j];
                int cost_2 = s2[j] + dp[i][j+1];
                cost = min(cost_1, cost_2);
            }
            dp[i][j] = cost;
        }
    }
    return dp[0][0];
}
int minimumDeleteSum(string s1, string s2) {
    return recursion(s1, s2, 0, 0);

    vector<vector<int>> dp(s1.size()+1, vector<int>(s2.size()+1, -1));
    return memoization(s1, s2, 0, 0, dp);

    return tabulation(s1, s2);
}

// Longest Palindromic Substring - LC(5)
// int maxLen = 1, start = 0;
// recursive solution
bool recursion(string &s, int i, int j) {
    // base case
    if(i >= j)
        return true;
    
    // recursion
    bool flag = false;
    if(s[i] == s[j])
        flag = recursion(s, i+1, j-1);
    if(flag) {
        int currLen = j - i + 1;
        if(currLen > maxLen) {
            maxLen = currLen;
            start = i;
        }
    }
    return flag;
}
// memoization solution
bool memoization(string &s, int i, int j, vector<vector<int>> &dp) {
    // base case
    if(i >= j)
        return true;

    // memoization
    if(dp[i][j] != -1)
        return dp[i][j];
    
    // recursion
    bool flag = false;
    if(s[i] == s[j])
        flag = memoization(s, i+1, j-1, dp);
    if(flag) {
        int currLen = j - i + 1;
        if(currLen > maxLen) {
            maxLen = currLen;
            start = i;
        }
    }
    dp[i][j] = flag;
    return dp[i][j];
}
// tabulation solution
string tabulation(string &s) {
    // created a 2D vector, also solved the base case
    vector<vector<int>> dp(s.size()+1, vector<int>(s.size()+1, 1));

    // tabulation
    for(int i=s.size()-1; i>=0; --i) {
        dp[i][i] = 1;
        for(int j=0; j<=s.size()-1; ++j) {
            bool flag = false;
            if(s[i] == s[j])
                flag = dp[i+1][j-1];
            if(flag) {
                int currLen = j - i + 1;
                if(currLen > maxLen) {
                    maxLen = currLen;
                    start = i;
                }
            }
            dp[i][j] = flag;
        }
    }
    return s.substr(start, maxLen);
}
string longestPalindrome(string s) {
    int n = s.size();
    vector<vector<int>> dp(s.size()+1, vector<int>(s.size()+1, -1));
    for(int i=0; i<n; ++i) {
        for(int j=i; j<n; ++j)
            bool t = memoization(s, i, j, dp);
    }
    return s.substr(start, maxLen);
}

// Distinct Subsequences - LC(115)
// recursive solution
int recursion(string &s, string &t, int i, int j) {
    // base case
    if(j == t.length())
        return 1;
    if(i == s.length())
        return 0;

    // recursion
    int ans = 0;
    if(s[i] == t[j])
        ans += recursion(s, t, i+1, j+1);
    ans += recursion(s, t, i+1, j);
    return ans;
}
// memoization solution
int memoization(string &s, string &t, int i, int j, vector<vector<int>> &dp) {
    // base case
    if(j == t.length())
        return 1;
    if(i == s.length())
        return 0;

    // memoization
    if(dp[i][j] != -1)
        return dp[i][j];

    // recursion
    int ans = 0;
    if(s[i] == t[j])
        ans += memoization(s, t, i+1, j+1, dp);
    ans += memoization(s, t, i+1, j, dp);
    dp[i][j] = ans;
    return dp[i][j];
}
// tabulation solution
int tabulation(string &s, string &t) {
    int n=s.length(), m=t.length();
    vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
    
    // base case / first case
    for(int col=0; col<=m; ++col)
        dp[n][col] = 0;
    for(int row=0; row<=n; ++row)
        dp[row][m] = 1;

    // tabulation
    for(int i=n-1; i>=0; --i) {
        for(int j=m-1; j>=0; --j) {
            long long int ans = 0;
            if(s[i] == t[j])
                ans += dp[i+1][j+1];
            ans += dp[i+1][j];
            dp[i][j] = ans;
        }
    }
    return dp[0][0];
}
int numDistinct(string s, string t) {
    return recursion(s, t, 0, 0);

    vector<vector<int>> dp(s.length()+1, vector<int>(t.length()+1, -1));
    return memoization(s, t, 0, 0, dp);

    return tabulation(s, t);
}

// word break I - LC(139)
bool check(vector<string> &wordDict, string &s) {
    for(auto i:wordDict)
        if(s == i) return true;
    return false;
}

// recursive solution
bool recursion(string &s, vector<string> &wordDict, int start) {
    // base case
    if(start == s.size())
        return true;
    
    // recursion
    bool flag = 0;
    string word = "";
    for(int i=start; i<s.size(); ++i) {
        word += s[i];
        if(check(wordDict, word))
            flag = flag || recursion(s, wordDict, i+1);
    }
    return flag;
}

// memoization solution
bool memoization(string &s, vector<string> &wordDict, int start, vector<int> &dp) {
    // base case
    if(start == s.size())
        return true;

    // memoization
    if(dp[start] != -1)
        return dp[start];
    
    // recursion
    bool flag = 0;
    string word = "";
    for(int i=start; i<s.size(); ++i) {
        word += s[i];
        if(check(wordDict, word))
            flag = flag || memoization(s, wordDict, i+1, dp);
    }
    return dp[start] = flag;
}

// tabulation solution
bool tabulation(string s, vector<string>& wordDict) {
    // base case solved
    vector<int> dp(s.size()+1, 1);

    // tabulation
    for(int start = s.size()-1; start >= 0; --start) {
        bool flag = 0;
        string word = "";
        for(int i=start; i<s.size(); ++i) {
            word += s[i];
            if(check(wordDict, word))
                flag = flag || dp[i+1];
        }
        dp[start] = flag;
    }
    return dp[0];
}
bool wordBreak(string &s, vector<string> &wordDict) {
    return recursion(s, wordDict, 0);

    vector<int> dp(s.size()+1, -1);
    return memoization(s, wordDict, 0, dp); 

    return tabulation(s, wordDict);
}

// word break II - LC(140)
// recursive solution
vector<string> recursion(string &s, unordered_map<string, bool> &dict, int i) {
    // base case
    if(i == s.size())
        return {""};
    
    // recursion
    vector<string> ans;
    string word;
    for(int j=i; j<s.size(); ++j) {
        word.push_back(s[j]);
        // word didn't found in dictionary
        if(dict.find(word) == dict.end())
            continue;
        // word found in dictionary
        auto right = recursion(s, dict, j+1);
        for(auto rightPart : right) {
            string endPart;
            if(rightPart.size() > 0)
                endPart = " " + rightPart;
            ans.push_back(word + endPart);
        }
    }
    return ans;
}

// memoization solution
unordered_map<int, vector<string>> dp;
vector<string> memoization(string &s, unordered_map<string, bool> &dict, int i) {
    // base case
    if(i == s.size())
        return {""};

    // memoization
    if(dp.find(i) != dp.end())
        return dp[i];
    
    // recursion
    vector<string> ans;
    string word;
    for(int j=i; j<s.size(); ++j) {
        word.push_back(s[j]);
        // word didn't found in dictionary
        if(dict.find(word) == dict.end())
            continue;
        // word found in dictionary
        auto right = memoization(s, dict, j+1);
        for(auto rightPart : right) {
            string endPart;
            if(rightPart.size() > 0)
                endPart = " " + rightPart;
            ans.push_back(word + endPart);
        }
    }
    return dp[i] = ans;
}
vector<string> wordBreak(string s, vector<string>& wordDict) {
    unordered_map<string, bool> dict;
    for(auto word : wordDict)
        dict[word] = 1;
    
    return recursion(s, dict, 0);

    return memoization(s, dict, 0);
}

// game stone II - LC(1140)
// recursive solution
int recursion(vector<int> &piles, int i, int M, bool alice) {
    // base case
    if(i == piles.size())
        return 0;

    // recursion
    int ans = alice ? INT_MIN : INT_MAX;
    int total = 0;
    for(int X=1; X<=2*M; ++X){
        if(i+X-1 >= piles.size())
            break;
        total += piles[i+X-1];
        if(alice)
            ans = max(ans, total + recursion(piles, i+X, max(X, M), !alice));
        else 
        // taking min so that it'll give alice's ans rather than bob's
            ans = min(ans, recursion(piles, i+X, max(X, M), !alice));
    }
    return ans;
}
// memoization solution
int memoization(vector<int> &piles, int i, int M, bool alice, vector<vector<vector<int>>> &dp) {
    // base case
    if(i == piles.size())
        return 0;

    // memoization
    if(dp[i][M][alice] != -1)
        return dp[i][M][alice];

    // recursion
    int ans = alice ? INT_MIN : INT_MAX;
    int total = 0;
    for(int X=1; X<=2*M; ++X){
        if(i+X-1 >= piles.size())
            break;
        total += piles[i+X-1];
        if(alice)
            ans = max(ans, total + memoization(piles, i+X, max(X, M), !alice, dp));
        else 
            ans = min(ans, memoization(piles, i+X, max(X, M), !alice, dp));
    }
    return dp[i][M][alice] = ans;
}
// tabulation solution
int tabulation(vector<int> &piles) {
    vector<vector<vector<int>>> dp(piles.size()+1, vector<vector<int>>(piles.size()+1, vector<int>(2, 0)));

    // tabulation
    for(int i=piles.size()-1; i>=0; --i) {
        for(int M=piles.size(); M>=1; --M) {
            for(int alice=0; alice<=1; ++alice) {
                int ans = alice ? INT_MIN : INT_MAX;
                int total = 0;
                for(int X=1; X<=2*M; ++X){
                    if(i+X-1 >= piles.size())
                        break;
                    total += piles[i+X-1];
                    if(alice)
                        ans = max(ans, total + dp[i+X][max(X, M)][!alice]);
                    else 
                        ans = min(ans, dp[i+X][max(X, M)][!alice]);
                }
                dp[i][M][alice] = ans;
            }
        }
    }
    return dp[0][1][1];
}
int stoneGameII(vector<int>& piles) {
    return recursion(piles, 0, 1, true);

    vector<vector<vector<int>>> dp(piles.size()+1, vector<vector<int>>(piles.size()+1, vector<int>(2, -1)));
    return memoization(piles, 0, 1, true, dp);

    return tabulation(piles);
}

// stone game III - LC(1406)
// recursive solution
int recursion(vector<int> &sv, int i) {
    // base case
    if(i == sv.size())
        return 0;

    // recursion
    int ans = INT_MIN, total=0;
    for(int X=1; X<=3; ++X) {
        if(i+X-1 >= sv.size())
            break;
        total += sv[i+X-1];
        ans = max(ans, total - recursion(sv, i+X));
    }
    return ans;
}
// memoization solution
int memoization(vector<int> &sv, int i, vector<int> &dp) {
    // base case
    if(i == sv.size())
        return 0;

    // memoization
    if(dp[i] != -1)
        return dp[i];

    // recursion
    int ans = INT_MIN, total=0;
    for(int X=1; X<=3; ++X) {
        if(i+X-1 >= sv.size())
            break;
        total += sv[i+X-1];
        ans = max(ans, total - memoization(sv, i+X, dp));
    }
    return dp[i] = ans;
}
// tabulation solution
int tabulation(vector<int> &sv) {
    vector<int> dp(sv.size()+1, 0);

    // tabulation
    for(int i=sv.size()-1; i>=0; --i) {
        int ans = INT_MIN, total=0;
        for(int X=1; X<=3; ++X) {
            if(i+X-1 >= sv.size())
                break;
            total += sv[i+X-1];
            ans = max(ans, total - dp[i+X]);
        }
        dp[i] = ans;
    }
    return dp[0];
}
string stoneGameIII(vector<int>& stoneValue) {
    // int ans = recursion(stoneValue, 0);

    // vector<int> dp(stoneValue.size()+1, -1);
    // int ans = memoization(stoneValue, 0, dp);

    int ans = tabulation(stoneValue);

    if(ans > 0) return "Alice";
    if(ans < 0) return "Bob";
    return "Tie";
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

    string s1, s2;
    cout << "enter two strings : ";
    cin >> s1 >> s2;
    cout << "lowest ASCII sum of deleted characters : " << minimumDeleteSum(s1, s2) << endl;

    string s;
    cout << "enter string : ";
    cin >> s;
    cout << "here's your longest palindromic substring : " << tabulation(s) << endl;

    string s, t;
    cout << "enter string [s] or [t] : ";
    cin >> s >> t;
    cout << " number of distinct subsequences of [s] which equals [t] : " << numDistinct(s, t) << endl;

    string s;
    int n;
    cout << "enter the string [s] : ";
    cin >> s;
    cout << "how many string you want to add : ";
    cin >> n;
    vector<string> wordDict(n);
    for(int i=0; i<n; ++i)
        cin >> wordDict[i];
    if(wordBreak(s, wordDict))
        cout << "true" << endl;
    else    
        cout << "false" << endl;

    string s;
    int n;
    cout << "enter the string [s] : ";
    cin >> s;
    cout << "how many string you want to add : ";
    cin >> n;
    vector<string> wordDict(n);
    for(int i=0; i<n; ++i)
        cin >> wordDict[i];
    vector<string> ans = wordBreak(s, wordDict);
    cout << "[ ";
    for(auto a : ans)
        cout << a << " , ";
    cout << "]" << endl;

    int n;
    cout << "enter the size of piles : ";
    cin >> n;
    vector<int> piles(n);
    for(int i=0; i<n; ++i)
        cin >> piles[i];
    cout << "maximum number of stones Alice can get : " << stoneGameII(piles) << endl;

    int n;
    cout << "enter the size of vector : ";
    cin >> n;
    vector<int> stoneValue(n);
    for(int i=0; i<n; ++i)
        cin >> stoneValue[i];
    cout << stoneGameIII(stoneValue) << endl;
     
    return 0;
}