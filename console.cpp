#include "console.h"

/**
 * @brief distributes commands from console
 * 
 * @param [in] command command that needs to be complited
 * 
 * @return execution status
 */
static int run_commands(char *command);
static int clean_buffer(FILE *stream);
static int sort_file(char **text, int text_line_len, compare_str_func func);
static int open_file(char *** text, int *text_line_len);
static int generate_text(char ***text_for_generate, int *text_for_generate_len);

int run_console(){
    while (1){
        char command[max_len] = {};
        printf(CONSOLE_PIRPLE ">>>" CONSOLE_RESET);

        int c = 0;
        c = getchar();
        if (c != '-')  continue;

        scanf("%10s", command);
        int command_status = run_commands(command);

        if (command_status == 1){
            printf(CONSOLE_PIRPLE "THE END\n" CONSOLE_RESET);
            return 0;
        }
        if (command_status == -1){
            printf(CONSOLE_RED "ERROR\n" CONSOLE_RESET);
        }
        if (command_status == -2){
            printf(CONSOLE_RED "There is no such command!\n" CONSOLE_RESET);
        }
        clean_buffer(stdin);
    }
}

int clean_buffer(FILE *stream){
    int c = 0;
    do{
        c = fgetc(stream);
    } while (c != '\n' && c != EOF);

    return c ==  EOF;
}

static int run_commands(char *command){
    static char **text = NULL;
    static int   text_line_len = 0;

    static char **text_for_generate = NULL;
    static int    text_for_generate_len = 0;

    if (my_strcmp(command, "q") == 0) return 1;

    if (my_strcmp(command, "of") == 0){
        return open_file(&text, &text_line_len);
    }

    if (my_strcmp(command, "s1") == 0){
        return sort_file(text, text_line_len, my_strcmp);
    }

    if (my_strcmp(command, "s2") == 0){
        return sort_file(text, text_line_len, my_strcmp_without_case);
    }

    if (my_strcmp(command, "s3") == 0){
        return sort_file(text, text_line_len, my_strrcmp_without_case);
    }

    if (my_strcmp(command, "g") == 0){
        return generate_text(&text_for_generate, &text_for_generate_len);
    }

    return -2;
}


static int open_file(char *** text, int *text_line_len){
    int text_len  = 0;
    char file_name[max_len] = {};
    printf(CONSOLE_BLUE "Print file name: " CONSOLE_RESET);

    scanf("%100s", file_name);

    char *getted_text = read_file(file_name, &text_len);
    if (getted_text == NULL) return -1;

    *text_line_len = find_len_text_lines(getted_text);
    if (text_line_len == 0) return -1;

    *text = split_text(getted_text, *text_line_len);
    if (*text == NULL) return -1;
    printf(CONSOLE_GREEN "COMPLITED\n" CONSOLE_RESET);
    return 0;
}

static int sort_file(char **text, int text_line_len, compare_str_func func){
    if (text == NULL){
            return -1;
        }
    sort_text(text, text_line_len, func);
    print_text(text, text_line_len);
    return 0;
}

static int generate_text(char ***text_for_generate, int *text_for_generate_len){
    if (*text_for_generate == NULL){
        int text_len  = 0;
        const char *file_name = "ONEGIN.txt";

        char *getted_text = read_file(file_name, &text_len);
        if (getted_text == NULL) return -1;

        *text_for_generate_len = find_len_text_lines(getted_text);
        if (*text_for_generate_len == 0) return -1;

        *text_for_generate = split_text(getted_text, *text_for_generate_len);
        if (*text_for_generate == NULL) return -1;

        sort_text(*text_for_generate, *text_for_generate_len, my_strrcmp_without_case);
    }
    int generate_text_len = 0;

    printf(CONSOLE_BLUE "How many lines you want generate: " CONSOLE_RESET);
    scanf("%d", &generate_text_len);

    generate_random_text(*text_for_generate, *text_for_generate_len, generate_text_len);
    return 0;
}