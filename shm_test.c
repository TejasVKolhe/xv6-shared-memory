#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int shmid = shmget(1234, 4096, IPC_CREAT);
    if (shmid < 0) {
        printf("shmget failed\n");
        exit(1);
    }
    printf("Shared memory segment ID: %d\n", shmid);
    exit(0);
}

