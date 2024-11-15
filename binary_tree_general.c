#include <stdio.h>
#include <stdlib.h>

/**
 * Definition of a tree node.
 */
typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} Node_t;

/**
 * Definition of a queue node.
 */
typedef struct QueueNode {
    Node_t *node;
    struct QueueNode *next;
} QNode_t;

/**
 * Definition of a queue.
 */
typedef struct {
    QNode_t *head, *tail;
} Queue_t;

/**
 * \note Caller must call free() after use.
 */
Queue_t *initQueue() {
    Queue_t *q = (Queue_t *)malloc(sizeof(Queue_t));
    q->head = q->tail = NULL;
    return q;
}

void enqueue(Queue_t *q, Node_t *node) {
    QNode_t *tail = (QNode_t *)malloc(sizeof(QNode_t));
    tail->node = node;
    tail->next = NULL;
    q->tail = q->tail ? (q->tail->next = tail) : (q->head = tail);
}

int dequeue(Queue_t *q, Node_t **node) {
    if (!q->head) {
        return 0;
    }
    QNode_t *tmp = q->head;
    *node = tmp->node;
    q->head = tmp->next ? tmp->next : (q->tail = NULL);
    free(tmp);
    return 1;
}

#define NULL_NODE -1

#define ADD_NODE_MACRO(q, nums, node) if (*++nums != NULL_NODE) {              \
    node = (Node_t *)malloc(sizeof(Node_t));                                   \
    node->val = *nums;                                                         \
    enqueue(q, node);                                                          \
} else {                                                                       \
    node = NULL;                                                               \
}

/**
 * \brief Build tree by array.
 */
Node_t *buildTree(int *nums, int numsSize) {
    if (!numsSize) {
        return NULL;
    }
    Queue_t *q = initQueue();
    Node_t *root = (Node_t *)malloc(sizeof(Node_t)), *node;
    root->val = *nums;
    enqueue(q, root);
    while (--numsSize) {
        dequeue(q, &node);
        ADD_NODE_MACRO(q, nums, node->left);
        if (!--numsSize) {
            node->right = NULL;
            break;
        }
        ADD_NODE_MACRO(q, nums, node->right);
    }
    while (dequeue(q, &node)) {
        node->left = node->right = NULL;
    }
    free(q);
    return root;
}

/**
 * \brief Print tree.
 */
void printTree(Node_t *root, char *title) {
    printf("%s = [", title);
    if (root) {
        printf("%d", root->val);
        Queue_t *q = initQueue();
        enqueue(q, root->left);
        enqueue(q, root->right);
        int nullCnt = 0;
        while (dequeue(q, &root)) {
            if (!root) {
                nullCnt++;
                continue;
            }
            while (nullCnt) {
                printf(",null");
                nullCnt--;
            }
            printf(",%d", root->val);
            enqueue(q, root->left);
            enqueue(q, root->right);
        }
        free(q);
    }
    printf("]\n");
}

void freeTree(Node_t *root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/**
 * \brief Invert tree.
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
 * \brief Check whether tree is symmetric.
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
        freeTree(root);
    }

    return 0;
}
