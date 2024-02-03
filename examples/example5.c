/*
 *	Example 5:
 *
 *	Open a HCML file.
 *	Delete an entry.
 *	Close a file.
 *
 * */
#include <hcml.h>

int main(void) {
	hcml_file_t file;
	hcml_file_open(&file, "example.hcml");

	if (hcml_delete_key(&file, "new_family", "somekey") == 0) {
		printf("Successfully deleted the entry!\n");
	}

	hcml_file_close(&file);
}
