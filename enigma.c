#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define ALPHABET "abcdefghijklmnopqrstuvwxyz"

typedef struct
{
    char *rotor1;
    char *rotor2;
    char *rotor3;
    char str[83];
} rotors;

rotors *createRotors()
{
    rotors *newRotors = (rotors *)malloc(sizeof(rotors));
    if (newRotors == NULL)
    {
        // handle memory allocation failure
        return NULL;
    }

    newRotors->rotor1 = (char *)malloc(27 * sizeof(char)); // Allocate for 26 letters + '\0'
    if (newRotors->rotor1 == NULL)
    {
        free(newRotors);
        return NULL;
    }

    newRotors->rotor2 = (char *)malloc(27 * sizeof(char)); // Allocate for 26 letters + '\0'
    if (newRotors->rotor2 == NULL)
    {
        free(newRotors->rotor1);
        free(newRotors);
        return NULL;
    }

    newRotors->rotor3 = (char *)malloc(27 * sizeof(char)); // Allocate for 26 letters + '\0'
    if (newRotors->rotor3 == NULL)
    {
        free(newRotors->rotor1);
        free(newRotors->rotor2);
        free(newRotors);
        return NULL;
    }

    return newRotors;
}

void freeRotors(rotors *r)
{
    if (r != NULL)
    {
        free(r->rotor1);
        free(r->rotor2);
        free(r->rotor3);
        free(r);
    }
}

int find_index(const char *str, char c)
{
    char *chr = strchr(str, c);
    return chr ? (chr - str) : -1;
}

char reflector(char c)
{
    int len = strlen(ALPHABET);
    return ALPHABET[len - find_index(ALPHABET, c) - 1];
}

void load(rotors *rs, char *dest, int start)
{
    strncpy(dest, rs->str + start, 26);
    dest[26] = '\0'; // Null-terminate the string
    printf("%s\n", dest);
}

char enigma_char(rotors *rs, char c)
{
    int index = find_index(ALPHABET, c);
    if (index == -1)
        return c; // Return the character if not found in the alphabet

    char c1 = rs->rotor1[index];
    char c2 = rs->rotor2[find_index(ALPHABET, c1)];
    char c3 = rs->rotor3[find_index(ALPHABET, c2)];

    char reflected = reflector(c3);

    c3 = ALPHABET[find_index(rs->rotor3, reflected)];
    c2 = ALPHABET[find_index(rs->rotor2, c3)];
    c1 = ALPHABET[find_index(rs->rotor1, c2)];

    return c1;
}

void rotate_rotors()
{
    // Rotation logic not implemented
}

int main()
{
    rotors *rs = createRotors();
    if (rs == NULL)
    {
        fprintf(stderr, "Failed to create rotors\n");
        return 1;
    }

    int fd = open("rotor_state_today", O_RDONLY, 0644);
    if (fd == -1)
    {
        perror("Failed to open file");
        freeRotors(rs);
        return 1;
    }

    ssize_t bytes_read = read(fd, rs->str, sizeof(rs->str) - 1);
    if (bytes_read == -1)
    {
        perror("Failed to read file");
        close(fd);
        freeRotors(rs);
        return 1;
    }
    rs->str[bytes_read] = '\0'; // Null-terminate the read string
    close(fd);

    printf("%s\n", rs->str);

    load(rs, rs->rotor1, 0);
    load(rs, rs->rotor2, 27);
    load(rs, rs->rotor3, 54);

    char *plain = "og";
    int plainsize = strlen(plain);
    char cipher[plainsize + 1]; // +1 for the null-terminator

    for (int i = 0; i < plainsize; i++)
    {
        cipher[i] = enigma_char(rs, plain[i]);
        printf("Cipher index %d | ", i);
    }
    cipher[plainsize] = '\0';

    printf("Cipher text: %s\n", cipher);

    freeRotors(rs);
    return 0;
}
