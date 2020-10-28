#define MaxSize 30  // 假设结点至多30个

typedef struct tree_node* PtrNode;  // 定义二叉树结点指针类型为PtrNode
typedef char ElemType;  // 假定元素类型为int型

typedef struct tree_node
{
    ElemType data;
    PtrNode lchild, rchild;
}BTNode;

void CreateBTree(BTNode *&b, char *str);  // 根据二叉树括号表示法字符串生成对应的链式存储结构
// BTNode *FindNode(BTNode *b, ElemType x);  // 查找二叉树b中data域为x的结点，返回指向该结点的指针
BTNode *lchildNode(BTNode *p);  // 返回指向该结点的左孩子结点的指针
BTNode *lchildNode(BTNode *p);  // 返回指向该结点的右孩子结点的指针
int BTNodeDepth(BTNode *b);     // 返回二叉树（任一结点）的深度
void DisplayBTNode(BTNode *b);  // 打印二叉树

void preOrder(BTNode *b);    // 递归先序遍历
void inOrder(BTNode *b);     // 递归中序遍历
void postOrder(BTNode *b);   // 递归后序遍历

ElemType findMax(BTNode *b);
ElemType findMin(BTNode *b);