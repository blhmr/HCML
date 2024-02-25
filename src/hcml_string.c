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

char *string_replace(char *before, char *oldsub, char *newsub) {
  int old_length = strlen(oldsub);
  int new_length = strlen(newsub);
  int before_length = strlen(before);
  
  char *after;
  
  if (old_length == new_length) {
    after = malloc((before_length + 1) * sizeof(char));
  }
  else {
    int occurrences = 0;
    
    int i = 0;
    while (i < before_length) {
      if (strstr(&before[i], oldsub) == &before[i]) {
        occurrences++;
        i += old_length;
      }
      else i++;
    }
    int sub_diff = new_length - old_length;
    int after_length = before_length;
    after_length += occurrences * sub_diff;
    
    after = malloc((after_length + 1) * sizeof(char));
  }
  
  int i = 0;
  int j = 0;
  
  while ((size_t) i < strlen(before)) {
    if (strstr(&before[i], oldsub) == &before[i]) {
      strcpy(&after[j], newsub);
      i += old_length;
      j += new_length;
    }
    else
    {
      after[j] = before[i];
      i++;
      j++;
    }
  }
  after[j] = '\0';
  return after;
}

char* hcml_to_buffer(char* buffer) {
	return string_replace(buffer, " \\", (char*) "\n");
}

char* buffer_to_hcml(char* buffer) {
	return string_replace(buffer, (char*) "\n", " \\");
} 
