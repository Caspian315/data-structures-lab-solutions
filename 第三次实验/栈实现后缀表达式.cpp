#include<iostream>
#include<string>
#include<sstream>
using namespace std;

template<typename E>
class Stack{
public:
    void clear():
    bool push(const E& e);
    bool pop();
    bool peek();
    bool isEmpty();
    bool isFull();
};

template<typename E>
class arrStack : public Stack<E>{|
private:
    int mSize;
    int top;
    E *st;//底层数组
public:
    arrStack(int size){
        this->mSize = size;
        this->top = -1;
        this->st = new E[mSize];
    }    

    arrStack(){
        top = -1;
    }

    ~arrStack(){
        delete[] st;
    }

    void clear(){
        top = -1;
    }

    void push(const E& e){
        if(top == mSize - 1){
            cout << "栈满溢出" <<'\n';
        }else{
            st[++top] = e;
        }
    }

    E pop(){
            E item = st[top];
            st[top] = E();
            top--;
            return item;
    }

    E peek(){
        return st[top];
    }
};

arrStack<int> stk;

void solve(){   
    string input;
    getline(cin,input);

    string token;
    stringstream ss(input);

    bool isEnd = false;
    while(getline(ss,token,' ')){
        //遇到#终止
        if(token.back() == '#'){
            token.pop_back();
            isEnd = true;
        }

        if(!token.empty()){
            if(token[0] >= '0' && token[0] <= '9'){
                int num = stoi(token);
                stk.push(num);
            }else{
                //取出栈顶的两个数字参与运算
                int right = stk.peek();
                stk.pop();
                int left = stk.peek();
                stk.pop();

                int res = 0;
                if(token == "+"){
                    res = left + right;
                    stk.push(res);
                    continue;
                }else if(token == "-"){
                    res = left - right;
                    stk.push(res);
                    continue;
                }else if(token == "*"){
                    res = left * right;
                    stk.push(res);
                    continue;
                }else{
                    res = left / right;
                    stk.push(res);
                    continue;
                }   
            } 
        }

        if(isEnd)break;
    }
    cout << stk.peek() <<'\n';
    stk.pop();
}

int main(){
    solve();
    return 0;
}

