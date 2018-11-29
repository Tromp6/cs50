// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int f = atoi(argv[1]);

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
    BITMAPINFOHEADER bi;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    int oldHeight =abs(bi.biHeight);
    int oldWidth = bi.biWidth;
    bi.biWidth*=f;
    bi.biHeight=f*bi.biHeight;


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int newpadding = (4 - (bi.biWidth*sizeof(RGBTRIPLE)) % 4) % 4;
    int oldpadding = (4 - (oldWidth*sizeof(RGBTRIPLE)) % 4) % 4;

    //FEHLER wenn ich dieses padding benutze überspringe ich falsch beim input file

    bi.biSizeImage =   ((sizeof(RGBTRIPLE)*bi.biWidth)+newpadding)*abs(bi.biHeight);
    // write outfile's BITMAPINFOHEADER



    bf.bfSize=bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0; i < oldHeight; i++)
    {
        RGBTRIPLE triplet[oldWidth*f];
        int count =0;
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;


            // read RGB triple from infile

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);




            // write RGB triple to outfile


            for (int y =0;y<f;y++){
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            triplet[count]=triple;
            count++;




            }

        }
        fseek(inptr, oldpadding, SEEK_CUR);


            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }



        for(int z =0;z<f-1;z++){

            for(int u =0; u<count;u++){
                fwrite(&triplet[u], sizeof(RGBTRIPLE), 1, outptr);


            }
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }


        }


            count =0;


//Ok vlt is der Fehler dass ich nicht über das Padding im input file skippe
        // skip over padding, if any



    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
