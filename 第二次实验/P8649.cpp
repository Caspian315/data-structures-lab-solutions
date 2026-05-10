#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 3;
vector<ll> preSum(N, 0); 

unordered_map<int, int> remCount;

int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    
    int n, k;
    if(!(cin >> n >> k)) return 0;
    
    remCount[0]++; 
    
    ll ans = 0; 
    
    for(int i = 1; i <= n; ++i){
        ll val;
        cin >> val;
        preSum[i] = preSum[i - 1] + val; 

        int rem = preSum[i] % k;
        
        ans += remCount[rem];
        remCount[rem]++;
    }

    cout << ans << '\n';
    return 0;
}