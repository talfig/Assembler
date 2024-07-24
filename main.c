#include "preprocessor.h"
#include "errors.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("test.txt", "r");
    openFail(fp);
    return preprocess(fp);
}
