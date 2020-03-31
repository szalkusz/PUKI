  /**   ===========================
  *     PUKI - Picture Utility King
  *     ===========================
  *
  *     === Image engine module ===
  *
  * @authr Szalai András - kapcsolat@szalkusz.hu
  */

#include <stdio.h>
#include <stdlib.h>
#include "img_types.h"
#include "debugmalloc.h"

Image * Grayscale(Image *img){
    if(img != NULL){

        Image * modified = (Image *)malloc(sizeof(Image));
        modified->width = img->width;
        modified->height = img->height;
        modified->data = (Pixel**)malloc(modified->height * sizeof(Pixel*)); //allocate memory for pixel data
        modified->data[0] = (Pixel*)malloc(modified->width * modified->height * sizeof(Pixel)); //allocate memory for pixel data
        for (int y = 1; y < modified->height; y++){
                modified->data[y] = modified->data[0] + y*modified->width;
        }

        for(int y = 0; y < img->height; y++) {
            for(int x = 0; x < img->width; x++){
                int avg = (img->data[y][x].R + img->data[y][x].G + img->data[y][x].B) / 3; //AVERAGE
                modified->data[y][x].R = avg;
                modified->data[y][x].G = avg;
                modified->data[y][x].B = avg;
            }
        }
        free(img->data[0]);
        free(img->data);
        free(img);
        return modified;
    }
    else{
        return NULL;
    }
}

Image * Darken(Image *img){
    if(img != NULL){

        Image * modified = (Image *)malloc(sizeof(Image));
        modified->width = img->width;
        modified->height = img->height;
        modified->data = (Pixel**)malloc(modified->height * sizeof(Pixel*)); //allocate memory for pixel data
        modified->data[0] = (Pixel*)malloc(modified->width * modified->height * sizeof(Pixel)); //allocate memory for pixel data
        for (int y = 1; y < modified->height; y++){
                modified->data[y] = modified->data[0] + y*modified->width;
        }

        for(int y = 0; y < img->height; y++) {
            for(int x = 0; x < img->width; x++){
                modified->data[y][x].R = img->data[y][x].R / 2;
                modified->data[y][x].G = img->data[y][x].G / 2;
                modified->data[y][x].B = img->data[y][x].B / 2;
            }
        }
        free(img->data[0]);
        free(img->data);
        free(img);
        return modified;
    }
    else{
        return NULL;
    }
}

Image * Lighten(Image *img){
    if(img != NULL){

        Image * modified = (Image *)malloc(sizeof(Image));
        modified->width = img->width;
        modified->height = img->height;
        modified->data = (Pixel**)malloc(modified->height * sizeof(Pixel*)); //allocate memory for pixel data
        modified->data[0] = (Pixel*)malloc(modified->width * modified->height * sizeof(Pixel)); //allocate memory for pixel data
        for (int y = 1; y < modified->height; y++){
                modified->data[y] = modified->data[0] + y*modified->width;
        }

        for(int y = 0; y < img->height; y++) {
            for(int x = 0; x < img->width; x++){
                modified->data[y][x].R = ((img->data[y][x].R * 2) > 255)? 255 : (img->data[y][x].R * 2);
                modified->data[y][x].G = ((img->data[y][x].G * 2) > 255)? 255 : (img->data[y][x].G * 2);
                modified->data[y][x].B = ((img->data[y][x].B * 2) > 255)? 255 : (img->data[y][x].B * 2);
            }
        }
        free(img->data[0]);
        free(img->data);
        free(img);
        return modified;
    }
    else{
        return NULL;
    }
}

Image * Blur(Image *img){
    if(img != NULL){

        Image * modified = (Image *)malloc(sizeof(Image));
        modified->width = img->width;
        modified->height = img->height;
        modified->data = (Pixel**)malloc(modified->height * sizeof(Pixel*)); //allocate memory for pixel data
        modified->data[0] = (Pixel*)malloc(modified->width * modified->height * sizeof(Pixel)); //allocate memory for pixel data
        for (int y = 1; y < modified->height; y++){
                modified->data[y] = modified->data[0] + y*modified->width;
        }

        for(int y = 0; y < img->height; y++) {
            for(int x = 0; x < img->width; x++){

                //PIXEL
                long int R = 0;
                long int G = 0;
                long int B = 0;

                for(int iy = -17; iy < 18; iy++){
                    for(int ix = -17; ix < 18; ix++){ //slow, but according to the specification I have no choice..
                        int y_index = ((y + iy) < 0) ? 0 : (y + iy);
                        int x_index = ((x + ix) < 0) ? 0 : (x + ix);
                        y_index = (y_index >= img->height) ? img->height - 1 : y_index;
                        x_index = (x_index >= img->width) ? img->width - 1 : x_index;

                        //SUBPIXEL
                        R += img->data[y_index][x_index].R;
                        G += img->data[y_index][x_index].G;
                        B += img->data[y_index][x_index].B;
                    }
                }

                modified->data[y][x].R = R / 1225;
                modified->data[y][x].G = G / 1225;
                modified->data[y][x].B = B / 1225;

            }
        }
        free(img->data[0]);
        free(img->data);
        free(img);
        return modified;
    }
    else{
        return NULL;
    }
}

Image * Sharpen(Image *img){
    if(img != NULL){

        int sharpenForce = 1;
        int kernel[3][3];

        kernel[0][0] = 0;
        kernel[0][1] = -1*sharpenForce;
        kernel[0][2] = 0;

        kernel[1][0] = -1*sharpenForce;
        kernel[1][1] = (4*sharpenForce) +1;
        kernel[1][2] = -1*sharpenForce;

        kernel[2][1] = 0;
        kernel[2][2] = -1*sharpenForce;
        kernel[2][0] = 0;

        Image * modified = (Image *)malloc(sizeof(Image));
        modified->width = img->width;
        modified->height = img->height;
        modified->data = (Pixel**)malloc(modified->height * sizeof(Pixel*)); //allocate memory for pixel data
        modified->data[0] = (Pixel*)malloc(modified->width * modified->height * sizeof(Pixel)); //allocate memory for pixel data
        for (int y = 1; y < modified->height; y++){
                modified->data[y] = modified->data[0] + y*modified->width;
        }

        for(int y = 0; y < img->height; y++) {
            for(int x = 0; x < img->width; x++){

                int NewPixelValueR = 0;
                int NewPixelValueG = 0;
                int NewPixelValueB = 0;

                  for (int YK = -1; YK < 2 ;YK++){
                    for(int XK = -1; XK < 2; XK++){

                       int y_index = y+YK;
                       int x_index = x+XK;
                       y_index = (y_index >= img->height || y_index < 0) ? img->height - 1 : y_index;
                       x_index = (x_index >= img->width || x_index < 0) ? img->width - 1 : x_index;

                       int PixelValueR = img->data[y_index][x_index].R;
                       int PixelValueG = img->data[y_index][x_index].G;
                       int PixelValueB = img->data[y_index][x_index].B;

                       NewPixelValueR += kernel[YK+1][XK+1] * PixelValueR;
                       NewPixelValueG += kernel[YK+1][XK+1] * PixelValueG;
                       NewPixelValueB += kernel[YK+1][XK+1] * PixelValueB;

                      }
                    }

                    modified->data[y][x].R = (NewPixelValueR > 255) ? 255 : (NewPixelValueR < 0) ? 0 : NewPixelValueR;
                    modified->data[y][x].G = (NewPixelValueG > 255) ? 255 : (NewPixelValueG < 0) ? 0 : NewPixelValueG;
                    modified->data[y][x].B = (NewPixelValueB > 255) ? 255 : (NewPixelValueB < 0) ? 0 : NewPixelValueB;

            }
        }
        free(img->data[0]);
        free(img->data);
        free(img);
        return modified;
    }
    else{
        return NULL;
    }
}
