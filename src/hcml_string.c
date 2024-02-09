/* Hatim's Configuration Markup Language */

// hcml_string.c
#include "../include/hcml.h"

bool hcml_valid_family(const char* family) {
    if (family == NULL || strlen(family) == 0) // handle null or empty string
        return false;

    while (*family != '\0') {
        char c = *family;
        if (!(isalnum(c) || c == '_' || c == '/')) // check if character is a letter, number, underscore, or slash
            return false;
        family++;
    }

    return true;
}

bool hcml_valid_key(const char* key) {
    if (key == NULL || strlen(key) == 0) // handle null or empty string
        return false;

    while (*key != '\0') {
        char c = *key;
        if (!(isalnum(c) || c == '_')) // check if character is a letter, number, or underscore
            return false;
        key++;
    }

    return true;
}

bool hcml_valid_value(const char* value) {
    if (value == NULL || strlen(value) == 0)
		return false;
	else
		return true;
}

bool hcml_valid_entry(hcml_entry_t* entry) {
	return (hcml_valid_key(entry->key) && hcml_valid_family(entry->family) && hcml_valid_value(entry->value));
}

