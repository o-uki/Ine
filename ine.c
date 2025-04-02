#include <stdio.h>
#include <string.h>

int in_row;

/* フローコマンドの型と生成する関数 */
struct flow_command
{
    char *token[16];
    char *type[32];
};

struct flow_command create_flow_command(char set_token[16], char set_type[32])
{
    struct flow_command new_command;

    *new_command.token = set_token;
    *new_command.type = set_type;

    return new_command;
}

/* Ineを実行する関数 */
void run_command(char rows[256][128])
{
    struct flow_command flow_commands[4] = {
        create_flow_command("I", "sequence"),
        create_flow_command("?", "selection")
    };

    printf("%s", rows[1]);
}

int main(void)
{
    /* ファイル読み込み */
    FILE *filep = fopen("sample.ine", "r");

    char source_code_rows[256][128];
    size_t get_file_row = 0;

    char file_row[128];
    while (fgets(file_row, 128, filep)[strlen(file_row) - 1] == '\n')
    {
        strcpy(source_code_rows[get_file_row], file_row);

        get_file_row++;
    }
    fgets(file_row, 128, filep);
    strcpy(source_code_rows[get_file_row], file_row);

    run_command(source_code_rows);
    
    fclose(filep);

    return 0;
}