#include <stdio.h>
#include <string.h>

/* 見ている行 */
int in_row;

/* コマンドの型と生成する関数 */
struct Command
{
    char* token[16];
    char* type[32];
};

struct Command create_command(char set_token[], char set_type[])
{
    struct Command new_command;

    *new_command.token = set_token;
    *new_command.type = set_type;

    return new_command;
}

/* 関数コマンドの実行内容定義 */
int run_function_command(char type[], int operands[])
{
    if (strcmp(type, "write") == 0)
    {
        printf("%d\n", operands[0]);

        return 1;
    }

    return 0;
};

/* Ineを実行する関数 */
void run_commands(char rows[], size_t x_size, size_t y_size)
{
    /* フローコマンド定義 */
    struct Command flow_commands[] = {
        create_command("I", "sequence"),
        create_command("?", "selection")
    };

    /* 関数コマンド定義 */
    struct Command function_commands[] = {
        create_command("wr", "write"),
        create_command("eq", "equal")
    };

    for (size_t i = 0; i < sizeof flow_commands / sizeof flow_commands[0]; i++)
    {
        char copy_token[16];
        for (size_t j = 0; j < strlen(*flow_commands[i].token); j++)
        {
            copy_token[j] = rows[in_row * x_size + j];
        }

        if (strcmp(*flow_commands[i].token, copy_token))
        {
            
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