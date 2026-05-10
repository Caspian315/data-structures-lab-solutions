#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e4 + 3;
int maxNum = 0;
vector<ll> preSum(N,0); 
unordered_map<int,int> firstPositon;



int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    //intitial
    int n;cin >> n;
    firstPositon[0] = 0;
    for(int i = 1;i <= n; ++i){
        ll val;cin >> val;
        preSum[i] = preSum[i - 1] + val;

        int rem = preSum[i] % 7;
        if(!firstPositon.count(rem)){
            firstPositon[rem] = i;
        }else{
            maxNum = max(maxNum,i - firstPositon[rem]);
        }
    }

    cout << maxNum << '\n';

    return 0;
}