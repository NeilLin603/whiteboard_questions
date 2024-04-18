#include <stdio.h>
#include <stdlib.h>

// Newton-Raphson Method:
// y(n + 1) = y(n) - f(y(n)) / f'(y(n))
// y = sqrt(x)
// f(y) = y^2 - x = 0
// f'(y) = 2y
float squareRoot(float x) {
    float y = x, f = y * y - x;
    while (f > 0.001f || f < -0.001f) {
        y -= f / (2.0f * y);
        f = y * y - x;
    }
    return y;
}

int main() {
    float x;
    printf("Enter a num: ");
    scanf("%f", &x);

    printf("sqrt(%.3f) = %.3f\n", x, squareRoot(x));
    system("pause");
    return 0;
}
