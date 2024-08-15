#ifndef TOKEN_UTILS_H
#define TOKEN_UTILS_H

#define MIN_CHAR_VALUE 32 /* The first printable ASCII character */
#define MAX_CHAR_VALUE 126 /* The last printable ASCII character */

int nextToken(char *dest, char **ptr, const char delim);

int nextString(char *dest, char **ptr, int line_counter);

#endif /* TOKEN_UTILS_H */
