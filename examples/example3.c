/*
 *	Example 3:
 *	Open a HCML file.
 *	Insert an entry.
 *	Close the file.
 *
 * */

#include <hcml.h>

int main(void) {
	hcml_file_t file;

	hcml_file_open(&file, "example.hcml");
	
	if (hcml_insert_value(&file, "new_family", "somekey", "value") == 0) {
		printf("Successfully inserted the entry!\n");
	}

	hcml_file_close(&file);
}
