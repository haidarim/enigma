#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define ALPHABET "abcdefghijklmnopqrstuvwxyz"

typedef struct{
    char *rotor1;
    char *rotor2;
    char *rotor3;
    char str[83];

}rotors;

rotors *rs;

int size(char *str){
    return (int) sizeof(str)/sizeof(str[0]);
}

int find_index(char *str, int size, char c){
    char *chr = strchr(str,c);
    return chr-str;

}

char reflector(char c){
    int len = size(ALPHABET);
    return ALPHABET[len-find_index(ALPHABET, len, c)-1];
}

void load(char* des , int start){
    char tmp[27];
    for(int i = 0; i<=26; i++){
        tmp[i] = rs->str[start+i];
    }
    tmp[27] = '\0';
    des = tmp;
    //printf("%s\n", des);
}

char enigma_char(char c){
    char c1, c2, c3;
    c1 = rs->rotor1[find_index(ALPHABET, 27, c)];
    c2 = rs->rotor2[find_index(ALPHABET, 27, c1)];
    c3 = rs->rotor3[find_index(ALPHABET, 27, c2)];
    
    char reflected = reflector(c3);

    c3 = ALPHABET[find_index(rs->rotor3, 27,reflected)];
    c2 = ALPHABET[find_index(rs->rotor2, 27,c3)];
    c1 = ALPHABET[find_index(rs->rotor1, 27,c2)];

    return c1;
}

void rotate_rotors(){
    //rs->rotor1 = rs->rotor1;//TODO
}

int main()
{
    int fd = open("rotor_state_today", O_RDONLY, 0644);
    if(fd == -1)
    {
        perror("fd fialed");
        close(fd);
        return 1;
    }

    rs = (rotors*) malloc(sizeof(rotors));
    ssize_t bytes_written = read(fd, rs->str, 83);
    if (bytes_written == -1) {
        perror("read failed");
        close(fd);
        return 1;
    }
    //printf("%s\n", rs->str);
    close(fd);

    load(rs->rotor1, 0);
    load(rs->rotor2, 27);
    load(rs->rotor3, 54);

    char *plain = "hi";
    int plainsize = size(plain);
    char cipher[plainsize];
    int state = 0;
    for(int i = 0; i<plainsize; i++){
        cipher[i] = enigma_char(*(plain+i));
    }
    cipher[plainsize] = '\0';
    //printf("%s", cipher);
    free(rs);
    return 0; 
}