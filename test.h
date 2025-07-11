#ifndef TEST_H
#define TEST_H


int my_strlen(const char* str);

char* my_strcpy(char* dest, const char* src);

void transpose(int* matrix, int* result, int rows, int cols);

typedef void (*p)(int);
void callback(p fuc);
void trigger(int value);
void my_callback(int value);

#endif // TEST_H