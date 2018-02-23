#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // If fewer or more than 1 command-line arguments, return 1 to stderr
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover diskimage\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char outfile[10];
    char *jpg = ".jpg";
    int title = 0;

    // open disk image and store address in inptr
    FILE *inptr = fopen(infile, "r");
    // return 2 if disk image is invalid
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // initialize buffer - temporary storage
    unsigned char buffer[513];

    // read until EOF
    while ( fread(buffer, 512, 1, inptr) != 0 )
    {
        // start of jpeg file
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // format filename string and store in outfile
            sprintf(outfile, "%03d%s", title, jpg);
            // open outfile and assign address to outptr
            FILE *outptr = fopen(outfile, "w");
            // write in to outptr from buffer 512 bytes
            fwrite(buffer, 512, 1, outptr);

            // continue until EOF
            while (fread(buffer, 512, 1, inptr) != 0)
            {
                // if beginning of next jpeg found
                if (buffer[0] == 0xff &&
                    buffer[1] == 0xd8 &&
                    buffer[2] == 0xff &&
                    (buffer[3] & 0xf0) == 0xe0)
                {
                    fclose(outptr); // close file, move pointer back 512 bytes, and +1 to title
                    fseek(inptr, -512, SEEK_CUR);
                    title++;
                    break;
                }
                else
                {
                    // keep writing into outptr until new jpeg found
                    fwrite(buffer, 512, 1, outptr);
                }
            }
        }
    }
    // close infile
    fclose(inptr);

    // success
    return 0;
}