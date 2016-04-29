#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glusterfs/api/glfs.h>

int main (int argc, char** argv) {
    const char *gfserver = "server";
    const char *gfvol = "gfs_volume";

    int ret;
    glfs_t *fs;
    glfs_fd_t *fd;

    fs = glfs_new(gfvol);   // Virtual filesystem type struct
    glfs_set_volfile_server (fs, "tcp", gfserver, 0);
    ret = glfs_init (fs);
    if (ret) {
        printf( "Failed to connect server/volume: %s/%s\n", gfserver, gfvol );
        exit(ret);
    }

    char *greet = "Hello, Gluster!\n";
    fd = glfs_creat(fs, "greeting.txt", O_RDWR, 0644);
    glfs_write(fd, greet, strlen(greet), 0);
    glfs_close(fd);
    return 0;
}
