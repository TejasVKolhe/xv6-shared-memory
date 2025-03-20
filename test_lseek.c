#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main() {
    int fd = open("ls_testfile.txt", O_CREATE | O_RDWR);
    if (fd < 0) {
        printf(1, "open failed\n");
        exit();
    }

    write(fd, "abcdefghij", 10);  // 10 bytes

    int off = lseek(fd, 5, SEEK_SET);
    printf(1, "Offset after SEEK_SET to 5: %d\n", off);

    write(fd, "X", 1);  // Overwrite 6th character with 'X'

    off = lseek(fd, -2, SEEK_CUR);
    printf(1, "Offset after SEEK_CUR -2: %d\n", off);

    write(fd, "Y", 1);  // Overwrite 5th character with 'Y'

    off = lseek(fd, 0, SEEK_END);
    printf(1, "Offset after SEEK_END: %d\n", off);

    close(fd);
    exit();
}
