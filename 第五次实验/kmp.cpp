#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include<string>
#include<vector>
using namespace std;


//得到优化前的next数组
vector<int> getNext(const string& pattern){
	int n = pattern.length();
	//initial
	vector<int> next(n,-1);
	int i = 0;
	int j = -1;

	while(i < n - 1){
		if(j == -1 || pattern[i] == pattern[j]){
			i++;
			j++;
			next[i] = j;
		}else{
			j = next[j];
		}
	}

	return next;
}

//得到优化后的next数组
vector<int> getBetterNext(const string& pattern){
	int n = pattern.length();
	//initial
	vector<int> next(n,-1);
	int i = 0;
	int j = -1;
	while(i < n - 1){
		if(j == -1 || pattern[j] == pattern[i]){
			i++;
			j++;
			if(pattern[j] == pattern[i]){
				next[i] = next[j];
				//优化点：如果回退后的字符与当前字符相同，那么与text串比较时必然会再次失败，此时不妨让j再次回退
			}else{
				next[i] = j;
			}	
		}else{
			j = next[j];
		}
	}
	return next;
}

// KMP匹配，返回第一个匹配位置（从0开始），若未找到则返回-1
int kmpSearch(const string& text,const string& pattern,vector<int>& next){
	int n = text.length();
	int m = pattern.length();

	int i = 0;
	int j = 0;
	while(i < n && j < m){
		if(j == -1 || text[i] == pattern[j]){
			i++;
			j++;
		}else{
			j = next[j];
		}
	}
	
	return (j == m) ? i - m : -1;
}

void solve(){
	string text,pattern;
	cin >> text >> pattern;

	vector<int> next = getNext(pattern);
	for(int i = 0;i < next.size();++i){
		cout << next[i] << ' ';
	}cout << '\n';
	
	vector<int> betterNext = getBetterNext(pattern);
	for(int i = 0;i < betterNext.size(); ++i){
		cout << betterNext[i] << ' ';
	}cout << '\n';

	int firstIndex = kmpSearch(text,pattern,betterNext);
	cout << firstIndex << '\n';
}

int main()
{
	//输入重定向
	FILE* instream;
	instream = freopen("input.txt", "r", stdin);

	int count = 0;		//定义测试样例个数，数列长度，窗口大小

	if(scanf("%d", &count)!=1)			//输入测试样例组数
		return 1;

	for (int i = 0; i < count; i++)		//测试count组测试样例
	{
		solve();
	}

	fclose(instream);
	return 0;
}