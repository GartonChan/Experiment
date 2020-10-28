#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char const *argv[])
{
    char *str;
    str = (char *)malloc(sizeof(char) * 100);
    printf("输入数据（字符串表示法）建立二叉树\n");
    scanf("%s", str);
    BTNode *b;
    CreateBTree(b, str);
    printf("输出二叉树：");
    DisplayBTNode(b);
    printf("\n");
    printf("先序遍历:");
    preOrder(b);
    printf("\n");
    printf("中序遍历:");
    inOrder(b);
    printf("\n");
    printf("后序遍历:");
    postOrder(b);
    printf("\n");
    printf("深度Depth:%d\n", BTNodeDepth(b));
    printf("最大元的数据为:%c\n", findMax(b));
    printf("最小元的数据为:%c\n", findMin(b));
    return 0;
}

void CreateBTree(BTNode *&b, char *str)
{
    BTNode *Stack[MaxSize];  // 用栈保存创建二叉树时的双亲结点
    int top = -1;  // 栈Stack的栈顶指针
    BTNode *p = NULL;  // 结点指针， 指向
    int k; // 用于判断下一个结点是左孩子还是右孩子结点， 1为左， 2为右
    int index = 0;  // 扫描字符串的下标位置
    char ch;
    // 初始化
    ch = str[index];  // ch为第一个字符
    b = NULL;         // 树指针为空 
    while (ch != '\0'){
        switch (ch){
        case '(':        // 遇到'('表明下一结点为左孩子结点
            k = 1;  
            top++;   // 前一结点作为双亲结点入栈
            Stack[top] = p;
            break;
        case ',':        // 遇到','表明下一结点为右孩子结点
            k = 2;  
            break;
        case ')':        // 遇到')'表明当前栈顶的双亲结点的左右孩子结点构造完毕
            top--;    // 当前栈顶的双亲结点出栈  
            break;
        default:         // 其他字符时， 默认其为创建结点的data域内容
            p = (BTNode *)malloc(sizeof(BTNode));
            p->data = ch;
            p->lchild = p->rchild = NULL;  // 左右孩子结点指针初始化
            if (b == NULL)  // 树为空时， 令其为根结点
                b = p;
            else{
                switch (k){
                case 1:
                    Stack[top]->lchild = p;
                    break;
                case 2:
                    Stack[top]->rchild = p;
                    break;
                }
            }
        }
        // 当前字符处理完成，处理后一个字符
        index++;
        ch = str[index];   
    }
}

/* 返回指向当前结点的左孩子结点的指针 */
BTNode *lchildNode(BTNode *p)
{
    return p->lchild;
}

/* 返回指向当前结点的右孩子结点的指针 */
BTNode *rchildNode(BTNode *p)
{
    return p->rchild;
}

/* 打印输出二叉树字符串 */
void DisplayBTNode(BTNode *b)
{
    if (b != NULL){  // 树为空则无输出
        printf("%c", b->data);
        if (b->lchild != NULL || b->rchild != NULL){
            printf("(");
            DisplayBTNode(b->lchild);
            if(b->rchild != NULL)
                printf(",");
            DisplayBTNode(b->rchild);
            printf(")");
        }
    }
}

/* 求二叉树中某结点的深度 */
int BTNodeDepth(BTNode *b)
{
    int lchildDepth, rchildDepth;
    if (b == NULL)  // 树为空返回0
        return 0;
    else {
        lchildDepth = BTNodeDepth(b->lchild);
        rchildDepth = BTNodeDepth(b->rchild);
        return (lchildDepth>rchildDepth? lchildDepth+1: rchildDepth+1);
    }
}

/* 二叉树的前序遍历递归算法 */
void preOrder(BTNode *b)
{
    if (b != NULL){
        printf("%c", b->data);
        preOrder(b->lchild);
        preOrder(b->rchild);
    }
}

/* 二叉树的中序遍历递归算法 */
void inOrder(BTNode *b)
{
    if (b != NULL){
        inOrder(b->lchild);
        printf("%c", b->data);
        inOrder(b->rchild);
    }
}

/* 二叉树的后序遍历递归算法 */
void postOrder(BTNode *b)
{
    if (b != NULL){
        postOrder(b->lchild);
        postOrder(b->rchild);
        printf("%c", b->data);
    }
}

ElemType findMax(BTNode *b)
{
    static ElemType max = 0;
    if (b != NULL){
        if(b->data > max)
            max = b->data;
        findMax(b->lchild);
        findMax(b->rchild);
    }
    return max;
}

ElemType findMin(BTNode *b)
{
    static ElemType min = 127;
    if (b != NULL){
        if(b->data < min)
            min = b->data;
        findMin(b->lchild);
        findMin(b->rchild);
    }
    return min;
}