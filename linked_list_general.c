#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) do { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
} while (0)

typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node_t;

/**
 * \brief Sort list
 */
void sortList(Node_t *head) {
    if (head) {
        Node_t *cur = head->next;
        while (cur) {
            if (cur->val < head->val) {
                SWAP(cur->val, head->val);
            }
            cur = cur->next;
        }
        sortList(head->next);
    }
}

/**
 * \brief Reverse list
 */
void reverseList(Node_t **head) {
    Node_t *pre = NULL, *next;
    while (*head) {
        next = (*head)->next;
        (*head)->next = pre;
        pre = *head;
        *head = next;
    }
    *head = pre;
}

/**
 * \brief Insert a node by value
 */
void insertNodeByValue(Node_t **head, int val) {
    Node_t *pre = NULL, *next = *head;
    while (next) {
        if (next->val >= val) {
            break;
        }
        pre = next;
        next = pre->next;
    }
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->val = val;
    new->next = next;
    if (pre) {
        pre->next = new;
    } else {
        *head = new;
    }
}

/**
 * \brief Delete a node by value
 */
int deleteNodeByValue(Node_t **head, int val) {
    Node_t *pre = NULL, *cur = *head;
    while (cur) {
        if (cur->val > val) {
            return 0;
        }
        if (cur->val == val) {
            break;
        }
        pre = cur;
        cur = cur->next;
    }
    if (!cur) {
        return 0;
    }
    if (pre) {
        pre->next = cur->next;
    } else {
        *head = cur->next;
    }
    free(cur);
    return 1;
}

/**
 * \brief Insert a node by index
 */
int insertNodeByIndex(Node_t **head, int val, int index) {
    Node_t *pre = NULL, *next = *head;
    while (index--) {
        if (!(pre = next)) {
            return 0;
        }
        next = pre->next;
    }
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->val = val;
    new->next = next;
    if (pre) {
        pre->next = new;
    } else {
        *head = new;        
    }
    return 1;
}

/**
 * \brief Delete a node by index
 */
int deleteNodeByIndex(Node_t **head, int *val, int index) {
    Node_t *pre = NULL, *cur = *head;
    while (index--) {
        pre = cur;
        if (!(cur = cur->next)) {
            return 0;
        }
    }
    *val = cur->val;
    if (pre) {
        pre->next = cur->next;
    } else {
        *head = cur->next;
    }
    free(cur);
    return 1;
}

Node_t *createList(int *nums, int numsSize) {
    if (!numsSize) {
        return NULL;
    }
    Node_t *head = (Node_t *)malloc(sizeof(Node_t));
    head->val = *nums;
    head->next = createList(nums + 1, numsSize - 1);
    return head;
}

void printList(Node_t *head, char *name) {
    printf("%s = ", name);
    while (head) {
        printf("(%d)->", head->val);
        head = head->next;
    }
    printf("null\n");
}

void freeList(Node_t **head) {
    if (*head) {
        Node_t *temp = *head;
        *head = temp->next;
        free(temp);
        freeList(head);
    }
}

int main() {
    int nums[] = {5,1,3,0,7,9,2,8,4,6};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int val, index;

    // Create list
    Node_t *head = createList(nums, numsSize);
    printList(head, "Original list");

    // Sort list
    sortList(head);
    printList(head, "Sorted list");

    // Insert a node by value
    printf("Enter a num to insert: ");
    scanf("%d", &val);
    insertNodeByValue(&head, val);
    printList(head, "New list");

    // Delete a node by value
    printf("Enter a num to delete: ");
    scanf("%d", &val);
    if (deleteNodeByValue(&head, val)) {
        printList(head, "New list");
    } else {
        printf("%d doesn't exist in the list.\n", val);
    }

    // Reverse list
    reverseList(&head);
    printList(head, "\nReversed list");

    // Insert a node by index
    printf("Enter a num to insert: ");
    scanf("%d", &val);
    printf("Enter the index to insert: ");
    scanf("%d", &index);
    if (insertNodeByIndex(&head, val, index)) {
        printList(head, "New list");
    } else {
        printf("The index exceeds list bounds.\n");
    }

    // Delete a node by index
    printf("Enter the index to delete: ");
    scanf("%d", &index);
    if (deleteNodeByIndex(&head, &val, index)) {
        printf("The value of deleted node = %d\n", val);
        printList(head, "New list");
    } else {
        printf("The index exceeds list bounds.\n");
    }

    // Free list
    freeList(&head);

    system("pause");
    return 0;
}
