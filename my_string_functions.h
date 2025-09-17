/**
 * @file my_string_functions.h
 * @brief contain string functions
 */

#ifndef my_string_functions_h_
#define my_string_functions_h_
#include <stdio.h>
#include <stdlib.h>

const size_t new_str_len      = 64;
const size_t line_coefficient = 2;

/**
 * @brief compairs two strings
 * 
 * @param [in]  str1   first string
 * @param [in]  str2   second string
 * 
 * @return 0 if strings are equal or number less than 0 if str1 < str2
 *  number greater than 0 if str1 > str2 
 */
int my_strcmp(const char *str1, const char *str2);

/**
 * @brief reads n characters from the stream to string and put it in calloc
 * 
 * @param [out]  str       string
 * @param [in]   num_chars number of symbols
 * @param [in]   stream    stream
 * 
 * @return point to calloc
 */
ssize_t my_getline(char **str, size_t *n, FILE *stream);

/**
 * @brief transform string to calloc
 * 
 * @param [in]  str string
 * 
 * @return point to calloc
 */
char * my_strdup(const char *str);

/**
 * @brief reads n characters from the stream to string
 * 
 * @param [out]  str      string
 * @param [in]  num_chars number of symbols
 * @param [in]  stream    stream
 * 
 * @return string
 */
char * my_fgets(char *str, int num_chars, FILE *stream);

/**
 * @brief change type from string to int
 * 
 * @param [in]  str string
 * 
 * @return number
 */
int my_atoi(const char * str);

/**
 * @brief put n symbols from one string to the end of another
 * 
 * @param [in]  str_dest line where symbols are added
 * @param [out] str_add  string from that symbols are added
 * @param [in]  len      number of added sympols
 * 
 * @return point on new string
 */
char * my_strncat(char * str_dest, const char * str_add, size_t len);

/**
 * @brief put one string to the end of another
 * 
 * @param [in]  str_dest line where symbols are added
 * @param [out] str_add  string from that symbols are added
 * 
 * @return point on new string
 */
char * my_strcat(char * str_dest, const char * str_add);

/**
 * @brief copy n symbols from one string to another
 * 
 * @param [in]  new_str string where to copy
 * @param [out] out_str copied string
 * @param [in]  len     number of copied sympols
 * 
 * @return point on new string
 */
char * my_strncpy(char * new_str, const char * old_str, size_t len);

/**
 * @brief copy one string to another
 * 
 * @param [in]  new_str copied string
 * @param [out] out_str string where to copy
 * 
 * @return point on new string
 */
char * my_strcpy(char * new_str, const char * old_str);

/**
 * @brief find size of string
 * 
 * @param [in] str string
 * 
 * @return size of string
 */
size_t my_strlen(const char * str);

/**
 * @brief find symbol in string
 * 
 * @param [in] str     string
 * @param [in] symbol  symbol
 * 
 * @return character pointer
 */
char * my_strchr(const char * str, int symbol);

/**
 * @brief print string
 * 
 * @param [in] str string
 * 
 * @return number > 1 if success else EOF
 */
int my_puts(const char* str);

#endif