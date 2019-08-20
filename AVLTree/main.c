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

// 查找非空的二叉搜索树中的最小 data 值的结点，需要注意的整棵树不需要搜索
AVLTreeNode *findMinimumValueNode(AVLTree tree) {
    if (!tree) {
        return NULL;
    } else if (tree->left) {
        return findMinimumValueNode(tree->left);
    }
    return tree;
}

AVLTreeNode *deleteNode(AVLTree *tree, int key) {
    // STEP 1. 进行 Binary Search Tree 删除
    // 树为空，返回 NULL
    if (!*tree) {
        return *tree;
    }
    // 树不为空，且待删除结点的值 key 小于当前结点的值，则递归其左子树
    if (key < (*tree)->data) {
        (*tree)->left = deleteNode(&(*tree)->left, key);
    }
    // 树不为空，且待删除结点的值 key 大于当前结点的值，则递归其右子树
    else if (key > (*tree)->data) {
        (*tree)->right = deleteNode(&(*tree)->right, key);
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
            AVLTree temp;
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
            /* 3. 待删除结点既有左孩子又有右孩子，找到待删除结点的直接后继（即右孩子中最小（最左）的结点）或者直接前驱（即左孩子孩子中最大（最右）的结点），用该结点（直接后继或直接前驱）来替换待删除结点，然后删除该结点（直接后继或直接前驱）。*/
        else {
            // 获得直接 in-order 后继结点(右子树最小值)
            AVLTree successor = findMinimumValueNode((*tree)->right);
            // 将直接后继结点的值赋给待删除结点的值
            (*tree)->data = successor->data;
            // 删除直接后继结点
            (*tree)->right = deleteNode(&(*tree)->right, successor->data);
        }
    }
    // STEP 2. 更新当前节点的高度
    (*tree)->height = max(height((*tree)->left), height((*tree)->right)) + 1;
    // STEP 3. 获取该节点的平衡因子(检查该节点是否不平衡)
    int balance = getBalance(*tree);
    // 如果这个结点是不平衡，那么判断 LL(右旋)，LR(先左旋，再右旋)，RR(左旋)，RL（先右旋，再左旋）这四种情况
    // a. Left Left Case
    if (balance > 1 && getBalance((*tree)->left) >= 0) {
        return rightRotate(&(*tree));
    }
    // b. Left Right Case
    if (balance > 1 && getBalance((*tree)->left) < 0) {
        // left rotate left subtree
        (*tree)->left = leftRotate((*tree)->left);
        return rightRotate(&(*tree));
    }
    // c. Right Right Case
    if (balance < -1 && getBalance((*tree)->right) <= 0) {
        return leftRotate(&(*tree));
    }
    // d. Right Left Case
    if (balance < -1 && getBalance((*tree)->right) > 0) {
        // right rotate right subtree
        (*tree)->right = rightRotate(&(*tree)->right);
        return leftRotate(&(*tree));
    }
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
    int key = 7;
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

/* The AVL Tree after deletion of 7
                        4
                     /     \
                   2        8
                  / \      / \
                 1    3   6   9
                         /     \
                        5      10
*/
    tree = deleteNode(&tree, key);
    printf("In-Order traversal after deletion of %d \n", key);
    inOrderTraversal(tree, level);
    // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 8 -> 9 -> 10
    return 0;
}