#include <stdio.h>
#include <hcml.h>

int main(void) {
	hcml_file_t file;
	hcml_file_open(&file, "example.hcml");
	{
		char* value;
		if ((value = hcml_get_value(&file, "personal_info", "name")) != NULL) {
			printf("Value : %s from file %s\n", value, file.filename);
			free(value);
		}
		else printf("Error !\n");
	}
	hcml_file_close(&file);
}
