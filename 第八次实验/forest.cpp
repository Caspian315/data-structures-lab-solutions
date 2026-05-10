#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX_QUEUE_SIZE 200
typedef int ElemType;
//数据类型
//定义树节点，采用左孩子/右兄弟链式存储
typedef struct Node
{
	int data;
	struct Node* leftChild;
	struct Node* rightSibling;
} Node, * Tree;


//先序创建树
int CreateForest(Tree* T)
{
	ElemType ch;
	ElemType temp;
	scanf_s("%d", &ch);
	temp = getchar();
	if (ch == -1)
		* T = NULL;
	else {
		*T = (Tree)malloc(sizeof(Node));
		if (!(*T))
			exit(-1);
		(*T)->data = ch;
		printf("输入%d的子树：", ch);
		CreateForest(&(*T)->leftChild);
		printf("输入%d的兄弟：", ch);
		CreateForest(&(*T)->rightSibling);
	}return 1;
}

//先根遍历森林
void TraverseForest(Tree T)
{
	if (T == NULL)return;
	printf("%d ", T->data);
	TraverseForest(T->leftChild);
	TraverseForest(T->rightSibling);
}

//后根遍历森林
void PostOrderForest(Tree T)
{
	if (T == NULL)return;
	PostOrderForest(T->leftChild);
    printf("%d ",T->data);
    PostOrderForest(T->rightSibling);
}

// 设计递归算法，计算森林的叶子结点的个数
int CountLeaves(Tree root)
{   
    int cnt = 0;
    if (!root) // 如果树为空则返回0
	{
		return 0;
	}
	else
	{
        if(root->leftChild == NULL){
            cnt++;
        }else{
            cnt += CountLeaves(root->leftChild);
        }
        cnt += CountLeaves(root->rightSibling);
	}
    return cnt;
    
}


// 设计递归算法，计算森林的高度
int height(Tree root)
{
	int hchild = 0, hsibling = 0;
	if (root == NULL) return -1;//树的高度从0开始算，所以这里改成0
	
	    hchild = height(root->leftChild) + 1;
        hsibling = height(root->rightSibling);
        
    return (hchild > hsibling ? hchild : hsibling);
}


//主函数
int main(void)
{
	Tree T;

	int deepth, num = 0;
	printf("请输入第一个结点的值,-1表示没有对应子树:\n");
	CreateForest(&T);
	printf("先序遍历森林:\n");
	TraverseForest(T);
	printf("\n");
	printf("后序遍历森林:\n");
	PostOrderForest(T);
	printf("\n");

	num = CountLeaves(T);
	printf("森林的叶子结点个数为:%d", num);
	printf("\n");

	deepth = height(T);
	printf("森林的高度为:%d", deepth);
	printf("\n");

	return 0;
}