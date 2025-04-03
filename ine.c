#include <stdio.h>
#include <string.h>

/* 見ている行 */
int program_count = 1;

/* コマンドの型と生成する関数 */
struct Command
{
    char* token[16];
    char* type[32];
};

struct Command create_command(char* set_token, char* set_type)
{
    struct Command new_command;

    *new_command.token = set_token;
    *new_command.type = set_type;

    return new_command;
}

/* 関数コマンドの実行内容定義 */
int run_function_command(char* type, int* operands)
{
    if (strcmp(type, "write") == 0)
    {
        printf("%d\n", operands[0]);

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
        create_command("+", "connection")
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
            if (strcmp(*flow_commands[i].type, "sequence") == 0)
            {
                /* 関数コマンドに当てはまるか */
                for (size_t j = 0; j < sizeof function_commands / sizeof function_commands[0]; j++)
                {
                    /* 文字列を比較したい文字数切り出す用の変数リセット */
                    for (size_t k = 0; k < strlen(copy_token); k++)
                    {
                        copy_token[k] = '\0';
                    }

                    /* 文字列切り出し */
                    for (size_t k = 0; k < strlen(*function_commands[j].token); k++)
                    {
                        copy_token[k] = rows[program_count * x_size + k + strlen(*flow_commands[i].token) + 1];
                    }

                    /* 引数を */
                }
            }
        }
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
        memmove(source_code_rows[get_file_row], file_row, sizeof file_row);

        get_file_row++;
    }
    fgets(file_row, 128, filep);
    memmove(source_code_rows[get_file_row], file_row, sizeof file_row);

    run_commands(&source_code_rows[0][0], 128, 256);
    
    fclose(filep);

    return 0;
}