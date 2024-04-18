#include <stdio.h>

#define SWAP(a, b) do { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
} while (0)

int strLen(char *s) {
    char *t = s - 1;
    while (*++t);
    return t - s;
}

void reverseString(char *s) {
    int i = -1, j = strLen(s);
    while (++i < --j) {
        SWAP(s[i], s[j]);
    }
}

int main() {
    char s[] = "This is a string";
    printf("Original string: %s\n", s);

    reverseString(s);
    printf("Reversed string: %s\n", s);

    return 0;
}
