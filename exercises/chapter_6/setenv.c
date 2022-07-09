// Реализуйте функции setenv() и unsetenv(), используя функции getenv(), putenv()
// и там, где это необходимо, код, который изменяет массив environ напрямую. Ваша 
// версия функции unsetenv() должна проверять наличие нескольких определений 
// переменной среды и удалять все определения (точно так же, как это делает glibc-версия 
// функции unsetenv())

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../lib/tlpi_hdr.h"

int setenv_usr(const char *name, const char *value, int overwrite) {
    int string_length = strlen(name) + strlen(value) + 2; // 1 + 1 -> "=" + "\0"

    char *new_env = (char *)malloc(string_length * sizeof(char));
    if (new_env == NULL) {
        return -1;
    }

    strcat(new_env, name);
    strcat(new_env, "=");
    strcat(new_env, value);

    // if there is a var in environ with "name" and overwrite = 0 -> do nothing
    if (overwrite == 0) {
        if (getenv(name) != NULL) {
            return 0;
        }
    }

    if (putenv(new_env) != 0) {
        return -1;
    }

    return 0;
}

void show_eviron() {
    extern char **environ;
    char **ep;
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);
}

int main(int argc, char *argv[]) {

    if (argc < 4 || strcmp("--help", argv[1]) == 0) {
        usageErr("%s variable_name variable_value overwrite\n", argv[0]);
        return 0;
    }

    char *end;
    int overwrite = strtol(argv[3], &end, 10);
    if (*end != '\0') {
        usageErr("%s variable_name variable_value overwrite\n", argv[0]);
        return 0;
    }

    printf("__Environment before changing:\n");
    show_eviron();
    
    printf("__Environment after changing:\n");
    if (setenv_usr(argv[1], argv[2], overwrite)) {
        err_exit("Erorr during change environment!");
    } else {
        show_eviron();
    }
    
    return 0;
}
