//  C program to implement binary search tree
#include <stdio.h>
#include <stdlib.h>

# define TRUE 1
# define FALSE 0

typedef int Status;

typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode, *BinaryTree;

BinaryTreeNode *createBinaryTreeNode(int value) {
    BinaryTree newNode = (BinaryTree) malloc(sizeof(BinaryTreeNode));
    if (!newNode) {
        printf(stderr, "Out of memory!!! (create_node)\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BinaryTreeNode *searchNode(BinaryTree tree, int key) {
    // 树空返回 NULL
    if (!tree) {
        return NULL;
    } else if (key == tree->data) {
        return tree;
    } else if (key < tree->data) {
        return searchNode(tree->left, key);
    } else {
        return searchNode(tree->right, key);
    }
}

// insert a new node into the BST
Status insertNode(BinaryTree *tree, int value) {
    // 空树 直接插入新结点返回成功
    if (!*tree) {
        // 将创建的新结点赋给当前结点
        *tree = createBinaryTreeNode(value);
        return TRUE;
    } else if (searchNode(*tree, value)) {
        // 树不为空，检查树中是否存在值与 value 相同的结点，若存在返回插入失败
        return FALSE;
    } else if (value < (*tree)->data) {
        // 树不为空，且树中不存在值与 value 相同的结点，且 value 比当前结点的值要小，则递归其左子树
        return insertNode(&(*tree)->left, value);
    } else {
        // 树不为空，且树中不存在值与 value 相同的结点，且 value 比当前结点的值要大，则递归其右子树
        return insertNode(&(*tree)->right, value);
    }
}

// 创建二叉搜索树
void createBinarySearchTree(BinaryTree *tree, int arr[], int n) {
    *tree = NULL;
    int i = 0;
    while (i < n) {
        insertNode(&(*tree), arr[i]);
        i++;
    }
}
// function to find the minimum value in a node
BinaryTreeNode *findMinimumValueNode(BinaryTree tree) {
    if (!tree) {
        return NULL;
    } else if (tree->left) {
        return findMinimumValueNode(tree->left);
    }
    return tree;
}

BinaryTreeNode *deleteNode(BinaryTree *tree, int key) {
    // 树为空，返回 NULL
    if (!*tree) {
        return NULL;
    }
    // 树不为空，且待删除结点的值 key 小于当前结点的值，则递归其左子树
    if (key < (*tree)->data) {
        (*tree)->left = deleteNode(&(*tree)->left, key);
    }
    // 树不为空，且待删除结点的值 key 大于当前结点的值，则递归其右子树
    else if (key > (*tree)->data) {
        (*tree)->right= deleteNode(&(*tree)->right, key);
    }
    // 树不为空，且待删除结点的值 key 等于当前结点的值，进行删除操作
    else {
        // 1. 待删除结点没有孩子，直接删除结点
        if (!(*tree)->left && !(*tree)->right) {
            free(*tree);
            return NULL;
        }
        // 2. 待删除结点只有一个孩子，将孩子替换待删除结点
        else if (!(*tree)->left || !(*tree)->right) {
            BinaryTree temp;
            // 待删除结点只有右孩子，没有左孩子，将右孩子替换待删除结点
            if (!(*tree)->left) {
                temp = (*tree)->right;
            }
            // 待删除结点只有左孩子，没有右孩子，将左孩子替换待删除结点
            else {
                temp = (*tree)->left;
            }
            free(*tree);
            return temp;
        }
        // 3. 待删除结点既有左孩子又有右孩子，找到待删除结点的直接后继（即右孩子中最小（最左）的结点）或者直接前驱（即左孩子孩子中最大（最右）的结点）
        //    用该结点（直接后继或直接前驱）来替换待删除结点，然后删除该结点（直接后继或直接前驱）。
        else {
            // 获得直接后继结点
            BinaryTree successor = findMinimumValueNode((*tree)->right);
            // 将直接后继结点的值赋给待删除结点的值
            (*tree)->data = successor->data;
            // 删除直接后继结点
            (*tree)->right = deleteNode(&(*tree)->right, successor->data);
        }
    }
    return *tree;
}

// 访问二叉树结点的具体操作
void printDataAndLevel(int data, int level) {
    printf("%d at %d level\n", data, level);
}

void inOrderTraversal(BinaryTree tree, int level) {
    if (!tree) {
        return;
    }
    inOrderTraversal(tree->left, level + 1);
    printDataAndLevel(tree->data, level);
    inOrderTraversal(tree->right, level + 1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int level = 1;
    int key = 3;
    BinaryTree tree;

    createBinarySearchTree(&tree, arr, n);
    printf("In-Order traversal of the binary search tree \n");
    inOrderTraversal(tree, level);

    printf("\nDelete key : %d\n", key);
    tree = deleteNode(&tree, key);
    printf("In-Order traversal of the modified tree \n");
    inOrderTraversal(tree, level);
    return 0;
}