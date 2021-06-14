#include "server.h"

SocketObj *sockets;

void *connection_handler(void *socket_desc);

static void *on_dir_change(void *socket_desc);

Command parse_command(char *command_str) {
    for (int i = GET_LIST; i <= UNDEFINED; ++i) {
        if (strcmp(COMMAND[i], command_str) == 0) return (Command) i;
    }
    return UNDEFINED;
}

FILE *openfile(const char *dirname, struct dirent *dir, const char *mode, char **date) {
    char pathname[1024] = {0};
    FILE *f;
    sprintf(pathname, "%s/%s", dirname, dir->d_name);
    f = fopen(pathname, mode);

    struct stat attr;
    stat(pathname, &attr);
    *date = ctime(&attr.st_mtime);
    return f;
}

int run_server(unsigned int port, char *path) {
    chdir(path);

    struct sockaddr_in server_addr, client_addr;
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        perror("Could not create socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    int opt = 1;
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) perror("setsockopt");

    if (bind(socket_desc, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed. Error");
        exit(1);
    }
    listen(socket_desc, 3);

    printf("Server listen on port %d...\n", port);

    pthread_t dir_state_thread;
    pthread_create(&dir_state_thread, NULL, on_dir_change, NULL);

    int c = sizeof(struct sockaddr_in), client_sock;
    while ((client_sock = accept(socket_desc, (struct sockaddr *) &client_addr, (socklen_t *) &c))) {
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("Connection accepted; Client IP: %s\n", client_ip);

        sockets = sflist_append(sockets, client_sock);

        int *new_sock = malloc(1);
        *new_sock = client_sock;

        pthread_t sniffer_thread;
        pthread_create(&sniffer_thread, NULL, connection_handler, (void *) (new_sock));
    }
    if (client_sock < 0) {
        perror("accept failed");
        exit(1);
    }

    return 0;
}

void notify(int sock){
    printf("Sending notification to socket %d\n", sock);
    char *resp = malloc(BUFSIZ);
    memset(resp, 0, BUFSIZ);
    strcpy(resp, STATUS[UPDATE]);
    write(sock, resp, BUFSIZ);
    free(resp);
}

void *on_dir_change(void *socket_desc) {
    int length, i = 0, wd;
    int fd;
    char buffer[BUF_LEN];

    char *working_dir = malloc(255 * sizeof(char));
    getwd(working_dir);


    /* Initialize Inotify*/
    fd = inotify_init();
    if ( fd < 0 ) {
    perror( "Couldn't initialize inotify");
    }

    /* add watch to starting directory */
    wd = inotify_add_watch(fd, working_dir, IN_CREATE | IN_MODIFY | IN_DELETE); 

    if (wd == -1)
    {
        printf("Couldn't add watch to %s\n", working_dir);
    }
    else
    {
        printf("Watching:: %s\n", working_dir);
    }

    /* do it forever*/
    while(1)
    {
        i = 0;
        length = read( fd, buffer, BUF_LEN );  

        if ( length < 0 ) {
        perror( "read" );
        }  

        while ( i < length ) {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
        if ( event->len ) {
            if ( event->mask & IN_CREATE) {
                slist_observer(sockets, notify);      
            }
            if ( event->mask & IN_DELETE) {
                slist_observer(sockets, notify);     
            }  
            i += EVENT_SIZE + event->len;
        }
        }
    }
    /* Clean up*/
    inotify_rm_watch( fd, wd );
    close( fd );

    return 0;
}



void *connection_handler(void *socket_desc) {
    int sock = *(int *) socket_desc;
    char *response, client_message[BUFSIZ] = {0};

    int read_size;
    while ((read_size = recv(sock, client_message, BUFSIZ, 0)) > 0) {
        Command command = parse_command(client_message);
        char *body = trim(client_message + REQUEST_BODY_OFFSET);

        printf("New command: %s;    Body: %s\n", COMMAND[command], body);

        response = malloc(BUFSIZ * 8);
        memset(response, 0, sizeof(*response));

        switch (command) {
            case GET_LIST: {
                struct dirent **namelist;
                int n = scandir(body, &namelist, NULL, alphasort);
                if (n < 0) {
                    perror("Couldn't open the directory");
                    strcpy(response, STATUS[ERROR]);
                    strcpy(response + RESPONSE_BODY_OFFSET, "Couldn't open the directory");
                    write(sock, response, BUFSIZ);
                } else {
                    char *ptr = response;
                    for (int i = 0; i < n; i++) {
                        char *date;

                        FILE *f = openfile(body, namelist[i], "r", &date);
                        if (namelist[i]->d_type == DT_REG) {
                            fseek(f, 0, SEEK_END);
                            ptr += sprintf(ptr, "FILE\t%s\t%lu\t%s\n", namelist[i]->d_name, ftell(f), date);
                        } else if (namelist[i]->d_type == DT_DIR) {
                            ptr += sprintf(ptr, "DIR\t%s\t%d\t%s\n", namelist[i]->d_name, 0, date);
                        }

                        fclose(f);
                        free(namelist[i]);
                    }
                    write(sock, response, BUFSIZ * 8);
                }
                break;
            }
            case GET_FILE:
                if (!file_exists(body)) {
                    strcpy(response, STATUS[ERROR]);
                    strcpy(response + RESPONSE_BODY_OFFSET, "File not found!");
                    write(sock, response, BUFSIZ);
                } else if (is_directory(body)) {
                    strcpy(response, STATUS[ERROR]);
                    strcpy(response + RESPONSE_BODY_OFFSET, "Isn't regular file!");
                    write(sock, response, BUFSIZ);
                } else {
                    FILE *file = fopen(body, "r");
                    if (file == NULL) {
                        strcpy(response, STATUS[ERROR]);
                        strcpy(response + RESPONSE_BODY_OFFSET, "Couldn't read file!");
                        write(sock, response, BUFSIZ);
                    } else {
                        int fd = open(body, O_RDONLY);
                        struct stat file_stat;
                        fstat(fd, &file_stat);
                        printf("File Size: %ld bytes\n", file_stat.st_size);

                        sprintf(response, "%lu", file_stat.st_size);
                        write(sock, response, BUFSIZ);


                        long long remain_data = file_stat.st_size;
                        int offset = 0;
                        do {
                            int count = remain_data > BUFSIZ ? BUFSIZ : remain_data;
                            char *data = malloc(count);

                            pread(fd, data, count, offset);
                            offset += count;

                            write(sock, data, count);
                            free(data);

                            remain_data -= count;
                            printf("[+] Sent %d bytes of file... Remaining: %llu\n", count, remain_data);

                        } while (remain_data > 0);
                        printf("File data sent successfully.\n\n");
                    }
                    fclose(file);
                }
                break;
            case UPLOAD: {
                //UPLOAD    \0file.txt
                //12455
                char *file_response = malloc(BUFSIZ);
                recv(sock, file_response, BUFSIZ, 0);
                long long file_size = atoll(file_response);
                printf("File Size: %lld bytes\n", file_size);

                long long remain_data = file_size;
                FILE *fp = fopen(body, "w");
                while (remain_data > 0) {
                    int len = recv(sock, file_response, BUFSIZ, 0);
                    fwrite(file_response, len, 1, fp);
                    remain_data -= len;
                    memset(file_response, 0, BUFSIZ);
                    printf("[+] Received %d bytes of file... Remaining: %llu\n", len, remain_data);
                }
                free(file_response);
                fclose(fp);
                break;

            }
            case UNDEFINED:
            default:
                write(sock, client_message, strlen(client_message));
                break;
        }
        memset(client_message, 0, sizeof(client_message));
        free(response);
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    sockets = slist_remove(sockets, sock);

    close(sock);
    free(socket_desc);
    return 0;
}
