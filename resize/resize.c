#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // If fewer or more than 3 command-line arguments, return 1 to stderr
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // initialize resize factor n
    int n = atoi(argv[1]);

    // n must be a positive integer less than or equal to 100 but greater than 0
    if ((n < 0 ) || (n > 100))
    {
        fprintf(stderr, "Please choose a positive integer between 0 and 100.\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
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

    // remember original image info
    int wd = bi.biWidth;
    int ht = abs(bi.biHeight);
    int padding = (4 - (wd * sizeof(RGBTRIPLE)) % 4) % 4; // original padding
    int pad = (4 - (wd * n * sizeof(RGBTRIPLE)) % 4) % 4; // new file padding
    int fixer = ht * n * pad; // last piece of the puzzle

    // update bitmap file and info headers to write in resized image
    bi.biWidth *= n;
    bi.biHeight *= n;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * wd * n) * (ht * n)) + fixer;
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < ht; i++)
    {
        // iterate over each scanline n times
        for (int h = 0; h < n; h++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < wd; j++)
            {
                // iterate over each pixel n times
                for (int g = 0; g < n; g++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                    // go back one pixel until the pixel is printed n - 1 times
                    if (g != (n - 1))
                    {
                        fseek(inptr, -sizeof(RGBTRIPLE), SEEK_CUR);
                    }
                }
            }

            // add padding to new file as needed to make each line a multiple of 4 bytes
            if (pad != 0)
            {
                for (int k = 0; k < pad; k++)
                {
                    fputc(0x00, outptr);
                }
            }

            // move file pointer back to the beginning of the prev scanline until that line is printed n times
            if (h != (n - 1))
            {
                fseek(inptr, -(sizeof(RGBTRIPLE) * wd), SEEK_CUR);
            }
        }
        // skip padding in original file, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}