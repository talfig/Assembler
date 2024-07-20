#include "preprocessor.h"

int main(int argc, char *argv[]) {
    FILE *fp = preprocess(fopen("test.txt", "r"));
    fclose(fp);
    return 0;
}
