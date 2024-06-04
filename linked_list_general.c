#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node_t;

/**
 * \brief Merge to sorted list.
 */
void merge(Node_t **l1, Node_t *l2) {
    if (!*l1) {
        *l1 = l2;
        return;
    }
    if (l2) {
        if ((*l1)->val < l2->val) {
            merge(&l2, (*l1)->next);
            (*l1)->next = l2;
        } else {
            merge(l1, l2->next);
            l2->next = *l1;
            *l1 = l2;
        }
    }
}

/**
 * \brief Merge sort a list.
 */
void mergeSort(Node_t **head) {
    if (*head && (*head)->next) {
        Node_t *slow = *head, *fast = (*head)->next;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        slow->next = NULL;
        mergeSort(head);
        mergeSort(&fast);
        merge(head, fast);
    }
}

/**
 * \brief Reverse list
 */
void reverseList(Node_t **head) {
    Node_t *pre = NULL, *cur = *head, *next;
    while (cur) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    *head = pre;
}

/**
 * \brief Insert a node by value
 */
void insertNodeByValue(Node_t **head, int val) {
    Node_t *pre = NULL, *next = *head;
    while (next) {
        if (val <= next->val) {
            break;
        }
        pre = next;
        next = next->next;
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
        if (val == cur->val) {
            if (pre) {
                pre->next = cur->next;
            } else {
                *head = cur->next;
            }
            free(cur);
            return 1;
        }
        pre = cur;
        cur = cur->next;
    }
    return 0;
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
    if (!*head) {
        return 0;
    }
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

Node_t *createList(int *vals, int valsSize) {
    if (!valsSize) {
        return NULL;
    }
    Node_t *head = (Node_t *)malloc(sizeof(Node_t));
    head->val = *vals;
    head->next = createList(vals + 1, valsSize - 1);
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
        freeList(&(*head)->next);
        free(*head);
        *head = NULL;
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
    mergeSort(head);
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
