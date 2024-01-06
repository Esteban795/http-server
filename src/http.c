#include "../headers/http.h"

char* decodeURL(const char* src) {
    size_t src_len = strlen(src);
    char* decoded = malloc(FILES_FOLDER_LEN + src_len + 1);
    size_t decoded_len = FILES_FOLDER_LEN;
    memcpy(decoded,FILES_FOLDER,FILES_FOLDER_LEN);
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
    int file_fd = open(filename,O_RDONLY);
    if (file_fd == -1) { //file doesn't exist
        snprintf(response, BUFFER_SIZE,"HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found");
        return strlen(response);
    }
    int response_len = strlen(HTTPHeader);
    memcpy(response,HTTPHeader,strlen(HTTPHeader));

    ssize_t bytes_read;
    while ((bytes_read = read(file_fd,response + response_len,BUFFER_SIZE - response_len)) > 0) {
        response_len += bytes_read;
    }
    free(HTTPHeader);
    close(file_fd);
    return response_len;
}