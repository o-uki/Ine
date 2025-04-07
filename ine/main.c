#include "../file.h"
#include "./function.h"
#include "./token.h"
#include <stdio.h>
#include <string.h>

/* ソースコードの最大行列数 */
#define MAX_ROW_SIZE 256
#define MAX_COLUMN_SIZE 256

int main(void)
{
    /* ファイル読み込み */
    FILE* file_point = fopen(file_name, "r");
    char source_code[MAX_ROW_SIZE][MAX_COLUMN_SIZE];

    /* 文字列切り出し用文字列 */
    char copy_string[MAX_ROW_SIZE];

    /* PC */
    size_t program_count = 0;

    for (size_t i = 0; fgets(source_code[i], MAX_COLUMN_SIZE, file_point) != NULL; i++);

    while (source_code[program_count][0] != '\0')
    {
        
    }

    return 0;
}

/* 文字列切り出し関数 */
char* string_subtract(char* string, char* copy_string, int start_index, int length)
{
    /* 代入する文字列を空文字列に */
    for (size_t i = 0; i < sizeof copy_string; i++)
    {
        copy_string[i] = '\0';
    }

    /* 文字を1文字ずつ代入 */
    for (size_t i = 0; i < length; i++)
    {
        copy_string[i] = string[start_index + i];
    }

    return copy_string;
}