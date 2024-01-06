#ifndef HTTP_H
#define HTTP_H

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "string_utils.h"

#define BUFFER_SIZE 32768
#define FILES_FOLDER "./static/"
#define FILES_FOLDER_LEN strlen(FILES_FOLDER)


char* decodeURL(const char* src);

int buildHTTPresponse(const char* filename, const char* file_ext, char* response);

#endif