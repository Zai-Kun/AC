#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const int SIZE = sizeof(int);

int main(int argc, char *argv[]) {
    int fd = shm_open("/ac_flags", O_RDWR, 0666);
    
    if (fd == -1) {
        printf("Creating shared memory\n");
        fd = shm_open("/ac_flags", O_CREAT | O_RDWR, 0666);
        ftruncate(fd, SIZE);
    }

    int *flag = mmap(0x0, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    *flag = atoi(argv[1]);
}
