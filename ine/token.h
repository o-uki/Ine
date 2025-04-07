/* コマンドの型 */
struct Command
{
    char *token;
    char *code;
};

struct Command flow_commands[] = {
    {.token = "I", .code = "sequence"},
    {.token = "?", .code = "selection"}
};