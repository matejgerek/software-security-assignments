#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ASCII_SIZE 128
#define ERROR_MESSAGE "chyba\n"
#define NULL_TERMINATOR '\0'

int update_key_index(int key_index, int key_len) {
    key_index++;
    if (key_index >= key_len) {
        key_index = 0;
    }
    return key_index;
}

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
        key_index = update_key_index(key_index, key_len);
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

int main(int argc, char *argv[]) {
    int s_flag = 0;
    int d_flag = 0;

    char *password_value = NULL;
    char *input_file_value = NULL;
    char *output_file_value = NULL;

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        switch (arg[0]) {
            case '-':
                switch (arg[1]) {
                    case 's':
                        s_flag = 1;
                        break;
                    case 'd':
                        d_flag = 1;
                        break;
                    case 'p':
                        if (i + 1 < argc) {
                            password_value = argv[i + 1];
                            i++;
                        } else {
                            printf(ERROR_MESSAGE);
                            return 1;
                        }
                        break;
                    case 'i':
                        if (i + 1 < argc) {
                            input_file_value = argv[i + 1];
                            i++;
                        } else {
                            printf(ERROR_MESSAGE);
                            return 1;
                        }
                        break;
                    case 'o':
                        if (i + 1 < argc) {
                            output_file_value = argv[i + 1];
                            i++;
                        } else {
                            printf(ERROR_MESSAGE);
                            return 1;
                        }
                        break;
                    default:
                        printf(ERROR_MESSAGE);
                        break;
                }
                break;
            default:
                printf(ERROR_MESSAGE);
                break;
        }
    }

    if (s_flag == 1 && d_flag == 1) {
        printf(ERROR_MESSAGE);
        return 1;
    }

    if (s_flag == 0 && d_flag == 0) {
        printf(ERROR_MESSAGE);
        return 1;
    }

    char plaintext[100] = "Hello&$}, world!";
    char key[100] = "secret";
    char ciphertext[100];
    char decrypted_plaintext[100];

    vigenere_encrypt(plaintext, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    vigenere_decrypt(ciphertext, key, decrypted_plaintext);
    printf("Decrypted message: %s\n", decrypted_plaintext);


    return 0;
}