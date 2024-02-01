#include <hcml.h>

int main(void) {
	hcml_file_t file;
	hcml_file_open(&file, "example.hcml");

	char* value = hcml_get_value(&file, "personal_info", "country");

	if (value != NULL) {
		printf("GOT VALUE: %s\n", value);
		free(value);
	}

	hcml_file_close(&file);
}
