#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ASCII_SIZE 128
#define ERROR_MESSAGE "chyba\n"
#define NULL_TERMINATOR '\0'
#define BUFFER_SIZE 1024

void vigenere_encrypt(char *plaintext, char *key, char *ciphertext) {
    int plaintext_len = strlen(plaintext);
    int key_len = strlen(key);
    int key_index = 0;
    for (int i = 0; i < plaintext_len; i++) {
        int encrypted_character = (int) plaintext[i] + (int) key[key_index];
        if (encrypted_character >= ASCII_SIZE) {
            encrypted_character = encrypted_character - ASCII_SIZE;
        }
        ciphertext[i] = (char) encrypted_character;
        key_index++;
        if (key_index >= key_len) {
            key_index = 0;
        }
    }
    ciphertext[plaintext_len] = NULL_TERMINATOR;
}

void vigenere_decrypt(char *ciphertext, char *key, char *plaintext) {
    int ciphertext_length = strlen(ciphertext);
    int key_length = strlen(key);
    int key_index = 0;
    for (int i = 0; i < ciphertext_length; i++) {
        int decrypted_char = (int) ciphertext[i] - (int) key[key_index];
        if (decrypted_char < 0) {
            decrypted_char = decrypted_char + ASCII_SIZE;
        }
        plaintext[i] = (char) decrypted_char;
        key_index = (key_index + 1) % key_length;
    }
    plaintext[ciphertext_length] = NULL_TERMINATOR;
}

typedef struct {
    int s_flag;
    int d_flag;
    char *password_value;
    char *input_file_value;
    char *output_file_value;
} Arguments;

void parse_argument(Arguments *args, char *arg, int *i, int argc, char *argv[]) {
    switch (arg[1]) {
        case 's':
            args->s_flag = 1;
            break;
        case 'd':
            args->d_flag = 1;
            break;
        case 'p':
            if (*i + 1 < argc) {
                args->password_value = argv[*i + 1];
                (*i)++;
            } else {
                printf(ERROR_MESSAGE);
                exit(1);
            }
            break;
        case 'i':
            if (*i + 1 < argc) {
                args->input_file_value = argv[*i + 1];
                (*i)++;
            } else {
                printf(ERROR_MESSAGE);
                exit(1);
            }
            break;
        case 'o':
            if (*i + 1 < argc) {
                args->output_file_value = argv[*i + 1];
                (*i)++;
            } else {
                printf(ERROR_MESSAGE);
                exit(1);
            }
            break;
        default:
            printf(ERROR_MESSAGE);
            exit(1);
    }
}

Arguments parse_arguments(int argc, char *argv[]) {
    Arguments args = {0};

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        if (arg[0] == '-') {
            parse_argument(&args, arg, &i, argc, argv);
        } else {
            printf(ERROR_MESSAGE);
            exit(1);
        }
    }

    if (args.s_flag == 1 && args.d_flag == 1) {
        printf(ERROR_MESSAGE);
        exit(1);
    }

    if (args.s_flag == 0 && args.d_flag == 0) {
        printf(ERROR_MESSAGE);
        exit(1);
    }

    return args;
}

void write_to_file(char *filename, char *text) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf(ERROR_MESSAGE);
        exit(1);
    }
    fprintf(file, "%s", text);
    fclose(file);
}

void read_from_file(char *filename, char *buffer) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(ERROR_MESSAGE);
        exit(1);
    }
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) != 0) {}
    if (ferror(file)) {
        printf(ERROR_MESSAGE);
        fclose(file);
        exit(1);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    Arguments args = parse_arguments(argc, argv);

    char buffer[BUFFER_SIZE];
    read_from_file(args.input_file_value, buffer);

    char write_buffer[BUFFER_SIZE];
    void (*operation)(char *, char *, char *) = args.s_flag == 1 ? vigenere_encrypt : vigenere_decrypt;
    operation(buffer, args.password_value, write_buffer);
    write_to_file(args.output_file_value, write_buffer);

    return 0;
}