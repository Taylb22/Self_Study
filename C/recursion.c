#include <stdio.h>

int factorial(int n) {
    if (n <= 1) return 1;

    return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    return n + fibonacci(n - 1);
}

int main () {
    int n = 10;
    
    printf("\nFactorial of %d is equal to %d\n", n, factorial(n));
    printf("The %dth number of Fibonacci is %d\n", n, fibonacci(n));

    return 0;
}