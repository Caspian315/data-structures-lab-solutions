#include<iostream>
#include<utility>
using namespace std;

template <class T>
class arrList {
private:
    T* aList;
    int maxSize;
    int curLen;
    int position;
public:
    arrList(const int size) {
        maxSize = size;
        aList = new T[maxSize];
        curLen = position = 0;
    }
    

    ~arrList() {
        delete[] aList;
    }

    void clear() {
        delete[] aList;
        curLen = position = 0;
        aList = new T[maxSize];
    }
    
    int length() {
        return curLen;
    }
    
    bool append(const T value) {
        if (curLen >= maxSize) {
            return false; // 数组已满
        }
        aList[curLen] = value;
        curLen++;
        return true;
    }

    bool insert(const int p, const T value);
    void setValue(const int p, T value);
    
    T getValue(int p); 
    
    void del(int length, int p);
    int getPos(T value);
    void del(int p);
};

template<class T>
void arrList<T>::del(int len, int p) {
    for (int i = p; i < len - 1; i++) {
        aList[i] = aList[i + 1];
    }
    curLen--; 
}

template<class T>
T arrList<T>::getValue(int p) { 
    return aList[p];
}

template<class T>
int arrList<T>::getPos(T value) {
    for (int i = 0; i < curLen; i++) { 
        if (value == aList[i]) {
            return i;
        }
    }
    return -1;
}

template<class T>
void arrList<T>::setValue(const int p, T value) {
    aList[p] = value;
}

arrList<pair<int, int>>* addArrList(arrList<pair<int, int>>& list1, arrList<pair<int, int>>& list2) {
    int maxResSize = list1.length() + list2.length();
    
    arrList<pair<int, int>>* resultList = new arrList<pair<int, int>>(maxResSize);
    
    int i = 0, j = 0;
    while (i < list1.length() && j < list2.length()) {
        pair<int,int> p1 = list1.getValue(i);
        pair<int,int> p2 = list2.getValue(j);

        if (p1.second > p2.second) {
            resultList->append(p1);
            i++;
        } else if (p1.second < p2.second) {
            resultList->append(p2);
            j++;
        } else {
            // 指数相等时系数相加
            int sumCoef = p1.first + p2.first;
            if (sumCoef != 0) {
                resultList->append({sumCoef, p1.second});
            }
            i++;
            j++;
        }
    }

    // 处理剩余项
    while (i < list1.length()) {
        resultList->append(list1.getValue(i));
        i++;
    }
    while (j < list2.length()) {
        resultList->append(list2.getValue(j));
        j++;
    }

    return resultList;
}

int main(){
    arrList<pair<int,int>> list1(100);
    arrList<pair<int,int>> list2(100);

    int a, b;
    // 读取第一个多项式
    while (cin >> a >> b) {
        list1.append({a, b});
        if (cin.peek() == '\n') {
            cin.get();
            break;
        }
    }
    // 读取第二个多项式
    while (cin >> a >> b) {
        list2.append({a, b});
        while(cin.peek() == ' ') cin.get(); 
        if (cin.peek() == '\n') {
            cin.get();
            break;
        }
    }

    arrList<pair<int, int>>* result = addArrList(list1, list2);

    int resLen = result->length();
    for (int i = 0; i < resLen; i++) {
        pair<int, int> p = result->getValue(i);
        cout << p.first << ' ' << p.second;
        if (i != resLen - 1) {
            cout << ' ';
        }
    }
    cout << endl;

    delete result;

    return 0;
}