#include <stdio.h>
#include <stdlib.h>

#define NULL_NODE -1

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

/**
 * \brief Build tree by array
 */
Node_t *buildTree(int *nums, int numsSize) {
    if (!numsSize) {
        return NULL;
    }
    Node_t *root = (Node_t *)malloc(sizeof(Node_t)), *node;
    root->val = *nums;
    Queue_t q = {NULL, NULL};
    enqueue(&q, root);
    while (dequeue(&q, &node)) {
        if (node) {
            if (--numsSize > 0) {
                if (*++nums != NULL_NODE) {
                    node->left = (Node_t *)malloc(sizeof(Node_t));
                    node->left->val = *nums;
                } else {
                    node->left = NULL;
                }
                enqueue(&q, node->left);
            } else {
                node->left = NULL;
            }
            if (--numsSize > 0) {
                if (*++nums != NULL_NODE) {
                    node->right = (Node_t *)malloc(sizeof(Node_t));
                    node->right->val = *nums;
                } else {
                    node->right = NULL;
                }
                enqueue(&q, node->right);
            } else {
                node->right = NULL;
            }
        } else {
            numsSize -= 2;
        }
    }
    return root;
}

/**
 * \brief Print tree
 */
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

/**
 * \brief Invert tree
 */
void invertTree(Node_t *root) {
    if (root) {        
        Node_t *ret = root->left;
        root->left = root->right;
        root->right = ret;
        invertTree(root->left);
        invertTree(root->right);
    }
}

static int isSymmetricSub(Node_t *left, Node_t *right) {
    if (!left && !right) {
        return 1;
    }
    if (left && !right || !left && right) {
        return 0;
    }
    if (left->val != right->val) {
        return 0;
    }
    return isSymmetricSub(left->left, right->right) &&
           isSymmetricSub(left->right, right->left);
}

/**
 * \brief Check whether tree is symmetric
 */
int isSymmetric(Node_t *root) {
    return root ? isSymmetricSub(root->left, root->right) : 1;
}

int main() {
    struct TestCase {
        int nums[15], numsSize;
    } tc[] = {
        {.nums = {1, 2, 2, NULL_NODE, 3, 3, NULL_NODE}, .numsSize = 7},
        {.nums = {3, 5, 7, 1, NULL_NODE, 3, 4}, .numsSize = 7}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    Node_t *root;
    char *s;
    for (int i = 0; i < tcSize; i++) {
        printf("Test case %d:\n", i + 1);

        // Build tree
        root = buildTree(tc[i].nums, tc[i].numsSize);
        printTree(root, "Original tree");

        // Invert tree
        invertTree(root);
        printTree(root, "Inverted tree");

        // Check whether the tree is symmetric
        s = isSymmetric(root) ? "" : "not ";
        printf("This tree is %ssymmetric.\n\n", s);

        // Free tree
        freeTree(&root);
    }

    return 0;
}
