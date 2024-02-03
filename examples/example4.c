/*
 *	Example 4:
 *	Open a HCML file.
 *	Update the entry from the previous example.
 *	Close the HCML file.
 *
 * */
#include <hcml.h>

int main(void) {
	hcml_file_t file;
	hcml_file_open(&file, "example.hcml");
	
	int r;
	if (r = hcml_update_value(&file, "new_family", "somekey", "newvalue") == 0) {
		printf("Successfully updated the entry!\n");
	}
	else printf("Something went wrong.\n");
}
