  /**   ===========================
  *     PUKI - Picture Utility King
  *     ===========================
  *
  *     === Image IO module ===
  *
  * @authr Szalai András - kapcsolat@szalkusz.hu
  */

#include <stdio.h>
#include <stdbool.h>
#include "img_types.h"
#include "debugmalloc.h"

Image *ReadImg(char *fileName){
    char buffer[64];
    Image *img;
    FILE *fp;
    int c, colorDepth;

    //REGION - Open & check & initialize file

        fp = fopen(fileName, "rb");

        if (fp == NULL) {
             fprintf(stderr, "Cannot open file.\n");
             return NULL;
        }

        if (fgets(buffer, sizeof(buffer), fp) == NULL) {
             fprintf(stderr, "Cannot read file.\n");
             return NULL;
        }

        if (buffer[0] != 'P' || buffer[1] != '6') {
             fprintf(stderr, "Wrong image format. Only PPM images are accepted (P6).\n");
             return NULL;
        }

        img = (Image *)malloc(sizeof(Image)); //allocate memory for Image (w, h, *p)
        if (img == NULL) {
             fprintf(stderr, "Cannot allocate memory.\n");
             return NULL;
        }

		//some parts of the code here have been inspired by posts on stackoverflow.com
        //jump comments out
        c = getc(fp); //read the next char to check if its a comment
        while (c == '#') { //check if the new part is a comment or not
            while (getc(fp) != '\n');
            c = getc(fp); //modify position indicator
        }
        ungetc(c, fp); //back

    //ENDREGION

    //REGION - Initialize pixel array

        if (fscanf(fp, "%d %d", &img->width, &img->height) != 2) {
             fprintf(stderr, "Image size isn't define a 2D matrix.\n");
             return NULL;
        }

        if (fscanf(fp, "%d", &colorDepth) != 1) {
             fprintf(stderr, "Cannot find valid color depth.\n");
             return NULL;
        }

        if (colorDepth!= 255) {
             fprintf(stderr, "Only 8-bit images are allowed.\n");
             return NULL;
        }

    //ENDREGION

    //REGION - Read pixel array

        while (fgetc(fp) != '\n'); //modify position indicator
        img->data = (Pixel**)malloc(img->height * sizeof(Pixel*)); //allocate memory for pixel data
        img->data[0] = (Pixel*)malloc(img->width * img->height * sizeof(Pixel)); //allocate memory for pixel data
        for (int y = 1; y < img->height; y++){
                img->data[y] = img->data[0] + y*img->width;
        }

        if (img == NULL) {
             fprintf(stderr, "Cannot allocate memory.\n");
             return NULL;
        }

        //2D load
        for(int y = 1; y < img->height; y++){
            fread(img->data[y], 3 * img->width, 1, fp); //fread(TO, NUM. OF BYTES IN A BLOCK (ROW) (R,G,B => 3), NUMBER OF LINES, FROM)
        }

    //ENDREGION

    fclose(fp);

    return img;
}

bool SaveImg(char *fileName, Image *img){
    FILE *fp;

    fp = fopen(fileName, "wb");
    if (fp == NULL) {
         fprintf(stderr, "Cannot save file.\n");
         return false;
    }

    //REGION - Write header

        //Magic number
        fprintf(fp, "P6\n");

        //Image size
        fprintf(fp, "%d %d\n",img->width,img->height);

        //Color depth
        fprintf(fp, "%d\n",255);

    //ENDREGION

    //REGION - Write data

        for(int y = 0; y < img->height; y++){
            fwrite(img->data[y], 3 * img->width, 1, fp);
        }

    //ENDREGION

    fclose(fp);

    return true;
}
