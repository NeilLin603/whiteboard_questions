#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) do { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
} while (0)

typedef int (*CompareFunc_t)(const void *, const void *);
typedef void (*SortAlg_t)(int *, int, CompareFunc_t);

/**
 * \brief Selection sort
 */
void selectSort(int *nums, int numsSize, CompareFunc_t compar) {
    if (numsSize > 1) {
        for (int i = 1; i < numsSize; i++) {
            if (compar(nums, nums + i) > 0) {
                SWAP(*nums, nums[i]);
            }
        }
        selectSort(nums + 1, numsSize - 1, compar);
    }
}

/**
 * \brief Insertion sort
 */
void insertSort(int *nums, int numsSize, CompareFunc_t compar) {
    for (int i = 1; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (compar(nums + j, nums + i) > 0) {
                SWAP(nums[i], nums[j]);
            }
        }
    }
}

/**
 * \brief Bubble sort
 */
void bubbleSort(int *nums, int numsSize, CompareFunc_t compar) {
    if (numsSize > 1) {
        for (int i = 1; i < numsSize; i++) {
            if (compar(nums + i - 1, nums + i) > 0) {
                SWAP(nums[i -1], nums[i]);
            }
        }
        bubbleSort(nums, numsSize - 1, compar);
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
int binarySearch(int *nums, int numsSize, int target, CompareFunc_t compar) {
    int i = 0, j = numsSize - 1, k;
    while (i <= j) {
        k = i + j >> 1;
        if (compar(nums + k, &target) < 0) {
            i = k + 1;
        } else if (compar(nums + k, &target) > 0) {
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

int descinding(const void *a, const void *b) {
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
        SortAlg_t sort1, sort2;
    } TestCase[] = {
        {.nums1 = {3,1,5,0,7,6}, .nums1Size = 6, .nums2 = {8,4,2,9}, .nums2Size = 4,
         .compar = ascending, .sort1 = selectSort, .sort2 = insertSort},
        {.nums1 = {2,5,9,0,7}, .nums1Size = 5, .nums2 = {6,1,3,8,4}, .nums2Size = 5,
         .compar = descinding, .sort1 = bubbleSort, .sort2 = quickSort}};
    int tcSize = sizeof(TestCase) / sizeof(TestCase[0]);

    int *nums3, nums3Size, target, index;
    printf("Enter a num to be searched: ");
    scanf("%d", &target);

    for (int i = 0; i < tcSize; i++) {
        printf("\nTest case %d:\n", i + 1);

        // Sort nums1
        printf("\n// Sort nums1\n");
        printArray(TestCase[i].nums1, TestCase[i].nums1Size, "Original nums1");
        TestCase[i].sort1(TestCase[i].nums1, TestCase[i].nums1Size, TestCase[i].compar);
        printArray(TestCase[i].nums1, TestCase[i].nums1Size, "Sorted nums1");

        // Sort nums2
        printf("\n// Sort nums2\n");
        printArray(TestCase[i].nums2, TestCase[i].nums2Size, "Original nums2");
        TestCase[i].sort2(TestCase[i].nums2, TestCase[i].nums2Size, TestCase[i].compar);
        printArray(TestCase[i].nums2, TestCase[i].nums2Size, "Sorted nums2");

        // Merge sort nums1 & nums2 to nums3
        printf("\n// Merge sort nums1 & nums2 to nums3\n");
        nums3Size = TestCase[i].nums1Size + TestCase[i].nums2Size;
        nums3 = (int *)malloc(nums3Size * sizeof(int));
        mergeSort(TestCase[i].nums1, TestCase[i].nums1Size,
                  TestCase[i].nums2, TestCase[i].nums2Size,
                  nums3, TestCase[i].compar);
        printArray(nums3, nums3Size, "nums3");

        // Binary search
        printf("\n// Search the index of input num in nums3\n");
        index = binarySearch(nums3, nums3Size, target, TestCase[i].compar);
        free(nums3);
        if (index != -1) {
            printf("The index of %d in nums3 = %d\n", target, index);
        } else {
            printf("%d is not exist in nums3.\n", target);
        }
    }

    system("pause");
    return 0;
}
