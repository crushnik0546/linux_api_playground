// Напишите программу, чтобы посмотреть, что случится, если попытаться осуществить 
// переход с помощью функции longjmp() в функцию, возвращение из которой уже произошл

#include <stdio.h>
#include <setjmp.h>

static jmp_buf env;

void func_setjmp() {
    printf("Enter to func with setjmp()\n");

    if(setjmp(env) == 0) {
        printf("First call of setjmp()\n");
    } else {
        printf("Jump to setjmp\n");
    }
}

int main(int argc, char *argv[]) {
    func_setjmp();

    longjmp(env, 1);

    printf("End\n");

    return 0;
}