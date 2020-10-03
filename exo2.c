#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

int main(int argc, char** argv){
    FILE* ifp;

        /* Arguments */
    if ( argc != 2 ){
      printf("\nUsage: %s <file> \n\n", argv[0]);
      exit(0);
    }

    /* Opening */
    ifp = fopen(argv[1],"r");
    if (ifp == NULL) {
      printf("error in opening input file %s\n", argv[1]);
      exit(1);
    }

    

    /*  Magic number reading */
    int ich1 = pm_getc( ifp );
    if ( ich1 == EOF ) pm_erreur( "EOF / read error / magic number" );
    int ich2 = pm_getc( ifp );
    if ( ich2 == EOF ) pm_erreur( "EOF /read error / magic number" );

    if(ich2 != '6') pm_erreur("File format not correct\n");

    gray* red, *gre, *blu;
    
    int cols,rows,maxval;

    cols = pm_getint( ifp );
    rows = pm_getint( ifp );
    maxval = pm_getint( ifp );


    red = malloc(sizeof(gray)*cols*rows);
    gre = malloc(sizeof(gray)*cols*rows);
    blu = malloc(sizeof(gray)*cols*rows);

    for(int j=0; j<rows; j++){
        for(int i=0; i<cols;i++){
            red[cols*j+i] = pm_getrawbyte(ifp);
            gre[cols*j+i] = pm_getrawbyte(ifp);
            blu[cols*j+i] = pm_getrawbyte(ifp);
        }
    }

    FILE* fred = fopen("red.ppm","w");
    FILE* fgre = fopen("gre.ppm","w");
    FILE* fblu = fopen("blu.ppm","w");
    FILE* fgray = fopen("gray.pgm","w");

    fputc(ich1,fred);
    fputc(ich2,fred);
    fputc((int) '\n',fred);

    fputc(ich1,fgre);
    fputc(ich2,fgre);
    fputc((int) '\n',fgre);

    fputc(ich1,fblu);
    fputc(ich2,fblu);
    fputc((int) '\n',fblu);

    fprintf(fgray,"P5\n");

    fprintf(fred,"%d %d\n", cols, rows);
    fprintf(fred,"%d \n",maxval);

    fprintf(fgre,"%d %d\n", cols, rows);
    fprintf(fgre,"%d \n",maxval);

    fprintf(fblu,"%d %d\n", cols, rows);
    fprintf(fblu,"%d \n",maxval);

    fprintf(fgray,"%d %d\n", cols, rows);
    fprintf(fgray,"%d \n",maxval);

    
    int i,j;
    
    for(j=0; j < rows; j++){
      for(i=0; i < cols ; i++){
            fputc(red[cols*j+i],fred);
            fputc(0,fred);
            fputc(0,fred);
           
            fputc(0,fgre);
            fputc(gre[cols*j+i],fgre);
            fputc(0,fgre);

            fputc(0,fblu);
            fputc(0,fblu);
            fputc(blu[cols*j+i],fblu);
            
            fputc((gre[cols*j+i]+blu[cols*j+i]+red[cols*j+i])/3,fgray);

      }

    }

      /* Closing */
      fclose(ifp);
      fclose(fred);
      fclose(fgre);
      fclose(fblu);
      return 0;
}