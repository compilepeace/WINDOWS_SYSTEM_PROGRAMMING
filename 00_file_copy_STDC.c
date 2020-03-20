#include <stdio.h>

#define BUF_SIZE 0X100


int main(int argc, char** argv)
{
	FILE *inputFile, *outputFile;
	errno_t err;

	if (argc != 3) {
		printf("Usage: %s <input_file> <new_file>\n", argv[0]);
		return 0x1;
	}

	err = fopen_s(&inputFile, argv[1], "rb");
	if (err != 0) {
		printf("%s: fopen() -> %s does not exist", argv[0], argv[1]);
		return 0x2;
	}

	err = fopen_s(&outputFile, argv[2], "wb");
	if (err != 0) {
		printf("%s: fopen() -> %s could not create the file \"%s\"", argv[0], argv[1], argv[2]);
		return 0x3;
	}


	char buffer[BUF_SIZE];
	size_t bytes_read, bytes_written;
	// Read the file till nomore characters are left
	// Read 0x100 (256) bytes from the input file at once
	while ((bytes_read = fread(buffer, sizeof(char), 0x100, inputFile)) > 0) {
		bytes_written = fwrite(buffer, sizeof(char), bytes_read, outputFile);
		if (bytes_written != bytes_read) {
			printf("%s: fwrite() failed !", argv[0]);
		}
	}

	return 0;
}
