#include <stdio.h>
#include "my_string_functions.h"
#include "onegin.h"
#include "file_read.h"



int main(){
    const char * file_name = "ONEGIN.txt";
    int text_len  = 0;

    char * getted_text = read_file(file_name, &text_len);

    int text_line_len = find_len_text_lines(getted_text);
    char ** text = split_text(getted_text, text_line_len);
/**
    sort_text(text, text_line_len, my_strcmp);
    print_text(text, text_line_len);

    sort_text(text, text_line_len, my_strcmp_without_case);
    print_text(text, text_line_len);
 */
    sort_text(text, text_line_len, my_strrcmp_without_case);
    //print_text(text, text_line_len);
    //printf("%d ", text_line_len);
    int generate_text_len = 0;
    scanf("%d", &generate_text_len);

    generate_random_text(text, text_line_len, generate_text_len);
    return 0;
}
