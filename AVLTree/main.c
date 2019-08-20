// C program to implement AVL Tree(Self-Balancing Binary Search Tree)
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLTreeNode {
    int data;
    // 高度
    int height;
    // 左孩子
    struct AVLTreeNode *left;
    // 右孩子
    struct AVLTreeNode *right;
} AVLTreeNode, *AVLTree;

// get the height of the tree
int height(AVLTree tree) {
    if (!tree) {
        return 0;
    }
    return tree->height;
}

// get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Get Balance factor of node N
int getBalance(AVLTree tree) {
    if (!tree) {
        return 0;
    }
    return height(tree->left) - height(tree->right);
}

// 右旋
/*
T1, T2, T3 and T4 are subtrees.
        tree                                    y
        / \                                   /   \
       y   T4      Right Rotate (tree)      x     tree
      / \          - - - - - - - - ->      /  \    /  \
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
 */
AVLTreeNode *rightRotate(AVLTree *tree) {
    // y 指向 tree 的左子树根结点
    AVLTree y = (*tree)->left;
    // T3 指向 y 的右子树根结点
    AVLTree T3 = y->right;
    // 旋转
    y->right = *tree;
    (*tree)->left = T3;
    // 更新高度
    (*tree)->height = max(height((*tree)->left), height((*tree)->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    // 返回新的根结点
    return y;
}

// 左旋
/*
T1, T2, T3 and T4 are subtrees.
     tree                                y
     /  \                              /   \
    T1   y      Left Rotate(tree)    tree    x
        /  \    - - - - - - - ->     / \    / \
       T2   x                       T1  T2 T3  T4
           / \
         T3  T4
 */
AVLTreeNode *leftRotate(AVLTree *tree) {
    // y 指向 tree 的右子树根结点
    AVLTree y = (*tree)->right;
    // T2 指向 y 的左子树根结点
    AVLTree T2 = y->left;
    // 旋转
    y->left = *tree;
    (*tree)->right = T2;
    // 更新高度
    (*tree)->height = max(height((*tree)->left), height((*tree)->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    // 返回新的根结点
    return y;
}

// 创建结点
AVLTreeNode *createNewNode(int data) {
    AVLTree newNode = (AVLTreeNode *) malloc(sizeof(AVLTreeNode));
    if (!newNode) {
        printf(stderr, "Out of memory!!! (create_node)\n");
        exit(1);
    }
    newNode->data = data;
    // new node is initially added at leaf
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 根据 key 值查找树
AVLTreeNode *searchNode(AVLTree tree, int key) {
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

AVLTreeNode *insertNode(AVLTree *tree, int data) {
    // 1. 执行正常的 BST 插入
    // 直接插入新结点 返回新结点
    if (!*tree) {
        return createNewNode(data);
    } else if (searchNode(*tree, data)) {
        // 树不为空，检查树中是否存在值与 data 相同的结点，若存在返回结点
        return *tree;
    } else if (data < (*tree)->data) {
        // 树不为空，且树中不存在值与 data 相同的结点，且 data 比当前结点的值要小，则递归其左子树
        (*tree)->left = insertNode(&(*tree)->left, data);
    } else {
        // 树不为空，且树中不存在值与 data 相同的结点，且 data 比当前结点的值要大，则递归其右子树
        (*tree)->right = insertNode(&(*tree)->right, data);
    }
    // 2. 更新祖先结点的高度
    (*tree)->height = max(height((*tree)->left), height((*tree)->right)) + 1;
    // 3. 获取祖先结点的平衡因子，检查此节点是否不平衡
    int balance = getBalance(*tree);
    // 如果这个结点是不平衡，那么判断 LL(右旋)，LR(先左旋，再右旋)，RR(左旋)，RL（先右旋，再左旋）这四种情况
    // a. Left Left Case
    if (balance > 1 && data < (*tree)->left->data) {
        return rightRotate(&(*tree));
    }
    // b. Left Right Case
    if (balance > 1 && data > (*tree)->left->data) {
        // left rotate left subtree
        (*tree)->left = leftRotate(&(*tree)->left);
        // then right rotate
        return rightRotate(&(*tree));
    }
    // c. Right Right Case
    if (balance < -1 && data > (*tree)->right->data) {
        return leftRotate(&(*tree));
    }
    // d. Right Left Case
    if (balance < -1 && data < (*tree)->right->data) {
        // right rotate right subtree
        (*tree)->right = rightRotate(&(*tree)->right);
        // then left rotate
        return leftRotate(&(*tree));
    }
    // 如果都没有返回未修改的结点指针
    return *tree;
}

// 访问二叉树结点的具体操作
void printDataAndLevel(int data, int level) {
    printf("%d at %d level\n", data, level);
}

void inOrderTraversal(AVLTree tree, int level) {
    if (!tree) {
        return;
    }
    inOrderTraversal(tree->left, level + 1);
    printDataAndLevel(tree->data, level);
    inOrderTraversal(tree->right, level + 1);
}

// 创建二叉搜索树
void createAVLTree(AVLTree *tree, int arr[], int n) {
    *tree = NULL;
    int i = 0;
    while (i < n) {
        *tree = insertNode(&(*tree), arr[i]);
        i++;
    }
}

/* Drier program to test above function*/
int main() {
    int arr[] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int level = 1;
    AVLTree tree;

/* The constructed AVL Tree would be
                        4
                     /     \
                   2        7
                  / \      / \
                 1    3   6   9
                         /   / \
                        5   8  10
*/
    createAVLTree(&tree, arr, n);
    printf("In-Order traversal of the constructed AVL tree is \n");
    inOrderTraversal(tree, level);
    // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
    return 0;
}