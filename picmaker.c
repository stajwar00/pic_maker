#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int create_file(char * file_name){
    int fd;
    fd = open(file_name, O_CREAT | O_EXCL | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1){
        fd = open(file_name, O_TRUNC, 0644);
    }
    printf("\nFile created\n");
    return fd;
}

int main(int argc, char * argv[]){
    char * file_name = "image.ppm";
    int fd = create_file(file_name);
    printf("\nfile opened");
    if (fd < 0){
        printf("Error %d: %s", errno, strerror(errno));
        return 1;
    }

    char data[20];
    snprintf(data, sizeof(data), "P3\n500 500\n255");
    write(fd, data, strlen(data));
    printf("\n wrote in");
 
    char image[3];
    for (int i = 0; i < 500; i++){
        for (int j = 0; j < 500; j++){
            image[0] = rand() % 255;
            image[1] = rand() % 255;
            image[2] = rand() % 255;
            snprintf(data, sizeof(data), "\n%d %d %d", image[0], image[1], image[2]);
            write(fd, data, strlen(data));
        }
    }

    close(fd);

}

