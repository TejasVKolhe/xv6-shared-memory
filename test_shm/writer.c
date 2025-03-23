#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Shared memory size
#define SHM_KEY 1234   // Unique key for shared memory

int main() {
    int shmid;
    char *shm_addr;

    // Create shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    shm_addr = (char *)shmat(shmid, NULL, 0);
    if (shm_addr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    printf("Writer Process: Type messages (type 'exit' to quit)\n");

    while (1) {
        printf("You: ");
        fgets(shm_addr, SHM_SIZE, stdin);

        if (strncmp(shm_addr, "exit", 4) == 0) {
            break;
        }
        sleep(1);  // Give reader some time to read
    }

    // Detach shared memory
    shmdt(shm_addr);

    // Remove shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
