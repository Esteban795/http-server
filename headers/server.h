#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "string_utils.h"
#include "http.h"

#define MYPORT 8080
#define BUFFER_SIZE 32768
#define FILES_FOLDER "../static/"

char* getFile(const char* filename);

#endif