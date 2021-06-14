#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"
#include "client.h"
#include "server.h"


void help(char *argv[]) {
    printf("Usage:\n"
           "\t%s server <port> <working_dir>    - Run server\n"
           "\t%s client <port> <ip_address>        - Connect to server\n", argv[0], argv[0]);
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        int port = atoi(argv[2]);
        if (port <= 0 || port > 65535) {
            puts("Неверно задан порт");
            exit(1);
        }

        if (strcmp(argv[1], "server") == 0) {

            if (!file_exists(argv[3])) {
                puts("Выбранная директория не найдена!");
                exit(1);
            }

            if (!is_directory(argv[3])) {
                puts("Проверьте параметр рабочей директории!");
                exit(1);
            }

            return run_server(port, argv[3]);
        } else if (strcmp(argv[1], "client") == 0) {
            run_ui();
            return start_client(argv[3], port);
        } else help(argv);
    } else help(argv);


    return 0;
}
