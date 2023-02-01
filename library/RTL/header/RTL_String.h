

#ifndef __STR_H__
#define	__STR_H__

    #include <stdlib.h> // for atoi()
    #include <string.h> // for strlen()
    /**
     * Str_StartsWith
     * Returns true if the string starts with the given token.
     * Parameters:
     * - string: Input string.
     * - token: Sub-string to be checked.
     */
    #define Str_StartsWith( string, token ) (  0 == str_index_of_first_token(string, token) )
    #define Str_BeginsWith( string, token ) (  0 == str_index_of_first_token(string, token) )

    #define Str_Compare( string, token )    ( 0 == strcmp( string, token ) )


    /**
     * Str_IndexOf
     * Returns the index of the given token (the index of the first character of the token).
     * Parameters:
     * - string: Input string.
     * - token: Sub-string to be checked.
     */
    #define Str_IndexOf( string, token ) ( str_index_of_first_token(string, token) )

    /**
     * Str_Contains
     * Returns true if the string contains the given token.
     * Parameters:
     * - string: Input string.
     * - token: Sub-string to be checked.
     */
    #define Str_Contains( string, token ) ( -1 != str_index_of_first_token(string, token) )


    /**
     * Str_EndsWith
     * Returns true if the string ends with the given token.
     * Parameters:
     * - string: Input string.
     * - token: Sub-string to be checked.
     */
    #define Str_EndsWith( string, token ) ( strlen(string) == (strlen(token) + str_index_of_last_token(string, token)) )


    /**
     * Str_Crops
     * Returns the cropped string specified by the staring and ending indexes.
     * Parameters:
     * - str: Input string.
     * - idxStart: Starting index.
     * - idxEnd: Ending index.
     * - out: Output buffer of cropped string.
     */
    #define Str_Crops( str, idxStart, idxEnd, out ) str_crop_string( str, idxStart, idxEnd, out )

    /**
     * Str_CropsBetween
     * Returns the cropped string specified by the staring and ending strings.
     * Parameters:
     * - str: Input string.
     * - strStart: Starting string.
     * - strEnd: Ending string.
     * - out: Output buffer of cropped string.
     */
    #define Str_CropsBetween( str, strStart, strEnd, out ) str_crop_between( str, strStart, strEnd, out )


    /**
     * Str_CountOf
     * Returns the number of tokens found in the input string.
     *  Parameters:
     * - str: Input string.
     * - token: Target string.
     */
    #define Str_CountOf( str, token )   str_count_of_token( str, token )


    /**
     * Str_SplitParameters
     * Splits parameters from the given line of parameters that separated by the token.
     * Returns the number of parameters.
     * Parameters:
     * - line: Input string ending with "\r\n", e.g., "pwm:0:200:500:1000\r\n".
     * - token: String separator, e.g., ":" or "another".
     * - out: Output array, e.g., unsigned int out[6].
     */
    #define Str_SplitParameters( line, token, out ) str_split_parameters( line, token, out )


    /**
     * Str_ExtractParameters
     * Extracts parameters from the given line of parameters that separated by ":".
     * Returns the number of parameters.
     * Parameters:
     * - line: Input string ending with "\r\n", e.g., "beep:4250:250:80\r\n".
     * - out:  Output array, e.g., unsigned int out[6].
     */
    #define Str_ExtractParameters( line, out ) str_split_parameters( line, ",", out )



    /**
     * str_index_of_first_token
     * Returns the index of the first token.
     * Returns -1, if the token is not found.
     * Parameters:
     * - str: Input string.
     * - token: Target string.
     * Example:
     *  str = "hello world"
     *  if token = "hello", it will return 0 (index of 'h').
     *  if token = "world", it will return 6 (index of 'w').
     */
    int str_index_of_first_token(const char *str, const char *token);


    /**
     * str_index_of_last_token
     * Returns the index of the last token.
     * Returns -1, if the token is not found.
     * Parameters:
     * - str: Input string.
     * - token: Target string.
     * Example:
     *  str = "dog cat dog cat"
     *  if token = "doc", it will return  8 (index of the second 'd').
     *  if token = "cat", it will return 12 (index of the second 'c').
     */
    int str_index_of_last_token(const char *str, const char *token);


    /**
     * str_index_of_first_char
     * Returns the index of the first char found in the given string.
     * Returns -1 if the target character is not found.
     */
    int str_index_of_first_char(const char *str, char c);


    /**
     * str_crop_string
     * Returns the cropped string specified by the staring and ending positions.
     * Parameters:
     * - str: Input string.
     * - start: Starting position.
     * - stop: Ending position.
     * - out: Output buffer of cropped string.
     */
    char *str_crop_string(const char *src, int start, int stop, char *out);


    char *str_crop_between( const char *str, const char *strStart, const char *strEnd, char *out );


    /**
     * str_index_of_first_char
     * Returns the index of the first character found in the given string.
     * Returns -1, if the target character is not found.
     */
    int str_index_of_first_char(const char *str, char c);



    /**
     * str_index_of_last_char
     * Returns the index of the last character found in the given string.
     * Returns -1, if the target character is not found.
     */
    int str_index_of_last_char(const char *str, char c);

    int str_count_of_token( const char *str, const char* token );

    int str_split_parameters( const char *line, const char *token, float *out ) ;


    /*
    char* str_copy(char *src, char *dst);
    char* str_raw_copy(char *src, int length, char *dst);
    int str_is_ascii_line(const char *str);
    char *str_trim_left(char *src, char *out);
    char *str_trim_right(char *src, char *out);
    char *str_remove_char(char *str, char *out, char c);
    char *str_replace_char(char *str, char *out, char org, char rpc );
    int str_length(const char *str);
    int str_raw_index_of_first_token(const char *str, int length, const char *token);
    int str_index_of_last_token(const char *str, const char *token);
    char *str_sub_string(const char *src, int index, int length, char *out);
    int str_to_int(char *src);
    int str_last_char(char *str, char *c);
    int str_first_char(char *str, char *c);
    */

#endif
