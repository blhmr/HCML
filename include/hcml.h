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

// <family: key = value>, '<' + family_len + ':' + space + key_len + space + '=' + value_len + '>'
// So that means:		family + key + value + 8

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
int hcml_file_open(hcml_file_t* hcml_file, const char* filename);
int hcml_file_close(hcml_file_t* hcml_file);
int hcml_file_rename(hcml_file_t* hcml_file, const char* newname);
int hcml_file_delete(hcml_file_t* hcml_file);

// hcml_handle.c
char* hcml_get_value(hcml_file_t* hcml_file, const char* family, const char* key); // DONE

int hcml_insert_value(hcml_file_t* hcml_file, const char* family, const char* key, const char* value);
int hcml_insert_value_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry);

int hcml_update_value(hcml_file_t* hcml_file, const char* family, const char* key, const char* value);
int hcml_update_value_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry);

/* ------------ THESE ARE UNDONE -----------------*/
int hcml_delete_key(hcml_file_t* hcml_file, const char* family, const char* key);
int hcml_delete_key_entry(hcml_file_t* hcml_file, hcml_entry_t* hcml_entry);

int hcml_delete_family(hcml_file_t* hcml_file, const char* family);
/* -----------------------------------------------*/

// hcml_info.c (DONE)
bool hcml_family_exist(hcml_file_t* hcml_file, const char* family);
bool hcml_key_exist(hcml_file_t* hcml_file, const char* family, const char* key);
size_t hcml_entry_num(hcml_file_t* hcml_file);
int64_t hcml_get_line_key(hcml_file_t* hcml_file, const char* family, const char* key);

// hcml_entry.c (DONE)
hcml_entry_t hcml_entry_create(const char* family, const char* key, const char* value);
int hcml_entry_parse(hcml_entry_t* hcml_entry, const char* string);

// hcml_enums.c (DONE)
hcml_type_t hcml_get_type(const char* line);

#ifdef __c_plus_plus
} // extern C
#endif

#endif
