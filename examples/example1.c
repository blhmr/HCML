/*
 *
 *	Example 1:
 *
 * Open a HCML file, rename it then close it.
 *
 * */

#include <hcml.h>

int main(void) {
	hcml_file_t file;

	if (hcml_file_open(&file, "file.hcml") == 0) {
		printf("Successfully opened file!\n");
	}

	if (hcml_file_rename(&file, "renamed.hcml") == 0) {
		printf("Successfully renamed file!\n");
	}

	if (hcml_file_close(&file) == 0) {
		printf("Successfully closed the file!\n");
	}

	return 0;
}
