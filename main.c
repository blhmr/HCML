#include <stdio.h>
#include <hcml.h>

int main(void) {
	hcml_file_t file;

	hcml_file_open(&file, "example.hcml");

//	hcml_delete_key(&file, "account_info", "password2");

	hcml_delete_family(&file, "additional_info");
	hcml_file_close(&file);
	return 0;
}
