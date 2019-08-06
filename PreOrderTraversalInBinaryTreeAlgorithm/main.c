// C program for pre-order traversal in binary tree
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lChild, *rChild;
} BiTNode, *BiTree;

// 创建一棵二叉树，约定用户遵循前序遍历的方式输入数据
void createBinaryTreeByPreOrder(BiTree *tree) {
    char c;
    scanf("%c", &c);
    if (' ' == c) {
        *tree = NULL;
    } else {
        *tree = (BiTNode *) malloc(sizeof(BiTNode));
        (*tree)->data = c;
        createBinaryTreeByPreOrder(&(*tree)->lChild);
        createBinaryTreeByPreOrder(&(*tree)->rChild);
    }
}

// 访问二叉树结点的具体操作
void printDataAndLevel(char data, int level) {
    printf("%c at  %d level\n", data, level);
}

// 前序遍历二叉树
void traverseBinaryTreeByPreOrder(BiTree tree, int level) {
    if (tree) {
        printDataAndLevel(tree->data, level);
        traverseBinaryTreeByPreOrder(tree->lChild, level + 1);
        traverseBinaryTreeByPreOrder(tree->rChild, level + 1);
    }
}

int main() {
    int level = 1;
    BiTree tree = NULL;
    // 输入 'ABD  E  CF   '
    printf("请输入 'ABD  E  CF   '\n");
    printf("\n");
    createBinaryTreeByPreOrder(&tree);
    traverseBinaryTreeByPreOrder(tree, level);
    return 0;
}