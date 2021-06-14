#include "ui.h"
#include "flist.h"

#define SELECTED COLOR_PAIR(1)

WINDOW *window_main, *window_size, *window_date, *window_help, *pad;
int cursor = 2;
int pointer = 0;
int files_count = 0;
static FileObj *files = NULL;
bool view_mode = false;

void init_file_wrap() {
    files = flist_clear(files);
    cursor = 2;
    pointer = 0;

    wclear(window_main);
    wborder(window_main, '|', '|', ' ', ' ', ' ', ' ', ' ', ' ');

    wclear(window_size);
    wborder(window_size, ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ');

    wclear(window_date);
    wborder(window_date, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

}

void print_files_info() {
    FileObj *ptr = files;
    files_count = 0;
    while (ptr != NULL) {
        files_count++;
        File *file = &ptr->file;
        if (pointer == cursor - 2) {
            wattron(window_main, SELECTED);
            wmove(window_main, cursor, 2 + strlen(file->name));
            wprintw(window_main, "%*c", (COLS - 2 - strlen(file->name) - 38), ' ');
        }
        wmove(window_main, cursor, 2);
        wprintw(window_main, "%s", file->name);
        if (strcmp(file->type, "FILE") == 0) {
            wmove(window_size, cursor, 3);
            wprintw(window_size, "%s", "F");
        } else {
            wmove(window_size, cursor, 3);
            wprintw(window_size, "%s", "D");
        }

        wmove(window_date, cursor, 1);
        wprintw(window_date, "%s", file->date);


        wattroff(window_main, SELECTED);

        wrefresh(window_main);
        wrefresh(window_size);
        wrefresh(window_date);
        cursor++;

        ptr = ptr->next;
    }
}

void append_file_info(File *file) {
    files = flist_append(files, file->name, file->type, file->date, file->size);
}

void main_window_widget() {
    int width = COLS - 36;
    window_main = newwin(LINES - 2, width, 0, 0);
    keypad(window_main, TRUE);
    noecho();

    wborder(window_main, '|', '|', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window_main);

}

void size_window_widget() {
    int width = 10;
    window_size = newwin(LINES - 2, width, 0, COLS - 36);
    wborder(window_size, ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window_size);
}

void date_window_widget() {
    int width = 25;
    window_date = newwin(LINES - 2, width, 0, COLS - 26);
    wborder(window_date, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window_date);
}

void help_window_widget() {
    window_help = newwin(2, COLS, LINES - 2, 0);
    wborder(window_help, '|', '|', ' ', ' ', ' ', ' ', ' ', ' ');

    if (!view_mode) {
        wattron(window_help, SELECTED);
        wmove(window_help, 0, 1);
        wprintw(window_help, EXIT_LETTER_SPACED);

        wmove(window_help, 1, 1);
        wprintw(window_help, REFRESH_LETTER_SPACED);

        wmove(window_help, 0, 18);
        wprintw(window_help, " Enter ");

        wmove(window_help, 1, 18);
        wprintw(window_help, BACK_TO_HOME_LETTER_SPACED);

        wmove(window_help, 0, 51);
        wprintw(window_help, DOWNLOAD_LETTER_SPACED);

        wmove(window_help, 1, 51);
        wprintw(window_help, UPLOAD_LETTER_SPACED);
        wattroff(window_help, SELECTED);

        wmove(window_help, 0, 5);
        wprintw(window_help, "Exit");
        wmove(window_help, 1, 5);
        wprintw(window_help, "Refresh");
        wmove(window_help, 0, 26);
        wprintw(window_help, "Open");
        wmove(window_help, 1, 26);
        wprintw(window_help, "Back to home");
        wmove(window_help, 0, 55);
        wprintw(window_help, "↓ Download file");
        wmove(window_help, 1, 55);
        wprintw(window_help, "↑ Upload file");
    } else {
        wattron(window_help, SELECTED);
        wmove(window_help, 0, 1);
        wprintw(window_help, EXIT_VIEW_MODE_LETTER_SPACED);

        wmove(window_help, 1, 1);
        wprintw(window_help, EXIT_LETTER_SPACED);

        wmove(window_help, 0, 18);
        wprintw(window_help, " ↑ ");

        wmove(window_help, 1, 18);
        wprintw(window_help, " ↓ ");
        wattroff(window_help, SELECTED);

        wmove(window_help, 0, 5);
        wprintw(window_help, "Close file");
        wmove(window_help, 1, 5);
        wprintw(window_help, "Exit");
        wmove(window_help, 0, 26);
        wprintw(window_help, "Prev line");
        wmove(window_help, 1, 26);
        wprintw(window_help, "Next line");
    }
    wrefresh(window_help);
}

void print_tmp_file() {
    wclear(pad);

    FILE *file = fopen(BUFFER_TMP_FILE, "r");
    if (file == NULL) exit(EXIT_FAILURE);
    char *line = NULL;
    size_t len = 0;
    int i = 0;
    while (getline(&line, &len, file) != -1 && view_mode) {
        if (i >= pointer) {
            if (strlen(line) > COLS - 2) i++;
            if (i <= (LINES + pointer - 4))
                wprintw(pad, "%s", line);
        }
        i++;
    }
    fclose(file);
    if (line != NULL) free(line);
    prefresh(pad, 0, 0, 0, 0, LINES - 2, COLS - 1);
    help_window_widget();
    refresh();

}

void init_file_view() {
    view_mode = true;
    wclear(window_main);
    delwin(window_size);
    delwin(window_date);
    delwin(window_help);
    refresh();

    pad = newpad(LINES - 2, COLS - 1);
    wborder(pad, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(pad);

    keypad(pad, TRUE);
    pointer = 0;

    usleep(10000);
    print_tmp_file();
}

void run_ui() {
    cursor = 2;
    pointer = 0;

    setlocale(LC_CTYPE, "ru_RU.UTF-8");
    initscr();
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    main_window_widget();
    size_window_widget();
    date_window_widget();
    help_window_widget();
}

void up_down_event() {
    wclear(window_main);
    wborder(window_main, '|', '|', ' ', ' ', ' ', ' ', ' ', ' ');

    wclear(window_size);
    wborder(window_size, ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ');

    wclear(window_date);
    wborder(window_date, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    usleep(5000);
    print_files_info();
}

int old_pointer = 0;

void start_read_key(void (*on_select)(char *, bool), void (*on_download)(char *), void (*on_upload)(char *)) {
    curs_set(0);
    int c;
    while ((c = toupper(wgetch(view_mode ? pad : window_main))) != EXIT_LETTER) {
        if (view_mode) {
            if (c == KEY_DOWN) {
                pointer++;
                usleep(5000);
                print_tmp_file();
            }
            if (c == KEY_UP) {
                pointer--;
                print_tmp_file();
            }

            if (c == EXIT_VIEW_MODE_LETTER) {
                view_mode = false;
                delwin(pad);
                refresh();
                run_ui();
                pointer = old_pointer;
                print_files_info();
            }
        } else {
            if (c == KEY_UP) {
                if (pointer != 0) {
                    cursor = 2;
                    pointer--;
                    up_down_event();
                }
            }
            if (c == KEY_DOWN) {
                if (pointer != files_count - 1) {
                    cursor = 2;
                    pointer++;
                    up_down_event();
                }
            }
            if (c == 10 /*enter*/) {
                old_pointer = pointer;
                File file = flist_at(files, pointer)->file;
                on_select(file.name, strcmp(file.type, "DIR") != 0);
            }
            if (c == REFRESH_LETTER) {
                on_select(NULL, false);
            }
            if (c == HELP_LETTER) {
                on_select("", false);
            }
            if (c == DOWNLOAD_LETTER) {
                File file = flist_at(files, pointer)->file;
                if (strcmp(file.type, "DIR") != 0) on_download(file.name);
            }
            if (c == UPLOAD_LETTER) {
                WINDOW *window_input = newwin(1, COLS, LINES - 3, 0);
                wborder(window_input, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

                wattron(window_input, SELECTED);
                wprintw(window_input, " Input filename: ");
                echo();
                curs_set(1);
                wrefresh(window_input);
                char *path = malloc(255 * sizeof(char));
                wgetstr(window_input, path);

                wattroff(window_input, SELECTED);
                noecho();
                delwin(window_input);

                wclear(window_main);
                wborder(window_main, '|', '|', ' ', ' ', ' ', ' ', ' ', ' ');

                cursor = 2;
                print_files_info();
                on_upload(trim(path));
                free(path);
            }
        }
    }
    clear();
    endwin();
}
