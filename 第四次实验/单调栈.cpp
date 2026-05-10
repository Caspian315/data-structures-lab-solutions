#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

    int monotonicStack(vector<int>& heights) {
        int n = heights.size();
        int maxVal = 0; 
        
        stack<int> s1;
        vector<int> nextMinIndex(n);
        stack<int> s2;
        vector<int> lastMinIndex(n);
        
        for(int i = n - 1; i >= 0; --i) {
            while(!s1.empty() && heights[s1.top()] >= heights[i]) {
                s1.pop();
            }
            nextMinIndex[i] = s1.empty() ? n : s1.top();
            s1.push(i);    
        }
        

        for(int i = 0; i < n; ++i) { 
            while(!s2.empty() && heights[s2.top()] >= heights[i]) {
                s2.pop();
            }

            lastMinIndex[i] = s2.empty() ? -1 : s2.top();
            s2.push(i);
        }
    
        for(int i = 0; i < n; ++i) {
            int width = nextMinIndex[i] - lastMinIndex[i] - 1;
            int tempArea = heights[i] * width;
            maxVal = max(tempArea, maxVal);
        }
        
        return maxVal;
    }


void solve(){
	int n;cin >> n;
	vector<int> heights(n);
	for(int i = 0;i < n; ++i){
		cin >> heights[i];
	}	

	int res = monotonicStack(heights);
	cout << "The result is " << res << '\n';
}

int main()
{
	//输入重定向
	FILE* instream;
	instream = freopen("input.txt", "r", stdin);

	int count = 0, n = 0, k = 0;		//定义测试样例个数，数列长度，窗口大小

	if(scanf("%d", &count)!=1)			//输入测试样例组数
		return 1;

	for (int i = 0; i < count; i++)		//测试count组测试样例
	{
		solve();
	}

	fclose(instream);
	return 0;
}

