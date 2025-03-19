#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "stddef.h"
#define NSHM 64

extern struct shm{
    struct spinlock lock;
    int id;
    int nattached;
    int nframes;
    char *frames[NSHM];
}shminfo[NSHM];

//have to set the initial values of shminfo


void shmget(uint key, size_t size, int shmflg) 
{
    struct proc *curproc = myproc(); 
    uint sz = curproc->sz;

    int found = -1;
    for (int i = 0; i < NSHM; i++) 
    {
        if (shminfo[i].id == key) 
        {
            acquire(shminfo[i].lock);
            found = i;
            break;
        }
    }
    if (found != -1)
    {
        for(int j = 0; j < shminfo[found].nframes; j++)
        {
            //change permissions here
            mappages(curproc->pgdir, (char*)sz, PGSIZE, V2P(shminfo->frames[j]), PTE_W|PTE_U);
            sz += PGSIZE;
            //release(shminfo[found].lock);
        }
        curproc->sz = sz;
        return found;
    }
    else
    {
        for (int i = 0; i < 64; i++)
        {
            if (shminfo[i].id == 0)
            {
                key = i;
                break;
            }

        }
        if(size > 0)
        {
            if((sz = allocshmuvm(curproc->pgdir, sz, sz + size, &shminfo)) == 0)
                return -1;
            shminfo[key].nframes = (size / PGSIZE) + 1;
        }
        curproc->sz = sz;
    }
}
