/* Hatim's Configuration Markup Language */

// hcml_file.c
#include "../include/hcml.h"

int hcml_file_open(hcml_file_t* hcml_file, const char* filename) {
	assert(filename != NULL);

	strncpy(hcml_file->filename, filename, 255);
	hcml_file->filename[strlen(filename)] = '\0';

	hcml_file->file = fopen(hcml_file->filename, "a+");
	if (hcml_file->file == NULL) return -1;
	return 0;
}

int hcml_file_close(hcml_file_t* hcml_file) {
	if (hcml_file->file == NULL) return -1;
	else fclose(hcml_file->file);
	hcml_file->filename[0] = '\0';
	return 0;
}

int hcml_file_rename(hcml_file_t* hcml_file, const char* newname) {
	if (hcml_file->file == NULL) return -1;
	else {
		rename(hcml_file->filename, newname);
		hcml_file->filename[0] = '\0';
		strcpy(hcml_file->filename, newname);
		return 0;
	}
}


int hcml_file_delete(hcml_file_t* hcml_file) {
	if (hcml_file->file == NULL) return 1;
	else {
		remove(hcml_file->filename);
		hcml_file->filename[0] = '\0';
		return 0;
	}
}

