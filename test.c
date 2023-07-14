#include <stdio.h>
#include <string.h>

void replaceNBSP(char* str) {
	char* nbsp = "&nbsp;";
	char* occurrence = NULL;

	while ((occurrence = strstr(str, nbsp)) != NULL) {
		// Calculate the length of the nbsp entity
		size_t nbspLen = strlen(nbsp);

		// Replace the nbsp occurrence with a space character
		*occurrence = ' ';

		// Shift the remaining characters to the left to remove the nbsp entity
		memmove(occurrence + 1, occurrence + nbspLen, strlen(occurrence + nbspLen) + 1);
	}
}

int main() {
	char text[] = "Hello&nbsp;World! This is&nbsp;a test.";

	printf("Before replacement: %s\n", text);

	replaceNBSP(text);

	printf("After replacement: %s\n", text);

	return 0;
}
