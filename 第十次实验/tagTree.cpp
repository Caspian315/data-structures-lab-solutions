#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

struct Node{
    int val;
    int ltag;
    int rtag;

    Node() : val(0), ltag(0), rtag(0) {}
    Node(int _val,int _ltag,int _rtag) : val(_val), ltag(_ltag), rtag(_rtag){}
};

class TreeNode{
public:
    int val;
    TreeNode* leftChild;
    TreeNode* rightSibling;

    TreeNode() : val(0), leftChild(nullptr),rightSibling(nullptr){}


};

TreeNode* buildTree(vector<Node> tagTree,int cnt){
        stack<TreeNode*> stk;
        TreeNode* root = new TreeNode();
        TreeNode* pointer = root;

        for(int i = 0;i < cnt - 1; ++i){
            pointer->val = tagTree[i].val;
            if(tagTree[i].rtag == 0){
                stk.push(pointer);
            }else{
                pointer->rightSibling = nullptr;
            }

            TreeNode* temppointer = new TreeNode(); 
            if(tagTree[i].ltag == 0){
                pointer->leftChild = temppointer;
            }else{
                pointer->leftChild = nullptr;
                pointer = stk.top();
                stk.pop();
                pointer->rightSibling = temppointer;
            }
            pointer = temppointer;
        }
        //处理最后一个节点
        pointer->val = tagTree[cnt - 1].val;
        pointer->leftChild = nullptr;
        pointer->rightSibling = nullptr;

        return root;
    } 

void levelOrder(TreeNode* root){
    if(root == nullptr){
        return;
    }

    queue<TreeNode*> q;
    q.push(root);
    bool isFirst = true;

    while(!q.empty()){
        TreeNode* cur = q.front();
        q.pop();

        if(!isFirst)cout << ' ';
        isFirst = false;
        cout << cur->val;
        TreeNode* child = cur->leftChild;
        while(child != nullptr){
            q.push(child);
            child = child->rightSibling;
        }
    }

    cout << '\n';
}


void solve(){
    int n;cin >> n;
    vector<Node> tagTree(n);
    for(int i = 0;i < n; ++i){
        int v,l,r;cin >> v >> l >> r;
        tagTree[i].val = v;
        tagTree[i].ltag = l;
        tagTree[i].rtag = r;
    }

    TreeNode* root = buildTree(tagTree,n);

    levelOrder(root);
}

int main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
