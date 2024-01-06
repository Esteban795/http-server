#include "../headers/http.h"

char* decodeURL(const char* src) {
    size_t src_len = strlen(src);
    char* decoded = malloc(src_len + 1);
    size_t decoded_len = 0;

    // decode %2x to hex
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] == '%' && i + 2 < src_len) {
            int hex_val;
            sscanf(src + i + 1, "%2x", &hex_val);
            decoded[decoded_len++] = hex_val;
            i += 2;
        } else decoded[decoded_len++] = src[i];
    }
    decoded[decoded_len] = '\0';
    return decoded;
}

int buildHTTPresponse(const char* filename, const char* file_ext, char* response) {
    const char* mime_type = getMimeType(file_ext);
    char* HTTPHeader = malloc(sizeof(char) * BUFFER_SIZE);

    snprintf(HTTPHeader, BUFFER_SIZE,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n",mime_type);
    int file_fd = open(filename,"r");
    if (file_fd == -1) { //file doesn't exist
        snprintf(response, BUFFER_SIZE,"HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found");
        return strlen(response);
    }
    struct stat filestat;
    fstat(file_fd,&filestat);
}