#include <stdio.h>
#include <hcml.h>

int main(void) {
	hcml_file_t file;

	hcml_file_open(&file, "example.hcml");

	hcml_entry_t entry = {"account_info", "username", "hatim"};

	hcml_update_value_entry(&file, &entry);

	hcml_file_close(&file);
	return 0;
}
