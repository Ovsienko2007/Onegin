#include "console.h"

/**
 * @brief complit commands from console
 * 
 * @param [in] command command
 * 
 * @return command execution status
*/
static int run_commands(char *command);

/**
 * @brief clean buffer of stream
 * 
 * @param [in] stream stream
 * 
 * @return has the input in the stream ended
*/
static int clean_buffer(FILE *stream);

/**
 * @brief sort text lines by the funct and print result
 * 
 * @param [out]   text       the text
 * @param [in]    num_lines  the number of lines in text
 * @param [in]    func       the function by which sorting occurs
 * 
 * @return  function execution status
 */
static int sort_print_file(char **text, int text_line_len, compareFunc func);

/**
 * @brief read text from file and split it into lines 
 * 
 * @param [out]    text           lines from file
 * @param [out]    text_line_len  number of lines in text
 * 
 * @return  function execution status
 */
static int open_file(char *** text, int *text_line_len);

/**
 * @brief generate and print text by lines from another text, sort input text
 * 
 * @param [out]   text_for_generate       the text from which the lines are taken (sort this text)
 * @param [in]    text_for_generate_len   number of lines in text
 * 
 * @return  function execution status
 */
static int generate_text(const char * file_name);

/**
 * @brief reads lines from a file in initial order
 * 
 * @param [out]   text_points       points on lines
 * @param [in]    line_count        number of lines in text
 * 
 * @return  function execution status
 */
static int print_file_text(char ** text_points, int line_count);

/**
 * @brief finds the minimum pointer to a string in text
 * 
 * @param [in]    text_points       points on strings
 * @param [in]    line_count        number of strings in text
 * 
 * @return  the minimum pointer to a string in text
 */
static char * min_point(char **text_points, int line_count);

int run_console(){
    while (1){
        char command[max_len] = {};
        printf(CONSOLE_PIRPLE ">>>" CONSOLE_RESET);

        int c = 0;
        c = getchar();
        if (c != '-'){
            if (c != '\n'){
                clean_buffer(stdin);
                printf(CONSOLE_RED "There is no such command!\n" CONSOLE_RESET);
            } 
            continue;
        }  

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

    if (my_strcmp(command, "of") == 0){
        return open_file(&text, &text_line_len);
    }

    if (my_strcmp(command, "s1") == 0){
        return sort_print_file(text, text_line_len, my_strcmp_for_sort);
    }

    if (my_strcmp(command, "s2") == 0){
        return sort_print_file(text, text_line_len, my_strcmp_without_case);
    }

    if (my_strcmp(command, "s3") == 0){
        return sort_print_file(text, text_line_len, my_strrcmp_without_case);
    }

    if (my_strcmp(command, "g1") == 0){
        return generate_text("ONEGIN.txt");
    }

    if (my_strcmp(command, "g2") == 0){
        return generate_text("Swearing.txt");
    }

    if (my_strcmp(command, "p") == 0){
        return print_file_text(text, text_line_len);
    }

    if (my_strcmp(command, "q") == 0) return 1;
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

static int sort_print_file(char **text, int text_line_len, compareFunc func){
    if (text == NULL){
            return -1;
        }
    clock_t start = clock();

    my_qsort(text, sizeof(char *), 0, text_line_len, func);

    clock_t end = clock();
    double time_spent = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

    printf("Time was spent sorting: " CONSOLE_YELLOW  "%0.3f s\n" CONSOLE_RESET, time_spent);
    
    print_text(text, text_line_len);
    return 0;
}

static int generate_text(const char * file_name){
    int text_len  = 0;

    char *getted_text = read_file(file_name, &text_len);
    if (getted_text == NULL) return -1;


    int text_for_generate_len = find_len_text_lines(getted_text);
    if (text_for_generate_len == 0) return -1;

    char ** text_for_generate = split_text(getted_text, text_for_generate_len);
    if (text_for_generate == NULL) return -1;

    clock_t start = clock();

    my_qsort(text_for_generate, sizeof(char *), 0, text_for_generate_len, my_strrcmp_without_case);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time was spent sorting: " CONSOLE_YELLOW  "%0.3f s\n" CONSOLE_RESET, time_spent);

    int generate_text_len = 0;

    printf(CONSOLE_BLUE "How many lines you want generate: " CONSOLE_RESET);
    scanf("%d", &generate_text_len);

    generate_random_text(text_for_generate, text_for_generate_len, generate_text_len);
    return 0;
}

static int print_file_text(char ** text_points, int line_count){
    if (text_points == NULL) return -1; 
    char * text = min_point(text_points, line_count);
    printf("%4d: \"%s\"\n", 0, text);
    for (int text_position = 1; text_position < line_count; text++){
        if (text[0] == '\0'){
            printf("%4d: \"%s\"\n", text_position, text + 1);
            text_position++;
        }
    }
    printf("_____________________________\n");

    return 0;
}

static char * min_point(char **text_points, int line_count){
    char *ans = text_points[0];
    for (int text_position = 0; text_position < line_count; text_position++){
        ans = ans < text_points[text_position] ? ans : text_points[text_position];
    }
    return ans;
}