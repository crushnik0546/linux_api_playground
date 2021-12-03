#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

int main()
{
    if (close(STDIN_FILENO) == -1)
        errExit("close");

    int fd = 9;
    fd = open("tmp.txt", O_RDONLY); // fd = 0
    if (fd == -1)
        errExit("open");

    return 0;
}