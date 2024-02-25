#include <stdio.h>
#include <hcml.h>

#define MAX 40

#define _BOOL_STR(b) ( b == 1 ? "true" : "false")

int main(void) {
	hcml_file_t file;
	hcml_file_open(&file, "example.hcml");
	char* string = hcml_get_value(&file, "info/profile", "bio");
	printf("%s\n", string);
	free(string);
	hcml_file_close(&file);
}
