#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//!*****************************************************************************
//! General functions
//!*****************************************************************************
/**
 * \brief Memory copy function
 */
void memCpy(int *dst, const int *src, int numsSize) {
    while (numsSize--) {
        *(dst + numsSize) = *(src + numsSize);
    }
}

/**
 * \brief Print array function
 */
void printArray(const int *nums, int numsSize, const char *title) {
    printf("%s = [", title);
    if (numsSize) {
        printf("%d", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", *(nums + i));
        }
    }
    printf("]\n");
}

//!*****************************************************************************
//! Compare functions
//!*****************************************************************************
/**
 * \brief Ascending order compare function
 */
int ascending(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

/**
 * \brief Descending order compare function
 */
int descending(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

typedef int (*CompareFunc_t)(const void *, const void *);

//!*****************************************************************************
//! Sorting algorithms
//!*****************************************************************************
/**
 * \brief Macro to swap values of two variables
 */
#define SWAP(a, b)                                                             \
    *(a) ^= *(b);                                                              \
    *(b) ^= *(a);                                                              \
    *(a) ^= *(b)

/**
 * \brief Selection sort
 */
void selectSort(int *nums, int numsSize, CompareFunc_t compar) {
    while (--numsSize) {
        for (int i = 1; i <= numsSize; i++) {
            if (compar(nums, nums + i) > 0) {
                SWAP(nums, nums + i);
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
                SWAP(nums + i, nums + j);
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
                SWAP(nums + i, nums + i + 1);
            }
        }
    }
}

/**
 * \brief Quick sort
 */
void quickSort(int *nums, int numsSize, CompareFunc_t compar) {
    if (numsSize > 1) {
        int i = -1, j = numsSize, s = *(nums + (numsSize >> 1));
        for (;;) {
            while (compar(nums + ++i, &s) < 0);
            while (compar(nums + --j, &s) > 0);
            if (i >= j) {
                break;
            }
            SWAP(nums + i, nums + j);
        }
        quickSort(nums, i , compar);
        quickSort(nums + j + 1, numsSize - j - 1, compar);
    }
}

/**
 * \brief Merge sort
 */
void mergeSort(int *nums, int numsSize, CompareFunc_t compar) {
    if (numsSize > 1) {
        int n = numsSize >> 1, m = numsSize - n,
            *nums2 = (int *)malloc(sizeof(int) * n);
        memCpy(nums2, nums + m, n);
        mergeSort(nums, m, compar);
        mergeSort(nums2, n, compar);

        // Merge two nums array
        while (m && n) {
            *(nums + --numsSize) = compar(nums + m - 1, nums2 + n - 1) > 0 ?
                                   *(nums + --m) : *(nums2 + --n);
        }
        while (n--) {
            *(nums + n) = *(nums2 + n);
        }

        free(nums2);
    }
}

//!*****************************************************************************
//! Binary search function
//!*****************************************************************************
/**
 * \brief Binary search
 */
int binarySearch(const int *nums, int numsSize, int target,
                 CompareFunc_t compar) {
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

//!*****************************************************************************
//! Main function
//!*****************************************************************************
#define NUMS_SIZE 10  // Size of the test array
#define NUMS_MAX  100 // Maximum value of the test array

int main() {
    srand(time(NULL)); // Set random seed to time

    //--------------------------------------------------------------------------
    // Sorting order
    //--------------------------------------------------------------------------
    struct {
        CompareFunc_t compar;
        char *name;
    } Ords[] = {
        {.compar = ascending, .name = "ascending"},
        {.compar = descending, .name = "descending"}
    };
    int ordsSize = sizeof(Ords) / sizeof(Ords[0]);

    //--------------------------------------------------------------------------
    // Sorting approach
    //--------------------------------------------------------------------------
    struct {
        void (*func)(int *, int, CompareFunc_t);
        char *name;
    } Algs[] = {
        {.func = selectSort, .name = "Selection sort"},
        {.func = insertSort, .name = "Insertion sort"},
        {.func = bubbleSort, .name = "Bubble sort"},
        {.func = quickSort, .name = "Quick sort"},
        {.func = mergeSort, .name = "Merge sort"}
    };
    int algsSize = sizeof(Algs) / sizeof(Algs[0]);

    //--------------------------------------------------------------------------
    // Functional tests
    //--------------------------------------------------------------------------
    // Init array
    int reset[NUMS_SIZE], nums[NUMS_SIZE];
    for (int i = 0; i < NUMS_SIZE; i++) {
        reset[i] = rand() % NUMS_MAX;
    }
    printArray(reset, NUMS_SIZE, "Original");

    char s[256]; // Character array for storing strings
    int input, index;

    // Test for each algorithm
    for (int i = 0; i < ordsSize; i++) {
        for (int j = 0; j < algsSize; j++) {
            memCpy(nums, reset, NUMS_SIZE); // Reset nums
            Algs[j].func(nums, NUMS_SIZE, Ords[i].compar); // Sort nums
            sprintf(s, "%sed by %s order", Algs[j].name, Ords[i].name);
            printArray(nums, NUMS_SIZE, s);
        }

        // Test for binary search
        printf("Enter a number to be searched: ");
        scanf("%d", &input);
        index = binarySearch(nums, NUMS_SIZE, input, Ords[i].compar);
        if (index != -1) {
            printf("Index of %d = %d\n\n", input, index);
        } else {
            printf("%d is not exist in nums.\n\n", input);
        }
    }

    system("pause");
    return 0;
}
