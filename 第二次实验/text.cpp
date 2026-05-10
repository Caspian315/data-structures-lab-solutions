#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 3;
int n,k,q;
vector<int> preFix(N,0);
vector<int> nums(N,0);
vector<int> preSum(N,0);

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n >> k >> q;
    while(n--){
        int l,r;cin >> l >> r;
        preFix[l]++;
        preFix[r + 1]--;
    }

    nums[1] = preFix[1]; 
    //initial nums
    for(int i = 2;i < N ; ++i){
        nums[i] = nums[i - 1] + preFix[i];
    }

    //initial preSum
    for(int i = 1;i < N; ++i){
        preSum[i] = preSum[i - 1] + (nums[i] >= k ? 1 : 0);
    }

    while(q--){
        int a,b;cin >> a >> b;
        cout << preSum[b] - preSum[a - 1] <<'\n';
    }

    return 0;
}

