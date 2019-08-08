// C program to Implement Threaded Binary Tree Algorithm.
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

// 线索存储标志位
// Link(0)   表示指向左右孩子的指针
// Thread(1) 表示指向前驱后继的线索
typedef enum {
    LINK,
    THREAD
} PointerTag;

typedef struct ThreadedBinaryNode {
    ElemType data;
    struct ThreadedBinaryNode *lChild, *rChild;
    PointerTag lTag, rTag;
} ThreadedBinaryNode, *ThreadedBinaryTree;

// 全局变量，始终指向刚刚访问过的结点
ThreadedBinaryTree pre;

// 根据前序遍历的方式来创建二叉树
void constructBinaryTreeFromPreOrder(ThreadedBinaryTree *tree) {
    char c;
    scanf("%c", &c);
    if ('_' == c) {
        *tree = NULL;
    } else {
        *tree = (ThreadedBinaryNode *) malloc(sizeof(ThreadedBinaryNode));
        (*tree)->data = c;
        (*tree)->lTag = LINK;
        (*tree)->rTag = LINK;
        constructBinaryTreeFromPreOrder(&(*tree)->lChild);
        constructBinaryTreeFromPreOrder(&(*tree)->rChild);
    }
}

// 中序遍历线索化
void inOrderThreading(ThreadedBinaryTree tree) {
    if (tree) {
        // 递归左孩子线索化
        inOrderThreading(tree->lChild);

        // 如果该结点没有左孩子，设置 lTag 为 THREAD，并把 lChild 指向刚刚访问的结点
        if (!tree->lChild) {
            tree->lTag = THREAD;
            tree->lChild = pre;
        }
        // 如果 pre 结点无右孩子，说明 pre 的后继应该为 tree
        // 设置 pre 的 rTag 为 THREAD，并将 rChild 指向 tree 作为 pre 的后继
        if (!pre->rChild) {
            pre->rTag = THREAD;
            pre->rChild = tree;
        }
        // 将当前结点 tree 赋给 pre
        pre = tree;

        // 递归右孩子线索化
        inOrderThreading(tree->rChild);
    }
}

void initInOrderThreading(ThreadedBinaryTree *p, ThreadedBinaryTree T) {
    // 指向根结点
    *p = (ThreadedBinaryNode *) malloc(sizeof(ThreadedBinaryNode));
    (*p)->lTag = LINK;
    (*p)->rTag = THREAD;
    (*p)->rChild = *p;
    // 空二叉树，p 的 lChild 指向自己本身
    if (!T) {
        (*p)->lChild = *p;
    } else {
        // 如果不是空二叉树，p 的 lChild 指向 T
        (*p)->lChild = T;
        // 将 p 赋值给 pre
        pre = *p;
        // 中序遍历线索化
        inOrderThreading(T);
        // 最后遍历的结点指向根结点
        pre->rChild = *p;
        pre->lTag = THREAD;
        // 根结点的后继指向最后遍历的结点
        (*p)->rChild = pre;
    }
}

int main() {
    ThreadedBinaryTree T = NULL;
    ThreadedBinaryTree P = NULL;
    // "ABDH__I__EJ___CF__G__"
    printf("请输入 'ABDH__I__EJ___CF__G__'\n");
    printf("\n");
    constructBinaryTreeFromPreOrder(&T);
    initInOrderThreading(&P, T);
    return 0;
}