#include <iostream>
#include <cstring>
using namespace std;

char pattern[20000002];
int prefix[20000002];
int dp[20000002];

void prefixTable(const int& len){
    int i = -1, j = 0;
    prefix[0] = -1;
    while(j < len){
        if(i == -1 || pattern[i] == pattern[j])
            prefix[++j] = ++i;
        else
            i = prefix[i];
    }
}


int main() {
    scanf("%s", pattern);
    int len = strlen(pattern);
    prefixTable(len);
    long long ans = 0;
    for(int i = 1; i <= len; i++) {
        dp[i] = 1;
    }
    for(int i = 1; i <= len; i++) {
        dp[i] = dp[prefix[i]]+1;
        ans+=dp[i];
    }
    printf("%lld\n", ans);
}