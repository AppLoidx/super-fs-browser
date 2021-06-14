#include <fcntl.h>
#include <pthread.h>
#include "client.h"

static char *current_dir;
static int server_socket;


void build_request(char **request, Command command, char *body) {
    char *ret = malloc(BUFSIZ);
    memset(ret, 0, BUFSIZ);
    if (ret != NULL) {
        strcpy(ret, COMMAND[command]);
        strcpy(ret + REQUEST_BODY_OFFSET, body);
    }
    *request = ret;
}

void parse_file_info(char *str, File **file) {
    File *ret = malloc(sizeof *ret);
    if (ret != NULL) {
        ret->name = malloc(255 * sizeof(char));
        ret->type = malloc(5 * sizeof(char));
        ret->date = malloc(25 * sizeof(char));
        memset(ret->name, 0, 255 * sizeof(char));
        memset(ret->type, 0, 5 * sizeof(char));
        memset(ret->date, 0, 25 * sizeof(char));

        char *tmp_size = malloc(20 * sizeof(char *));
        memset(tmp_size, 0, sizeof(&tmp_size));


        int step = 0;
        int prev_idx = 0;
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == '\t') {
                if (step == 0) memcpy(ret->type, str, i);
                if (step == 1) memcpy(ret->name, str + prev_idx + 1, i - prev_idx - 1);
                if (step == 2) {
                    memcpy(tmp_size, str + prev_idx + 1, i - prev_idx - 1);
                    ret->size = strtoul(tmp_size, NULL, 10);
                    memcpy(ret->date, str + i + 1, strlen(str) - i - 1);
                    break;
                }
                prev_idx = i;
                step++;
            }
        }

        free(tmp_size);
    }
    *file = ret;
}

void get_files_list() {
    char *request;
    char *response = malloc(BUFSIZ * 8);
    memset(response, 0, BUFSIZ * 8);

    build_request(&request, GET_LIST, current_dir);
    if (send(server_socket, request, BUFSIZ, 0) <= 0) {
        refresh();
        endwin();
        perror("Could not send data");
        exit(1);
    }
    if (recv(server_socket, response, BUFSIZ * 8, 0) <= 0) {
        refresh();
        endwin();
        puts("recv failed");
        exit(1);
    }

    init_file_wrap();
    char *line_ptr = strtok(response, "\n");
    while (line_ptr != NULL) {
        File *file;
        parse_file_info(line_ptr, &file);
        append_file_info(file);

        line_ptr = strtok(NULL, "\n");
        free(file->type);
        free(file->name);
        free(file->date);
        free(file);
    }

    print_files_info();
    free(request);
    free(response);
}

void download_file(char *name, char *save_name, bool need_open) {
    char *path = malloc(255 * sizeof(char));
    strcat(path, current_dir);
    strcat(path, "/");
    strcat(path, trim(name));

    char *response = malloc(BUFSIZ);
    memset(response, 0, BUFSIZ);

    char *request;
    build_request(&request, GET_FILE, path);
    free(path);


    if (send(server_socket, request, BUFSIZ, 0) <= 0) {
        refresh();
        endwin();
        perror("Could not send data");
        exit(1);
    }

    if(recv(server_socket, response, BUFSIZ, 0) <= 0){
        refresh();
        endwin();
        puts("recv failed");
        exit(1);
    }

    long file_size = atol(response);
    memset(response, 0, BUFSIZ);

    long remain_data = file_size;

    printf("Saved to temp file with name %s", save_name);

    FILE *fp = fopen(save_name, "w");
    while (remain_data > 0) {
        int len = recv(server_socket, response, BUFSIZ, 0);
        fwrite(response, len, 1, fp);
        remain_data -= len;
        memset(response, 0, BUFSIZ);
    }
    fclose(fp);

    if (need_open) init_file_view();

    free(request);
    free(response);
}

void on_download(char *name) {
    download_file(name, name, false);
}

void on_upload(char *name) {
    if (strcmp(name, "") == 0) return;

    int position = -1;
    for (int i = 0; i < strlen(name); ++i)
        if (name[i] == '/') position = i;

    char *file_name = malloc(255 * sizeof(char));
    memset(file_name, 0, 255 * sizeof(char));
    strcpy(file_name, name + (position != -1 ? position + 1 : 0));

    if (file_exists(name) && !is_directory(name)) {
        int fd = open(name, O_RDONLY);
        struct stat file_stat;
        fstat(fd, &file_stat);

        char *request;
        build_request(&request, UPLOAD, file_name);
        send(server_socket, request, BUFSIZ, 0);
        free(request);

        request = malloc(BUFSIZ);
        memset(request, 0, BUFSIZ);

        sprintf(request, "%lu", file_stat.st_size);
        send(server_socket, request, BUFSIZ, 0);
        free(request);

        long long remain_data = file_stat.st_size;
        int offset = 0;
        do {
            int count = remain_data > BUFSIZ ? BUFSIZ : remain_data;
            char *data = malloc(count);

            pread(fd, data, count, offset);
            offset += count;

            send(server_socket, data, count, 0);
            free(data);

            remain_data -= count;
        } while (remain_data > 0);

    }

    free(file_name);
    get_files_list();
}

void on_select(char *name, bool is_file) {
    if (name == NULL) {
        get_files_list();
        return;
    }
    if (!is_file) {
        if (strcmp(trim(name), ".") == 0) {
            get_files_list();
            return;
        } else if (strcmp(trim(name), "") == 0) {
            memset(current_dir, 0, sizeof(*current_dir));
            strcpy(current_dir, ".");
            get_files_list();
            return;
        } else if (strcmp(trim(name), "..") == 0) {
            int index = -1;
            for (int i = 0; i < strlen(current_dir); i++)
                if (current_dir[i] == '/') index = i;

            if (index != -1) {
                char *tmp = malloc(255 * sizeof(char));
                memset(tmp, 0, 255 * sizeof(char));
                memcpy(tmp, current_dir, index);

                memset(current_dir, 0, sizeof(*current_dir));
                strcpy(current_dir, tmp);

                get_files_list();
                free(tmp);
            }
        } else {
            strcat(current_dir, "/");
            strcat(current_dir, trim(name));
            get_files_list();
        }
    } else {
        download_file(name, BUFFER_TMP_FILE, true);
    }
}

static void *on_dir_change() {
    char *response = malloc(BUFSIZ);
    memset(response, 0, BUFSIZ);

    while (recv(server_socket, response, BUFSIZ, MSG_PEEK) > 0){
        if(strcmp(response, STATUS[UPDATE]) == 0){
            recv(server_socket, response, BUFSIZ, 0);
            if(!view_mode) get_files_list();
        }
    }
    free(response);
    return 0;
}

int start_client(char *address, unsigned int port) {
    struct sockaddr_in server;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Could not create socket");
        return 1;
    }
    server.sin_addr.s_addr = inet_addr(address);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(server_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Failed connect to server");
        return 1;
    }

    current_dir = malloc(255 * sizeof(char));
    memset(current_dir, 0, sizeof(*current_dir));
    strcpy(current_dir, ".");

    get_files_list();

    pthread_t sniffer_thread;
    pthread_create(&sniffer_thread, NULL, on_dir_change, NULL);

    start_read_key(on_select, on_download, on_upload);


    close(server_socket);
    free(current_dir);
    return 0;
}