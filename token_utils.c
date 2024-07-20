int isWhitespace(char a) {
    return  (a == ' ') ||
            (a == '\t') ||
            (a == '\n');
}

void nextToken(char *dest, char **ptr) {
    while(*ptr && isWhitespace(**ptr)) (*ptr)++;
    while(*ptr && !isWhitespace(**ptr)) {
        *dest = **ptr;
        dest++;
        (*ptr)++;
    }
    *dest = '\0';
}
