/* Hatim's Configuration Markup Language */

// hcml_enums.c
#include "../include/hcml.h"

hcml_type_t hcml_get_type(const char* line) {
	size_t len = strlen(line);
	if (line[len] != '\n') {
		if (line[0] == '\n') return HCML_BLANK;
		else {
			if (line[0] == '#') return HCML_COMMENT;
			else if (line[0] == '<' && line[len - 2] == '>' && strchr(line, ':') != NULL && strchr(line, '=') != NULL) return HCML_ENTRY;
			else return HCML_UNKOWN;
		}
	}
	else {
		return HCML_UNKOWN;
	}
}
