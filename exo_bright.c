#include <stdio.h>
#include <stdlib.h>
#include "Util.h"

int main(int argc, char** argv){
    FILE* ifp;

        /* Arguments */
    if ( argc != 3 ){
      printf("\nUsage: %s <file> <brightness> \n\n", argv[0]);
      exit(0);
    }
    double bright = atof(argv[2]);

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
  
    /* We read those */

    int cols,rows,maxval;

    cols = pm_getint( ifp );
    rows = pm_getint( ifp );
    maxval = pm_getint( ifp );

    /* We going to start reading and then writing */

    FILE* fres = fopen("res.pgm","w");

    fprintf(fres,"P6");
    fputc((int) '\n',fres);

    fprintf(fres,"%d %d\n", cols, rows);
    fprintf(fres,"%d \n",maxval);

    gray buff;
    float buffbright;
    for(int j=0; j<rows; j++){
        for(int i=0; i<cols;i++){
            
            buff = pm_getrawbyte(ifp);
            buffbright = ((float) buff) * bright;
            if(buffbright > 255.) buffbright = 255.;
            fputc((int) buffbright,fres);
            buff = pm_getrawbyte(ifp);
            buffbright = ((float) buff) * bright;
            if(buffbright > 255.) buffbright = 255.;
            fputc((int) buffbright,fres);
            buff = pm_getrawbyte(ifp);
            buffbright = ((float) buff) * bright;
            if(buffbright > 255.) buffbright = 255.;
            fputc((int) buffbright,fres);

        }
    }


      /* Closing */
      fclose(ifp);
      fclose(fres);
      return 0;
}