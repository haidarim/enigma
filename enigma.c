#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

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

char reflector(char c){
    char *str = "abcdefghijklmnopqrstuvwxyz";
    int size = (int) sizeof(str)/sizeof(str[0]);
    char *chr = strchr(str,c);
    int chrindx = chr-str;
    return str[size-chrindx-1];
}



char enigma_char(char c, char *str){
    char c1, c2, c3;
    int size = (int)(sizeof(str)/sizeof(str[0]));
    char *tmp;
    for(int i = 0; i<size; i++){
        if(data[i] == ' '){
            //printf("counter= %d\n", counter);
            //counter = 0;

            *tmp = "";
            continue;
        }else if(data[i] == '\0')
        {
            printf("counter= %d\n", counter);
            break;
        }
        tmp[i] = str[i];        
    }
}

int main()
{
    char rotor1[27] = "abcdefghijklmnopqrstuvwxyz";
    char rotor2[27]; 
    char rotor3[27]; 
    
    

    shuffle(rotor1, 27);

    strcpy(rotor2, rotor1);
    shuffle(rotor2, 27);
    
    strcpy(rotor3,rotor2);
    shuffle(rotor3, 27);

    int fd = open("rotor_state_today", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        perror("fd fialed");
        exit(-1);
    }
    
    char data[83];
    strcpy(data, rotor1);
    strcat(data, " ");
    strcat(data, rotor2);
    strcat(data, " ");
    strcat(data, rotor3);

    // Write the structure to the file
    ssize_t bytes_written = write(fd, &data, 83);
    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return 1;
    }

    close(fd);
    /*int data_size = (int)(sizeof(data)/sizeof(data[0]));
    printf("%s \n %d\n", data, data_size);
    
    int counter = 0;
    for(int i = 0; i<data_size; i++){
        if(data[i] == ' '){
            printf("counter= %d\n", counter);
            counter = 0;
            continue;
        }else if(data[i] == '\0')
        {
            printf("counter= %d\n", counter);
            break;
        }
        counter++;
    }*/

    char *plain = "hi";
    char *ciper;
    
    int plainsize = sizeof(plain)/sizeof(plain[0]);
    for(int i = 0; i<plainsize; i++){
        ciper[i] = enigma
    }
    return 0; 
}