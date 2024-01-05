#ifndef STRING_UTLIS_H
#define STRING_UTLIS_H

#include <string.h>
#include <stdbool.h>
#include <strings.h>

const char* getFileExt(const char* filename);

const char* getMimeType(const char* file_ext);


#endif