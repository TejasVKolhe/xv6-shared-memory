#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "stddef.h"

extern struct {
    struct spinlock lock;
    uint id;
    int nattached;
    struct shm_page {
        char *frame;
    } shm_pages[64];
}shminfo[64];

void shmget(uint key, size_t size, int shmflg) 
{
    cprintf("Hello world");
    return;
    /*
    int NO_OF_PAGES = size / PGSIZE + 1;
    int found;
    for (int i = 0; i < 64; i++) 
    {
        if (shminfo[i].id == key) 
        {
            acquire(shminfo[i].lock);
            found = i;
            break;
        }
    }
    for(int j = 0; j < 64; j++)
    {
        char *va = (char*)PGROUNDUP(myproc()->sz);

        mappages(myproc()->pgdir, va, PGSIZE, V2P(shminfo.shm_pages[i].frame), PTE_W | PTE_U);
        myproc()->sz = (uint)va + PGSIZE;
        release( shminfo.lock);
        return i;
    }

    // If not found, allocate a new shared memory segment
    for (int i = 0; i < 64; i++) 
    {

        if  shminfo.shm_pages[i].id == 0) 
        {
            char *frame = kalloc();
            if (!frame) 
            {
                release( shminfo.lock);
                return (void*)-1; 
            }
            //memset(frame, 0, PGSIZE);
         shminfo.shm_pages[i].id = key;
         shminfo.shm_pages[i].frame = frame;
         shminfo.shm_pages[i].refcnt = 1;

            char *va = (char*)PGROUNDUP(myproc()->sz);
            mappages(myproc()->pgdir, va, PGSIZE, V2P(frame), PTE_W | PTE_U);
            myproc()->sz = (uint)va + PGSIZE;
            release( shminfo.lock);
            return i;
        }
    }

    release( shminfo.lock);
    return (void*)-1;
    */
}
