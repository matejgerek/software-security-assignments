#include <stdio.h>
#include <string.h>

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main() {
    char *users[] = {"user1", "user2", "user3", "user4", "user5"};
    char *passwords[] = {"password1", "password2", "password3", "password4", "password5"};
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        char input[strlen(users[i]) + strlen(passwords[i]) + 1];
        sprintf(input, "%s%s", users[i], passwords[i]);

        unsigned long hash_val = hash((unsigned char *)input);

        printf("%s:%lu\n", users[i], hash_val);
    }

    return 0;
}
