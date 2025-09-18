#include <stdio.h>
#include "my_string_functions.h"
#include "onegin.h"
#include "file_read.h"



int main(){
    const char * file_name = "text.txt";
    int text_len  = 0;

    char * getted_text = read_file(file_name, &text_len);

    int text_line_len = find_len_text_lines(getted_text);
    char ** text = split_text(getted_text, text_line_len);

    sort_text(text, text_line_len, my_strcmp);
    print_text(text, text_line_len);

    sort_text(text, text_line_len, my_strcmp_without_case);
    print_text(text, text_line_len);

    sort_text(text, text_line_len, my_strrcmp_without_case);
    print_text(text, text_line_len);

    return 0;
}
