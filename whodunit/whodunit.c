#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // If fewer or more than 2 command-line arguments, return 1 to stderr
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }

    // remember filenames
    // pointer variable stores address to the first char in the string (command line argument)
    char *infile = argv[1];
    char *outfile = argv[2];

    // open input file
    // inptr will contain the address to the file that infile points to
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) // if input file cannot be opened for reading, return 2 to stderr
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    // outptr will contain the address to the file that outfile points to
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL) // if output file cannot be opened for writing, return 3 to stderr
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // size_t fread(void* ptr, size_t size, size_t blocks, FILE* fp)
    // fread reads from the file 'fp' an element of 'size' bites 'blocks' number of times
    // on each fread, it will store the bytes in a buffer pointer to by ptr
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf; // create a struct of BITMAPFILEHEADER and call it bf
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi; // create a struct of BITMAPINFOHEADER and call it bi
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // fwrite writes out to file 'outptr' an element of sizeof(x) size 1 time (because one struct)
    // on each fwrite, it will write from the buffer pointer to by bf / bi
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // read scanline, pixel by pixel
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage in a struct of type RGBTRIPLE called 'triple'
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // change pixel's color as necessary
            // if red, change to white
            if (triple.rgbtRed == 0xff && triple.rgbtGreen == 0x00 &&
                triple.rgbtBlue == 0x00)
            {
                triple.rgbtRed = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtBlue = 0xff;
            }
            // if Green and Blue are ff and Red isn't, change to black
            // e0ffff e2ffff e4ffff ebffff fdffff e6ffff f1ffff f3ffff
            if (triple.rgbtRed != 0xff && triple.rgbtGreen == 0xff &&
                triple.rgbtBlue == 0xff)
            {
                triple.rgbtRed = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtBlue = 0x00;
            }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}