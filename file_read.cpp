#include "file_read.h"

int split_text(data_text *data){
    assert(data->text != NULL);

    char *text = data->text;
    data->text_points = (char **)calloc(data->size, sizeof(char *));
    if (data->text_points == NULL) return NULL;

    for (int text_position = 0; text_position < data->size; text_position++){
        data->text_points[text_position] = text;

        text = my_strchr(text, '\n');
        if  (text == NULL) break;

        *text = '\0';
        text++;
    }
    free(text);
    return 1;
}

int find_len_text_lines(data_text data){
    assert(data.text != NULL);

    int line_count = 0;
    while (true){
        data.text = my_strchr(data.text, '\n');
        if (data.text == NULL) break;
        data.text++;
        line_count++;
    }
    return line_count + 1;
} 

char * read_file(const char * file_name, data_text *data){
    assert(file_name != NULL);
    assert(data != NULL);

    size_t file_len = find_file_size(file_name) / sizeof(char) + 1;

    char * file_text = (char *)calloc(file_len, sizeof(char));
    if (file_text == NULL)  return NULL;

    int file_descriptor = open(file_name, O_RDONLY);
    
    if (file_descriptor == -1){
        close(file_descriptor);
        return NULL;
    }

    data->size = read(file_descriptor, file_text, find_file_size(file_name));

    close(file_descriptor);

    if (data->size == -1) return NULL;

    file_text[data->size] = '\0';

    return file_text;
} 

off_t find_file_size(const char * file_name){
    assert(file_name != NULL);
    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1) return 0;

    return file_stat.st_size;
}