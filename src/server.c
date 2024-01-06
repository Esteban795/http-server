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

void* createClientThread(void* arg) {
    int client_fd = *((int*)arg); //cast to int and then dereference
    char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
    ssize_t bytes_rcvd = recv(client_fd,buffer,BUFFER_SIZE,0);
    if (bytes_rcvd > 0) {
        regex_t regex;
        regcomp(&regex, "^GET /([^ ]*) HTTP/1", REG_EXTENDED);
        regmatch_t matches[2];
        if (!regexec(&regex,buffer,2,matches,0)) { //get request detected
            buffer[matches[1].rm_eo] = '\0';
            const char* url_encoded_filename = buffer + matches[1].rm_so;
            char* filename = decodeURL(url_encoded_filename);

            char file_ext[32];
            strcpy(file_ext,getFileExt(filename));

            char* response = malloc(sizeof(char) * BUFFER_SIZE * 2);
            int response_len = buildHTTPresponse(filename,file_ext,response);

            send(client_fd,response,response_len,0);
            free(response);
            free(filename);
        }
        regfree(&regex);
    }
    close(client_fd);
    free(buffer);
    free(arg);
    return NULL;
}

int setupServer(int port){
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY; //accept connections from any address

    int server_fd = socket(AF_INET,SOCK_STREAM,0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int yes = 1;
    if (setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }


    if (listen(server_fd,MAX_CLIENTS) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server all set up and listening on port %d\n",port);
    return server_fd;
}

int main(int argc,char* argv[]){
    int MYPORT = 8080;
    if (argc == 2) {
        MYPORT = atoi(argv[1]);
    } else if (argc > 2) {
        fprintf(stderr,"Usage: %s [port] (default is 8080).\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    int server_fd = setupServer(MYPORT);
    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int* client_fd = malloc(sizeof(int)); //avoids annoying casts when threading
        if ((*client_fd = accept(server_fd,(struct sockaddr*)&client_addr,&client_addr_len)) == -1) {
            perror("accept");
            continue;
        }
        printf("New connection from %s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        pthread_t client_thread;
        pthread_create(&client_thread,NULL,createClientThread,(void*)client_fd);
        pthread_detach(client_thread);
        printf("Closed connection from %s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    }
    close(server_fd);
    return 0;
}