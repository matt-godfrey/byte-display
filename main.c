// Write a program that displays the contents of a file as bytes and as characters. Have the user
// specify the file name on the command line. Here’s what the output will look like when the
// program is used to display the pun.c file of Section 2.1:
// Offset Bytes Characters
// ------ ----------------------------- ----------
// 0 23 69 6E 63 6C 75 64 65 20 3C #include <
// 10 73 74 64 69 6F 2E 68 3E 0D 0A stdio.h>..
// 20 0D 0A 69 6E 74 20 6D 61 69 6E ..int main
// 30 28 76 6F 69 64 29 0D 0A 7B 0D (void)..{.
// 40 0A 20 20 70 72 69 6E 74 66 28 . printf(
// 50 22 54 6F 20 43 2C 20 6F 72 20 "To C, or
// 60 6E 6F 74 20 74 6F 20 43 3A 20 not to C:
// 70 74 68 61 74 20 69 73 20 74 68 that is th
// 80 65 20 71 75 65 73 74 69 6F 6E e question
// 90 2E 5C 6E 22 29 3B 0D 0A 20 20 .\n");..
// 100 72 65 74 75 72 6E 20 30 3B 0D return 0;.
// 110 0A 7D .}
// Each line shows 10 bytes from the file, as hexadecimal numbers and as characters. The
// number in the Offset column indicates the position within the file of the first byte on the
// line. Only printing characters (as determined by the isprint function) are displayed;
// other characters are shown as periods. Note that the appearance of a text file may vary,
// depending on the character set and the operating system. The example above assumes that
// pun.c is a Windows file, so 0D and 0A bytes (the ASCII carriage-return and line-feed
// characters) appear at the end of each line. Hint: Be sure to open the file in "rb" mode.


#include <complex.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }

    // Get file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    printf("File size: %ld\n", fileSize);

    int count = fileSize / sizeof(unsigned char);

    unsigned char *data = (unsigned char *)malloc(fileSize);
    if (data == NULL) {
        perror("Error: unable to allocate memory for byte array\n");
        return -1;
    }

    size_t ret = fread(data, sizeof(unsigned char), count, fp);
    if (ret != count) {
        perror("error: fread encountered an error reading to array.\n");
        return -1;
    }

    printf("Just read %zu items.\n", ret);
    printf("size of first: %zu\n", sizeof(data[0]));

    size_t i = 0, j = 0;
    // arr_pos
    printf("%-10zu", i);
    for (; i < fileSize; i++) {
        printf("%02X ", data[i]);

        if ((i+1) % 10 == 0) {

            printf("    ");
            j = (i+1) - 10;
            int count = 0;
            for (; count < 10; count++) {
                if (isprint(data[j]))
                    printf("%c", data[j]);
                else
                    printf(".");
                j++;
            }
            printf("\n");
            printf("%-10zu", (i+1));
        }
    }
    if (j < fileSize) {
        // didn't print a full row
        int row_pos = i % 10;
        int remaining_spaces = 10 - row_pos;
        for (int k = (10 - remaining_spaces); k < 10; k++) {
            printf("   ");
        }
        printf("   ");
        for (; j < fileSize; j++) {
            printf("%c", data[j]);
        }
    }
    printf("\n");

    // ret = fwrite(data, sizeof(int), count, stdout);

    free(data);
    fclose(fp);
    return 0;
}
