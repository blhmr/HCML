/* ---- HCML: Hatim's configuration markup language ---- */

#ifndef __HCML_H__
#define __HCML_H__

#ifdef __c_plus_plus
extern C {
#endif

/* ---- Standard libraries ---- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>

/* ---- Macros ---- */
#ifndef HCML_MAX_LEN_KEY
	#define HCML_MAX_LEN_KEY 50
#endif

#ifndef HCML_MAX_LEN_VALUE
	#define HCML_MAX_LEN_VALUE 50
#endif

#ifndef HCML_MAX_LEN_FAMILY
	#define HCML_MAX_LEN_FAMILY 50
#endif

#ifndef HCML_MAX_LEN_ARRAY
	// Size of each element in an array
	#define HCML_MAX_LEN_ARRAY 20
#endif

#define HCML_MAX_LEN_LINE (HCML_MAX_LEN_KEY + HCML_MAX_LEN_VALUE + HCML_MAX_LEN_FAMILY + 9) // In case im wrong

/* ---- Enumerations ---- */
typedef enum {
	HCML_COMMENT = 1,
	HCML_BLANK = 0,
	HCML_ENTRY = 2,
	HCML_UNKOWN = -1
} hcml_type_t;

/* ---- Structures ---- */
typedef struct __attribute__((packed)) {
	char family [HCML_MAX_LEN_FAMILY + 1];
	char key [HCML_MAX_LEN_KEY + 1];
	char value [HCML_MAX_LEN_VALUE + 1];
} hcml_entry_t;

typedef struct __attribute__((packed)) {
	char filename[255];
	FILE* file;
} hcml_file_t;

/* ---- Functions ---- */
// hcml_file.c (DONE)
int hcml_file_open(hcml_file_t* hcml_file, const char* filename);											// Open HCML file
int hcml_file_close(hcml_file_t* hcml_file);																// Close HCML file
int hcml_file_rename(hcml_file_t* hcml_file, const char* newname);											// Rename HCML file
int hcml_file_delete(hcml_file_t* hcml_file);																// Delete HCML file

// hcml_handle.c
char* hcml_get_value(hcml_file_t* hcml_file, const char* family, const char* key);							// Get the value as string (must be freed) 

int hcml_insert_value(hcml_file_t* hcml_file, const char* family, const char* key, const char* value);		// Insert the value into HCML file
int hcml_insert_value_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry);								// Same thing using the hcml_entry_t struct

int hcml_update_value(hcml_file_t* hcml_file, const char* family, const char* key, const char* value);		// Update a value in HCML file
int hcml_update_value_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry);								// Same thing using entry struct

int hcml_delete_key(hcml_file_t* hcml_file, const char* family, const char* key);							// Delete a key from HCML file
int hcml_delete_key_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry);								// .... using struct

int hcml_delete_family(hcml_file_t* hcml_file, const char* family);											// Delete the whole family

// hcml_info.c (DONE)
bool hcml_family_exist(hcml_file_t* hcml_file, const char* family);											// Check if family exists
bool hcml_key_exist(hcml_file_t* hcml_file, const char* family, const char* key);							// Check if key exists
size_t hcml_entry_num(hcml_file_t* hcml_file);																// Check how many entries are in a HCML file
int64_t hcml_get_line_key(hcml_file_t* hcml_file, const char* family, const char* key);						// Get the line number of an entry

/* Undone */
void hcml_line_info(const char* line);

// hcml_entry.c (DONE)
hcml_entry_t hcml_entry_create(const char* family, const char* key, const char* value);						// Initialize the entry struct
int hcml_entry_parse(hcml_entry_t* hcml_entry, const char* string);											// Parse a string to entry struct, must end with '\n'

// hcml_enums.c (DONE)
hcml_type_t hcml_get_type(const char* line);																// Get the type of a string line, ends with '\n' (For example: Blank or comment or entry)

// hcml_array.c
//
//	<food: fruits = apple,banana,orange>
//	hcml_value_is_array() => true
//	hcml_parse_from_array() => {"apple", "banana", "orange"}
//	hcml_parse_to_array(3, "apple", "banana", "orange") => "apple,banana,orange"
//
bool hcml_value_is_array(const char* value);
char** hcml_parse_from_array(const char* string);
char* hcml_parse_to_array(int num_args, ...);

// hcml_string.c
//
// family: letters, numbers, underscore and dot
// key: letters, numbers and underscore
// value: anything that is in ASCII or UTF-8
//
bool hcml_valid_family(const char* family);
bool hcml_valid_key(const char* key);
bool hcml_valid_value(const char* value);
bool hcml_valid_entry(hcml_entry_t* entry);

#ifdef __c_plus_plus
} // extern C
#endif

#endif
