#ifndef ONEGIN_H_
#define ONEGIN_H_

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "my_string_functions.h"

/**
 * @brief the function by which sorting occurs
 */
typedef int (*compareFunc)(const void *, const void *);

/**
 * @brief sort text lines from start to end by the func
 * 
 * @param [out]   data       the array
 * @param [in]    elem_size  the size of 1 element
 * @param [in]    start      the number of first line fron text wich will be sorted
 * @param [in]    end        the number of last line fron text wich will be sorted
 * @param [in]    compare_func       the function by which sorting occurs
 * 
 * @return  sorted text 
 */
void my_qsort(const void *data, size_t elem, int start, int end, compareFunc compare_func);

/**
 * @brief sort text lines by the func
 * 
 * @param [out]   data            the array
 * @param [in]    elem_size       the size of elements from array
 * @param [in]    num_lines       the number of lines in text
 * @param [in]    compare_func    the function by which sorting occurs
 * 
 * @return  sorted text 
 */
int bubble_sort(void *text, size_t elem_size, int num_lines, compareFunc compare_func);

/**
 * @brief compairs two strings skips initial non-alphabetic characters
 * 
 * @param [in]    param1       point on the first string
 * @param [in]    param2       point on the second string
 * 
 * @return  0 if strings are equal or number less than 0 if str1 < str2 
 *          number greater than 0 if str1 > str2 
 */
int my_strcmp_without_case(const void *parsm1, const void *parsm2);

/**
 * @brief compairs two strings from the end skips initial and final non-alphabetic characters
 * 
 * @param [in]    param1       point on the first string
 * @param [in]    param2       point on the second string
 * 
 * @return  0 if strings are equal or number less than 0 if str1 < str2 
 *          number greater than 0 if str1 > str2 
 */
int my_strrcmp_without_case(const void *param1, const void *param2);

/**
 * @brief compairs two strings
 * 
 * @param [in]    param1       point on the first string
 * @param [in]    param2       point on the second string
 * 
 * @return  0 if strings are equal or number less than 0 if str1 < str2 
 *          number greater than 0 if str1 > str2 
 */
int my_strcmp_for_sort(const void *param1, const void *param2);

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

/**
 * @brief generate text by lines from another text 
 * 
 * @param [in]    text            input text
 * @param [in]    text_line_len   lines in inout text
 * @param [in]    text_line_len   lines in generated text
 * 
 * @return  0
 */
int generate_random_text(char **text, int text_len, int gen_len);

#endif