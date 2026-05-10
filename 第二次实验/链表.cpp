#include<iostream>
#include<utility>
using namespace std;

template<typename E>
class MyLinkedList{
    struct Node{
        E val;
        Node* prev;
        Node* next;

        Node(E val) : val(val), prev(nullptr),next(nullptr){}
    };

    int size;
    //虚拟头尾节点
    Node* head;
    Node* tail;

    public:
    MyLinkedList(){
        head = new Node(E());
        tail = new Node(E());
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    ~MyLinkedList(){
        Node* curr = head;
        while(curr != nullptr){
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    //增
    void addLast(E e) {
        Node* x = new Node(e);
        Node* temp = tail->prev;

        temp->next = x;
        x->prev = temp;

        x->next = tail;
        tail->prev = x;

        size++;
    }

    //查
    E get(int index) {
        Node* p = getNode(index);
        return p->val;
    }

    int getSize() const{
        return size;
    }

private:
    Node* getNode (int index) {
        //根据index判断是从head开始还是从tail开始
        if (index <= size / 2) {
            Node* p = head->next;
            for (int k = 0; k < index; ++k) {
                p = p->next;
            }
            return p; 
        }
        else {
            Node* p = tail->prev;
            for (int k = 0; k < size - index - 1; ++k) {
                p = p->prev;
            }
            return p; 
        }
    }
};


MyLinkedList<pair<int,int>> addLinkedList(MyLinkedList<pair<int,int>>& linkedList1, MyLinkedList<pair<int,int>>& linkedList2){
    MyLinkedList<pair<int,int>> resultList;
    int i = 0, j = 0; 
    
    while(i < linkedList1.getSize() && j < linkedList2.getSize()){
        pair<int,int> pair1 = linkedList1.get(i);
        pair<int,int> pair2 = linkedList2.get(j);

        if(pair1.second > pair2.second){
            resultList.addLast({pair1.first,pair1.second});
            ++i;
            continue;
        }else if(pair2.second > pair1.second){
            resultList.addLast({pair2.first,pair2.second});
            ++j;
            continue;
        }else{
            //此时指数相等
            int value = pair1.first + pair2.first;
            // 系数相加为0时，该项抵消，不加入结果链表
            if (value != 0) {
                resultList.addLast({value,pair1.second});
            }
            ++i;
            ++j;
            continue;
        }
    }   

    //最后只可能有一个多项式没有填充完毕
    if(i < linkedList1.getSize()){
        for(int k = i; k < linkedList1.getSize(); ++k){
            pair<int,int> pair1 = linkedList1.get(k);
            resultList.addLast({pair1.first,pair1.second});
        }
    }else if(j < linkedList2.getSize()){
        for(int k = j; k < linkedList2.getSize(); ++k){
            pair<int,int> pair2 = linkedList2.get(k);
            resultList.addLast({pair2.first,pair2.second});
        }
    }
    return resultList;
}   

int main(){
    MyLinkedList<pair<int,int>> linkedList1;
    MyLinkedList<pair<int,int>> linkedList2;

    MyLinkedList<pair<int,int>> resultList;
    
    //a为系数，b为指数
    int a, b;

    //读取第一个多项式
    while (cin >> a >> b) {
        linkedList1.addLast({a, b});
        
        while(cin.peek() == ' ') cin.get(); 
        
        if (cin.peek() == '\n') {
            cin.get();
            break;
        }
    }

    //读取第二个多项式
    while(cin >> a >> b){
        linkedList2.addLast({a,b});
        while(cin.peek() == ' ') cin.get();
        
        if(cin.peek() =='\n' ){
            cin.get();
            break;
        }
    }

    resultList = addLinkedList(linkedList1, linkedList2);
    int _size = resultList.getSize();
    for(int i = 0; i < _size; ++i){
        pair<int,int> resPair = resultList.get(i);
        int val1 = resPair.first;
        int val2 = resPair.second;
        // 格式为: 系数 指数
        cout << val1 << ' ' << val2;
        if (i != _size - 1) cout << ' '; // 项与项之间加空格
    }
    cout << endl;
    
    return 0;
}