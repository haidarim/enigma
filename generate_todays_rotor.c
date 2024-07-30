#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTVUWXYZÖÄÅabcdefghijklmnopqrstuvwxyzöäå"

void shuffle(char *arr, int size){
    srand((unsigned int) time(NULL));
    size--; 
    for(int i = 0; i<size; i++){
        int randIndex = i + rand()% (size-i);
        char tmp = arr[i];
        arr[i] = arr[randIndex];
        arr[randIndex] = tmp;
    }
    
}


int main()
{
    char rotor1[59];
    char rotor2[59]; 
    char rotor3[59]; 
    
    strcpy(rotor1, ALPHABET);
    shuffle(rotor1, 59);

    strcpy(rotor2, rotor1);
    shuffle(rotor2, 59);
    
    strcpy(rotor3,rotor2);
    shuffle(rotor3, 59);

    int fd = open("rotor_state_today", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        perror("fd fialed");
        exit(-1);
    }
    
    char data[179];
    strcpy(data, rotor1);
    strcat(data, " ");
    strcat(data, rotor2);
    strcat(data, " ");
    strcat(data, rotor3);

    // Write the structure to the file
    ssize_t bytes_written = write(fd, &data, 179);
    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}
