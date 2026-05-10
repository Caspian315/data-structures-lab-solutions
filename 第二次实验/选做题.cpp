 #include<iostream>
 using namespace std;
 
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

  //我的思路与课上讲的不太相同：
  //分别将两个链表反转(用分治的思路)，然后再连接
  //灵感来自https://leetcode.cn/problems/reverse-linked-list/

  ListNode* reverseList(ListNode* head){
    //base case
    if(head == nullptr || head->next == nullptr){
        return head;
    }

    ListNode* last = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;

    return last;
  }

  ListNode* mergeTwoList(ListNode* head1,ListNode* head2){
    //虚拟头节点
    ListNode* dummy = new ListNode(0);
    ListNode* p1 = head1;
    ListNode* p2 = head2;
    ListNode* p = dummy;
    while(p1 != nullptr && p2 != nullptr){
      if(p1->val > p2->val){
        p->next = p1;
        p = p->next;
        p1 = p1->next;
      }else{
        p->next = p2;
        p = p->next;
        p2 = p2->next;
      }
    }

    if(p1 != nullptr){
      p->next = p1;
    }else{
      p->next = p2;
    } 
    ListNode* res = dummy->next;
    delete dummy;
    return res;
  }
  
  ListNode* initList(){
    ListNode* dummy = new ListNode(0);
    ListNode* p = dummy;
    int val;
    while(cin >> val){
      ListNode* newNode = new ListNode(val);
      p->next = newNode;
      p = p->next;
      if(cin.peek() == '\n')break;
    }
    ListNode* res = dummy->next;
    delete dummy;
    return res;
  }

  int main(){
    ListNode* p1 = initList();
    ListNode* p2 = initList();
    ListNode* res1 = reverseList(p1);
    ListNode* res2 = reverseList(p2);

    ListNode* p = mergeTwoList(res1, res2);
    ListNode* p0 = p;
    while(p0 != nullptr){
      cout<< p0->val;
      if(p0->next != nullptr)cout<<' ';
    }
    cout<<endl;
  }