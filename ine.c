#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 見ている行 */
size_t program_count;

/* コマンドの型と生成する関数 */
struct Command
{
    char* token[16];
    char* code[32];
};

struct Command create_command(char* set_token, char* set_code)
{
    struct Command new_command;

    *new_command.token = set_token;
    *new_command.code = set_code;

    return new_command;
}

/* 接頭辞の型と生成する関数 */
struct Argument_Prefix
{
    char* token[8];
    char* code[32];
};

struct Argument_Prefix create_argument_prefix(char* set_token, char* set_code)
{
    struct Argument_Prefix new_argument_prefix;

    *new_argument_prefix.token = set_token;
    *new_argument_prefix.code = set_code;

    return new_argument_prefix;
}

/* 接頭辞の内容定義関数 */
int calculate_argument_prefix(char* code, char* argument)
{
    if (strcmp(code, "hexadecimal") == 0)
    {
        return strtol(argument, NULL, 16);
    } else if (strcmp(code, "binary") == 0)
    {
        return strtol(argument, NULL, 2);
    }

    return 0;
}

/* 接頭辞によって引数を変換する関数 */
int calculate_argument(char* argument_string)
{
    /* 接頭辞定義 */
    struct Argument_Prefix argument_prefixes[] = {
        create_argument_prefix("r", "reference"),
        create_argument_prefix("h", "hexadecimal"),
        create_argument_prefix("b", "binary")
    };

    /* 文字列を比較したい文字数切り出す用の変数 */
    char copy_string[16];

    /* 接頭辞があるか判断してあれば戻り値を返し関数終了 */
    for (size_t i = 0; i < sizeof argument_prefixes / sizeof argument_prefixes[0]; i++)
    {
        for (size_t j = 0; j < sizeof copy_string; j++)
        {
            copy_string[j] = '\0';
        }

        for (size_t j = 0; j < strlen(*argument_prefixes[i].token); j++)
        {
            copy_string[j] = argument_string[j];
        }

        if (strcmp(copy_string, *argument_prefixes[i].token) == 0)
        {

            for (size_t j = 0; j < sizeof copy_string; j++)
            {
                copy_string[j] = '\0';
            }
            for (size_t j = 0; j < strlen(argument_string) - strlen(*argument_prefixes[i].token); j++)
            {
                copy_string[j] = argument_string[strlen(*argument_prefixes[i].token) + j];
            }
            
            return calculate_argument_prefix(*argument_prefixes[i].code, copy_string);
        }
    }

    return strtol(argument_string, NULL, 10);
}

/* 引数を取得する関数 */
int* get_arguments(char* rows, size_t x_size, char* flow_command_token, char* function_command_token)
{
    /* 一時的に引数を保存する変数 */
    char argument_string[16];
    int arguments[8], return_arguments[8];
    size_t arugment_string_count = 0, arguments_count = 0;

    /* 引数が書いてある文字列をコピー */
    char copy_arguments_token[128];

    copy_arguments_token[0] = rows[program_count * x_size + strlen(flow_command_token) + strlen(function_command_token) + 1];
    for (size_t k = 1; !(copy_arguments_token[strlen(copy_arguments_token) - 1] == '\0' || copy_arguments_token[strlen(copy_arguments_token) - 1] == ')'); k++)
    {
        copy_arguments_token[k] = rows[program_count * x_size + k + strlen(flow_command_token) + strlen(function_command_token) + 1];
    }

    for (size_t k = 0; k < strlen(copy_arguments_token); k++)
    {
        if (!(copy_arguments_token[k] == '(' || copy_arguments_token[k] == ')' || copy_arguments_token[k] == ','))
        {
            argument_string[arugment_string_count] = copy_arguments_token[k];
            arugment_string_count++;
        } else if (copy_arguments_token[k] == ',')
        {
            arguments[arguments_count] = calculate_argument(argument_string);
            arguments_count++;

            for (size_t l = 0; l < sizeof argument_string; l++)
            {
                argument_string[l] = '\0';
            }
            arugment_string_count = 0;
        } else if (copy_arguments_token[k] == ')')
        {
            arguments[arguments_count] = calculate_argument(argument_string);
        }
    }

    return memcpy(return_arguments, arguments, sizeof arguments);
}

/* 関数コマンドの実行内容定義関数 */
int run_function_command(char* code, int* arguments)
{
    if (strcmp(code, "write") == 0)
    {
        printf("%d\n", arguments[0]);

        return 1;
    }

    return 0;
};

/* Ineを実行する関数 */
void run_commands(char* rows, size_t x_size, size_t y_size)
{
    /* フローコマンド定義 */
    struct Command flow_commands[] = {
        create_command("I", "sequence"),
        create_command("?", "selection"),
        create_command("+", "connection"),
    };

    /* 関数コマンド定義 */
    struct Command function_commands[] = {
        create_command("wr", "write"),
        create_command("eq", "equal")
    };

    /* フローコマンドに当てはまるか */
    for (size_t i = 0; i < sizeof flow_commands / sizeof flow_commands[0]; i++)
    {
        /* 文字列を比較したい文字数切り出す用の変数 */
        char copy_token[16];

        /* 文字列切り出し */
        for (size_t j = 0; j < strlen(*flow_commands[i].token); j++)
        {
            copy_token[j] = rows[program_count * x_size + j];
        }

        if (strcmp(*flow_commands[i].token, copy_token) == 0)
        {
            if (strcmp(*flow_commands[i].code, "sequence") == 0)
            {
                /* 関数コマンドに当てはまるか */
                for (size_t j = 0; j < sizeof function_commands / sizeof function_commands[0]; j++)
                {
                    /* 文字列を比較したい文字数切り出す用の変数リセット */
                    for (size_t k = 0; k < sizeof copy_token; k++)
                    {
                        copy_token[k] = '\0';
                    }

                    /* 文字列切り出し */
                    for (size_t k = 0; k < strlen(*function_commands[j].token); k++)
                    {
                        copy_token[k] = rows[program_count * x_size + k + strlen(*flow_commands[i].token) + 1];
                        // printf("b: %lu\n", program_count * x_size + k + strlen(*flow_commands[i].token) + 1);
                    }

                    // printf("c: %s\n", copy_token);

                    /* 関数コマンドがあるか判定 */
                    if (strcmp(copy_token, *function_commands[j].token) == 0)
                    {
                        /* 引数の配列 */
                        int arguments[8];
                        
                        memcpy(arguments, get_arguments(rows, x_size, *flow_commands[i].token, *function_commands[j].token), sizeof *get_arguments(rows, x_size, *flow_commands[i].token, *function_commands[j].token));
                        run_function_command(*function_commands[j].code, arguments);
                    }
                }

                program_count++;
                printf("Hello\n");
            }
        }
    }

    if (!(strlen(&rows[program_count * x_size]) == 0))
    {
        run_commands(rows, x_size, y_size);
    }
}

int main(void)
{
    /* ファイル読み込み */
    FILE* filep = fopen("sample.ine", "r");

    char source_code_rows[256][128];
    size_t get_file_row = 0;

    char file_row[128];
    while (fgets(file_row, 128, filep)[strlen(file_row) - 1] == '\n')
    {
        memcpy(source_code_rows[get_file_row], file_row, sizeof file_row);

        get_file_row++;
    }
    fgets(file_row, 128, filep);
    memcpy(source_code_rows[get_file_row], file_row, sizeof file_row);

    run_commands(&source_code_rows[0][0], 128, 256);
    
    fclose(filep);

    return 0;
}