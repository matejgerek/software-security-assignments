#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// main accepting command line arguments
int main(int argc, char *argv[])
{
    int s_flag = 0;
    int d_flag = 0;

    char *password_value = NULL;
    char *input_file_value = NULL;
    char *output_file_value = NULL;

    // parse command line arguments
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];

        if (strcmp(arg, "-s") == 0) {
            s_flag = 1;
            continue;
        }
        if (strcmp(arg, "-d") == 0) {
            d_flag = 1;
            continue;
        }

        if (strcmp(arg, "-p") == 0) {
            if (i + 1 < argc) {
                password_value = argv[i + 1];
                i++;
            } else {
                printf("Error: -p flag requires a value.\n");
                return 1;
            }
            continue;
        }

        if (strcmp(arg, "-i") == 0) {
            if (i + 1 < argc) {
                input_file_value = argv[i + 1];
                i++;
            } else {
                printf("Error: -i flag requires a value.\n");
                return 1;
            }
            continue;
        }

        if (strcmp(arg, "-o") == 0) {
            if (i + 1 < argc) {
                output_file_value = argv[i + 1];
                i++;
            } else {
                printf("Error: -o flag requires a value.\n");
                return 1;
            }
            continue;
        }
        printf("Error: unknown flag: %s", arg);
    }

    if (s_flag == 1 && d_flag == 1) {
        printf("Error: -s and -d flags cannot be used together.\n");
        return 1;
    }
    if (s_flag == 0 && d_flag == 0) {
        printf("Error: -s or -d flag must be used.\n");
        return 1;
    }

    return 0;
}