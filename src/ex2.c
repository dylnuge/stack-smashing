#include <stdio.h>

void root_mode() {
    printf("Exploit succeeded\n");
}

void get_username() {
    char username[12];
    gets(username);
}

int main(int argc, char **args) {
    if (argc != 1) {
        return 1;
    }

    get_username();
}
