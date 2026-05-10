#include <iostream>
#include <fstream>
using namespace std;
const int N = 1e2 + 5;

void solve() {
    int m, n; cin >> m >> n;
    int a[N];
    int b[N];

    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    // 双指针
    int i = 0;
    int j = 0;
    while (i < m && j < n) {
        if (a[i] < b[j]) {  
            cout << a[i] << ' ';
            ++i;
        }
        else if (a[i] > b[j]) {  
            cout << b[j] << ' ';
            ++j;
        }
        else {  
            ++i;
            ++j;
        }
    }

    
    if (i == m) {
        for (int k = j; k < n; ++k) {
            cout << b[k] << ' ';  
        }
    }
    else if (j == n) {
        for (int k = i; k < m; ++k) {
            cout << a[k] << ' ';  
        }
    }
    cout << '\n';
}

int main()
{
    // 输入重定向
    ifstream instream("input1.txt");

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