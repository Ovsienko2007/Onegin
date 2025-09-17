#ifndef ONEGIN_H_
#define ONEGIN_H_
#include "my_string_functions.h"

const size_t new_text_size = 16;
const size_t text_line_size = 16;


/**
 * @brief reads lines_num lines from stream and put them into text
 * 
 * @param [in]  stream     first stream
 * @param [in]  lines_num  number of lines wich will be read
 * @param [out] text       text in wich lines are put
 * 
 * @return 0 if strings are equal or number less than 0 if str1 < str2
 *  number greater than 0 if str1 > str2 
 */
int read_file(FILE * stream, int *text_len, char *** text);

int sort(char ***str, int num_element, int (*func)(const char *, const char*));

#endif