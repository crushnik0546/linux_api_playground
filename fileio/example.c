#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define BUFF_SIZE 20

int main()
{
    // if (close(STDIN_FILENO) == -1)
    //     errExit("close");

    // int fd = 9;
    // fd = open("tmp.txt", O_RDONLY); // fd = 0
    // if (fd == -1)
    //     errExit("open");

    char buffer[BUFF_SIZE];
    if(read(STDIN_FILENO, &buffer, BUFF_SIZE) == -1)
        errExit("read");
    
    printf("Input data: %s", buffer);

    char true_buffer[BUFF_SIZE + 1];
    ssize_t num_read = read(STDIN_FILENO, &true_buffer, BUFF_SIZE);

    if (num_read == -1)
        errExit("read");

    true_buffer[num_read] = 0;

    printf("Input data: %s\n", true_buffer);

    return 0;
}