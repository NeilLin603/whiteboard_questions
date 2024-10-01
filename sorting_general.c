#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b)                                                             \
    (a) ^= (b);                                                                \
    (b) ^= (a);                                                                \
    (a) ^= (b)

typedef int (*CompareFunc_t)(const void *, const void *);
typedef void (*SortFunc_t)(int *, int, CompareFunc_t);

/**
 * \brief Selection sort
 */
void selectSort(int *nums, int numsSize, CompareFunc_t compar) {
    while (numsSize-- > 1) {
        for (int i = 1; i <= numsSize; i++) {
            if (compar(nums, nums + i) > 0) {
                SWAP(*nums, *(nums + i));
            }
        }
        nums++;
    }
}

/**
 * \brief Insertion sort
 */
void insertSort(int *nums, int numsSize, CompareFunc_t compar) {
    for (int j = 1; j < numsSize; j++) {
        for (int i = 0; i < j; i++) {
            if (compar(nums + i, nums + j) > 0) {
                SWAP(*(nums + i), *(nums + j));
            }
        }
    }
}

/**
 * \brief Bubble sort
 */
void bubbleSort(int *nums, int numsSize, CompareFunc_t compar) {
    while (--numsSize) {
        for (int i = 0; i < numsSize; i++) {
            if (compar(nums + i, nums + i + 1) > 0) {
                SWAP(*(nums + i), *(nums + i + 1));
            }
        }
    }
}

/**
 * \brief Quick sort
 */
void quickSort(int *nums, int numsSize, CompareFunc_t compar) {
    if (numsSize > 1) {
        int i = -1, j = numsSize, s = nums[numsSize >> 1];
        for (;;) {
            while (compar(nums + ++i, &s) < 0);
            while (compar(nums + --j, &s) > 0);
            if (i >= j) {
                break;
            }
            SWAP(nums[i], nums[j]);
        }
        quickSort(nums, i, compar);
        quickSort(nums + j + 1, numsSize - j - 1, compar);
    }
}

/**
 * \brief Merge sort
 */
void mergeSort(int *nums1, int m, int *nums2, int n, int *nums3, CompareFunc_t compar) {
    int k = m + n;
    while (m && n) {
        nums3[--k] = compar(nums1 + m - 1, nums2 + n - 1) > 0 ? nums1[--m] : nums2[--n];
    }
    while (m) {
        nums3[--k] = nums1[--m];
    }
    while (n) {
        nums3[--k] = nums2[--n];
    }
}

/**
 * \brief Binary search
 */
int binarySearch(int *nums, int numsSize, int val, CompareFunc_t compar) {
    int i = 0, j = numsSize - 1, k;
    while (i <= j) {
        k = i + j >> 1;
        if (compar(nums + k, &val) < 0) {
            i = k + 1;
        } else if (compar(nums + k, &val) > 0) {
            j = k - 1;
        } else {
            return k;
        }
    }
    return -1;
}

int ascending(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int descending(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

void printArray(int *nums, int numsSize, char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", *nums);
        while (--numsSize) {
            printf(",%d", *++nums);
        }
    }
    printf("]\n");
}

int main() {
    struct {
        int nums1[10], nums1Size, nums2[10], nums2Size;
        CompareFunc_t compar;
        SortFunc_t sort1, sort2;
    } tc[] = {
        {.nums1 = {5,0,4,7,3,9}, .nums1Size = 6, .nums2 = {6,1,8,2}, .nums2Size = 4,
         .compar = ascending, .sort1 = selectSort, .sort2 = insertSort},
        {.nums1 = {9,0,4}, .nums1Size = 3, .nums2 = {2,8,6,7,1,3,5}, .nums2Size = 7,
         .compar = descending, .sort1 = bubbleSort, .sort2 = quickSort}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    int *nums3, nums3Size, val, index;
    for (int i = 0; i < tcSize; i++) {
        printf("Test case %d:\n", i + 1);

        // Sort nums1
        printArray(tc[i].nums1, tc[i].nums1Size, "\nOriginal nums1");
        tc[i].sort1(tc[i].nums1, tc[i].nums1Size, tc[i].compar);
        printArray(tc[i].nums1, tc[i].nums1Size, "Sorted nums1");

        // Sort nums2
        printArray(tc[i].nums2, tc[i].nums2Size, "\nOriginal nums2");
        tc[i].sort2(tc[i].nums2, tc[i].nums2Size, tc[i].compar);
        printArray(tc[i].nums2, tc[i].nums2Size, "Sorted nums2");

        // Merge sort num1 & nums2 to nums3
        nums3Size = tc[i].nums1Size + tc[i].nums2Size;
        nums3 = (int *)malloc(nums3Size * sizeof(int));
        mergeSort(tc[i].nums1, tc[i].nums1Size, tc[i].nums2, tc[i].nums2Size,
                  nums3, tc[i].compar);
        printArray(nums3, nums3Size, "\nnums3");

        // Binary search
        printf("\nEnter a num to search: ");
        scanf("%d", &val);
        index = binarySearch(nums3, nums3Size, val, tc[i].compar);
        if (index != -1) {
            printf("The index of %d in nums3 = %d\n\n", val, index);
        } else {
            printf("%d not found in nums3.\n\n", val);
        }

        free(nums3);
    }

    system("pause");
    return 0;
}
