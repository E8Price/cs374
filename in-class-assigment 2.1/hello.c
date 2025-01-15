#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char x[128] = "Hello\n";
    char *y = "Hello\n";

    write(1, x, 6);
    write(1, "Hello\n", 6);
    write(1, y, 6);

}