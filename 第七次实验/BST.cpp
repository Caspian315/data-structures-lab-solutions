#include<iostream>

using namespace std;


struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int _val) : val(_val),left(nullptr),right(nullptr){}
};

class bst{
private:


    TreeNode* insertHelper(TreeNode* node,int val){
        if(node == nullptr){    
            return new TreeNode(val);
        }

        if(val < node->val){
            node->left = insertHelper(node->left,val);
        }else if(val > node->val){
            node->right = insertHelper(node->right,val);
        }
        //val == node->val的情况不用管，使bst中不存在重复元素

        return node;
    }

    TreeNode* findMin(TreeNode* node){
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }

    TreeNode* removeHelper(TreeNode* node,int val){
        //base case
        if(node == nullptr){
            return node;
        }

        if(val < node->val){
            node->left = removeHelper(node->left,val);
        }else if(val > node->val){
            node->right = removeHelper(node->right,val);
        }else{
            //case 1 为叶子节点或者只有左孩子或右孩子
            if(node->left == nullptr){
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            if(node->right == nullptr){
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            //case 2 左孩子右孩子都有
            TreeNode* minNode = findMin(node->right);
            node->val = minNode->val;
            node->right = removeHelper(node->right,minNode->val);

        }
       return node;
}

    void traverseRemove(TreeNode* node){
        if(node == nullptr){
            return;
        }
        
        traverseRemove(node->left);
        traverseRemove(node->right);

        delete node;
    }

public:
    TreeNode* root;

    bst(int val){
        root = new TreeNode(val);
    }

    void push(int val){
        root = insertHelper(root,val);
    }

    void remove(int val){
        root = removeHelper(root,val);
    }

    ~bst(){
        traverseRemove(root);
    }
    
};

void traversePre(TreeNode* node){
    if(node == nullptr)return;

    cout << node->val << ' ';

    traversePre(node->left);
    traversePre(node->right);

}

void traverseIn(TreeNode* node){
    if(node == nullptr)return;

    traverseIn(node->left);
    cout << node->val << ' ';
    traverseIn(node->right);

}


void solve(){
    int val;
    // 先读取第一个值作为根节点
    if(cin >> val){
        bst myBst(val);
        // 已知样例后面还有 10 个数字
        for(int i = 0; i < 10; ++i){
            cin >> val;
            myBst.push(val);
        }

        traversePre(myBst.root);
        cout << '\n';

        traverseIn(myBst.root);
        cout << '\n';
    }
}


int main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    solve();
    return 0;
}