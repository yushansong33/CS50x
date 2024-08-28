#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // buffer for JEPG check
    BYTE buffer[BLOCK_SIZE];

    // buffer for file name
    char filename[8];
    FILE *image; //>>output of JPEGs
    int count = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, BLOCK_SIZE, 1, raw))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count != 0)
            {
                fclose(image);
            }
            sprintf(filename, "%03i.jpg", count);
            image = fopen(filename, "w");
            fwrite(buffer, BLOCK_SIZE, 1, image);
            count++;
        }
        else if (count > 0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, image);
        }
    }

    fclose(raw);
    fclose(image);
}
