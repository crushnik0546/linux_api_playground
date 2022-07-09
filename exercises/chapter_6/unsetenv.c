// Реализуйте функции setenv() и unsetenv(), используя функции getenv(), putenv()
// и там, где это необходимо, код, который изменяет массив environ напрямую. Ваша 
// версия функции unsetenv() должна проверять наличие нескольких определений 
// переменной среды и удалять все определения (точно так же, как это делает glibc-версия 
// функции unsetenv())

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../lib/tlpi_hdr.h"

int unsetenv_usr(const char *name) {

    if (strstr(name, "=") != NULL) {
        return -1;
    }

    while (getenv(name) != NULL) {
        // glibc реализация putenv удаляет переменную среды 
        // если в name отсутствует знак равенства "="
        if (putenv(name) != 0) {  
            return -1;
        }
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

    if (argc < 2 || strcmp("--help", argv[1]) == 0) {
        usageErr("%s variable_name\n", argv[0]);
        return 0;
    }

    printf("__Environment before changing:\n");
    show_eviron();
    
    printf("__Environment after changing:\n");
    if (unsetenv_usr(argv[1])) {
        err_exit("Erorr during change environment!");
    } else {
        show_eviron();
    }
    
    return 0;
}
