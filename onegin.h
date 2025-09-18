#ifndef ONEGIN_H_
#define ONEGIN_H_

#include <ctype.h>
#include <stdlib.h>

#include "my_string_functions.h"

typedef int (*compare_str_func)(const char *, const char*);

/**
 * @brief sort text lines by the funct
 * 
 * @param [out]   text       the text
 * @param [in]    num_lines  the number of lines in text
 * @param [in]    func       the function by which sorting occurs
 * 
 * @return  sorted text 
 */
int sort_text(char **text, int num_lines, compare_str_func func);

/**
 * @brief compairs two strings skips initial non-alphabetic characters
 * 
 * @param [in]    str1       the first string
 * @param [in]    str2       the second string
 * 
 * @return  0 if strings are equal or number less than 0 if str1 < str2 
 *          number greater than 0 if str1 > str2 
 */
int my_strcmp_without_case(const char *str1, const char *str2);

/**
 * @brief compairs two strings from the end skips initial and final non-alphabetic characters
 * 
 * @param [in]    str1       the first string
 * @param [in]    str2       the second string
 * 
 * @return  0 if strings are equal or number less than 0 if str1 < str2 
 *          number greater than 0 if str1 > str2 
 */
int my_strrcmp_without_case(const char *str1, const char *str2);

/**
 * @brief print new_text_len lines from text
 * 
 * @param [in]    text            text
 * @param [in]    text_line_len   number of text line
 * 
 * @return  0 if strings are equal or number less than 0 if str1 < str2 
 *          number greater than 0 if str1 > str2 
 */
void print_text(char **text, int text_line_len);

int generate_random_text(char **text, int text_len, int gen_len);
#endif