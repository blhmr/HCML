/* Hatim's Configuration Markup Language */

// hcml_array.c
#include "../include/hcml.h"

// Done and tested
bool hcml_value_is_array(const char* value) {
	return strchr(value, ';') != NULL;
}

char** hcml_parse_from_array(const char* string) {
	assert(string != NULL);
	char** elements = malloc(sizeof(char*) * HCML_MAX_LEN_ARRAY);
	const char* delimiter = ";";
	char* token;
	int index = 0;

	// printf("STRING: %s\n", string);

	if (elements == NULL) return NULL;

	char string_clone[strlen(string)];
	for (size_t i = 0; i < strlen(string); i++) {
		string_clone[i] = string[i];
	}

	string_clone[strlen(string_clone)] = '\0';

	token = strtok(string_clone, delimiter);

	while (token != NULL) {
		elements[index] = strdup(token);
		if (elements[index] == NULL) {
			for (int i = 0; i < index; i++) {
				free(elements[i]);
			}
			free(elements);
			return NULL;
		}

		token = strtok(NULL, delimiter);
		index++;
	}

	elements[index] = NULL;
	return elements;
}

char* hcml_parse_to_array(int num_args, ...) {
	va_list args;
	va_start(args, num_args);
	int index = 0;

	char* array_string = malloc(HCML_MAX_LEN_VALUE * sizeof(char));
	if (array_string == NULL) return NULL;

	for (int i = 0; i < num_args; i++) {
		const char* arg = va_arg(args, const char*);
		index += snprintf(array_string + index, HCML_MAX_LEN_VALUE - index, "%s%s", (i == 0 ? "" : ";"), arg);
	}

	array_string[index] = '\0';

	va_end(args);

	return array_string;
}
