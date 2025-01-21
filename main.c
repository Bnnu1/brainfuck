#include <stdio.h>

int main() {
	// Brainfuck tape and pointer
	int tape[30000];
	int* tape_ptr = tape;

	// Stack for loops
	int loops[50];
	int top = -1;

	char filename[100];
	printf("File name: ");
	scanf("%s", filename);

	FILE* file = fopen(filename, "r");

	// Get EOF for file size	
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char code[file_size];

	if (file == NULL) {
		printf("Error occurred while opening file\n");
		return 1;
	}

	// Assign file stream output to code
	fread(code, 2, file_size, file);

	for (int i = 0; i <= file_size; i++) {
		switch (code[i]) {
			case '<':
				tape_ptr--;
				break;
			case '>':
				tape_ptr++;
				break;
			case '-':
				--*tape_ptr;
				break;
			case '+':
				++*tape_ptr;
				break;
			case '.':
				putchar(*tape_ptr);
				break;
			case ',':
				*tape_ptr = getchar();
				break;
			case '[':
				top++;
				loops[top] = i;
				break;
			case ']':
				if (*tape_ptr != 0) {
					i = loops[top];
				} else {
					top--;
				}
				break;
			default:
				break;
		}
	}

	fclose(file);

	// For terminals
	printf("\n");

	return 0;
}

