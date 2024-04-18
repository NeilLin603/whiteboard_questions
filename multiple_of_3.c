#include <stdio.h>
#include <stdlib.h>

// n = abcde (in binary)
//   = (abc << 2) + de = abc * 4 + de
//
// n is a multiple of 3 if and only if (abc + de) is a multiple of 3
// where abc = n >> 2, de = n & 3
int isMultipleOf3(int n) {
    if (n < 0) {
        return isMultipleOf3(-n);
    }
    if (n == 0 || n == 3) {
        return 1;
    }
    if (n < 3) {
        return 0;
    }
    return isMultipleOf3((n >> 2) + (n & 3));
}

int main() {
    int n;
    printf("Enter a num: ");
    scanf("%d", &n);

    char *s = isMultipleOf3(n) ? "" : "not ";
    printf("%d is %sa multiple of 3.\n", n, s);
    system("pause");
    return 0;
}
