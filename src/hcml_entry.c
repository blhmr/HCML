/* Hatim's Configuration Markup Language */

// hcml_entry.c
#include "../include/hcml.h"

hcml_entry_t hcml_entry_create(const char* family, const char* key, const char* value) {
	hcml_entry_t entry;
	
	if (hcml_valid_family(family) && hcml_valid_key(key) && hcml_valid_value(value)) {
		strcpy(entry.family, family);
		strcpy(entry.key, key);
		strcpy(entry.value, value);
	}
	else entry = (hcml_entry_t) {"0", "0", "0"};

	return entry;
}

int hcml_entry_parse(hcml_entry_t* hcml_entry, const char* string) {
	assert(string != NULL);

	if (hcml_get_type(string) == HCML_ENTRY) {
		if (sscanf(string, "<%[^:]: %[^ ] = %[^>]>", hcml_entry->family, hcml_entry->key, hcml_entry->value) == 3)
			return 0;
		else return -1;
	}
	else return -2;
}
