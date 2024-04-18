#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} Node_t;

typedef struct QueueNode {
    Node_t *node;
    struct QueueNode *next;
} QNode_t;

typedef struct {
    QNode_t *head;
    QNode_t *tail;
} Queue_t;

/**
 * \brief Insert a node to BST
 */
int insertNode(Node_t **root, int val) {
    if (!*root) {
        *root = (Node_t *)malloc(sizeof(Node_t));
        (*root)->val = val;
        (*root)->left = (*root)->right = NULL;
        return 1;
    }
    if (val < (*root)->val) {
        return insertNode(&(*root)->left, val);
    }
    if (val > (*root)->val) {
        return insertNode(&(*root)->right, val);
    }
    return 0;
}

/**
 * \brief Delete a node from BST
 */
int deleteNode(Node_t **root, int val) {
    // 根結點為空，刪除節點失敗，返回0
    if (!*root) {
        return 0;
    }

    // 刪除數值小於或大於根結點資料域值，向左樹或右樹遞迴
    if (val < (*root)->val) {
        return deleteNode(&(*root)->left, val);
    }
    if (val > (*root)->val) {
        return deleteNode(&(*root)->right, val);
    }

    // 左樹或右樹為空樹，刪除根結點並把另一邊的子樹遞補至根結點
    Node_t *ret = *root;
    if (!ret->left) {
        *root = ret->right;
        free(ret);
        return 1;
    }
    if (!ret->right) {
        *root = ret->left;
        free(ret);
        return 1;
    }

    // 左右子樹皆不為空樹，取左子樹的右葉節點作為新的根結點
    Node_t *pre = NULL;
    *root = ret->left;
    while ((*root)->right) {
        pre = *root;
        *root = pre->right;
    }
    if (pre) {
        pre->right = NULL;
        (*root)->left = ret->left;
    }
    (*root)->right = ret->right;
    free(ret);
    return 1;
}

/**
 * \brief Search node in BST
 */
int searchNode(Node_t *root, int val) {
    if (!root) {
        return 0;
    }
    if (val < root->val) {
        return searchNode(root->left, val);
    }
    if (val > root->val) {
        return searchNode(root->right, val);
    }
    return 1;
}

int enqueue(Queue_t *q, Node_t *node) {
    QNode_t *new = (QNode_t *)malloc(sizeof(QNode_t));
    if (!new) {
        return 0;
    }
    new->node = node;
    new->next = NULL;
    if (q->head) {
        q->tail->next = new;
        q->tail = new;
    } else {
        q->head = q->tail = new;
    }
    return 1;
}

int dequeue(Queue_t *q, Node_t **node) {
    if (!q->head) {
        return 0;
    }
    QNode_t *ret = q->head;
    *node = ret->node;
    q->head = ret->next;
    free(ret);
    if (!q->head) {
        q->tail = NULL;
    }
    return 1;
}

void printTree(Node_t *root, char *name) {
    printf("%s = [", name);
    Queue_t q = {NULL, NULL};
    enqueue(&q, root);
    Node_t *node;
    while (dequeue(&q, &node)) {
        if (node) {
            printf("%d,", node->val);
            enqueue(&q, node->left);
            enqueue(&q, node->right);
        } else {
            printf("null,");
        }
    }
    printf("\b]\n");
}

void freeTree(Node_t **root) {
    if (*root) {
        freeTree(&(*root)->left);
        freeTree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}

int main() {
    int nums[] = {5,3,8,1,2,4,6,9};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    // Build BST
    Node_t *root = NULL;
    for (int i = 0; i < numsSize; i++) {
        insertNode(&root, nums[i]);
    }
    printTree(root, "Original BST");

    int val;
    printf("Enter a value to be deleted: ");
    scanf("%d", &val);

    // Search node
    char *s = searchNode(root, val) ? "" : "not ";
    printf("%d is %sin the BST.\n", val, s);

    // Delete node
    s = deleteNode(&root, val) ? "succeeded" : "failed";
    printf("Delete %d in BST %s.\n", val, s);
    printTree(root, "New BST");

    // Free free
    freeTree(&root);

    system("pause");
    return 0;
}
