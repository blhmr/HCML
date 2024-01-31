/* Hatim's Configuration Markup Language */

// hcml_info.c
#include "../include/hcml.h"

// Done and tested
bool hcml_family_exist(hcml_file_t* hcml_file, const char* family) {
	char line_buffer[HCML_MAX_LEN_LINE + 1];
	bool flag = false;

	rewind(hcml_file->file);
	while (fgets(line_buffer, HCML_MAX_LEN_LINE, hcml_file->file) && !flag) {
		hcml_entry_t entry;
		hcml_entry_parse(&entry, line_buffer);
		if (!strcmp(entry.family, family)) {
			flag = true;
		}
	}

	return flag;
}

// Done and tested
bool hcml_key_exist(hcml_file_t* hcml_file, const char* family, const char* key) {
	bool flag = false;
	if (hcml_family_exist(hcml_file, family)) {
		char line_buffer[HCML_MAX_LEN_LINE + 1];

		rewind(hcml_file->file);
		while (fgets(line_buffer, HCML_MAX_LEN_LINE, hcml_file->file) && !flag) {
			hcml_entry_t entry;
			hcml_entry_parse(&entry, line_buffer);
			if (!strcmp(entry.key, key)) {
				flag = true;
			}
		}
	}

	return flag;
}

// Done and tested
size_t hcml_entry_num(hcml_file_t* hcml_file) {
	char buffer[HCML_MAX_LEN_LINE + 1];
	size_t counter = 0;

	rewind(hcml_file->file);
	while (fgets(buffer, HCML_MAX_LEN_LINE, hcml_file->file)) {
		if (hcml_get_type(buffer) == HCML_ENTRY) counter++;
	}

	return counter;
}

// Done + doubts
int64_t hcml_get_line_key(hcml_file_t* hcml_file, const char* family, const char* key) {
	assert(family != NULL && key != NULL);

	if (hcml_key_exist(hcml_file, family, key)) {
		char line_buffer[HCML_MAX_LEN_LINE + 1];
		size_t line_num = 1;

		rewind(hcml_file->file);
		while (fgets(line_buffer, HCML_MAX_LEN_LINE, hcml_file->file)) {
			hcml_entry_t entry;
			hcml_entry_parse(&entry, line_buffer);
			if (strcmp(entry.key, key)) line_num++;
			else break;
		}

		return line_num;
	}
	else return -1;
}
