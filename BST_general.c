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
 * \brief Search node
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

/**
 * \brief Insert a node
 */
void insertNode(Node_t **root, int val) {
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->val = val;
    new->left = new->right = NULL;
    if (!*root) {
        *root = new;        
    }
    if (val < (*root)->val) {
        insertNode(&(*root)->left, val);
    }
    if (val > (*root)->val) {
        insertNode(&(*root)->right, val);
    }
}

/**
 * \brief Delete a node
 */
int deleteNode(Node_t **root, int val) {
    // 根結點為空，刪除節點失敗，返回0
    if (!*root) {
        return 0;
    }

    // 要刪除的值小於或大於根結點資料域的值，向左樹或右樹遞迴
    if (val < (*root)->val) {
        return deleteNode(&(*root)->left, val);
    }
    if (val > (*root)->val) {
        return deleteNode(&(*root)->right, val);
    }

    // 左樹或右樹為空樹，則刪除根結點後，另一邊的子樹成為新的根結點
    Node_t *temp = *root;
    if (!temp->left) {
        *root = temp->right;
        free(temp);
        return 1;
    }
    if (!temp->right) {
        *root = temp->left;
        free(temp);
        return 1;
    }

    // 左樹及右樹皆不為空樹，取左樹的右葉節點作為新的根結點
    Node_t *p = NULL;
    *root = temp->left;
    while ((*root)->right) {
        p = *root;
        *root = p->right;
    }
    if (p) {
        p->right = NULL;
        (*root)->left = temp->left;
    }
    (*root)->right = temp->right;
    free(temp);
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
    QNode_t *temp = q->head;
    *node = temp->node;
    q->head = temp->next;
    free(temp);
    if (!q->head) {
        q->tail = NULL;
    }
    return 1;
}

void printTree(Node_t *root, char *name) {
    printf("%s = [", name);
    if (root) {
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
        printf("\b");
    }
    printf("]\n");
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
    int nums[] = {3,1,5,4,6,7,8,1,5,4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    // Build a BST
    Node_t *root = NULL;
    for (int i = 0; i < numsSize; i++) {
        insertNode(&root, nums[i]);
    }
    printTree(root, "Original BST");

    // Search node
    int n;
    printf("Enter a num: ");
    scanf("%d", &n);
    char *s = searchNode(root, n) ? "" : "not ";
    printf("%d is %sin the BST.\n", n, s);

    // Delete node
    s = deleteNode(&root, n) ? "succeeded" : "failed";
    printf("Delete %d from BST %s.\n", n, s);
    printTree(root, "New BST");

    // Free tree
    freeTree(&root);
    printTree(root, "Freed tree");

    system("pause");
    return 0;
}
