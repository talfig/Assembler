#ifndef INTEGER_UTILS_H
#define INTEGER_UTILS_H

#define DATA_MAX_VALUE 16383
#define DATA_MIN_VALUE -16384
#define INSTRUCTION_MAX_VALUE 2047
#define INSTRUCTION_MIN_VALUE -2048
#define DATA_MAX_SIZE 6

int countDigits(int num);

int parseDataInt(char *str);

int parseInstructionInt(char *str);

#endif /* INTEGER_UTILS_H */
