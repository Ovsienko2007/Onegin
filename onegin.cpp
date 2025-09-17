#include "onegin.h"

int sort(char ***str, int num_element, int (*func)(const char *, const char*)){
    bool x = true;
    while (x){
        x = false;

        for (int i = 0; i < num_element - 1; i++){
            if (func((*str)[i], (*str)[i + 1]) > 0){
                x = true;
                char * l = (*str)[i];
                (*str)[i] = (*str)[i + 1];
                (*str)[i + 1] = l;
            }
        }
    }
    return 0;
}

int read_file(FILE * stream, int *text_len, char *** text){
    if (stream == NULL) return -1;

    int text_position = 0;
    
    for (;text_position < *text_len; text_position++){
        size_t len_str = text_line_size;
        my_getline(&((*text)[text_position]), &len_str, stream);

    }

    return text_position;
}