#include <windows.h>
#include <stdio.h>

#define MAX_SIZE 0x100

int main(int argc, char **argv)
{
    HANDLE hinFile, houtFile;

    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>", argv[0]);
        return 0x1;
    }

    hinFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hinFile == INVALID_HANDLE_VALUE) {
        printf("%s: Cannot open %s", argv[1]);
        return 0x2;
    }

    houtFile = CreateFile(argv[2], GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (houtFile == INVALID_HANDLE_VALUE) {
        printf("%s: Cannot open %s", argv[2]);
        return 0x3;
    }

    DWORD bytes_read, bytes_written;
    CHAR buffer[MAX_SIZE];
    
    // From hinFile, write to houtFile handle
    while ( (ReadFile(hinFile, buffer, MAX_SIZE, &bytes_read, NULL) && bytes_read) > 0) {
        WriteFile(houtFile, buffer, bytes_read, &bytes_written, NULL);
        if (bytes_written != bytes_read) {
            printf("%s: WriteFile() - %s Not completely written to %s", argv[0], argv[1], argv[2]);
            return 0x4;
        }
    }

    // Close the handles
    CloseHandle(hinFile);
    CloseHandle(houtFile);

return 0;
}