#include "../headers/server.h"

char* getFile(const char* filename){
    DIR* static_files_dir = opendir(FILES_FOLDER);
    if (static_files_dir == NULL) {
        perror("opendir");
        return NULL;
    }

    struct dirent* entry;
    char* found = NULL;
    while ((entry = readdir(static_files_dir)) != NULL){ //there are still files in the folder
        if (strcasecmp(entry->d_name,filename)) {
            found = entry->d_name;
            break;
        }
    }
    closedir(static_files_dir);
    return found; 
}