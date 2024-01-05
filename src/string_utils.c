#include "../headers/string_utils.h"


const char* getFileExt(const char* filename) {
    const char* dot = strrchr(filename,'.');
    if (!dot || dot == filename) return "";
    else return dot + 1;
}

const char* getMimeType(const char* file_ext) {
    if (!strcasecmp(file_ext,"html")) return "text/html";
    else if (!strcasecmp(file_ext,"css")) return "text/css";
    else if (!strcasecmp(file_ext,"txt")) return "text/txt";
    else if (!strcasecmp(file_ext,"jpg") || !strcmp(file_ext,"jpeg")) return "image/jpg";
    else if (!strcasecmp(file_ext,"png")) return "image/png";
    else return "application/octet-stream";
}

