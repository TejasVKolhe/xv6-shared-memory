#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234

int main() {
    int shmid;
    char *shm_addr;

    // Get shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
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

    printf("Reader Process: Waiting for messages...\n");

    while (1) {
        if (strlen(shm_addr) > 0) {
            printf("Sender: %s", shm_addr);

            if (strncmp(shm_addr, "exit", 4) == 0) {
                break;
            }

            // Clear the shared memory for the next message
            memset(shm_addr, 0, SHM_SIZE);
        }
        sleep(1); // Avoid CPU overuse
    }

    // Detach shared memory
    shmdt(shm_addr);

    return 0;
}
