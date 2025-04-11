#include "../file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ソースコードの最大行列数 */
#define MAX_ROW_SIZE 256
#define MAX_COLUMN_SIZE 256

/* 文字列切り出し関数 */
char* string_subtract(char* string, char* copy_string, int start_index, int length);

/* エラー処理関数 */
void get_error();

/* コマンドの型 */
struct Token
{
    char* token;
    char* code;
};

/* 引数を記号で区切る */
void separate_arguments(char* argument_string, char* prefix_arugments, size_t x_size);

int main(void)
{
    /* ファイル読み込み用の変数 */
    FILE* file_point = fopen(file_name, "r");
    char source_code[MAX_ROW_SIZE][MAX_COLUMN_SIZE];

    /* 文字列切り出し用文字列 */
    char copy_string[MAX_ROW_SIZE];

    /* PC */
    size_t program_count = 0;

    /* フローコマンドの配列 */
    struct Token flow_commands[] = {
        {.token = "I", .code = "sequence"},
        {.token = "?", .code = "selection"}
    };

    /* 関数コマンドの配列 */
    struct Token function_commands[] = {
        {.token = "wr", .code = "write"},
        {.token = "eq", .code = "equal"}
    };
    
    /* 接頭辞の配列 */
    struct Token prefix[] = {
        {.token = "H", .code = "hexadecimal"},
        {.token = "B", .code = "binary"},
        {.token = "#", .code = "string"},
    };
    

    /* ファイル読み込み */
    for (size_t i = 0; fgets(source_code[i], MAX_COLUMN_SIZE, file_point) != NULL; i++);

    while (source_code[program_count][0] != '\0')
    {
        /* フローコマンドを取得 */
        for (size_t i = 0; i < sizeof flow_commands / sizeof flow_commands[0]; i++)
        {
            if (strcmp(string_subtract(source_code[program_count], copy_string, 0, strlen(flow_commands[i].token)), flow_commands[i].token) == 0)
            {
                if (strcmp(flow_commands[i].code, "sequence") == 0)
                {
                    /* 順次実行 */
                    for (size_t j = 0; j < sizeof function_commands / sizeof function_commands[0]; j++)
                    {
                        if (strcmp(string_subtract(source_code[program_count], copy_string, strlen(flow_commands[i].token) + 1, strlen(function_commands[j].token)), function_commands[j].token) == 0)
                        {
                            if (source_code[program_count][strlen(flow_commands[i].token)] == ' ')
                            {
                                char prefix_argument_strings[32][64];

                                for (size_t k = 0; k < strlen(source_code[program_count]); k++)
                                {
                                    if (source_code[program_count][k] == ')')
                                    {
                                        string_subtract(source_code[program_count], copy_string, strlen(flow_commands[i].token) + strlen(function_commands[j].token) + 1, k - 3);

                                        break;
                                    };
                                }

                                separate_arguments(copy_string, &prefix_argument_strings[0][0], 64);
                                printf("%s\n", prefix_argument_strings[0]);
                                printf("%s\n", prefix_argument_strings[1]);
                                
                                break;
                            } else
                            {
                                /* フローコマンドと関数コマンドの間に空白がなければエラー */
                                get_error();
                            }
                        }
                    }

                    program_count++;
                    break;
                }
            } else if (i + 1 < sizeof flow_commands / sizeof flow_commands[0])
            {
                /* フローコマンドが認識されなかったときのエラー */
                get_error();
            }
        }
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

/* エラー処理関数 */
void get_error()
{
    printf("Error!!\n");
    exit(EXIT_FAILURE);
}

/* 引数を区切る */
void separate_arguments(char* argument_string, char* prefix_arugments, size_t x_size)
{
    size_t argument_length = 0, argument_count = 0;
    char copy_string[64];

    if (prefix_arugments[0] != '(')
    {
        for (size_t i = 0; i < strlen(argument_string); i++)
        {
            if (argument_string[i] == ',' || argument_string[i] == ')')
            {
                string_subtract(argument_string, &prefix_arugments[x_size * argument_count], i - argument_length, argument_length);
                argument_count++;

                argument_length = 0;
            } else if (argument_string[i] != '(')
            {
                argument_length++;
            }
        }
    } else
    {
        get_error();
    }
}