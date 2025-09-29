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
static int sort_print_file(data_text * data, compareFunc func);

/**
 * @brief read text from file and split it into lines 
 * 
 * @param [out]    text           lines from file
 * @param [out]    text_line_len  number of lines in text
 * 
 * @return  function execution status
 */
static int open_file(data_text *data);

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
static int print_file_text(data_text data);

static int clean_text(data_text *data){
    free(data->text.lines);
    free(data->buffer.text);
    data->buffer.size = 0;
    data->text.lines_count = 0;
    return 0;
}

int run_console(){
    while (true){
        char command[max_len] = {};
        printf(CONSOLE_PIRPLE ">>>" CONSOLE_RESET);

        int first_symbol = 0;
        first_symbol = getchar();
        if (first_symbol != '-'){
            if (first_symbol != '\n'){
                clean_buffer(stdin);
                printf(CONSOLE_RED "There is no such command!\n" CONSOLE_RESET);
            } 
            continue;
        }

        scanf("%15s", command);
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
    assert(stream);

    int symbol = 0; 
    do{
        symbol = fgetc(stream);
    } while (symbol != '\n' && symbol != EOF);

    return symbol ==  EOF;
}

static int run_commands(char *command){
    assert(command != NULL);

    static data_text data = {
        .buffer = {
            .size = 0,
            .text = NULL,
        },
        .text = {
            .lines_count = 0,
            .lines = NULL,
        }
    };

    if (my_strcmp(command, "of") == 0){
        clean_text(&data);
        return open_file(&data);
    }

    if (my_strcmp(command, "s1") == 0){
        return sort_print_file(&data, my_strcmp_for_sort);
    }

    if (my_strcmp(command, "s2") == 0){
        return sort_print_file(&data, my_strcmp_without_case);
    }

    if (my_strcmp(command, "s3") == 0){
        return sort_print_file(&data, my_strrcmp_without_case);
    }

    if (my_strcmp(command, "g1") == 0){
        return generate_text("ONEGIN.txt");
    }

    if (my_strcmp(command, "g2") == 0){
        return generate_text("Swearing.txt");
    }

    if (my_strcmp(command, "p") == 0){
        return print_file_text(data);
    }

    if (my_strcmp(command, "c") == 0){
        return clean_text(&data);
    }

    if (my_strcmp(command, "q") == 0) return 1;

    return -2;
}

static int open_file(data_text *data){
    char file_name[max_len] = {};
    printf(CONSOLE_BLUE "Print file name: " CONSOLE_RESET);

    scanf("%100s", file_name);

    read_file(file_name, data);
    if (data->buffer.text == NULL) return -1;

    data->text.lines_count = find_len_text_lines(*data);

    if (data->text.lines_count == 0) return -1;

    split_text(data);
    if (data->text.lines == NULL) return -1;
    printf(CONSOLE_GREEN "COMPLITED\n" CONSOLE_RESET);
    return 0;
}

static int sort_print_file(data_text *data, compareFunc func){
    if (data == NULL){
        return -1;
    }

    clock_t start = clock();

    my_qsort(data->text.lines, sizeof(char *), 0, data->text.lines_count, func);

    clock_t end = clock();
    double time_spent = (double)(end - start) * 1000 / CLOCKS_PER_SEC;

    printf("Time was spent sorting: " CONSOLE_YELLOW  "%0.3f s\n" CONSOLE_RESET, time_spent);
    
    print_text(data->text.lines, data->text.lines_count);

    return 0;
}

static int generate_text(const char * file_name){
    static data_text data = {
        .buffer = {
            .size = 0,
            .text = NULL,
        },
        .text = {
            .lines_count = 0,
            .lines = NULL,
        }
    };

    read_file(file_name, &data);
    if (data.buffer.text == NULL) return -1;

    data.text.lines_count = find_len_text_lines(data);
    if (data.text.lines_count == 0) return -1;

    split_text(&data);

    if (data.text.lines == NULL) return -1;

    clock_t start = clock();

    my_qsort(data.text.lines, sizeof(char *), 0, data.text.lines_count, my_strrcmp_without_case);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time was spent sorting: " CONSOLE_YELLOW  "%0.3f s\n" CONSOLE_RESET, time_spent);

    int generate_text_len = 0;

    printf(CONSOLE_BLUE "How many lines you want generate: " CONSOLE_RESET);
    scanf("%d", &generate_text_len);

    generate_random_text(data.text.lines, data.text.lines_count, generate_text_len);

    clean_text(&data);

    return 0;
}

static int print_file_text(data_text data){
    printf("%4d: \"%s\"\n", 0, data.buffer.text);

    for (int text_position = 1; text_position < data.text.lines_count; data.buffer.text++){
        if (data.buffer.text[0] == '\0'){
            printf("%4d: \"%s\"\n", text_position, data.buffer.text + 1);
            text_position++;
        }
    }
    printf("_____________________________\n");

    return 0;
}