/*
    analog of tee
    with flag -a (append)

    WARNING: without -a param the file overwrites but saves old content
*/

#include <fcntl.h>
#include "../../lib/tlpi_hdr.h"

#define BUFFER_SIZE 128

int main (int argc, char* argv[])
{
    int fd_out, num_read;
    char buf_stdin[BUFFER_SIZE];
    char* filename;

    if (argc < 2 || strcmp("--help", argv[1]) == 0 ||
        (strcmp(argv[1], "-a") == 0 && argc < 3))
        usageErr("%s {-a} file\n", argv[0]);

    if (strcmp(argv[1], "-a") == 0)
        filename = argv[2];
    else
        filename = argv[1];

    fd_out = open(filename, O_RDWR | O_CREAT,
        S_IRUSR | S_IWUSR |
        S_IRGRP | S_IWGRP |
        S_IROTH | S_IWGRP);   /* rw-rw-rw- */

    if (fd_out == -1)
        errExit("open file");

    // append to file
    if (strcmp(argv[1], "-a") == 0)
    {
        if(lseek(fd_out, 0, SEEK_END) == -1)
            errExit("lseek");
    }

    while((num_read = read(STDIN_FILENO, buf_stdin, BUFFER_SIZE - 1)) > 0)
    {
        if(write(fd_out, buf_stdin, num_read) != num_read)
            fatal("write() returned error or partial write occurred");
        
        if(write(STDOUT_FILENO, buf_stdin, num_read) != num_read)
            fatal("write() returned error or partial write occurred");
    }

    if(num_read == -1)
        errExit("read std_in");

    if (close(fd_out) == -1)
        errExit("close file");

    exit(EXIT_SUCCESS);
}