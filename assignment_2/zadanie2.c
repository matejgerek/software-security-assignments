#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 256
#define MAX_PASSWORD_LENGTH 256
#define MAX_LINE_LENGTH 200
#define MAX_KEY_LENGTH 256
#define MAX_KEYS_PER_USER 10
#define MAX_USERS 5

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password_hash[256];
    char keys[MAX_KEYS_PER_USER][MAX_KEY_LENGTH];
} User;

bool load_users(User users[], int max_num_users);

void remove_key(User *user, int index);

bool verify_key(User *user, char *key);

void print_user(User user);

void print_users(User users[], int num_users);

bool compare_passwords(char password[MAX_PASSWORD_LENGTH], char *password_hash);

User *find_user(User users[], int num_users, char *username);

void get_data_from_input(char *username, char *password, char *key);

/**
 * Computes the hash value of a given string.
 *
 * This function uses the djb2 hash algorithm to compute the hash value of
 * the given string. The hash value is an unsigned long integer that can be
 * used to uniquely identify the input string.
 *
 * @param str The string to hash.
 *
 * @return The hash value of the input string.
 */
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


int main(void) {
    User users[MAX_USERS];
    int num_users = 0;

    if (load_users(users, MAX_USERS)) {
        num_users = sizeof(users) / sizeof(users[0]);
    } else {
        printf("chyba\n");
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char key[MAX_KEY_LENGTH];
    get_data_from_input(username, password, key);

    User *user = find_user(users, num_users, username);
    if (user == NULL) {
        printf("chyba\n");
        return 1;
    }

    bool password_correct = compare_passwords(password, user->password_hash);

    return 0;
}

bool compare_passwords(char password[MAX_PASSWORD_LENGTH], char *password_hash) {
    unsigned long hashed_password = hash(password);
    char hashed_password_str[256];
    sprintf(hashed_password_str, "%lu", hashed_password);

    return strcmp(hashed_password_str, password_hash) == 0;
}

void get_data_from_input(char *username, char *password, char *key) {
    printf("meno: ");
    scanf("%s", username);
    printf("heslo: ");
    scanf("%s", password);
    printf("overovaci kluc: ");
    scanf("%s", key);
}

User *find_user(User users[], int num_users, char *username) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }

    return NULL;
}


bool load_users(User users[], int max_num_users) {
    FILE *fp = fopen("hesla.csv", "r");
    if (fp == NULL) {
        printf("chyba\n");
        return false;
    }

    char line[MAX_LINE_LENGTH];
    int user_index = 0;
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL && user_index < max_num_users) {
        char *token = strtok(line, ":");
        if (token == NULL) {
            continue;
        }

        // Copy username
        strcpy(users[user_index].username, token);

        // Copy password hash
        token = strtok(NULL, ":");
        if (token == NULL) {
            continue;
        }
        strcpy(users[user_index].password_hash, token);

        int key_index = 0;
        token = strtok(NULL, ",");
        while (token != NULL && key_index < MAX_KEYS_PER_USER) {
            strcpy(users[user_index].keys[key_index], token);
            token = strtok(NULL, ",");
            key_index++;
        }

        user_index++;
    }

    fclose(fp);

    return true;
}

void print_user(User user) {
    printf("Username: %s\n", user.username);
    printf("Password hash: %s\n", user.password_hash);
    printf("Keys:");
    for (int j = 0; j < MAX_KEYS_PER_USER; j++) {
        if (user.keys[j][0] != '\0') {
            printf(" %s", user.keys[j]);
        }
    }
    printf("\n\n");
}

void print_users(User users[], int num_users) {
    for (int i = 0; i < num_users; i++) {
        print_user(users[i]);
    }
}

