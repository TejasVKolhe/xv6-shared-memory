#define IPC_CREAT 0x200
#define IPC_EXCL  0x400

int shmget(uint key, size_t size, int shmflg);
void *shmat(int shmid, const void *shmaddr, int shmflg);