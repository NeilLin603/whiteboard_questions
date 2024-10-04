#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b)                                                             \
    (a) ^= (b);                                                                \
    (b) ^= (a);                                                                \
    (a) ^= (b)

typedef int (*CompareFunc_t)(const void *, const void *);

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
        int i = -1, j = numsSize, k = numsSize >> 1;
        for (;;) {
            while (compar(nums + ++i, nums + k) < 0);
            while (compar(nums + --j, nums + k) > 0);
            if (i >= j) {
                break;
            }
            SWAP(*(nums + i), *(nums + j));
        }
        quickSort(nums, i, compar);
        quickSort(nums + j + 1, numsSize - j - 1, compar);
    }
}

/**
 * \brief Memory copy function.
 */
void memCpy(int *dst, const int *src, int numsSize) {
    while (numsSize--) {
        *(dst + numsSize) = *(src + numsSize);
    }
}

/**
 * \brief The subfunction of mergeSort().
 */
void merge(int *nums1, int m, int *nums2, int n, CompareFunc_t compar) {
    while (m && n) {
        *(nums1 + m + n) = compar(nums1 + m - 1, nums2 + n - 1) > 0 ?
                           *(nums1 + --m) : *(nums2 + --n);
    }
    while (n) {
        *(nums1 + n) = *(nums2 + --n);
    }
}

/**
 * \brief Merge sort
 */
void mergeSort(int *nums, int numsSize, CompareFunc_t compar) {
    if (numsSize > 1) {
        int nums2Size = numsSize >> 1;
        numsSize -= nums2Size;
        int *nums2 = (int *)malloc(sizeof(int) * nums2Size);
        memCpy(nums2, nums + numsSize, nums2Size);

        mergeSort(nums, numsSize, compar);
        mergeSort(nums2, nums2Size, compar);

        merge(nums, numsSize, nums2, nums2Size, compar);
        free(nums2);
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
    // Assign the compare function for sorting order
    CompareFunc_t compar = ascending;
    // CompareFunc_t compar = descending;

    // Initialize an array
    int nums[] = {5,1,0,9,7,8,3,9,4,6,2},
        numsSize = sizeof(nums) / sizeof(nums[0]);
    printArray(nums, numsSize, "Original");

    // Array for reset
    int *numsReset = (int *)malloc(sizeof(int) * numsSize);
    memCpy(numsReset, nums, numsSize);

    // Select sort
    selectSort(nums, numsSize, compar);
    printArray(nums, numsSize, "Selection sorted");

    // Insertion sort
    memCpy(nums, numsReset, numsSize); // Reset nums
    insertSort(nums, numsSize, compar);
    printArray(nums, numsSize, "Insertion sorted");

    // Bubble sort
    memCpy(nums, numsReset, numsSize); // Reset nums
    bubbleSort(nums, numsSize, compar);
    printArray(nums, numsSize, "Bubble sorted");

    // Quick sort
    memCpy(nums, numsReset, numsSize); // Reset nums
    quickSort(nums, numsSize, compar);
    printArray(nums, numsSize, "Quick sorted");

    // Merge sort
    memCpy(nums, numsReset, numsSize); // Reset nums
    mergeSort(nums, numsSize, compar);
    printArray(nums, numsSize, "Merge sorted");

    // Binary search
    int input;
    printf("Enter a number to be searched: ");
    scanf("%d", &input);
    printf("Index of %d = %d\n", input,
           binarySearch(nums, numsSize, input, compar));

    free(numsReset);
    return 0;
}
