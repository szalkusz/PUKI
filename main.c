  /**   ===========================
  *     PUKI - Picture Utility King
  *     ===========================
  *
  *     === Main program ===
  *
  * @authr Szalai András - kapcsolat@szalkusz.hu
  */

#include <stdio.h>
#include <string.h>
#include "img_io.h"
#include "img_engine.h"
#include "img_types.h"
#include "debugmalloc.h"

int main(int argc, char *argv[])
{
    char source[201], destination[201], operation[11];

    if (argc-1 != 3) {

       printf("         _      _                  _               _     \n        /\\ \\   /\\_\\               /\\_\\            /\\ \\   \n       /  \\ \\ / / /         _    / / /  _         \\ \\ \\  \n      / /\\ \\ \\\\ \\ \\__      /\\_\\ / / /  /\\_\\       /\\ \\_\\ \n     / / /\\ \\_\\\\ \\___\\    / / // / /__/ / /      / /\\/_/ \n    / / /_/ / / \\__  /   / / // /\\_____/ /      / / /    \n   / / /__\\/ /  / / /   / / // /\\_______/      / / /     \n  / / /_____/  / / /   / / // / /\\ \\ \\        / / /      \n / / /        / / /___/ / // / /  \\ \\ \\   ___/ / /__     \n/ / /        / / /____\\/ // / /    \\ \\ \\ /\\__\\/_/___\\    \n\\/_/         \\/_________/ \\/_/      \\_\\_\\\\/_________/    \n                                                         ");
       printf("\nService can be used only with well defined parameters.\nPlease execute the application with taking care of the following points:\n\n");
       printf("=================\n");
       printf("How to call PUKI?\n");
       printf("=================\n\n");
       printf("==> puki sourceFileName.ppm destinationFileName.ppm operationName <==\n\n");
       printf("For more information please check the User Guide document. Application exits.\n");
       getchar();
       return 1;


       //For faster development:
       //sscanf("src.ppm", "%s", &source);
       //sscanf("dst.ppm", "%s", &destination);
       //sscanf("grayscale", "%s", &operation);
    }
    else{
       sscanf(argv[1], "%s", source);
       sscanf(argv[2], "%s", destination);
       sscanf(argv[3], "%s", operation);
    }

    Image *image = ReadImg(source);
    if(image == NULL){
        return 1;
    }

    Image * modified;

    if(strcmp("darken", operation) == 0){
        modified = Darken(image);
    }
    else if(strcmp("lighten", operation) == 0){
        modified = Lighten(image);
    }
    else if(strcmp("grayscale", operation) == 0){
        modified = Grayscale(image);
    }
    else if(strcmp("blur", operation) == 0){
        modified = Blur(image);
    }
    else if(strcmp("sharpen", operation) == 0){
        modified = Sharpen(image);
    }
    else{
        fprintf(stderr, "Undefined operation requested.");
        return 1;
    }

    if(SaveImg(destination, modified)){
        free(modified->data[0]);
        free(modified->data);
        free(modified);
        return 0;
    }
    else{
        free(modified->data[0]);
        free(modified->data);
        free(modified);
        return 1;
    }
}
