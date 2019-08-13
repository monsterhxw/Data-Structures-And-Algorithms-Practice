//  C program to implement binary search tree
#include <stdio.h>
#include <stdlib.h>

# define TRUE 1
# define FALSE 0

typedef int Status;

typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode *lChild;
    struct BinaryTreeNode *rChild;
} BinaryTreeNode, *BinaryTree;

Status searchBST(BinaryTree tree, int key, BinaryTree parent, BinaryTree *target) {
    //如果 tree 为空，说明查找失败，令 target 指针指向查找过程中最后一个叶子结点，并返回查找失败的信息
    if (!tree) {
        *target = parent;
        return FALSE;
    } else if (key == tree->data) {
        //如果相等，令 target 指针指向该关键字，并返回查找成功信息
        *target = tree;
        return TRUE;
    } else if (key < tree->data) {
        //如果 key 值比 tree 根结点的值小，查找其左子树
        return searchBST(tree->lChild, key, tree, target);
    } else {
        //如果 key 值比 tree 根结点的值小，查找其右子树
        return searchBST(tree->rChild, key, tree, target);
    }
}

Status insertBST(BinaryTree *tree, int key) {
    BinaryTree p;
    // 如果查找不成功，需做插入操作
    if (!searchBST(*tree, key, NULL, p)) {
        BinaryTree temp = (BinaryTree) malloc(sizeof(BinaryTree));
        temp->data = key;
        temp->lChild = NULL;
        temp->rChild = NULL;
        // 如果 p 为NULL，说明该二叉排序树为空树，此时插入的结点为整棵树的根结点
        if (!p) {
            *tree = temp;
        } else if (key < p->data) {
            //如果 p 不为 NULL，则 p 指向的为查找失败的最后一个叶子结点，只需要通过比较 p 和 e 的值确定 s 到底是 p 的左孩子还是右孩子
            p->lChild = temp;
        } else {
            p->rChild = temp;
        }
        return TRUE;
    }
    return FALSE;
}

Status delete(BinaryTree *target) {
    BinaryTree p, temp;
    // 情况 1，结点 p 本身为叶子结点，直接删除即可
    if (!(*target)->lChild && !(*target)->rChild) {
        *target = NULL;
    } else if ()
}

Status deleteBST(BinaryTree *tree, int key) {
    // 如果 tree 为空，说明不存在关键字等于 key 的数据元素
    if (!*tree) {
        return FALSE;
    }
    if (key == (*tree)->data) {
        delete(tree);
        return TRUE;
    } else if (key < (*tree)->data) {
        return deleteBST(&(*tree)->lChild, key);
    } else {
        return deleteBST(&(*tree)->rChild, key);
    }
}

int main() {
    printf("Hello, World!\n");
    return 0;
}