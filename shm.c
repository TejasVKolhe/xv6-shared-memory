#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "stddef.h"
#include "shm.h"
#define NSHM 64

extern struct shm{
    struct spinlock lock;
    int id;
    int nattached;
    int nframes;
    char *frames[NSHM];
}shminfo[NSHM];

//have to set the initial values of shminfo
void init_shm(){
    for(int i = 0; i < NSHM ; i++){
        initlock(&shminfo[i].lock, "shm_lock");
        shminfo[i].id = -1;
        shminfo[i].nattached = 0;
        shminfo[i].nframes = 0;
        for(int j = 0 ;j < NSHM ; j++){
            shminfo[i].frames[j] = NULL;
        }
    }
}


int shmget(uint key, size_t size, int shmflg) 
{
    struct proc *curproc = myproc(); 
    uint sz = curproc->sz;

    int found = -1;
    for (int i = 0; i < NSHM; i++) 
    {
        if (shminfo[i].id == key) 
        {
            acquire(&shminfo[i].lock);
            found = i;
            break;
        }
    }
    if (found != -1)
    {
        if((shmflg & IPC_CREAT) && (shmflg & IPC_EXCL)){
            release(&shminfo[found].lock);
            return -1;
        }

        for(int j = 0; j < shminfo[found].nframes; j++)
        {
            //change permissions here
            mappages(curproc->pgdir, (char*)sz, PGSIZE, V2P(shminfo[found].frames[j]), PTE_W|PTE_U|PTE_P);
            sz += PGSIZE;

        }
        curproc->sz = sz;
        //shminfo[found].nattached++;
        release(&shminfo[found].lock);
        return shminfo[found].id;
    }

    if(!(shmflg & IPC_CREAT)) return -1;

    else
    {
        for (int i = 0; i < NSHM; i++)
        {
            if (shminfo[i].id == -1)
            {
                key = i;
                break;
            }

        }
        if(size > 0)
        {
            if((sz = allocshmuvm(curproc->pgdir, sz, sz + size, &shminfo[key])) == 0)
                return -1;
            shminfo[key].nframes = (size / PGSIZE) + 1;
            shminfo[key].id = key;
            //shminfo[key].nattached = 1;
        }
        curproc->sz = sz;
        return key;
    }
}

void *shmat(int shmid, const void *shmaddr, int shmflg)
{
    shminfo[shmid].nattached++;
    return (void *)shminfo[shmid].frames;
}