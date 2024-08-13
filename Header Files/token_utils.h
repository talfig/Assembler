#ifndef TOKEN_UTILS_H
#define TOKEN_UTILS_H

int nextToken(char *dest, char **ptr, const char delim);

int nextString(char *dest, char **ptr, int line_counter);

#endif /* TOKEN_UTILS_H */
