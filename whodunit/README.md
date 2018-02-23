# Questions

## What's `stdint.h`?

A header file in C that declares a set of integer types as having certain widths.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

You can fill up exactly the amount of space you want in a file.
- They are signed and unsigned integer types from stdint.h.
- Defining the types well makes it easier and safer for the code to port.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE: 8 bits = 1 byte
DWORD: 32 bits = 4 bytes
LONG: signed 32 bits = 4 bytes
WORD: 16 bits = 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

Stored in bftype.
- Hex:    0x424d
- ASCII:  BM (bitmap!)

## What's the difference between `bfSize` and `biSize`?

bfSize: The size, in bytes, of the bitmap file.
biSize: The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If biHeight is negative, indicating a top-down DIB, biCompression must be either BI_RGB or BI_BITFIELDS.
- Top-down DIBs cannot be compressed.
- DIB (Device Independent Bitmap): Windows-specific general bitmap format. 

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount: The number of bits-per-pixel.
- Determines the number of bits that define each pixel and the maximum number of colors in the bitmap.
- Must be one of the following values:
    - 0: The number of bits-per-pixel is specified or is implied by the JPEG or PNG format.
    - 1: The bitmap is monochrome, and the bmiColors member of BITMAPINFO contains two entries.
         Each bit in the bitmap array represents a pixel.
         If the bit is clear, the pixel is displayed with the color of the first entry in the bmiColors table;
         if the bit is set, the pixel has the color of the second entry in the table.
    - 4: The bitmap has a maximum of 16 colors, and the bmiColors member of BITMAPINFO contains up to 16 entries.
         Each pixel in the bitmap is represented by a 4-bit index into the color table.
         For example, if the first byte in the bitmap is 0x1F, the byte represents two pixels.
         The first pixel contains the color in the second table entry, 
         and the second pixel contains the color in the sixteenth table entry.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

- Can't open the file.
- File cannot be found.
- Filename is invalid.
- Not enough memory
- File cannot be read

## Why is the third argument to `fread` always `1` in our code?

It specifies how many elements to read.
1 because we are reading 1 struct from the file.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

- 3 because it has to be a multiple of 4.
- 3 pixels * 3 bytes per pixel * 3 padding = 12
- Ensures the number of bytes in every row is a multiple of 4.

## What does `fseek` do?

int fseek(FILE* fp, long int offset, int from_where);
- when reading in from a file, the pointer continues in one direction, 
  from the start of the file to the end.
- fseek, however, allows you to change the location of the file pointer fp
- offset refers to how many bytes you want to change the current position of the file pointer fp. 
- go forward with positive numbers, or backward with negative numbers

## What is `SEEK_CUR`?

SEEK_CUR
- used with 'fseek' - see above
- sets starting point for the pointer specified in fseek when changing location
SEEK_END
- set file pointer fp to a location in relation to the end of the file
SEEK_SET
- set file pointer fp to a location in relation to the beginning of the file