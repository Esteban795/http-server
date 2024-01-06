#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <regex.h>
#include <sys/socket.h>

#include "string_utils.h"
#include "http.h"

#define MYPORT 8080
#define BUFFER_SIZE 32768
#define MAX_CLIENTS 100

char* getFile(const char* filename);

void* createClientThread(void* arg);

#endif