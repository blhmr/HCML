/* Hatim's Configuration Markup Language */

// hcml_handle.c
#include "../include/hcml.h"

// Done and tested
char* hcml_get_value(hcml_file_t* hcml_file, const char* family, const char* key) {
	assert(family != NULL && key != NULL);

	if (hcml_key_exist(hcml_file, family, key)) {
		char* value = malloc(HCML_MAX_LEN_VALUE + 1);
		char got_family[HCML_MAX_LEN_FAMILY + 1];
		char got_key[HCML_MAX_LEN_KEY + 1];

		char buffer[HCML_MAX_LEN_LINE + 1];

		int64_t line_num = hcml_get_line_key(hcml_file, family, key);

		rewind(hcml_file->file);
		for (int i = 0; i < line_num; i++) {
			fgets(buffer, HCML_MAX_LEN_LINE, hcml_file->file);
		}

		if (sscanf(buffer, "<%[^:]:%[^=]=%[^>]>\n", got_family, got_key, value) != 3) return NULL;
		else return value;
	}
	else return NULL;
}

// Done and tested
int hcml_insert_value(hcml_file_t* hcml_file, const char* family, const char* key, const char* value) {
	assert(family != NULL && key != NULL && value != NULL);

	rewind(hcml_file->file);
	hcml_entry_t entry = hcml_entry_create(family, key, value);

	if (!hcml_key_exist(hcml_file, family, key) && hcml_valid_entry(&entry)) {
		fprintf(hcml_file->file, "<%s:%s=%s>\n", family, key, value);
		return 0;
	}
	else return -1;
}

int hcml_insert_value_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry) {
	return hcml_insert_value(hcml_file, hcml_entry->family, hcml_entry->key, hcml_entry->value);
}

int hcml_update_value(hcml_file_t* hcml_file, const char* family, const char* key, const char* value) {
	assert(family != NULL && key != NULL && value != NULL);

	if (hcml_key_exist(hcml_file, family, key)) {
		char buffer[HCML_MAX_LEN_LINE + 1];
		FILE* temp = fopen("temp____.hcml", "a+");

		rewind(hcml_file->file);
		while (fgets(buffer, HCML_MAX_LEN_LINE, hcml_file->file)) {
			hcml_entry_t entry;
			if (hcml_get_type(buffer) == HCML_ENTRY) {
				hcml_entry_parse(&entry, buffer);
				if (!strcmp(entry.family, family) && !strcmp(entry.key, key)) {
					fprintf(temp, "<%s:%s=%s>\n", family, key, value);
				}
				else fprintf(temp, "<%s:%s=%s>\n", entry.family, entry.key, entry.value);
			}
			else fprintf(temp, buffer, HCML_MAX_LEN_LINE);
		}

		// This was harder than expected lol
		remove(hcml_file->filename);
		rename("temp____.hcml", hcml_file->filename);
		hcml_file->file = (FILE*) temp;
		return 0;
	}
	else return -1;
}

// Done and tested
int hcml_update_value_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry) {
	return hcml_update_value(hcml_file, hcml_entry->family, hcml_entry->key, hcml_entry->value);
}

// Done and tested with some doubts
int hcml_delete_key(hcml_file_t* hcml_file, const char* family, const char* key) {
	assert(family != NULL && key != NULL);

	if (hcml_key_exist(hcml_file, family, key)) {
		char buffer[HCML_MAX_LEN_LINE + 1];
		FILE* temp = fopen("temp____.hcml", "a+");

		rewind(hcml_file->file);
		while (fgets(buffer, HCML_MAX_LEN_LINE, hcml_file->file)) {
			hcml_entry_t entry;
			if (hcml_get_type(buffer) == HCML_ENTRY) {
				hcml_entry_parse(&entry, buffer);
				if (strcmp(entry.family, family) || strcmp(entry.key, key)) {
					fprintf(temp, "<%s:%s=%s>\n", entry.family, entry.key, entry.value);
				}
			}
			else fprintf(temp, buffer, HCML_MAX_LEN_LINE);
		}

		// This was harder than expected lol
		remove(hcml_file->filename);
		rename("temp____.hcml", hcml_file->filename);
		hcml_file->file = (FILE*) temp;
		return 0;
	}
	else return -1;
}

// Done and tested
int hcml_delete_key_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry) {
	return hcml_delete_key(hcml_file, hcml_entry->family, hcml_entry->key);
}

int hcml_delete_family(hcml_file_t* hcml_file, const char* family) {
	assert(family != NULL);

	if (hcml_family_exist(hcml_file, family)) {
		char buffer[HCML_MAX_LEN_LINE + 1];
		FILE* temp = fopen("temp____.hcml", "a+");

		rewind(hcml_file->file);
		while (fgets(buffer, HCML_MAX_LEN_LINE, hcml_file->file)) {
			hcml_entry_t entry;
			if (hcml_get_type(buffer) == HCML_ENTRY) {
				hcml_entry_parse(&entry, buffer);
				if (strcmp(entry.family, family)) {
					fprintf(temp, "<%s:%s=%s>\n", entry.family, entry.key, entry.value);
				}
			}
			else fprintf(temp, buffer, HCML_MAX_LEN_LINE);
		}

		// This was harder than expected lol
		remove(hcml_file->filename);
		rename("temp____.hcml", hcml_file->filename);
		hcml_file->file = (FILE*) temp;
		return 0;
	}
	else return -1;
}
