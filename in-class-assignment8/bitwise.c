#include <stdio.h>

/*
 * Expected output:
 *
 * 1111000000000000
 * 0000111111111111
 * 1010110011001100
 * 0101001100110011
 *
 * 1111
 * 0000
 * 1010
 * 0101
 *
 * 000000000000
 * 111111111111
 * 110011001100
 * 001100110011
 */

void merge_nums(unsigned a, unsigned b)
{
    unsigned int merged;
    merged = (a << 12) | b;
    printf("%016b\n", merged);
}

void get_high_4(unsigned a)
{
    unsigned int high_4;
    high_4 = a >> 12;
    printf("%04b\n", high_4);
}

void get_low_12(unsigned a)
{
    unsigned int low_12;
    low_12 = a & 0xFFF;
    printf("%012b\n", low_12);
}

int main(void)
{
    merge_nums(0b1111, 0b000000000000);
    merge_nums(0b0000, 0b111111111111);
    merge_nums(0b1010, 0b110011001100);
    merge_nums(0b0101, 0b001100110011);

    putchar('\n');

    get_high_4(0b1111000000000000);
    get_high_4(0b0000111111111111);
    get_high_4(0b1010110011001100);
    get_high_4(0b0101001100110011);

    putchar('\n');

    get_low_12(0b1111000000000000);
    get_low_12(0b0000111111111111);
    get_low_12(0b1010110011001100);
    get_low_12(0b0101001100110011);
}


