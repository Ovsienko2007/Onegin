#include <stdio.h>
#include "my_string_functions.h"
#include "onegin.h"
#include "file_read.h"

int main(){
    const char * file_name = "text.txt";
    int text_len  = 0;

    char * text = read_file(file_name, &text_len);

    int new_text_len = find_len_text_lines(text);
    char ** new_text = split_text(text, new_text_len);
    
    for (int i = 0; i < new_text_len; i++){
        printf("%4d: \"%s\"\n", i, new_text[i]);
    }
    printf("________________\n");

    sort(new_text, new_text_len, my_strcmp);

    for (int i = 0; i < new_text_len; i++){
        printf("%4d: \"%s\"\n", i, new_text[i]);
    }

    return 0;
}
