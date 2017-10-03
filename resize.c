#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.h"

int main(int argc, string argv[])
{
    
    // If there aren't four command-line arguments, print the usage of this program and return 1
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // Convertes the command-line argument from a string to a useable integer
    int n = atoi(argv[1]);
    
    // If n isn't between 1 and 100, print an error explaining so and return 5
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "n must be a number between 1 and 100.\n");
        return 5;
    }
    
    // Defines strings [char *] infile and outfile as the first and second command-line arguments, respectively [Knowing that ./whodunit is the zeroth argument]
    char *infile = argv[2];
    char *outfile = argv[3];
    
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

    // If the file doesn't meet the required specifications, print an error message that the file format is unsupported and return 4
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Edit information in the headers to match the upcoming changes
    BITMAPFILEHEADER out_bf;
	BITMAPINFOHEADER out_bi;	
	out_bf = bf;
	out_bi = bi;
	out_bi.biWidth = bi.biWidth * n;
	out_bi.biHeight = bi.biHeight * n;
	
	// Define old and new padding
	int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	int out_padding = (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	
	// Edit information in the headers to match the changes
	// abs() means absolute value of whatever is within the brackets. Forces the value to be positive, esentially. Ex. 5 stays as 5, -3 becomes 3
	out_bi.biSizeImage = ((sizeof(RGBTRIPLE) * out_bi.biWidth) + out_padding) * abs(out_bi.biHeight);
	out_bf.bfSize = out_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // Write new file and info header of outfile
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        
        // Write the line n amount of times
        for (int o = 0; o < n; o++)
        {
            
            // Iterate over pixels in each scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
    
                // Temporary storage
                RGBTRIPLE triple;
                
                // Read RGB triple from infile
                // &triple means the address of triple
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // Write the pixel n amount of times
                for (int y = 0; y < n; y++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // Skip over old padding
            fseek(inptr, in_padding, SEEK_CUR);
            
            // Writes padding back into outfile, with the additional effect of the resizing
            for (int k = 0; k < out_padding * n; k++)
                
                // fputc means file put character
                fputc(0x00, outptr);
                
                // More padding skipping
                fseek(inptr, -(bi.biWidth * 3 + in_padding ), SEEK_CUR);
        }
        
        // Last padding skip
        fseek(inptr, bi.biWidth * 3 + in_padding, SEEK_CUR);
    }

    // Close infile and outfile
    fclose(inptr);
    fclose(outptr);

    return 0;

}

// Had to look up fixes for program, which amounted to fseek not being used in the necessary places
