#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, string argv[])
{
    
    // If there aren't three command-line arguments, print the usage of this program and return 1
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }
    
    // Defines strings [char *] infile and outfile as the first and second command-line arguments, respectively [Knowing that ./whodunit is the zeroth argument]
    char *infile = argv[1];
    char *outfile = argv[2];
    
    // Open the first given file in read. If the output is NULL, print an error message describing how the file could not be read and return 2
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    // Open the second given file in write. If the output is NULL, print an error message describing how the file could not be created and return 3
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // Read the first given file's BMP file and info header
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // If the file doesn't meet the required specifications, print an error message describing the supported file type and return 4
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Write file and info header of outfile
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Iterate over pixels in each scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // Temporary storage
            RGBTRIPLE triple;

            // Read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // If the red value of the pixel is 255, reduce all the values in the pixel to 0
            if (triple.rgbtRed == 0xff)
            {
                triple.rgbtRed = 0x00;
                triple.rgbtBlue = 0x00;
                triple.rgbtGreen = 0x00;
            }

            // Write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // Writes padding back into outfile
        for (int k = 0; k < padding; k++)
        {
            
            // fputc means file put character
            fputc(0x00, outptr);
        }
    }

    // Close infile and outfile
    fclose(inptr);
    fclose(outptr);

    return 0;

}
