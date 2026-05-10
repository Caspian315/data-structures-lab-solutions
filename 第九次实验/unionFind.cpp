#include<iostream>
#include<vector>
using namespace std;


class UF{
private:

    int _count;//联通分量个数,初始为n
    vector<int> parent;

public:


    UF(int n){
        this->_count = n;
        parent.resize(n + 1);
        for(int i = 1;i <= n; ++i){
            parent[i] = i;//题目中n是从1开始的
        }
    }

    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);//这里用到了路径压缩，使得每一个节点的parent直接指向root，从而使find的时间复杂度降到O(1)
        }
        return parent[x];
    }   

    void connect(int a,int b){
        int rootA = find(a);
        int rootB = find(b);

        if(rootA != rootB){
            parent[rootA] = rootB;
            _count--;
        }

    }   

    bool isConnected(int a,int b){
        return find(a) == find(b);
    } 

};


int main(){
    int n,m;cin >> n >> m;
    UF uf(n);
    for(int i = 0;i < m; ++i){
        int a,b;cin >> a >> b;
        if(!uf.isConnected(a,b)){
            uf.connect(a,b);
        }
    }

    vector<vector<int>> ufs(n + 1);
    for(int i = 1;i <= n; ++i){
        int rootI = uf.find(i);
        ufs[rootI].push_back(i);
    }   

    for(int i = 1;i <= n; ++i){
        if(!ufs[i].empty()){
            for(int j = 0;j < ufs[i].size(); ++j){
                cout << ufs[i][j] <<' ';
            }
             cout << '\n';
        }

    }   


    return 0;
}