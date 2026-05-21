#include<iostream>
#include <fstream>
using namespace std;

void solve(){
    int m,n;cin >> m >> n;
    int resIdx =  0;
    while(true){
        int rem = n % 3;
        int nextIdx = resIdx * 3 + rem + 1;
        
        if(nextIdx >= m){
            cout << resIdx << '\n';
            break;
        }
        
        resIdx = nextIdx;
        n /= 3;
    }   

}

    int main()
{
	// 输入重定向
	ifstream instream("input.txt");

	if (!instream.is_open())
	{
		cout << "open file failed" << endl;
		return 1;
	}

	cin.rdbuf(instream.rdbuf());

	int T = 0;        // 定义测试用例数量

	if (!(cin >> T))  // 输入测试样例数量
		return 1;

	for (int i = 0; i < T; i++)      // 测试 T 组测试样例
	{
        solve();
	}

	return 0;
}
