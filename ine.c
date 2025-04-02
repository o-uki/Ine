#include <stdio.h>
#include <string.h>

int in_row;

char run_command(char row_chars[255])
{
    return row_chars[0];
}

int main(void)
{
    FILE *filep = fopen("sample.ine", "r");

    char file_row_chars[255];
    while (fgets(file_row_chars, 255, filep)[strlen(file_row_chars) - 1] == '\n')
    {
        printf("%c", run_command(file_row_chars));
    }
    fgets(file_row_chars, 255, filep);
    printf("%s\n", file_row_chars);
    
    fclose(filep);

    return 0;
}