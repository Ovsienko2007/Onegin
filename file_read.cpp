#include "file_read.h"

char ** split_text(char * text, int line_count){
    assert(text != NULL);
    char ** text_points = (char **)calloc(line_count, sizeof(char *));
    if (text_points == NULL) return NULL;

    for (int text_position = 0; text_position < line_count; text_position++){
        text_points[text_position] = text;

        text = my_strchr(text, '\n');
        if  (text == NULL) break;

        *text = '\0';
        text++;
    }
    return text_points;
}

int find_len_text_lines(const char * text){
    assert(text != NULL);

    int line_count = 0;
    while (true){
        text = my_strchr(text, '\n');
        if (text == NULL) break;
        text++;
        line_count++;
    }
    return line_count + 1;
} 

char * read_file(const char * file_name, int * text_len){
    assert(file_name != NULL);
    assert(text_len != NULL);

    size_t file_len = find_file_size(file_name) / sizeof(char) + 1;

    char * file_text = (char *)calloc(file_len, sizeof(char));
    if (file_text == NULL)  return NULL;

    int file_descriptor = open(file_name, O_RDONLY);
    
    if (file_descriptor == -1){
        close(file_descriptor);
        return NULL;
    }

    *text_len = read(file_descriptor, file_text, find_file_size(file_name));

    close(file_descriptor);

    if (*text_len == -1) return NULL;

    file_text[*text_len] = '\0';

    return file_text;
}

unsigned int find_file_size(const char * file_name){
    assert(file_name != NULL);
    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1) return 0;

    return file_stat.st_size;
}