#define MAX_SHM_SEGMENTS 32  // Maximum shared memory regions
#define MAX_SHM_PAGES 16     // Maximum pages per segment

struct shminfo {
    int key;                      // Unique key
    uint64 pa[MAX_SHM_PAGES];     // Physical page addresses
    int num_pages;                // Number of allocated pages
    int ref_count;                // Number of processes using it
    int is_allocated;             // 1 if allocated, 0 otherwise
};
