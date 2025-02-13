#include <stdio.h>

void print_stack_address(int n) {
    printf("Value: %d, Address: %p\n", n, (void*)&n);
    if (n > 1) {
        print_stack_address(n - 1);
    }
}

int main() {
    print_stack_address(9);
    return 0;
}
