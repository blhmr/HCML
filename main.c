#include <stdio.h>
#include <hcml.h>

int main(void) {
	hcml_file_t file;
	hcml_file_open(&file, "example.hcml");

	char* value;
	if ((value = hcml_get_value(&file, "info/profile", "bio")) == NULL) {
		fprintf(stderr, "Error getting data from file");
	}
	else {
		printf("%s\n", value);
		free(value);
	}

	hcml_file_close(&file);
}