#include <stdio.h>
#include <windows.h>

int main(int argc, LPTSTR argv[])
{
    // Checking for command line arguments
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 0x1;
    }

    // Making a copy of argv[1]
    if ( !CopyFile(argv[1], argv[2], FALSE) ) {
        printf("%s: CopyFile() failed miserably !\n", argv[0]);
        return 0x2;
    }

return 0;
}